Tic Tac Toe con Minimax y Poda Alfa-Beta

por -Cristobal Luna / 21.006.280-7
    -Juan Vargas / 20.428.612-4

--Instrucciones para ejecutar el programa--
compilador g++ (MinGW.org GCC-6.3.0-1) 6.3.0
Para ejecutar el programa:

g++ -o main main.cpp
./main

Explicaciones sobre el algoritmo utilizado
El Algoritmo Minimax es similar al algoritmo de backtracking, es usado para tomar decisiones respecto al mejor movimiento que se debe tomar en un juego. 
En el minimax los jugadores son llamados "maximizador" y "minimizador" el primeri intenta obtener el mejor puntaje mientas que el otro hace lo opuesto. 
Cada estado de el tablero tiene un valor asociado con el, por lo que en un inicio se empiezan con valores muy bajos para el maximizador que busca valores positivos y 
valores muy altos para el minimizador que busca valores negativos.

Explicación teórica del algoritmo Minimax y la poda alfa-beta
Minimax
El algoritmo Minimax es recursivo y se usa en juegos de suma cero como Tic Tac Toe. osea que que ambos jugadores juegan óptimamente:

Jugador Máximo: Busca maximizar la puntuación.
Jugador Mínimo: Busca minimizar la puntuación.
El algoritmo calcula la mejor puntuación posible para cada movimiento y selecciona el que optimice el resultado para el jugador actual.

Poda Alfa-Beta
La poda alfa-beta es una optimización del Minimax que reduce la cantidad de nodos evaluados. Utiliza dos parámetros:

Alfa: El valor mínimo garantizado para el jugador máximo.
Beta: El valor máximo garantizado para el jugador mínimo.
Si en cualquier rama el valor de alfa supera a beta, esa rama se descarta porque no afectará el resultado final.

Diagrama del árbol de juego
Caso: Primeros 3 movimientos

            (Raíz)
         /    |    \
      -1      0      1
     / \     / \    / \
    -1  0   0   1  -1  1


Cada nodo representa un estado del tablero.
Los números indican la evaluación del estado para el jugador actual (-1 = pierde, 0 = empate, 1 = gana).
Análisis de complejidad temporal
Sin poda alfa-beta
La complejidad de Minimax puro es 
O(N^M)

M: número promedio de movimientos posibles).
N: Profundidad del árbol.

Con poda alfa-beta
Con poda alfa-beta, el número de nodos evaluados se reduce significativamente. La complejidad promedio es 
O(N^(M/2))
por que descarta la mitad de las ramas en cada nivel.
