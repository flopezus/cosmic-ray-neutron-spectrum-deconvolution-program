"""Interfaz Python para los lanzadores Bash y los archivos ROOT de salida.

Este módulo no implementa el unfolding. Las funciones :func:`run_em` y
:func:`run_em_mc` llaman a los lanzadores que, a su vez, ejecutan las funciones
C++ de ``macros/deconv_CRNS.C``.
"""

from __future__ import annotations

import os
import re
import subprocess
from pathlib import Path
from typing import Iterable

import numpy as np
import pandas as pd
import uproot

_repo_override = os.environ.get("REPO_DIR")
REPO_DIR = (
    Path(_repo_override).expanduser().resolve()
    if _repo_override
    else Path(__file__).resolve().parents[2]
)

CONFIG_KEYS = (
    "CAMPAIGN",
    "STEPS",
    "TIME_GRID",
    "NDET",
    "MAX_STEPS",
    "BIN_SEED",
    "CUT",
    "PHYLST",
    "SCF",
    "NEUFTY",
    "TOTAL_EVENTS",
    "MAX_PARALLEL",
    "EXCLUDED_EVENTS",
    "SELECTED_EVENTS",
)

SCALAR_BRANCHES = (
    "ndet",
    "seed_bin_edgeds",
    "Intg_total",
    "Intg_th",
    "Intg_ep",
    "Intg_fs",
    "Intg_he",
    "Chi2",
    "Chi2red",
    "diff_criteria",
    "diff",
    "xi2",
    "barDelta",
    "std_cr",
    "em_it",
)

ENERGY_BIN_COUNT = 129

CHANNEL_CONFIGURATIONS = {
    1: "12 cm HDPE",
    2: "10 cm HDPE",
    3: "4 cm HDPE",
    4: "Cilindro HDPE",
    5: "7 mm Al + núcleo BHDPE",
    6: "18 cm HDPE",
    7: "20 cm HDPE",
    8: "1″ BHDPE + 10 cm HDPE",
    9: "20 cm BHDPE + 1″",
    10: "Cilindro 4 cm",
    11: "Cilindro 3 cm",
    12: "Pb + núcleo BHDPE 10 cm",
    13: "1″ BHDPE + grafito 15 cm",
    14: "1″ BHDPE + HDPE 15 cm",
    15: "24 cm HDPE",
    16: "Detector desnudo 1″",
}

_LEGACY_CAMPAIGNS = {
    "PUC",
    "UTFSM",
    "LCO",
    "Maricunga",
    "RetenDesierto",
    "UDA",
    "ULS",
    "JuanSoldado",
}

_ACTIVE_CHANNELS = {
    "legacy": (1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 16),
    "south": (1, 2, 3, 5, 6, 9, 10, 11, 12, 13, 16),
    "AllActive": tuple(range(1, 17)),
}

_CAMPAIGN_DATES = {
    "LCO": (2023, 7, 10),
    "Maricunga": (2023, 7, 14),
    "SanPedrodeAtacama": (2024, 11, 10),
    "Chapiquilta": (2024, 11, 17),
}

_BEAM_FACTORS = np.array(
    [
        1.38,
        1.37,
        1.28,
        1.42,
        1.37,
        1.37,
        1.36,
        2.33,
        1.29,
        1.43,
        1.41,
        5.00,
        1.80,
        1.96,
        1.30,
        1.15,
    ],
    dtype=float,
)


def _resolve(path: str | Path) -> Path:
    candidate = Path(path).expanduser()
    if not candidate.is_absolute():
        candidate = REPO_DIR / candidate
    return candidate.resolve()


def _positive_event(event: int) -> int:
    event = int(event)
    if event < 1:
        raise ValueError("event debe ser un entero positivo")
    return event


