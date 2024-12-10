Instrucciones para ejecutar el programa

Para compilar el programa:
g++ main.cpp -o main

Luego de que este compilado:
./main

Opciones del juego:
Escoge una opción en el menú:

1) Jugar entre 2 personas(JCJ)
2) Jugar contra la computadora (JCmaquina).
3) Salir del programa.

Sobre el algoritmo usado:
El programa usa el algoritmo Minimax optimizado con poda alfa-beta para que la computadora juegue lo mejor posible.

Como funciona:
Evaluación de estados:
+1 si la computadora gana.
-1 si gana el jugador.
0 si es un empate o el juego sigue.

Minimax:
La computadora intenta maximizar su puntaje y el jugador minimizarlo.
Explora posibles movimientos, decide cuál es el mejor, y hace la jugada.

Poda alfa-beta:
Es como un atajo para que el algoritmo no revise ramas innecesarias del árbol de decisiones.
Esto lo hace mucho más rápido sin afectar el resultado.

Explicación del algoritmo
Minimax
Es como un si hago esto, el oponente hará esto, y luego yo puedo hacer esto..., pero con el tablero completo. Va probando todas las posibilidades hasta encontrar la mejor jugada.

Poda alfa-beta
Básicamente, si ya sabe que una opción es peor que otra que ya analizó, la descarta sin perder tiempo revisándola.

Complejidad del algoritmo

Sin poda alfa-beta:
Tiempo que toma: donde  es, cuantas opciones hay por jugada y es la profundidad (o sea, cuantos turnos quedan).
En Tic-Tac-Toe,  es 9 y  también es 9 al principio, así que puede tardar un rato.

Con poda alfa-beta:
Tiempo que toma:  (en el mejor caso).
Mucho más rápido, sobre todo si el juego es más complicado.
