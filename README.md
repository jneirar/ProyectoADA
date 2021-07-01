# Proyecto de Análisis y Diseño de Algoritmos
### Integrantes
- Loja Zumaeta, Alex Jose
- Neira Riveros, Jorge Luis

## Problema del Min-Trie

Dada una secuencia de cadenas *S*, encontrar un *S*-ptrie con el menor número de aristas, además devolver este número.

### Pregunta 1 (Heurística Voraz):
Analize, diseñe e implemente una heurística voraz para el problema **Min-Trie**. Su algoritmo no deberá encontrar necesariamente la respuesta óptima.

* **Entrada del algoritmo:** Una secuencia *S* de *n* cadenas de longitud *m* sobre el alfabeto *Σ*.
* **Salida del algoritmo:** Un *S*-ptrie y su número de aristas.
* **Tiempo de ejecución del algoritmo**: *O(nm + mlgm)*.
* **Tiempo de ejecución del algoritmo**: *O(nm|Σ|)*.

Su algoritmo anterior, aunque es rápido, no resuelve el problema de manera exacta. El siguiente paso es diseñar un algoritmo recursivo, para ello encontraremos un subproblema al problema original. Sea *S = (s<sub>1</sub>, s<sub>2</sub>, ... , s<sub>n</sub>)*. Sea *OPT(i, j)* el número de aristas de una solución óptima para el subproblema que considera a las cadenas *s<sub>i</sub>, ... , s<sub>j</sub>*.

### Pregunta 2 (Recurrencia):
Plantee una recurrencia para *OPT(i, j)*.