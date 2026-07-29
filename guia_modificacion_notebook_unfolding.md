# Guía para modificar un notebook Jupyter: unfolding de espectros de neutrones

## Contexto de la actividad

Se dispone de una hora cronológica para realizar una clase principalmente práctica y computacional sobre espectroscopía de neutrones.

En los días previos, los estudiantes habrán participado en un laboratorio presencial de aproximadamente tres horas utilizando un detector de neutrones similar al empleado en el espectrómetro. Por lo tanto, el notebook no debe volver a desarrollar en detalle la física básica del detector, sino conectar la medición experimental con la reconstrucción del espectro.

El objetivo central de la clase es mostrar que, a partir de:

- los conteos o tasas de conteo medidos por canal;
- las funciones respuesta simuladas del espectrómetro;
- uno o más espectros semilla;

se puede obtener:

- un espectro de neutrones deconvolucionado;
- un diagnóstico de convergencia;
- una estimación de su incertidumbre mediante Monte Carlo.

El notebook se ejecutará dentro de un entorno Docker con JupyterLab ya implementado.

El cálculo científico debe seguir utilizando el código original en C++/ROOT. Python debe utilizarse principalmente como interfaz para:

- seleccionar el evento;
- cargar y mostrar datos;
- ejecutar el código C++/ROOT;
- presentar tablas y gráficos;
- analizar los criterios de parada;
- visualizar la incertidumbre.

---

# Idea central de la clase

La sesión debe mostrar una única cadena completa y fácil de seguir:

\[
\text{conteos por canal}
\rightarrow
\text{tasas de conteo}
\rightarrow
\text{funciones respuesta}
\rightarrow
\text{espectro semilla}
\rightarrow
\text{unfolding iterativo}
\rightarrow
\text{criterio de parada}
\rightarrow
\text{refolding}
\rightarrow
\text{Monte Carlo}
\rightarrow
\text{incertidumbre}
\]

Se recomienda que cada estudiante:

1. analice un solo evento real;
2. inspeccione los conteos y tasas por canal;
3. visualice las funciones respuesta;
4. calcule o interprete al menos una iteración del unfolding;
5. ejecute el unfolding completo del evento;
6. examine por qué el algoritmo se detuvo;
7. compare las tasas medidas con las tasas reconstruidas;
8. ejecute un Monte Carlo reducido;
9. compare el resultado docente con un resultado de alta estadística previamente calculado.

No se recomienda intentar generar 10 000 realizaciones aceptadas durante la clase. El objetivo es comprender el procedimiento y no reproducir toda la producción científica.

---

# Distribución recomendada de los 60 minutos

| Tiempo | Actividad | Resultado esperado |
|---:|---|---|
| 0–5 min | Conexión con el laboratorio | Entender qué representa cada canal |
| 5–12 min | Modelo directo o forward folding | Comprender cómo un espectro genera tasas por canal |
| 12–20 min | Inspección del evento | Identificar conteos, tasas, errores y respuestas |
| 20–30 min | Una iteración explícita de EM | Observar cómo cambia el espectro |
| 30–38 min | Ejecución completa del evento | Obtener espectro y diagnósticos |
| 38–48 min | Criterios de parada y refolding | Decidir si la solución es aceptable |
| 48–55 min | Monte Carlo e incertidumbre | Interpretar mediana y cuantiles |
| 55–60 min | Flujos integrales y cierre | Relacionar el unfolding con una magnitud física |

---

# Estructura recomendada del notebook

## 1. Introducción y conexión con el laboratorio

Incluir una breve explicación:

- cada configuración moderadora tiene una sensibilidad energética diferente;
- todos los canales observan combinaciones amplias de energías;
- ningún canal mide directamente un intervalo energético estrecho;
- el espectro se infiere usando simultáneamente todas las tasas medidas.

Pregunta inicial sugerida:

> Si todos los canales utilizan el mismo tipo de detector central, ¿por qué entregan tasas de conteo diferentes?

Respuesta esperada:

> Porque cada moderador modifica de manera diferente la energía de los neutrones antes de que lleguen al detector, produciendo una función respuesta distinta.

---

## 2. Selección del evento

Incluir una celda de configuración visible y simple:

```python
CONFIG_FILE = "ruta/a/configuracion.sh"
EVENT_ID = 1
```

