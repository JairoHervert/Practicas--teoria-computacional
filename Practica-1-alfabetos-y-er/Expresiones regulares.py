import os   # Permite usar comandos/funciones del so donde se ejecute el programa
import platform   # Proporciona informacion del so
import re
import random
import itertools

def clearScreen():
   if (platform.system() == "Windows"):
      os.system("cls")
   else:
      os.system("clear")

def ingresarAlfabeto():
   while True:
      print("INGRESE LOS SÍMBOLOS (LETRAS) PARA FORMAR EL ALFABETO ∑")
      print("Puede separar los elementos con comas ej: a, b, c")
      print("o pueden ingresarse por rango ej: a-z\n")
      
      entrada = input("Ingrese: ") # Registra como cadena
      simbolos = entrada.split(',')   # Lista de subcadenas con limitador ','
      alfabetoParcial = set()

      for simbolo in simbolos:
         simbolo = simbolo.strip()  # Eliminamos espacios al incio y final de cada simbolo
         if '-' in simbolo:
            rango = simbolo.split('-') #Separamos el rango en una lista de elementos delimitados por '-'
            if len(rango) == 2:  # El rango solo deberia tener dos elementos, incio y fin
               inicio, fin = rango
               if (len(inicio) == 1 and len(fin) == 1):
                  alfabetoParcial.update(set(chr(i) for i in range(ord(inicio), ord(fin) + 1))) # Actualiza el conjunto principal agregando el conjunto "set" creado a partir de castear chars a partir del rango del unicode de incio y fin
            else:
               print("El rango debe tener dos elemento: inicio y fin")
         else:
            if len(simbolo) >= 1:   # Que no llegue a ingresar ' ', espacios
               alfabetoParcial.add(simbolo)

      if (len(alfabetoParcial) >= 3):  # Una vez creado el alfabeto "parcial" evaluar que contenga al menos 3 elementos
         return alfabetoParcial
      else:
         print("Debe ingresar al menos tres elementos válidos para crear el alfabeto")
         input("Presione Enter para continuar...")
         clearScreen()

# Recorre el i caracter de w1 con los de w2 de manera consecutiva
def SubsecuenciaDe(w1, w2):
   i, j = 0, 0
   while i < len(w1) and j < len(w2):
      if w1[i] == w2[j]:
         i += 1
      j += 1
   return i == len(w1)


def ingresarCadenas(alfabeto):
   if not alfabeto:
      clearScreen()
      print("No se pueden ingresar cadenas porque el alfabeto no tiene ningún símbolo")
      input("Presione enter...")
      clearScreen()
      return
   
   while True:
      print("INGRESAR CADENAS w1 y w2\n")
      string1 = input("Ingrese la cadena w1: ")
      # Se evalua que toda la sucesion de las evaluaciones de los caracteres en la cadena sean true, es decir que perteenzcan al alfabeto
      if all(simbolo in alfabeto for simbolo in string1):
         print("Cadena w1 valida: ", string1)
         clearScreen()
         break
      else:
         print("\nCadena w1 no valida, contiene simbolos que no estan el en alfabeto ∑")
         print("Vuelva a ingresar la cadena 1")
         input("Presione enter...")
         clearScreen()

   while True:
      print("INGRESAR CADENAS w1 y w2\n")
      print("Cadena w1 valida: ", string1)
      string2 = input("Ingrese la cadena w2: ")
      
      if all(simbolo in alfabeto for simbolo in string2):
         break
      else:
         print("\nCadena w2 no valida, contiene simbolos que no estan el en alfabeto ∑")
         print("Vuelva a ingresar la cadena 2")
         input("Presione enter...")
         clearScreen()
   # Terminamos de ingresar

   prefijosNoPropiosDeW2 = {string2[:i] for i in range(len(string2) + 1)}  # Conjunto de prefijos NO PROPIOS de w2, utilizamos "slicing" para los i elementos iniciales
   prefijosPropiosDeW2 = {prefijo for prefijo in prefijosNoPropiosDeW2 if prefijo != "" and prefijo != string2}  # Conjunto de prefijos PROPIOS de w2

   subFijosNoPropiosW2 = {string2[i:] for i in range(len(string2) + 1)}  # Conjunto de subfijos NO PROPIOS de w2, slicing desde i hasta el final de la cadena
   subFijosPropiosW2 = {subfijo for subfijo in subFijosNoPropiosW2 if subfijo != "" and subfijo != string2}  # Conjunto de subfijos PROPIOS de w2

   subcadenasNoPropiasW2 = {""} | {string2[i:j] for i in range(len(string2) + 1) for j in range(i + 1, len(string2) + 1)}  # Agrega "", ademas itera sobre todas las subcadenas posibles de string2 con al menos 1 caracter
   subcadenasPropiasW2 = {subcadena for subcadena in subcadenasNoPropiasW2 if subcadena != "" and subcadena != string2}  # Conjunto de subcadenas PROPIAS de la cadena

   clearScreen()
   print("Cadena w1 valida: ", string1)
   print("Cadena w2 valida: ", string2)
   print("\n")

   foundRelationship = False  # Variable de bandera para rastrear si se encuentra una relación
   if (string1 == string2):
      print("w1 y w2 son iguales")
      foundRelationship = True

   if (string1 in prefijosPropiosDeW2):
      print("- w1 es un prefijo propio de w2")
      foundRelationship = True
   elif (string1 in prefijosNoPropiosDeW2):
      print("- w1 es un prefijo NO propio de w2")
      foundRelationship = True

   if (string1 in subFijosPropiosW2):
      print("- w1 es un subfijo propio de w2")
      foundRelationship = True
   elif (string1 in subFijosNoPropiosW2):
      print("- w1 es un subfijo NO propio de w2")
      foundRelationship = True

   if (string1 in subcadenasPropiasW2):
      print("- w1 es una subcadena propia de w2")
      foundRelationship = True
   elif (string1 in subcadenasNoPropiasW2):
      print("- w1 es una subcadena NO propia de w2")
      foundRelationship = True
   
   if SubsecuenciaDe(string1, string2):
      print("- W1 es subsecuencia de W2")
      foundRelationship = True

   if not foundRelationship:
      print("w1 NO TIENE relacion con w2")
   
   input("Presione enter...")
   clearScreen()