def load_shell_config(path: str | Path) -> dict[str, str]:
    """Carga la configuración con Bash ``source`` y devuelve sus variables.

    Bash sigue siendo la única implementación de la sintaxis del archivo. El
    pequeño bucle solo serializa las variables que usa la interfaz docente.
    """

    config = _resolve(path)
    if not config.is_file():
        raise FileNotFoundError(config)

    script = r"""
set -euo pipefail
source "$1"
shift
for key in "$@"; do
    if [[ -v "$key" ]]; then
        printf '%s\0%s\0' "$key" "${!key}"
    fi
done
"""
    proc = subprocess.run(
        [
            "bash",
            "--noprofile",
            "--norc",
            "-c",
            script,
            "bash",
            str(config),
            *CONFIG_KEYS,
        ],
        check=True,
        capture_output=True,
    )

    fields = proc.stdout.split(b"\0")
    if fields and fields[-1] == b"":
        fields.pop()
    if len(fields) % 2:
        raise RuntimeError("salida incompleta al cargar la configuración Bash")

    values = {
        fields[index].decode(): fields[index + 1].decode(errors="replace")
        for index in range(0, len(fields), 2)
    }
    missing = [key for key in CONFIG_KEYS[:10] if not values.get(key)]
    if missing:
        raise ValueError(
            f"faltan variables requeridas en {config}: {', '.join(missing)}"
        )
    return values


def run_em(
    config: str | Path,
    event: int,
) -> subprocess.CompletedProcess[str]:
    """Ejecuta el EM nominal de un único evento y propaga cualquier error."""

    config = _resolve(config)
    event = _positive_event(event)
    return subprocess.run(
        [
            "bash",
            str(REPO_DIR / "local_scripts/run_event_em_local.sh"),
            str(config),
            str(event),
        ],
        cwd=REPO_DIR,
        text=True,
        check=True,
    )


def run_em_mc(
    config: str | Path,
    event: int,
    target_accepted: int = 100,
    max_mc_trials: int = 200_000,
    mc_max_steps: int = 20,
    diff_limit: float = 0.02,
) -> subprocess.CompletedProcess[str]:
    """Ejecuta el modo docente configurable del EM-MC para un evento."""

    config = _resolve(config)
    event = _positive_event(event)
    return subprocess.run(
        [
            "bash",
            str(REPO_DIR / "local_scripts/run_event_em_mc_local.sh"),
            str(config),
            str(event),
            str(target_accepted),
            str(max_mc_trials),
            str(mc_max_steps),
            str(diff_limit),
        ],
        cwd=REPO_DIR,
        text=True,
        check=True,
    )


def _campaign_tag(config: dict[str, str], *, monte_carlo: bool) -> str:
    campaign = config["CAMPAIGN"]
    field_type = config["NEUFTY"]
    physics_list = config["PHYLST"]

    if physics_list == "FTFP_BERT":
        return f"{campaign}_FTFP_BERT_{field_type}"
    if physics_list == "QGSP_BERT":
        if monte_carlo:
            return f"{campaign}_{field_type}"
        return f"{campaign}_QGSP_BERT_{field_type}"
    raise ValueError(f"PHYLST no soportada: {physics_list}")


def expected_em_output(config: str | Path, event: int) -> Path:
    """Ruta construida por ``em_loop_seed_update`` en deconv_CRNS.C."""

    values = load_shell_config(config)
    event = _positive_event(event)
    steps = int(values["STEPS"])
    output_kind = "EM_stop" if steps == 0 else "EM"
    filename = (
        f"EM_unfolding_loop_campaign_{values['CAMPAIGN']}"
        f"_event_{event}_steps_{steps}"
        f"_timegrid_{values['TIME_GRID']}_ndet_{values['NDET']}.root"
    )
    return (
        REPO_DIR
        / "outputs"
        / "root"
        / "deconv_data_rootfile"
        / output_kind
        / values["CAMPAIGN"]
        / _campaign_tag(values, monte_carlo=False)
        / filename
    )


def expected_mc_output(config: str | Path, event: int) -> Path:
    """Ruta construida por ``em_loop_MC_opt_new_update`` en deconv_CRNS.C."""

    values = load_shell_config(config)
    event = _positive_event(event)
    steps = int(values["STEPS"])
    if steps == 0:
        output_kind = "EM_MC_stop"
        suffix = "_MC_stop.root"
    else:
        output_kind = "EM_MC"
        suffix = "_MC.root"
    filename = (
        f"EM_unfolding_loop_campaign_{values['CAMPAIGN']}"
        f"_event_{event}_steps_{steps}"
        f"_timegrid_{values['TIME_GRID']}_ndet_{values['NDET']}{suffix}"
    )
    return (
        REPO_DIR
        / "outputs"
        / "root"
        / "deconv_data_rootfile"
        / output_kind
        / values["CAMPAIGN"]
        / _campaign_tag(values, monte_carlo=True)
        / filename
    )


