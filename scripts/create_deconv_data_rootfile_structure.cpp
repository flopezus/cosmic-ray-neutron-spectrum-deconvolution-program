#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

bool ensure_directory(const fs::path& dir_path) {
    if (fs::exists(dir_path)) {
        if (fs::is_directory(dir_path)) {
            std::cout << "[OK] Ya existe: " << dir_path << '\n';
            return true;
        }
        std::cerr << "[ERROR] Existe pero no es directorio: " << dir_path << '\n';
        return false;
    }

    std::error_code ec;
    if (fs::create_directories(dir_path, ec)) {
        std::cout << "[CREADO] " << dir_path << '\n';
        return true;
    }

    std::cerr << "[ERROR] No se pudo crear: " << dir_path
              << " (" << ec.message() << ")\n";
    return false;
}

fs::path resolve_repo_root() {
    const fs::path current = fs::current_path();

    if (current.filename() == "scripts" && fs::exists(current.parent_path() / "outputs")) {
        return current.parent_path();
    }

    if (fs::exists(current / "outputs")) {
        return current;
    }

    return current.parent_path();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <campaign>\n";
        std::cerr << "Ejemplo: " << argv[0] << " LCO\n";
        return 1;
    }

    const std::string campaign = argv[1];
    const fs::path repo_root = resolve_repo_root();
    const fs::path base_root =
        repo_root / "outputs" / "root" / "deconv_data_rootfile";

    const std::vector<std::string> parent_dirs = {
        "EM_MC_stop",
        "EM_stop"
    };

    const std::vector<std::string> variants = {
        campaign + "_FTFP_BERT_BEAM",
        campaign + "_FTFP_BERT_MIX",
        campaign + "_FTFP_BERT_ISO"
    };

    bool all_ok = true;

    std::cout << "Directorio base del repositorio: " << repo_root << '\n';

    for (const auto& parent_dir : parent_dirs) {
        const fs::path campaign_root = base_root / parent_dir / campaign;
        all_ok = ensure_directory(campaign_root) && all_ok;

        for (const auto& variant : variants) {
            all_ok = ensure_directory(campaign_root / variant) && all_ok;
        }

        std::cout << "Ruta objetivo: " << campaign_root << '\n';
    }

    if (!all_ok) {
        std::cerr << "\nFinalizado con errores.\n";
        return 2;
    }

    std::cout << "\nEstructura verificada/creada correctamente para la campania: "
              << campaign << '\n';
    return 0;
}