def lenguajesAleatorios(alfabeto):
   lenguajeGenerado = False  # Variable para rastrear si se ha generado el lenguaje

   while True:
      try:
         np = int(input("Numero de palabras a generar: "))
         l = int(input("Longitud de palabras para el lenguaje a generar: "))
      except ValueError:
         print("Por favor, ingrese números enteros válidos para np y l.")
         input("Presione enter para volver a ingresar...\n")
         continue
   
      alfaList = list(alfabeto)
      PalabrasMAX = len(alfaList) ** l

      if np > PalabrasMAX:
         print("La cantidad deseada de palabras es mayor que el máximo posible.")
         if lenguajeGenerado:
            print("Puede generar un nuevo lenguaje con una cantidad válida.")
         input("Presione enter para volver a ingresar...\n")
      else:
         lenguaje = set()
         while len(lenguaje) < np:
            palabra = ''.join(random.choice(alfaList) for _ in range(l))
            lenguaje.add(palabra)
         
         lenguajeGenerado = True  # El lenguaje se ha generado con éxito
         return lenguaje

def diferenciaDeLenguajes(L1, L2):
   LD = set(set(L1) - set(L2))
   return LD

def elevarAlfabeto(alfabeto, potencia):
   alfabetoPotencia = set()
   potencia_abs = abs(potencia)
   if potencia == 0:
      return {'λ'}
   else:
      combinaciones = [''.join(tupla) for tupla in itertools.product(alfabeto, repeat=potencia_abs)]
      alfabetoPotencia = set(combinaciones)
      return alfabetoPotencia

###################### EXPRESIONES REGULARES ########################################
# 7.a
def FiveVowels(ConjuntoPalabras):
   # Expresion regular para evaluar las 5 vocales en orden
   regex = re.compile(r'(^(([bcdfghjklmnpqrstvwxyz]*a+[bcdfghjklmnpqrstvwxyz]*)+([bcdfghjklmnpqrstvwxyz]*e+[bcdfghjklmnpqrstvwxyz]*)+([bcdfghjklmnpqrstvwxyz]*i+[bcdfghjklmnpqrstvwxyz]*)+([bcdfghjklmnpqrstvwxyz]*o+[bcdfghjklmnpqrstvwxyz]*)+([bcdfghjklmnpqrstvwxyz]*u+[bcdfghjklmnpqrstvwxyz]*)+)+$)')
   for cadena in ConjuntoPalabras:
      if regex.match(cadena):
         print(f'"{cadena}" SI CUMPLE con el patrón de tener las cinco vocales en orden.')
      else:
         print(f'"{cadena}" NO CUMPLE con el patrón de tener las cinco vocales en orden.')

#7.b
def validarCadenaConDígitosRepetidos(cadena):
   return bool(re.search(r'(\d).*\1', cadena))