def scientific_inputs(config: str | Path) -> dict[str, Path]:
    """Devuelve los inputs principales usados por la configuración."""

    values = load_shell_config(config)
    campaign = values["CAMPAIGN"]
    physics_list = values["PHYLST"]
    response_campaign = (
        "LIN_Spectrometer_2025_FTFP"
        if physics_list == "FTFP_BERT"
        else "LIN_Spectrometer_2024_active_vol_fix"
    )
    return {
        "conteos": (
            REPO_DIR
            / "data/external/CRNS_Data"
            / campaign
            / f"{campaign}_data_{values['TIME_GRID']}min_complete.root"
        ),
        "semillas": (
            REPO_DIR
            / "data/external/EXPACS_Data/parma_cpp_flopez"
            / f"{campaign}_parma_fluxes.root"
        ),
        "bineado": (
            REPO_DIR
            / "data/external/EXPACS_Data/parma_cpp_flopez"
            / "ICRP116_binning_resume.csv"
        ),
        "respuestas": (
            REPO_DIR
            / "data/external/Response_Functions_CEFNEN_Spectrometer"
            / response_campaign
            / f"{values['SCF']}_factor"
        ),
    }


def active_channels(campaign: str) -> tuple[int, ...]:
    """Canales activados por ``Detectors_Array`` en la macro C++."""

    if campaign in _LEGACY_CAMPAIGNS:
        return _ACTIVE_CHANNELS["legacy"]
    if campaign in {"Chapiquilta", "SanPedrodeAtacama"}:
        return _ACTIVE_CHANNELS["south"]
    if campaign == "AllActive":
        return _ACTIVE_CHANNELS["AllActive"]
    raise ValueError(f"campaña sin arreglo de detectores conocido: {campaign}")


def load_event_channels(config: str | Path, event: int) -> pd.DataFrame:
    """Conteos, tasas e incertidumbres estadísticas del evento seleccionado."""

    values = load_shell_config(config)
    event = _positive_event(event)
    channels = active_channels(values["CAMPAIGN"])
    configured_ndet = int(values["NDET"])
    if configured_ndet != len(channels):
        raise ValueError(
            f"NDET={configured_ndet}, pero la macro activa {len(channels)} "
            f"canales para {values['CAMPAIGN']}"
        )

    input_path = scientific_inputs(config)["conteos"]
    branch_prefix = "NEUrate" if values["CUT"] == "cut1" else "NEUrateT"
    live_time = int(values["TIME_GRID"]) * 60.0

    with uproot.open(input_path) as root:
        tree = root["CRNS_MSDATA"]
        if event > tree.num_entries:
            raise ValueError(
                f"EVENT_ID={event} supera las {tree.num_entries} entradas de {input_path}"
            )
        counts = np.array(
            [
                tree[f"{branch_prefix}_D{channel:02d}"].array(
                    entry_start=event - 1,
                    entry_stop=event,
                    library="np",
                )[0]
                for channel in channels
            ],
            dtype=float,
        )

    rate = counts / live_time
    rate_uncertainty = np.sqrt(counts) / live_time
    relative_uncertainty = np.divide(
        rate_uncertainty,
        rate,
        out=np.full_like(rate, np.nan),
        where=rate > 0,
    )
    return pd.DataFrame(
        {
            "Canal": [f"D{channel:02d}" for channel in channels],
            "Configuración": [CHANNEL_CONFIGURATIONS[channel] for channel in channels],
            "Conteos": counts.astype(int),
            "Tiempo vivo [s]": live_time,
            "Tasa [s⁻¹]": rate,
            "Incertidumbre [s⁻¹]": rate_uncertainty,
            "Incertidumbre relativa [%]": 100.0 * relative_uncertainty,
        }
    )


