# Actividad local: Docker, JupyterLab, ROOT y PyROOT

Este entorno permite ejecutar un evento con las mismas funciones C++/ROOT que
usa producción:

- EM nominal: `em_loop_steps_update(...)`;
- EM Monte Carlo: `em_loop_MC_opt_new_update(...)`.

Python se usa como interfaz para elegir el evento, lanzar ROOT y leer los
resultados. El algoritmo de unfolding permanece en
`macros/deconv_CRNS.C`. Los scripts SLURM no se modifican.

## 1. Requisitos

El computador anfitrión necesita:

- Linux x86_64;
- Docker Engine;
- Docker Compose v2 (`docker compose`).

No necesita instalar ROOT, Python ni JupyterLab. La imagen usa Ubuntu 22.04 y la
distribución binaria oficial
`root_v6.32.06.Linux-ubuntu22.04-x86_64-gcc11.4.tar.gz`, sin etiquetas
flotantes.

Comprueba los requisitos:

```bash
docker --version
docker compose version
```

## 2. Construir y probar

Desde la raíz del repositorio:

```bash
./test_class.sh
```

La primera ejecución descarga e instala la imagen. El test comprueba:

- sintaxis Bash y configuración Compose;
- ROOT 6.32.06 y PyROOT;
- NumPy, pandas, Matplotlib, uproot, awkward e ipywidgets;
- macro, configuraciones e inputs LCO;
- carga de `deconv_CRNS.C` desde `local_scripts/`;
- presencia de las dos funciones usadas por los lanzadores.

El test no ejecuta el unfolding nominal ni un Monte Carlo completo.

Para construir solamente:

```bash
export LOCAL_UID="$(id -u)"
export LOCAL_GID="$(id -g)"
docker compose build jupyter
```

## 3. Iniciar JupyterLab

```bash
./start_class.sh
```

La URL predeterminada es:

```text
http://localhost:8888/lab?token=neutrons
```

El puerto se publica solo en `127.0.0.1`. Se puede cambiar el token o el puerto:

```bash
JUPYTER_TOKEN="mi-token-docente" JUPYTER_PORT=8890 ./start_class.sh
```

En ese caso la URL usa el nuevo puerto y token. Para ver los logs:

```bash
docker compose logs -f jupyter
```

El notebook de la actividad está en:

```text
classroom/notebooks/unfolding_local.ipynb
```

Las celdas del MC están protegidas por `RUN_REDUCED_MC = False`; hay que
cambiarlo explícitamente para iniciarlas.

## 4. EM nominal desde terminal

Con el contenedor iniciado:

```bash
docker compose exec jupyter bash \
  local_scripts/run_event_em_local.sh \
  configs/unfolding_configs/config_EM_MC_stop_LCO_60min_ISO.sh \
  1
```

El segundo argumento es un único `EVENT_ID`, no un arreglo. El lanzador valida
el rango `TOTAL_EVENTS` y rechaza los valores de `EXCLUDED_EVENTS`.

La llamada C++ es:

```cpp
em_loop_steps_update(
    CAMPAIGN,
    EVENT_ID,
    STEPS,
    TIME_GRID,
    NDET,
    MAX_STEPS,
    CUT,
    PHYLST,
    SCF,
    NEUFTY
);
```

## 5. EM Monte Carlo desde terminal

### Valores de producción

La interfaz de dos argumentos omite los nuevos parámetros C++ y usa sus
defaults:

```bash
docker compose exec jupyter bash \
  local_scripts/run_event_em_mc_local.sh \
  configs/unfolding_configs/config_EM_MC_stop_LCO_60min_ISO.sh \
  1
```

Los defaults conservados son:

```text
TARGET_ACCEPTED=10000
MAX_MC_TRIALS=20000000
MC_MAX_STEPS=20
DIFF_LIMIT=0.02
```

Esta ejecución puede tardar muchas horas o días y no es adecuada para una
clase.

### Valores docentes

```bash
docker compose exec jupyter bash \
  local_scripts/run_event_em_mc_local.sh \
  configs/unfolding_configs/config_EM_MC_stop_LCO_60min_ISO.sh \
  1 \
  100 \
  200000 \
  20 \
  0.02
```