def main():
   alfabeto = set()
   
   while True:
      print("/// OPCIONES DISPONIBLES EN EL PROGRAMA ///")
      print("1) Ingresar alfabeto ∑")
      print("2) Ver alfabeto actual")
      print("3) Ingresar cadenas w1 y w2")
      print("4) Lenguajes aleatorios L1, L2 y LD (L1 - L2)")
      print("5) Elevar el alfabeto actual a una potencia n")
      print("6) Cadenas minusculas con 5 vocales en orden (EXPRESIONES REGULARES)")
      print("7) Cadenas con al menos dos caracteres repetidos")
      print("8) salir...")

      option = input("\nSeleccione una opcion: ")
      
      if (option == "1"):
         clearScreen()
         alfabeto = ingresarAlfabeto()
         clearScreen()

      elif (option == "2"):
         if not alfabeto:
            print("NO HAY alfabeto registrado")
         else:
            print(alfabeto)
         input("Presione enter...")
         clearScreen()

      elif (option == "3"):
         clearScreen()
         ingresarCadenas(alfabeto)

      elif (option == "4"):
         clearScreen()
         if not alfabeto:
            clearScreen()
            print("No se pueden generar lenguajes porque el alfabeto no tiene ningún símbolo")
            input("\nPresione enter...")
            clearScreen()
         else:
            clearScreen()
            print("GENERADOR DE LENGUAJES")
            print("INGRESE LOS DATOS CORRESPONDIENTES A L1")
            L1 = lenguajesAleatorios(alfabeto)
            clearScreen()
            print(f"L1: {L1}")
            print("\nINGRESE LOS DATOS CORRESPONDIENTES A L2")
            L2 = lenguajesAleatorios(alfabeto)
            LD = diferenciaDeLenguajes(L1, L2)
            clearScreen()
            print("Lenguajes generados: ")
            print(f"L1: {L1}")
            print(f"L2: {L2}")
            print("\n")
            print(f"LD (L2 - L1): {LD}")
            input("Presione enter para regresar al menu...")
            clearScreen()

      elif (option == "5"):
         clearScreen()
         if not alfabeto:
            clearScreen()
            print("NO hay alfabeto registrado...")
            input("\nPresione enter...")
            clearScreen()
         else:
            clearScreen()
            potencia = input("Ingrese la potencia deseada para elevar el alfabeto actual ∑: ")
            if potencia.lstrip('-').isdigit():
               potencia = int(potencia)
               alfaPower = elevarAlfabeto(alfabeto, potencia)
               print("\n")
               print(f"∑ ^ {potencia}: {alfaPower}")
               input("\nPresione enter...")
               clearScreen()
            else:
               print("La potencia debe ser un numero")
               input("Presione enter para volver al inicio...")
               clearScreen()

      elif (option == "6"):
         clearScreen()
         Valido = {"rtaeioujutf", "arteheejyibgfohgfdujhfd","aaaejhjhihgghgough", "abejitou", "abejitouabejitou", "aeiouaeiou", "hknalleioomuwraamqekiodsu", "aheklinmounmajkertebhiohjju"}
         noValido = {"kayteemnoyug", "ejuyaklengtivdfsojhgu", "agheehklinmoythuvbazeyiawqeihjou"}
         print("//////////// 5 VOCALES EN ORDEN ////////////")
         print("Seleccione como desea evaluar QUE UNA CADENA TENGA LAS 5 VOCALES EN ORDEN")
         print("1) Probar un conjunto predeterminado de prueba")
         print("2) Ingresar por palabra o palabras")
         print("O presione enter Volver al inicio\n")
         
         sel = input("Seleccione opcion: ")
         clearScreen()
         if (sel == "1"):
            print("CONJUNTO DE CADENAS VALIDAS: \n")
            FiveVowels(Valido)
            print("\n\nCONJUNTO DE CADENAS NO VALIDAS: \n")
            FiveVowels(noValido)
            input("\nPresione enter para volver a inicio...")
            clearScreen()

         elif (sel == "2"):
            palabras = set()
            while True:
               palabra = input("Ingrese una palabra o presione Enter para terminar): ")
               if palabra:
                  palabras.add(palabra)
               else:
                  break
            if not palabras:
               print("Debes ingresar al menos una palabra")
               input("\nVolviendo a inicio...")
               clearScreen()
            else:
               print("\n")
               FiveVowels(palabras)
               input("Presione enter para volver al inicio...")
               clearScreen()
               
         else:
            print("Volviendo al inicio...")

      elif (option == "7"):
         clearScreen()
         while True:
            print("Ingrese la cadena a evaluar (debe contener al menos 5 caracteres) o 'q' para volver al inicio ")
            cad = input("Cadena: ")
            if cad == 'q':
               break  # Salir del bucle y volver al inicio
            if not cad.isdigit():
               print("La cadena no está conformada solo por dígitos. Inténtelo de nuevo.\n")
               input()
               clearScreen()
               continue
            if len(cad) >= 5:
               if validarCadenaConDígitosRepetidos(cad):
                     print(f'La cadena "{cad}" es válida, ya que contiene al menos dos dígitos repetidos.\n')
               else:
                     print(f'La cadena "{cad}" no es válida, ya que no contiene al menos dos dígitos repetidos.\n')
               continue
            else:
               print("La cadena debe contener al menos 5 caracteres. Inténtelo de nuevo.\n")
               input()
               clearScreen()
         
         clearScreen()


      elif (option == "8"):
         print("Saliendo...")
         break
      else:
         print("Opcion no valida")
         input("Presione enter...")
         clearScreen()

if __name__ == "__main__":
   main()