def load_energy_binning(config: str | Path) -> pd.DataFrame:
    """Bineado usado por el C++ para los 129 valores espectrales."""

    path = scientific_inputs(config)["bineado"]
    table = pd.read_csv(path).iloc[:ENERGY_BIN_COUNT].copy()
    required = {"Emid", "Ewid", "Elower", "Eupper"}
    missing = required.difference(table.columns)
    if missing:
        raise ValueError(f"faltan columnas en {path}: {', '.join(sorted(missing))}")
    return table.reset_index(drop=True)


def _response_file_map(directory: Path) -> dict[int, Path]:
    files: dict[int, Path] = {}
    for path in directory.glob("Efi_*.root"):
        match = re.match(r"Efi_(\d+)_", path.name)
        if match:
            files[int(match.group(1))] = path
    return files


def load_response_matrix(
    config: str | Path,
) -> tuple[np.ndarray, pd.DataFrame, pd.DataFrame]:
    """Matriz respuesta activa, bineado y metadatos en el orden de la macro."""

    values = load_shell_config(config)
    channels = active_channels(values["CAMPAIGN"])
    response_dir = scientific_inputs(config)["respuestas"]
    files = _response_file_map(response_dir)
    rows: list[np.ndarray] = []
    metadata: list[dict[str, object]] = []

    for channel in channels:
        response_number = channel
        if channel == 4 and values["CAMPAIGN"] not in _LEGACY_CAMPAIGNS:
            response_number = 17
        path = files.get(response_number)
        if path is None:
            raise FileNotFoundError(
                f"no se encontró la respuesta Efi_{response_number} en {response_dir}"
            )
        with uproot.open(path) as root:
            histogram_name = next(iter(root.keys(cycle=False)))
            response, _ = root[histogram_name].to_numpy(flow=False)
        if len(response) < ENERGY_BIN_COUNT:
            raise ValueError(
                f"{path} tiene {len(response)} bins; se requieren {ENERGY_BIN_COUNT}"
            )
        rows.append(np.asarray(response[:ENERGY_BIN_COUNT], dtype=float))
        metadata.append(
            {
                "Canal": f"D{channel:02d}",
                "Configuración": CHANNEL_CONFIGURATIONS[channel],
                "Archivo": path.name,
                "Histograma": histogram_name,
            }
        )

    matrix = np.stack(rows)
    if values["NEUFTY"] == "BEAM":
        matrix *= _BEAM_FACTORS[np.asarray(channels) - 1, None]
    elif values["NEUFTY"] == "MIX":
        mixed = {5, 6, 7, 8, 9, 12, 13, 14, 15}
        factors = np.array(
            [
                _BEAM_FACTORS[channel - 1] if channel in mixed else 1.0
                for channel in channels
            ]
        )
        matrix *= factors[:, None]
    elif values["NEUFTY"] != "ISO":
        raise ValueError(f"NEUFTY no soportado: {values['NEUFTY']}")

    # La macro usa el canal D01 para decidir si reemplaza un bin nulo en
    # todas las respuestas por un valor positivo despreciable.
    matrix[:, matrix[0] == 0.0] = 1.0e-23
    return matrix, load_energy_binning(config), pd.DataFrame(metadata)


def load_seed_spectrum(
    config: str | Path,
    seed_number: int = 1,
) -> tuple[pd.DataFrame, float]:
    """Semilla PARMA usada por C++ y su fracción volumétrica de agua."""

    values = load_shell_config(config)
    campaign = values["CAMPAIGN"]
    if campaign not in _CAMPAIGN_DATES:
        raise ValueError(f"fecha de semilla no definida para {campaign}")
    seed_number = int(seed_number)
    if seed_number < 1:
        raise ValueError("seed_number debe ser un entero desde 1")

    year, month, day = _CAMPAIGN_DATES[campaign]
    path = scientific_inputs(config)["semillas"]
    with uproot.open(path) as root:
        tree = root["BkgNeutronSpectra"]
        dates = tree.arrays(["Year", "Month", "Day", "WaterWF"], library="np")
        mask = (
            (dates["Year"] == year)
            & (dates["Month"] == month)
            & (dates["Day"] == day)
        )
        matching_entries = np.flatnonzero(mask)
        if seed_number > len(matching_entries):
            raise ValueError(
                f"seed_number={seed_number} supera las {len(matching_entries)} "
                f"semillas del {day:02d}-{month:02d}-{year}"
            )
        entry = int(matching_entries[seed_number - 1])
        differential = np.asarray(
            tree["NeutronFdiff"].array(
                entry_start=entry,
                entry_stop=entry + 1,
                library="np",
            )[0],
            dtype=float,
        )[:ENERGY_BIN_COUNT]
        water_fraction = float(dates["WaterWF"][entry])

    binning = load_energy_binning(config)
    spectrum = binning.copy()
    spectrum["Flujo diferencial"] = differential
    spectrum["Flujo por bin"] = differential * spectrum["Ewid"].to_numpy()
    return spectrum, water_fraction


