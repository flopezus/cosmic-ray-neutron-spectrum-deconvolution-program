# Instalación rápida con Docker

Esta guía permite descargar el repositorio y abrir la actividad en JupyterLab.
ROOT, PyROOT y las bibliotecas Python se instalan dentro de la imagen; no hay
que instalarlos manualmente en el computador.

## 1. Requisitos

La ejecución local está preparada y validada para **Linux x86_64**. Se necesita:

- Git;
- Docker Engine;
- Docker Compose v2, incluido actualmente como `docker compose`;
- conexión a internet y aproximadamente 5 GB libres durante la construcción.

Instala Docker siguiendo la
[guía oficial de Docker Engine](https://docs.docker.com/engine/install/) para
tu distribución. Después comprueba:

```bash
docker --version
docker compose version
```

Si no usas Linux x86_64, la alternativa recomendada es
[GitHub Codespaces](#alternativa-sin-instalar-docker-github-codespaces).

## 2. Descargar el repositorio

Abre una terminal en la carpeta donde quieras guardar la actividad y ejecuta:

```bash
git clone https://github.com/flopezus/cosmic-ray-neutron-spectrum-deconvolution-program.git
cd cosmic-ray-neutron-spectrum-deconvolution-program
```

También puedes usar **Code → Download ZIP** en GitHub, descomprimir el archivo
y abrir una terminal dentro de la carpeta extraída.

## 3. Construir y comprobar el entorno

Da permiso de ejecución a los scripts, por si descargaste un ZIP:

```bash
chmod +x start_class.sh stop_class.sh test_class.sh
```

Construye la imagen y ejecuta las comprobaciones:

```bash
./test_class.sh
```

La primera ejecución descarga Ubuntu, ROOT 6.32.06 y las dependencias, por lo
que puede tardar varios minutos. La imagen final ocupa aproximadamente 2 GB.
Al terminar debe aparecer:

```text
[OK] Entorno docente verificado. No se ejecutó un Monte Carlo completo.
```

## 4. Iniciar la actividad

```bash
./start_class.sh
```

Abre en el navegador:

```text
http://localhost:8888/lab?token=neutrons
```

Después abre el notebook:

```text
classroom/notebooks/unfolding_local.ipynb
```

Los resultados generados se guardan dentro de `outputs/` en el computador.

## 5. Detener Docker

Cuando termines:

```bash
./stop_class.sh
```

Esto detiene el contenedor, pero conserva la imagen y los resultados.

## Error de permisos de Docker

Si aparece `permission denied` al acceder a `/var/run/docker.sock`, agrega tu
usuario al grupo `docker`:

```bash
sudo usermod -aG docker "$USER"
newgrp docker
docker run --rm hello-world
```

El grupo `docker` concede privilegios equivalentes a `root`. Consulta los
[pasos posteriores oficiales de Docker](https://docs.docker.com/engine/install/linux-postinstall/)
antes de aplicarlo en un equipo compartido.

## Alternativa sin instalar Docker: GitHub Codespaces

Abre:

<https://codespaces.new/flopezus/cosmic-ray-neutron-spectrum-deconvolution-program?quickstart=1>

Inicia sesión en GitHub, crea el Codespace y espera a que abra JupyterLab. Si
solicita un token, escribe `neutrons`. Dentro de Codespaces no ejecutes
`start_class.sh`, `stop_class.sh` ni `test_class.sh`, porque el entorno ya está
ejecutándose dentro del contenedor.