Mostrar las variables principales:

```text
CAMPAIGN
EVENT_ID
TIME_GRID
NDET
STEPS
MAX_STEPS
BIN_SEED
CUT
PHYLST
SCF
NEUFTY
```

Evitar que los estudiantes tengan que editar rutas internas o argumentos complejos.

---

## 3. Conteos y tasas por canal

Mostrar una tabla con:

| Canal | Configuración | Conteos | Tiempo vivo | Tasa | Incertidumbre |
|---|---|---:|---:|---:|---:|

Usar:

\[
r_i=\frac{N_i}{T_i}
\]

y, para estadística de conteo:

\[
\sigma_{N_i}\approx\sqrt{N_i}
\]

\[
\sigma_{r_i}\approx\frac{\sqrt{N_i}}{T_i}
\]

Gráfico recomendado:

- eje horizontal: canal o configuración;
- eje vertical: tasa medida;
- barras de error estadísticas.

Preguntas sugeridas:

- ¿Qué canal presenta la mayor tasa?
- ¿Todos los canales tienen incertidumbre relativa similar?
- ¿Qué canal aporta menos información estadística?

---

## 4. Funciones respuesta

Presentar primero tres funciones respuesta representativas:

1. detector desnudo;
2. configuración moderadora intermedia;
3. configuración de respuesta extendida o con material de alto número atómico.

Después mostrar todas las funciones respuesta mediante un mapa de calor:

\[
R_{ij}
\]

donde:

- \(i\) representa el canal;
- \(j\) representa el bin de energía.

Usar energía en escala logarítmica.

Preguntas sugeridas:

- ¿Qué canales son más sensibles a bajas energías?
- ¿Qué canales extienden la respuesta hacia altas energías?
- ¿En qué regiones las respuestas se parecen demasiado entre sí?
- ¿En qué regiones el problema puede estar menos restringido?

---

# El modelo directo: forward folding

Antes de explicar el problema inverso, mostrar el modelo directo:

\[
\widehat n_i =
\sum_j R_{ij}\,\phi_j\,\Delta E_j
\]

donde:

- \(n_i\): tasa medida en el canal \(i\);
- \(R_{ij}\): función respuesta del canal \(i\) en el bin \(j\);
- \(\phi_j\): flujo diferencial en el bin \(j\);
- \(\Delta E_j\): ancho del bin de energía;
- \(\widehat n_i\): tasa predicha por el espectro candidato.

El notebook debe mostrar:

1. un espectro semilla;
2. las tasas medidas;
3. las tasas obtenidas al plegar la semilla;
4. la razón entre tasas predichas y medidas.

Por ejemplo:

\[
q_i =
\frac{\widehat n_i}{n_i}
\]

Interpretación:

- \(q_i>1\): la semilla sobreestima el canal;
- \(q_i<1\): la semilla subestima el canal;
- \(q_i\approx1\): la predicción reproduce razonablemente el canal.

Pregunta sugerida:

> ¿Qué canales indican que la semilla debe aumentar o disminuir en determinadas regiones de energía?

---

# El problema inverso

Explicar que se conocen:

\[
\mathbf n
\quad\text{y}\quad
\mathbf R
\]

y se desea estimar:

\[
\boldsymbol{\phi}
\]

a partir de:

\[
\mathbf n \approx \mathbf R\boldsymbol{\phi}
\]

El problema es difícil porque:

- existen menos canales que bins de energía;
- las funciones respuesta son amplias;
- diferentes espectros pueden producir tasas similares;
- las fluctuaciones estadísticas pueden amplificarse;
- la solución depende del criterio de parada y, en cierta medida, de la semilla.

---

# Una iteración explícita del algoritmo EM

La actualización utilizada puede mostrarse como:

\[
\phi_j^{(s+1)}
=
\frac{1}{\sum_i R_{ij}}
\sum_i
\left[
R_{ij}\phi_j^{(s)}
\frac{n_i}{
\sum_k R_{ik}\phi_k^{(s)}\Delta E_k
}
\right]
\]

No se recomienda pedir a los estudiantes que programen el algoritmo completo desde cero.

En cambio, el notebook debe separar visualmente una iteración en los siguientes pasos:

## Paso 1: espectro actual

\[
\phi_j^{(s)}
\]

## Paso 2: plegamiento