def forward_fold(
    response_matrix: np.ndarray,
    differential_flux: np.ndarray,
    energy_width: np.ndarray,
) -> np.ndarray:
    """Aplica ``R @ (phi * dE)`` como ``Recalculate`` en la macro."""

    response = np.asarray(response_matrix, dtype=float)
    flux = np.asarray(differential_flux, dtype=float)
    widths = np.asarray(energy_width, dtype=float)
    if response.ndim != 2 or response.shape[1] != flux.size:
        raise ValueError("dimensiones incompatibles entre R y phi")
    if widths.shape != flux.shape:
        raise ValueError("dE debe tener la misma longitud que phi")
    return response @ (flux * widths)


def expected_em_log(config: str | Path, event: int) -> Path:
    """Log escrito por ``run_event_em_local.sh``."""

    values = load_shell_config(config)
    event = _positive_event(event)
    return (
        REPO_DIR
        / "outputs/log/local_em"
        / f"EM_{values['CAMPAIGN']}_event_{event}_{values['TIME_GRID']}min.log"
    )


def expected_mc_stats(config: str | Path, event: int) -> Path:
    """Resumen final de aceptadas/rechazadas escrito por el MC C++."""

    values = load_shell_config(config)
    event = _positive_event(event)
    return (
        expected_mc_output(config, event).parent
        / f"{values['CAMPAIGN']}_event_{event}_{values['TIME_GRID']}min_stat.txt"
    )


def em_iteration_history(
    log_file: str | Path,
    seed_number: int = 1,
) -> pd.DataFrame:
    """Extrae ``em_it``, ``chi2`` y ``diff`` del log para una semilla."""

    path = _resolve(log_file)
    if not path.is_file():
        raise FileNotFoundError(path)
    text = path.read_text(encoding="utf-8", errors="replace")
    seed_number = int(seed_number)
    start = re.search(
        rf"\bSeed:\s*{seed_number}\s+Starting\s+\.\.\.",
        text,
    )
    if start is None:
        raise ValueError(f"no se encontró la semilla {seed_number} en {path}")
    finish = re.search(
        rf"\bSeed:\s*{seed_number}\s+Finished\.",
        text[start.end() :],
    )
    stop = len(text) if finish is None else start.end() + finish.start()
    segment = text[start.end() : stop]
    number = r"[-+]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][-+]?\d+)?"
    matches = re.findall(
        rf"em_it\s+(\d+)\s+chi2\s+({number})\s+diff value\s+({number})",
        segment,
    )
    if not matches:
        raise ValueError(f"no hay diagnósticos de iteración para la semilla {seed_number}")
    return pd.DataFrame(matches, columns=["iteración", "Chi2", "diff"]).astype(
        {"iteración": int, "Chi2": float, "diff": float}
    )


def mc_run_summary(config: str | Path, event: int) -> dict[str, float | int]:
    """Intentos, aceptadas, rechazadas y fracción desde el resumen del MC."""

    path = expected_mc_stats(config, event)
    if not path.is_file():
        raise FileNotFoundError(path)
    text = path.read_text(encoding="utf-8", errors="replace")
    matches = re.findall(
        r"Accepted:\s*(\d+)/(\d+).*?Rejected:\s*(\d+)",
        text,
        flags=re.DOTALL,
    )
    if not matches:
        raise ValueError(f"no se pudo leer el resumen MC en {path}")
    accepted, target, rejected = map(int, matches[-1])
    attempts = accepted + rejected
    return {
        "intentos": attempts,
        "aceptadas": accepted,
        "rechazadas": rejected,
        "meta": target,
        "fracción": accepted / attempts if attempts else np.nan,
    }


