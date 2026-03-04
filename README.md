# 🚢 Rastreo de Embarcaciones Marítimas

**Trabajo Práctico Integrador — Tópicos de Programación (03635)**  
Universidad Nacional de La Matanza · Comisión 01-1949

---

## 📋 Descripción

Programa desarrollado en **ANSI C** para el rastreo y análisis de posiciones de embarcaciones marítimas. A partir de dos archivos CSV con registros ordenados por timestamp Unix, el sistema consolida la información, calcula distancias recorridas usando la **fórmula de Haversine** y determina las embarcaciones con mayor recorrido.

---

## ⚙️ Funcionalidades

- **Consolidación de archivos**: fusiona `posicionesA.csv` y `posicionesB.csv` en un único archivo ordenado cronológicamente (`posicionesFinal.csv`), eliminando registros duplicados.
- **Cálculo de distancia**: implementa la fórmula de Haversine para calcular la distancia aproximada entre dos coordenadas geográficas (latitud/longitud).
- **Distancia por embarcación**: procesa el archivo consolidado y muestra el total de kilómetros recorridos por cada embarcación.
- **Top 5**: muestra las 5 embarcaciones que más kilómetros recorrieron, utilizando un algoritmo de ordenamiento genérico por selección.

---

## 📁 Estructura del proyecto

```
Tp_Topicos_2024/
├── main.c              # Punto de entrada del programa
├── funciones.c         # Implementación de todas las funciones
├── header.h            # Definición de estructuras, constantes y prototipos
├── posicionesA.csv     # Archivo de posiciones (fuente A)
├── posicionesB.csv     # Archivo de posiciones (fuente B)
└── posicionesFinal.csv # Archivo consolidado (generado en ejecución)
```

---

## 🗂️ Formato de los archivos CSV

Cada línea tiene el siguiente formato:

```
fechaHora,matricula,latitud,longitud
```

| Campo      | Tipo     | Descripción                                      |
|------------|----------|--------------------------------------------------|
| fechaHora  | `long`   | Unix Timestamp (segundos desde 01/01/1970)       |
| matricula  | `string` | Identificador único de la embarcación (máx. 8 c) |
| latitud    | `double` | Coordenada de latitud en grados decimales        |
| longitud   | `double` | Coordenada de longitud en grados decimales       |

---

## 🚀 Compilación y ejecución

### Requisitos
- Compilador GCC (o cualquier compilador ANSI C compatible)
- Biblioteca matemática (`-lm`)

### Compilar
```bash
gcc main.c funciones.c -o rastreo -lm
```

### Ejecutar
```bash
./rastreo
```

> ⚠️ Los archivos `posicionesA.csv` y `posicionesB.csv` deben estar en el mismo directorio que el ejecutable.

---

## 🧠 Detalles técnicos

### Fórmula de Haversine
Para calcular la distancia entre dos puntos geográficos se utiliza:

```
a = sin²(Δlat/2) + cos(lat1) · cos(lat2) · sin²(Δlon/2)
c = 2 · atan2(√a, √(1−a))
d = R · c      (R = 6371 km)
```

### Ordenamiento genérico
Se implementó `OrdenSeleccion()` con punteros `void*` y función de comparación parametrizada (`Cmp`), permitiendo ordenar estructuras de cualquier tipo.

---

## 📌 Restricciones y criterios de diseño

- Desarrollado en **ANSI C** puro (compatibilidad multiplataforma)
- Uso de **aritmética de punteros** para manejo de vectores y cadenas
- **Sin VLA** (Variable Length Arrays)
- Variables declaradas al inicio del bloque
- Recorridos de archivos mínimos
- Sin acceso a memoria no asignada

---


## 📄 Licencia

Proyecto académico — UNLaM 2024