\[
\widehat n_i^{(s)}
=
\sum_kR_{ik}\phi_k^{(s)}\Delta E_k
\]

## Paso 3: factores de corrección por canal

\[
c_i^{(s)}
=
\frac{n_i}{\widehat n_i^{(s)}}
\]

## Paso 4: retroproyección de las correcciones

Cada canal contribuye a corregir los bins energéticos de acuerdo con su función respuesta.

## Paso 5: nuevo espectro

\[
\phi_j^{(s+1)}
\]

## Paso 6: nuevo plegamiento

\[
\widehat n_i^{(s+1)}
\]

Mostrar en una misma sección:

- espectro antes de la iteración;
- espectro después de la iteración;
- tasas medidas;
- tasas predichas antes;
- tasas predichas después;
- valor de \(\chi^2\);
- valor de `diff`.

---

# Criterios de parada

Esta debe ser una de las secciones centrales del notebook.

La clase debe destacar que:

> Más iteraciones no significan necesariamente una mejor solución física.

Deben presentarse dos preguntas distintas.

## 1. ¿La solución reproduce los datos?

Usar un estadístico como:

\[
\chi^2 =
\sum_i
\frac{
\left(
n_i-\widehat n_i
\right)^2
}{
\sigma_i^2
}
\]

El criterio usado puede presentarse como:

\[
\chi^2 \leq N_{\mathrm{det}}
\]

o con la desigualdad exacta implementada en el código.

Interpretación:

- un valor alto indica que el espectro no reproduce adecuadamente las tasas;
- un valor suficientemente bajo indica compatibilidad entre las tasas medidas y reconstruidas.

Mostrar un gráfico:

\[
\chi^2
\quad \text{vs.} \quad
\text{iteración}
\]

con una línea horizontal en:

\[
\chi^2=N_{\mathrm{det}}
\]

## 2. ¿El espectro dejó de cambiar?

Mostrar la definición exacta de `diff` utilizada por el código.

El criterio adoptado es:

\[
\mathrm{diff}\leq0.02
\]

Mostrar:

\[
\mathrm{diff}
\quad \text{vs.} \quad
\text{iteración}
\]

con una línea horizontal en:

\[
\mathrm{diff}=0.02
\]

## Condición combinada

Explicar que el algoritmo se detiene cuando se cumplen simultáneamente:

\[
\boxed{
\chi^2\leq N_{\mathrm{det}}
\quad\text{y}\quad
\mathrm{diff}\leq0.02
}
\]

salvo que se alcance antes el máximo de iteraciones.

La idea que deben recordar es:

\[
\boxed{
\text{reproducción de los datos}
+
\text{estabilidad de la solución}
}
\]

No basta con cumplir una sola condición.

---

# Comparación de paradas

Preparar tres resultados del mismo evento:

1. parada temprana;
2. parada adoptada;
3. parada tardía.

| Caso | Refolding | Forma del espectro | Interpretación |
|---|---|---|---|
| Parada temprana | Deficiente | Muy parecida a la semilla | Subajuste |
| Parada adoptada | Adecuado | Estable y razonable | Compromiso seleccionado |
| Parada tardía | Puede mejorar levemente | Más irregular | Riesgo de ajustar fluctuaciones |

Explicar que el criterio de parada funciona como una forma de regularización.

---

# Ejecución del unfolding nominal

El notebook debe incluir una celda que llame al código C++/ROOT mediante un helper Python o un script Bash local.

Ejemplo conceptual:

```python
run_em(
    config=CONFIG_FILE,
    event=EVENT_ID,
)
```

La celda debe mostrar:

- comando ejecutado;
- archivo de configuración;
- evento;
- directorio de salida;
- archivo ROOT generado;
- mensajes de error claros.

Después debe abrir el archivo ROOT y mostrar:

- nombre de los árboles;
- número de entradas;
- nombres de branches;
- resultados escalares;
- espectro deconvolucionado;
- tasas reconstruidas, si están disponibles.

---

# Refolding y validación de la solución

La validación principal debe ser comparar:

\[
n_i
\]

con:

\[
\widehat n_i =
\sum_jR_{ij}\phi_j\Delta E_j
\]

Mostrar un gráfico con:

- tasas medidas con barras de error;
- tasas reconstruidas;
- residuos o cocientes.

