# Ejecutar la actividad con GitHub Codespaces

GitHub Codespaces construye el mismo `docker/Dockerfile` usado localmente y
arranca JupyterLab dentro del contenedor. El estudiante solo necesita una
cuenta de GitHub y un navegador.

## Publicar el repositorio

1. Crea un repositorio vacío en GitHub. Para una clase abierta puede ser
   público; también puedes marcarlo como **Template repository**.
2. Revisa y confirma los cambios locales:

   ```bash
   git status
   git add -A
   git status
   git commit -m "Add Docker classroom and GitHub Codespaces"
   ```

   Antes del `commit`, confirma en el segundo `git status` que solo estén
   incluidos los archivos que quieres distribuir.

3. Conserva GitLab como `origin` y agrega GitHub como segundo remoto:

   ```bash
   git remote add github https://github.com/USUARIO/REPOSITORIO.git
   git push -u github classroom-docker-jupyter:main
   ```

Sustituye `USUARIO/REPOSITORIO` por el nombre real del repositorio.

Una vez publicado, también puedes compartir un enlace directo:

```text
https://codespaces.new/USUARIO/REPOSITORIO?quickstart=1
```

## Instrucciones para el estudiante

1. Abre el repositorio en GitHub.
2. Selecciona **Code → Codespaces → Create codespace on main**.
3. Espera a que termine la construcción inicial.
4. Codespaces abrirá el puerto **8888** como `JupyterLab · CRNS`.
5. Si Jupyter solicita un token, escribe:

   ```text
   neutrons
   ```

6. Abre:

   ```text
   classroom/notebooks/unfolding_local.ipynb
   ```

Si el navegador no se abre automáticamente, entra en la pestaña **Ports** de
Codespaces y selecciona el enlace del puerto 8888.

## Diferencia respecto de la ejecución local

Dentro de Codespaces no se ejecutan:

```bash
./start_class.sh
./stop_class.sh
./test_class.sh
```

Estos scripts administran Docker en un computador local. En Codespaces, el
propio entorno ya es el contenedor y JupyterLab se inicia automáticamente.

## Tiempo de la primera construcción

La primera creación puede tardar varios minutos porque descarga Ubuntu,
ROOT 6.32.06 y las dependencias Python. Las siguientes construcciones
aprovechan caché. Para una clase con muchas personas, el administrador del
repositorio puede configurar un **Codespaces prebuild** para la rama `main`.

## Datos y resultados

Los inputs necesarios para la actividad deben estar versionados en GitHub.
Los resultados bajo `outputs/` son locales a cada Codespace y no se guardan
en GitHub a menos que el estudiante los descargue o los confirme
explícitamente con Git.

El puerto 8888 queda configurado como privado. No se recomienda cambiarlo a
público, porque Jupyter permite ejecutar código dentro del Codespace.
