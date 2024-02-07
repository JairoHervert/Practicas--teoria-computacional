# Práctica 1. Alfabetos, lenguajes y expresiones regulares

## Objetivo
Hacer la implementación de alfabetos, lenguajes, y expresiones regulares mediante una aplicación en algún lenguaje de programación de alto nivel, en este caso python.

## Desarrollo
1. Leer el alfabeto ∑ que servirá como base para resolver esta práctica. El alfabeto debe tener al menos tres símbolos. Los símbolos deben poder ser ingresados de dos maneras posibles:
   • De forma individual (de uno en uno), por ejemplo: a, b, c, d, e, f; o bien: 0, 1, 2, 3, 4. 
   • Por rango, ingresando el primer símbolo del alfabeto a definir y a continuación el último (por ejemplo: a-z, m-x, F-Q, 0-9, 5-9, etc.).

2. Leer dos cadenas: w1 y w2 ambas elementos del alfabeto ∑. Las cadenas deben ser validadas por el programa: en caso de error en el ingreso de las cadenas, se debe hacer la indicación al usuario para que vuelva a ingresar la cadena de forma correcta. Una cadena es inválida si contiene algún símbolo que no pertenezca al alfabeto.

3. Indicar si w1 es un prefijo o sufijo (propio o no propio), o subcadena, o subsecuencia, o cualquier combinación anterior, de w2.

4. Con base en el alfabeto ∑ generar los lenguajes L1 y L2 de forma aleatoria. El número de elementos o palabras (np) a ser generados así como su longitud (l), serán valores de entrada que ingresará el usuario. Desplegar en pantalla los lenguajes generados L1 y L2.

5. Generar el lenguaje LD resultado de la diferencia de los lenguajes con la operación: L1 - L2. Desplegar en pantalla LD.

6. Obtener la potencia del alfabeto ∑. El valor de la potencia es un número entero (rango: -5 a 5) que debe ser leído desde el teclado. Desplegar el resultado de la potencia del alfabeto en pantalla.

7. Todas las cadenas de letras en minúsculas (a-z) que contengan las cinco vocales en orden. Las vocales pueden estar repetidas siempre que mantengan el orden. La secuencia completa de vocales también puede repetirse.- Ejemplos de palabras aceptadas: rtaeioujutf, arteheejyibgfohgfdujhfd, aaaejhjhihgghgough, hknalleioomuwraamqekiodsu, aheklinmounmajkertebhiohjju, etc.- Ejemplos de palabras no aceptadas: kayteemnoyug, ejuyaklengtivdfsojhgu, agheehklinmoythuvbazeyiawqeihjou.

Nota 1: En el inciso 7, el programa debe solicitar al usuario que ingrese la palabra a analizar. Como respuesta, el programa desplegará en pantalla la leyenda “palabra correcta” si la palabra ingresada cumple con la expresión regular; de otro modo, desplegará “palabra incorrecta” lo cual indica que  la palabra ingresada no cumple con la expresión regular. 

Nota 2: En el mismo inciso 7 se debe usar una expresión regular conforme a la sintaxis del lenguaje de programación usado, por ejemplo Java o Python. No se aceptará un programa que evite el uso de expresiones regulares mediante alguna implementación en el código.