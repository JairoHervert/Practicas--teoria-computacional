# Práctica 2. Analizador léxico. 

## Objetivo
Realizar la implementación de AFD´s que aceptan expresiones regulares, y aplicarlos para el diseño e implementación de un analizador léxico.

## Desarrollo

Parte I. Diseñar e implementar un Analizador léxico que, dado un programa fuente escrito en lenguaje Java, iden fique los valores numéricos (constantes) en sus diferentes pos (int, float, double) y notaciones.
   - Enteros (decimal, ocatal(0nnnn..), hexadecimal(0[x, X]nnnn...));
   - Reales (decimales con o sin exponente (n.nn[e, E][+,-]))

Para resolver el problema se construyó un AFD que opera los símbolos 
especiales definidos para cada una de las notaciones numericas definidas anteriormente y con tantos estados de aceptación como las diferentes formas numéricas que deben ser reconocidas (aceptadas), que en este caso son cinco: tres formas enteras y dos reales.

Par endo de nuestra definición formal de AFD:  
AFD = ( Σ, Q, q0, δ ,F)  
Tenemos que:  
Σ = { 0, … , F, +, - , b , ; , . , E, x }  
F = { C0, C1, C2, C3, C4, C5 }  
Encontrar: Q, q0, δ (o el diagrama de transición).

Entrada al Analizador léxico: La entrada al programa será un archivo de texto con la extensión .java el cual con ene un programa fuente en Java en donde tenemos constantes numéricas.

Salida del analizador léxico: La salida del programa serán mensajes de texto que indiquen si hay algún error en el uso de una constante numérica desde el punto de vista léxico.  

La salida del programa, teniendo como entrada el archivo fuente anterior, es 
la siguiente: 
   Error en línea 10.  
   Error en línea 11.  
   Error en línea 19. 
   Error en línea 21.  

Si el archivo EjemploPrac caAnalizador.java no tuviera ningún error la salida 
del Analizador sería:  
No hay errores de análisis léxico en las constantes numéricas del archivo 
programa.java.


Parte 2. Agregar los siguientes estados de aceptación al AFD del analizador léxico:
- Simbolos especiales I (Operadores de comparación (<,>,=, >=, <=, ==, !=) y operador de asignación (=))
- Simbolos especiales II ( Operadores aritmé cos (+, -, *, /. %)f)
-  Palabras reservadas de Java ( class, main, public, private, void, int,  etc.)
- Iden ficador válido en Java (var1, dato, prom_final, info, etc. )
-  Comentarios (Para una sola línea: // y Para más de una línea: /* … */)

## Entrada
- Debe existir un archivo de extencion .java en la misma ubicacion que el analizador lexico.
- Dentro de la función principal main, en las primeras lineas se ingresa el nombre del programa, modificar el nombre de la variable "nombre_archivo" segun el archivo .java que hayamos creado.