def root_keys(root_file: str | Path) -> dict[str, str]:
    """Nombres y clases de los objetos de nivel superior de un ROOT."""

    path = _resolve(root_file)
    if not path.is_file():
        raise FileNotFoundError(path)
    with uproot.open(path) as root:
        return dict(root.classnames(cycle=False))


def tree_names(root_file: str | Path) -> list[str]:
    """Lista los TTrees/RNTuples de nivel superior."""

    return [
        name
        for name, classname in root_keys(root_file).items()
        if classname == "TTree" or "RNTuple" in classname
    ]


def tree_entry_count(
    root_file: str | Path,
    tree_name: str = "em_loop_tree",
) -> int:
    """Número de entradas del árbol indicado."""

    path = _resolve(root_file)
    with uproot.open(path) as root:
        if tree_name not in root:
            raise KeyError(f"{tree_name!r} no existe en {path}")
        return int(root[tree_name].num_entries)


def tree_branches(
    root_file: str | Path,
    tree_name: str = "em_loop_tree",
) -> list[str]:
    """Lista los branches del árbol indicado."""

    path = _resolve(root_file)
    if not path.is_file():
        raise FileNotFoundError(path)
    with uproot.open(path) as root:
        if tree_name not in root:
            raise KeyError(f"{tree_name!r} no existe en {path}")
        return list(root[tree_name].keys())


def scalar_tree_table(
    root_file: str | Path,
    tree_name: str = "em_loop_tree",
    max_rows: int | None = 10,
    columns: Iterable[str] | None = None,
) -> pd.DataFrame:
    """Carga branches escalares conocidos en una tabla pandas."""

    path = _resolve(root_file)
    if not path.is_file():
        raise FileNotFoundError(path)

    requested = tuple(columns) if columns is not None else SCALAR_BRANCHES
    with uproot.open(path) as root:
        if tree_name not in root:
            raise KeyError(f"{tree_name!r} no existe en {path}")
        tree = root[tree_name]
        selected = [name for name in requested if name in tree.keys()]
        if not selected:
            return pd.DataFrame()
        arrays = tree.arrays(selected, library="np", how=dict)

    scalar_arrays = {
        name: np.asarray(values)
        for name, values in arrays.items()
        if np.asarray(values).ndim == 1
    }
    table = pd.DataFrame(scalar_arrays)
    return table if max_rows is None else table.head(max_rows)


def vector_tree_array(
    root_file: str | Path,
    branch: str = "deconv_vec",
    tree_name: str = "em_loop_tree",
) -> np.ndarray:
    """Carga un branch vectorial de longitud fija como matriz NumPy."""

    path = _resolve(root_file)
    with uproot.open(path) as root:
        if tree_name not in root:
            raise KeyError(f"{tree_name!r} no existe en {path}")
        tree = root[tree_name]
        if branch not in tree:
            raise KeyError(f"{branch!r} no existe en {tree_name!r} de {path}")
        vectors = tree[branch].array(library="np")
    if len(vectors) == 0:
        return np.empty((0, 0), dtype=float)
    lengths = {len(vector) for vector in vectors}
    if len(lengths) != 1:
        raise ValueError(f"{branch} contiene vectores de longitudes distintas")
    return np.stack(vectors).astype(float, copy=False)


def quantile_summary(
    table: pd.DataFrame,
    columns: Iterable[str] | None = None,
) -> pd.DataFrame:
    """Mediana, cuantiles 16/84 %, media y dispersión de columnas numéricas."""

    if columns is not None:
        available = [column for column in columns if column in table]
        numeric = table[available].select_dtypes(include="number")
    else:
        numeric = table.select_dtypes(include="number")
    if numeric.empty:
        return pd.DataFrame()

    result = numeric.quantile([0.15865, 0.50, 0.84135]).transpose()
    result.columns = ["q15.865", "mediana", "q84.135"]
    result["incertidumbre_-"] = result["mediana"] - result["q15.865"]
    result["incertidumbre_+"] = result["q84.135"] - result["mediana"]
    result["media"] = numeric.mean()
    result["desv_std"] = numeric.std()
    result["n"] = numeric.count()
    return result