Opciones de diagnóstico:

\[
\text{residuo}_i =
n_i-\widehat n_i
\]

\[
\text{residuo normalizado}_i =
\frac{n_i-\widehat n_i}{\sigma_i}
\]

\[
\text{razón}_i =
\frac{\widehat n_i}{n_i}
\]

Pregunta central:

> ¿El espectro reconstruido reproduce todos los canales dentro de sus incertidumbres?

---

# Incertidumbre mediante Monte Carlo

La incertidumbre debe explicarse como propagación de las fluctuaciones de los conteos.

Para cada réplica \(m\), generar un nuevo conjunto de datos:

\[
N_i^{*(m)}
\sim
\mathcal{N}
\left(
N_i,\sqrt{N_i}
\right)
\]

o usar el modelo exacto implementado en el código.

Luego:

1. se genera una realización de los conteos;
2. se ejecuta el unfolding;
3. se evalúan los criterios;
4. la realización se acepta o rechaza;
5. se guarda el espectro aceptado.

Cada realización aceptada produce:

\[
\boldsymbol{\phi}^{*(m)}
\]

El notebook debe mostrar visualmente:

```text
conteos originales
       ↓
fluctuación estadística
       ↓
nuevo conjunto de conteos
       ↓
unfolding
       ↓
criterios de aceptación
       ↓
espectro aceptado o rechazado
```

---

# Diferencia entre parada EM y aceptación Monte Carlo

Esta distinción debe aparecer explícitamente.

| Nivel | Pregunta |
|---|---|
| Parada del EM | ¿Cuándo dejamos de iterar para una realización? |
| Aceptación Monte Carlo | ¿La realización convergió de forma aceptable para incluirla en la incertidumbre? |

La aceptación puede incluir condiciones como:

\[
N_{\mathrm{iter}} < N_{\mathrm{iter,max}}
\]

\[
\chi^2 < N_{\mathrm{det}}
\]

\[
\mathrm{diff}<0.02
\]

Una realización que no cumple las condiciones debe considerarse rechazada.

Mostrar:

- número de intentos;
- número de aceptadas;
- número de rechazadas;
- fracción de aceptación.

\[
f_{\mathrm{aceptación}}
=
\frac{
N_{\mathrm{aceptadas}}
}{
N_{\mathrm{intentos}}
}
\]

---

# Monte Carlo reducido para la clase

No ejecutar la producción completa durante la hora.

Configuración docente sugerida:

```python
TARGET_ACCEPTED = 50  # o 100
MAX_MC_TRIALS = 200_000
MC_MAX_STEPS = 20
DIFF_LIMIT = 0.02
```

La cantidad final debe elegirse después de un benchmark.

La celda Monte Carlo debe estar comentada o requerir ejecución explícita.

Ejemplo conceptual:

```python
run_em_mc(
    config=CONFIG_FILE,
    event=EVENT_ID,
    target_accepted=100,
    max_mc_trials=200_000,
    mc_max_steps=20,
    diff_limit=0.02,
)
```

---

# Visualización de las realizaciones Monte Carlo

Mostrar inicialmente una muestra pequeña de espectros:

- 10 a 30 realizaciones aceptadas;
- trazos semitransparentes;
- espectro mediano destacado.

No mostrar miles de curvas al mismo tiempo.

Después representar distribuciones de:

- `Chi2`;
- `diff`;
- `em_it`;
- flujo total;
- flujo térmico;
- flujo epitérmico;
- flujo rápido;
- flujo de alta energía.

---

# Mediana e intervalo de incertidumbre

Para cada bin energético \(j\), calcular:

\[
q_{50,j}
\]

\[
q_{15.865,j}
\]

\[
q_{84.135,j}
\]

donde:

- \(q_{50,j}\): mediana;
- \(q_{15.865,j}\): cuantíl inferior;
- \(q_{84.135,j}\): cuantíl superior.

Los errores asimétricos son:

\[
\sigma_j^- =
q_{50,j}-q_{15.865,j}
\]

\[
\sigma_j^+ =
q_{84.135,j}-q_{50,j}
\]

El resultado debe representarse como:

- línea central: mediana;
- banda inferior: \(q_{15.865}\);
- banda superior: \(q_{84.135}\).

No usar únicamente la desviación estándar si las distribuciones son asimétricas.

