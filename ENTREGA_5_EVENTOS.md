# Entrega de cinco eventos

Cada estudiante repite el notebook para los cinco eventos indicados por el
docente. En la celda de selección se cambia `EVENT_ID` y después se ejecutan el
EM nominal y el Monte Carlo reducido. El ROOT se crea cuando termina el Monte
Carlo.

## Dónde se escriben los resultados

Codespaces monta el repositorio con escritura en `/workspace`. El lanzador crea
la carpeta necesaria y guarda cada ROOT Monte Carlo en:

```text
/workspace/outputs/root/deconv_data_rootfile/EM_MC_stop/<campaña>/<etiqueta>/
```

La ruta correcta usa `deconv_data_rootfile` en singular y `EM_MC_stop` sin `_`
inicial. En el explorador de Jupyter o de VS Code se abre:

```text
outputs/root/deconv_data_rootfile/EM_MC_stop/
```

Con Docker local, `/workspace` está enlazado con el repositorio y la misma
carpeta se ve como:

```text
./outputs/root/deconv_data_rootfile/EM_MC_stop/
```

## Descargar uno por uno

Después de ejecutar el Monte Carlo, su celda muestra un enlace al ROOT del
evento y otro al resumen de ejecución. Al final del notebook, la sección
**Descargar los cinco eventos, uno por uno** permite copiar los cinco números
en `ASSIGNED_EVENT_IDS` y muestra cinco enlaces separados.

Esa sección no vuelve a ejecutar el cálculo, no mueve los ROOT y no crea un
ZIP. Si un enlace falta, se debe volver al `EVENT_ID` indicado y terminar su
Monte Carlo.

También se puede descargar directamente desde el explorador de archivos:

1. Abrir `outputs/root/deconv_data_rootfile/EM_MC_stop/`.
2. Entrar en la campaña y su etiqueta.
3. Hacer clic derecho sobre cada archivo `.root`.
4. Seleccionar **Download**.

## Subir al repositorio de entrega

En el repositorio indicado por el docente, usar **Add file → Upload files**,
seleccionar los cinco `.root` descargados y confirmar el commit. Los resultados
de `outputs/` permanecen ignorados por el `.gitignore` de este proyecto para
evitar subirlos accidentalmente al repositorio del programa.
