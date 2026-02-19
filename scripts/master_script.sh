#!/bin/bash

#nohup ./master_script.sh  > output_master.log 2>&1 &

# Número total de núcleos disponibles
TOTAL_CORES=$(nproc)

# Define el rango de eventos para cada script
#~ declare -a event_ranges=("1,5" "6,10" "11,25" "26,30" "31,35") # Ajusta los rangos según sea necesario
declare -a event_ranges=("26,30") # Ajusta los rangos según sea necesario

# Nombre base del archivo que ejecuta el código ROOT
script_base="run_chapiquilta_em_mc_stop_"

# Ruta al directorio donde están tus scripts
script_dir="./scripts" # Cambia esta ruta si tus scripts están en otro lugar

# Asegúrate de que el directorio de scripts exista
mkdir -p "$script_dir"

# Crear los scripts con los diferentes rangos de eventos
for i in "${!event_ranges[@]}"; do
  range=${event_ranges[$i]}
  script_name="${script_base}${i}.C"
  function_name="${script_base}${i}" # La función principal debe coincidir con el nombre del archivo base

  # Generar el script con el rango de eventos adecuado
  cat > "${script_dir}/${script_name}" <<EOF
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

void ${function_name}() { // La función principal tiene el mismo nombre que el archivo
    gROOT->ProcessLine(".L /home/flopez/LIN/TESIS_DOC/Analysis/deconv/deconv_CRNS.C");
    gROOT->ProcessLine("em_loop_events_MC_opt_new(\"Chapiquilta\",${range},0,15,11,42,1,\"cut1\")");
}

#if !defined(__CINT__) && !defined(__ACLIC__)
int main(int /*argc*/, char ** /*argv*/) {
    ${function_name}(); // Llama a la función principal
    return 0;
}
#endif /* !defined(__CINT__) && !defined(__ACLIC__) */
EOF
done

# Lanza los scripts en diferentes núcleos
for i in "${!event_ranges[@]}"; do
  range=${event_ranges[$i]}
  script_name="${script_dir}/${script_base}${i}.C"
  log_file="${script_dir}/output_${i}.log"

  # Asignar cada script a un núcleo específico usando taskset
  #~ core_id=$((i % TOTAL_CORES))
  core_id=$((i % 6))
  echo "Lanzando ${script_name} en el núcleo ${core_id}"
  taskset -c ${core_id} root -l -b -q "${script_name}" > "${log_file}" 2>&1 &
done

# Esperar a que todos los procesos terminen
wait

echo "Todos los scripts han terminado."