---

# Interpretación de la banda de incertidumbre

Explicar claramente que la banda obtenida representa principalmente la incertidumbre propagada desde las fluctuaciones incluidas en el Monte Carlo.

No debe interpretarse automáticamente como incertidumbre total si no se han variado también:

- funciones respuesta;
- calibraciones;
- hipótesis angular;
- espectros semilla;
- tiempos vivos;
- selección de canales;
- eficiencia;
- parámetros sistemáticos.

Incluir un recuadro Markdown:

> La banda Monte Carlo describe la incertidumbre asociada al modelo de fluctuaciones utilizado. No incluye automáticamente todas las incertidumbres sistemáticas del experimento.

---

# Comparación con una referencia de alta estadística

Después del Monte Carlo docente reducido, cargar un archivo ya calculado con alta estadística, por ejemplo 10 000 realizaciones aceptadas.

Comparar:

- mediana docente;
- banda docente;
- mediana de referencia;
- banda de referencia.

Preguntas sugeridas:

- ¿La mediana cambia significativamente?
- ¿La banda docente es más irregular?
- ¿En qué regiones energéticas se necesita mayor estadística?
- ¿Cuántas realizaciones parecen suficientes para una demostración?

---

# Flujos integrales

El notebook debe calcular o mostrar:

\[
\Phi_{\mathrm{th}}
\]

\[
\Phi_{\mathrm{ep}}
\]

\[
\Phi_{\mathrm{fast}}
\]

\[
\Phi_{\mathrm{he}}
\]

\[
\Phi_{\mathrm{total}}
\]

Presentar una tabla:

| Región | Bins o intervalo energético | Flujo mediano | Incertidumbre inferior | Incertidumbre superior |
|---|---|---:|---:|---:|
| Térmica | Según configuración | — | — | — |
| Epitérmica | Según configuración | — | — | — |
| Rápida | Según configuración | — | — | — |
| Alta energía | Según configuración | — | — | — |
| Total | Todo el espectro | — | — | — |

Para la incertidumbre de una región, integrar cada réplica primero y obtener después los cuantiles de la distribución integral.

No integrar únicamente los errores bin a bin como si fueran independientes.

---

# Razón térmica

Calcular:

\[
\mathcal R =
\frac{
\Phi_{\mathrm{th}}
}{
\Phi_{\mathrm{ep}}+\Phi_{\mathrm{fast}}
}
\]

La distribución de \(\mathcal R\) debe calcularse réplica a réplica:

\[
\mathcal R^{*(m)}
=
\frac{
\Phi_{\mathrm{th}}^{*(m)}
}{
\Phi_{\mathrm{ep}}^{*(m)}
+
\Phi_{\mathrm{fast}}^{*(m)}
}
\]

Después obtener:

- mediana;
- cuantíl inferior;
- cuantíl superior.

No calcular la incertidumbre de la razón usando solamente cocientes de medianas.

---

# Figuras mínimas del notebook

El notebook debería producir, en este orden:

1. tasas medidas por canal;
2. funciones respuesta representativas;
3. mapa de calor de la matriz respuesta;
4. espectro semilla;
5. tasas medidas y tasas predichas por la semilla;
6. espectro antes y después de una iteración;
7. \(\chi^2\) frente a iteración;
8. `diff` frente a iteración;
9. tasas medidas frente a tasas refoldeadas;
10. espectro final nominal;
11. distribuciones Monte Carlo de diagnósticos;
12. muestra de espectros aceptados;
13. mediana con banda de incertidumbre;
14. flujos integrales;
15. distribución de la razón térmica;
16. comparación con alta estadística.

---

# Resultado final que debe obtener cada estudiante

Al final del notebook, generar un resumen automático:

```text
Campaña:
Evento:
Número de detectores:
Tiempo de integración:
Semilla:
Iteración de parada:
Chi2 final:
diff final:
Número de intentos Monte Carlo:
Número de realizaciones aceptadas:
Fracción de aceptación:
Flujo térmico:
Flujo epitérmico:
Flujo rápido:
Flujo de alta energía:
Flujo total:
Razón térmica:
```

Incluir además una pregunta final:

> ¿La solución reproduce adecuadamente las tasas medidas y qué región del espectro presenta mayor incertidumbre?

---

# Segundo evento