Los cuatro argumentos opcionales deben entregarse juntos:

```text
TARGET_ACCEPTED MAX_MC_TRIALS MC_MAX_STEPS DIFF_LIMIT
```

- `TARGET_ACCEPTED`: número deseado de espectros guardados;
- `MAX_MC_TRIALS`: máximo de semillas/realizaciones intentadas, aceptadas o no;
- `MC_MAX_STEPS`: límite usado por el EM de cada intento y por el filtro;
- `DIFF_LIMIT`: umbral externo para aceptar una realización.

El ROOT reducido usa el mismo nombre que una ejecución de producción del mismo
evento. Por ello, volver a ejecutar ese evento sustituye el resultado anterior.
Guarda una copia si necesitas comparar dos conjuntos de parámetros.

## 6. Criterios de parada y aceptación

Para `STEPS=0`, el EM interno itera mientras:

```cpp
diff > 0.02 || chi_square > ndet
```

La convergencia requiere simultáneamente `diff < 0.02` y
`chi_square < ndet`; `MAX_STEPS` evita un loop sin fin. La implementación
científica existente comprueba internamente `em_it > max_steps`, y se conserva
sin cambios.

El MC aplica después un filtro distinto para decidir si guarda el espectro:

```cpp
em_it < MC_MAX_STEPS &&
chi_square < ndet &&
diff < DIFF_LIMIT
```

Por tanto, detener el EM de un intento no equivale a aceptar ese intento. El
umbral interno histórico sigue siendo `0.02`; `DIFF_LIMIT` permite estudiar el
filtro externo sin reescribir el algoritmo.

## 7. Resultados persistentes

Todo el repositorio se monta en `/workspace`, por lo que los resultados quedan
en el host después de detener el contenedor:

```text
outputs/root/deconv_data_rootfile/EM_stop/...
outputs/root/deconv_data_rootfile/EM_MC_stop/...
outputs/log/local_em/...
outputs/log/local_em_mc/...
```

Los lanzadores imprimen una línea final `OUTPUT_ROOT=...` con el archivo
creado. El notebook usa las mismas rutas verificadas en la macro.

## 8. Por qué ROOT se ejecuta desde `local_scripts/`

`deconv_CRNS.C` abre entradas y salidas con rutas relativas:

```text
../data/external/...
../outputs/...
```

Los lanzadores cambian a `/workspace/local_scripts` antes de abrir ROOT. Así:

```text
local_scripts/../data
local_scripts/../outputs
local_scripts/../macros
```

apuntan a los directorios correctos y no es necesario modificar cientos de
rutas de la macro.

## 9. Discrepancia histórica de argumentos MC

La firma real anterior a los parámetros docentes termina así:

```cpp
int ndet,
int bin_seed,
int random_seed,
string cut,
string physic_list,
string scale_factor,
string neufield_type
```

Sin embargo, `scripts/run_events_em_mc_stop_jobs.sh` llama:

```text
NDET, MAX_STEPS, BIN_SEED, CUT, PHYLST, SCF, NEUFTY
```

En consecuencia, `MAX_STEPS` llega al parámetro llamado `bin_seed` y
`BIN_SEED` llega a `random_seed`. Los lanzadores locales conservan exactamente
ese orden. Con las configuraciones actuales, `BIN_SEED=1` selecciona la rama de
semillas aleatorias y el valor recibido en `bin_seed` no se usa en esa rama.

Además, el argumento `ndet` de `em_loop_steps_update` no se reenvía a
`em_loop_seed_update`; el número de detectores se deriva del conjunto activo.
Las configuraciones versionadas usan el valor consistente `NDET=11`, por lo que
los nombres de salida coinciden.

## 10. Verificar ROOT y PyROOT manualmente

```bash
docker compose exec jupyter root-config --version
```

Debe imprimir:

```text
6.32.06
```

Para PyROOT:

```bash
docker compose exec jupyter python3 -c \
  'import ROOT; print(ROOT.gROOT.GetVersion())'
```

Para comprobar que la macro carga desde el directorio correcto:

```bash
docker compose exec --workdir /workspace/local_scripts jupyter \
  root -l -b -q -e 'gROOT->ProcessLine(".L ../macros/deconv_CRNS.C"); gSystem->Exit(0);'
```

