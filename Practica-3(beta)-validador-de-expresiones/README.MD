# Práctica 3: Gramáticas independientes del contexto (GIC).

## Objetivo.
Realizar la implementación de una GIC utilizando un Autómata de Pila. Se puede emplear cualquier lenguaje de programación para la realización de esta práctica.

## Desarrollo.
El programa que implementa la GIC, definida anteriormente, debe realizar las 
siguientes funcionalidades: 

1. Validar expresiones de lenguaje C. El programa lee como entrada una línea que representa una expresión en lenguaje C; el programa da como salida “Aceptado” si la línea leída está en el lenguaje de la GIC, o “No aceptado” en caso contrario.

2. Dibujar el árbol de derivación. El programa deberá generar el árbol de derivación de alguna expresión que sea válida. El árbol resultante puede ser desplegado en modo gráfico o en modo texto (caracteres ASCII).

Notas: 
El nodo raíz debe ser el axioma. 
Los nodos internos deben corresponder con elementos del alfabeto de símbolos no terminales. 
Las hojas deben corresponder con elementos del alfabeto de símbolos terminales.