Si se desea comparar dos condiciones físicas:

- ejecutar solamente un evento durante la clase;
- cargar el segundo evento como resultado precalculado.

Comparar:

\[
\Delta\Phi_{\mathrm{th}}
\]

\[
\Delta\Phi_{\mathrm{ep}}
\]

\[
\Delta\Phi_{\mathrm{fast}}
\]

\[
\Delta\mathcal R
\]

El segundo evento no debe agregar una segunda ejecución extensa.

---

# Qué dejar fuera de la clase

No desarrollar en esta sesión:

- generación Geant4 de las funciones respuesta;
- detalles completos del detector proporcional;
- derivación formal completa de EM;
- procesamiento de cientos de eventos;
- uso de SLURM;
- producción completa de 10 000 realizaciones;
- todas las semillas disponibles;
- todas las hipótesis angulares;
- incertidumbres sistemáticas completas;
- comparación exhaustiva de algoritmos de unfolding.

La clase debe responder cuatro preguntas:

1. ¿Qué información entra al unfolding?
2. ¿Cómo se actualiza el espectro?
3. ¿Cómo sabemos cuándo detenernos?
4. ¿Cómo propagamos la incertidumbre de los conteos?

---

# Recomendaciones de implementación

## Mantener C++/ROOT como motor

El notebook no debe contener una segunda implementación científica completa.

Flujo recomendado:

```text
Notebook Python
    ↓
helper Python
    ↓
script local Bash
    ↓
macro C++/ROOT original
    ↓
archivo ROOT
    ↓
tablas y gráficos en Python
```

## Mostrar una iteración didáctica

Puede implementarse en Python una única iteración simplificada del algoritmo para mostrar:

- plegamiento;
- cocientes medido/predicho;
- retroproyección;
- actualización.

Esta celda es didáctica y no reemplaza el cálculo oficial.

## Evitar rutas editables por estudiantes

La configuración principal debe quedar en una celda simple.

No exigir que los estudiantes modifiquen:

- rutas del repositorio;
- rutas de outputs;
- nombres internos de archivos ROOT;
- comandos ROOT;
- argumentos de compilación.

## Mensajes de error

Si falla una ejecución, mostrar:

- comando;
- código de retorno;
- salida estándar;
- error estándar;
- archivo de log;
- posibles causas.

## Protección frente al Monte Carlo largo

Antes de ejecutar MC, mostrar una advertencia:

```text
Esta celda realizará un Monte Carlo reducido.
No utiliza los valores completos de producción.
```

Comprobar que:

```python
TARGET_ACCEPTED <= 500
```

o pedir confirmación si se supera un límite docente.

---

# Criterios de aceptación del notebook modificado

El notebook estará listo cuando:

1. abra sin errores dentro del Docker existente;
2. cargue la configuración del repositorio;
3. ejecute un único evento EM sin SLURM;
4. localice el archivo ROOT generado;
5. muestre ramas y resultados;
6. presente el forward folding;
7. muestre \(\chi^2\) y `diff`;
8. ejecute opcionalmente un MC reducido;
9. muestre realizaciones aceptadas y rechazadas;
10. calcule mediana y cuantiles;
11. presente el espectro con banda;
12. calcule flujos integrales réplica a réplica;
13. calcule la razón térmica réplica a réplica;
14. produzca un resumen final;
15. mantenga el código C++/ROOT original como motor científico.

---

# Filosofía de la actividad

La actividad no debe sentirse como una demostración pasiva ni como una sesión de instalación de software.

Debe ser una secuencia de preguntas:

1. ¿Qué midió cada canal?
2. ¿Qué predice la semilla?
3. ¿Cómo corrige EM esa predicción?
4. ¿Por qué el algoritmo se detiene?
5. ¿El espectro reproduce las mediciones?
6. ¿Cómo cambian los resultados cuando fluctúan los conteos?
7. ¿Qué significa la banda de incertidumbre?
8. ¿Qué magnitudes físicas se obtienen al integrar el espectro?

El objetivo final es que el estudiante comprenda que el espectro no es una curva medida directamente, sino una solución inferida y validada mediante:

\[
\boxed{
\text{datos}
+
\text{funciones respuesta}
+
\text{algoritmo}
+
\text{criterios de parada}
+
\text{propagación de incertidumbre}
}
\]