## 11. Detener

```bash
./stop_class.sh
```

Esto ejecuta `docker compose down`. Los resultados bajo `outputs/` no se
eliminan.

## 12. Limpiar

Detener y eliminar también la imagen construida:

```bash
docker compose down --rmi local
```

Eliminar resultados es una operación separada. Revísalos antes y borra solo
las subcarpetas generadas que realmente quieras descartar; los `.keep_dir`
versionados permiten conservar la estructura.

## 13. Permisos

`start_class.sh` exporta:

```bash
LOCAL_UID="$(id -u)"
LOCAL_GID="$(id -g)"
```

Compose ejecuta el contenedor con esos identificadores, evitando archivos
propiedad de `root`. Si quedaron archivos antiguos con otro propietario,
detén el contenedor y corrige únicamente esos resultados, por ejemplo:

```bash
sudo chown -R "$(id -u):$(id -g)" outputs
```

No ejecutes `sudo ./start_class.sh`, porque entonces se exportarán los
identificadores de `root`.

## 14. Problemas frecuentes

### El puerto 8888 está ocupado

```bash
JUPYTER_PORT=8890 ./start_class.sh
```

### Docker responde “permission denied”

Comprueba que el servicio esté activo y que tu usuario tenga permiso para usar
el socket de Docker. Cierra y abre la sesión después de añadir el usuario al
grupo configurado por tu distribución.

### ROOT no encuentra un archivo

Ejecuta el lanzador desde la raíz exactamente como en los ejemplos. El script
se encarga de cambiar a `local_scripts/`. Comprueba también:

```bash
./test_class.sh
```

### El MC termina con menos aceptados que la meta

Se alcanzó `MAX_MC_TRIALS` antes de `TARGET_ACCEPTED`. Aumenta los intentos o
discute qué criterio (`Chi2`, `diff`, `em_it`) está rechazando realizaciones.

## 15. Diferencias entre local y SLURM

| Producción SLURM | Actividad local |
|---|---|
| `#SBATCH`, `sbatch`, arrays | un `EVENT_ID` explícito |
| `SLURM_ARRAY_TASK_ID` | segundo argumento del script |
| `srun root` | `root -l -b` |
| módulos `ml root/6.32.06...` | ROOT 6.32.06 dentro de Docker |
| logs por job/array | `tee` en `outputs/log/local_*` |
| miles de eventos/10 000 aceptados | un evento/MC reducido |

No se eliminó ni sustituyó ningún script `.slurm` o job de producción.

## 16. Tamaño MC recomendado para una clase

Benchmark local de referencia, medido con ROOT 6.32.06, un núcleo y la
configuración LCO 60 min ISO para el evento 1:

| Ejecución | Resultado | Tiempo de pared |
|---|---:|---:|
| EM nominal | 501 semillas | 63,68 s |
| MC reducido | 10 aceptados / 2 773 rechazados | 52,48 s |
| MC docente | 100 aceptados / 21 130 rechazados | 159,83 s |

La ejecución de 100 aceptados hizo 21 230 intentos (aceptación aproximada de
0,47 %) y terminó al 10,62 % del tope de 200 000. La carga inicial de la macro
está incluida en los tiempos.

Para una actividad de una hora se recomiendan **100 espectros aceptados por
estudiante**, `MC_MAX_STEPS=20`, `DIFF_LIMIT=0.02` y un tope entre 50 000 y
200 000 intentos. Cien muestras bastan para visualizar distribuciones,
medianas y cuantiles, y en el equipo de referencia dejaron más de 55 minutos
para explicación y análisis. Mantener 200 000 como tope da margen ante una
tasa de aceptación menor y no aumenta el tiempo cuando se alcanza antes la
meta.

El hardware de los estudiantes puede ser más lento. El instructor puede
repetir un ensayo de 10–20 aceptados:

```bash
time docker compose exec jupyter bash \
  local_scripts/run_event_em_mc_local.sh \
  configs/unfolding_configs/config_EM_MC_stop_LCO_60min_ISO.sh \
  1 20 50000 20 0.02
```

Si ese ensayo supera dos minutos, usa 50 aceptados o prepara previamente un
ROOT de ejemplo para la parte de visualización.
