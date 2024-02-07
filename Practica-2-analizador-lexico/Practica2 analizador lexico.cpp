// LA VERSION DE LINUX (SE SUBIO A TEAMS) UTILIZA LA RUTA ABSOLUTA, A DIFERENCIA DE ESTA VERSION

#include <bits/stdc++.h>
using namespace std;

enum class Estado {
   q0,   // Inicial, vacio
   q1,   // signo +
   q28,  // signo -
   q2,   // ESTADO MUERTO
   q3,   // 0 decimal o paso a octal/hexa
   q4,   // Se recibio * (operaciones o cerrar comentario multilinea)
   q5,   // numero o identificador con ,(coma) concatenad0. ej: 12.2, (pedir espacio despues de este)
   q6,   // octal valido
   q7,   // paso a hexa: 0x, +0x, -0x, 0X, +0X, -0X  
   q8,   // entero dec VALIDO
   q9,   // hexadecimal valido
   q10,  // entero con punto, ej: 24. y floatvalido
   q11,  // Posible decimal del tipo: .xx
   q12,  // paso a decimal o entero con exponente
   q13,  // Expo VALIDO (dec o entero)
   q14,  // Paso de expo con signo, ej: 12.2e[+,-]
   q15,  // Se recibio (/) division o posible comentario de linea
   q16,  // Se recibio (//) comentario una  (ignorar el resto de la linea)
   q17,  // Se recibio (/*) indicio a comentario multilinea (ignorar hasta leer */)
   q18,  // Se recibio (*) en q17, puede cerrar el comentario multilinea
   q19,  // Comentario multilinea valido
   q20,  // Palabra reservada
   q21,  // Identificador Valido
   q22,   // Se recibio "_", posible identificador
   q23,  // Tipo de dato
   q24,  // Operador de comparacion
   q25,  // Operador de asignacion
   q26,  // Operador modulo %
   q27,   // Operador multiplicacion *
   // q28 ta despues del q1
   q29,  // Incrementar1 ++
   q30,   // Decrementar1 --
   q31,   // Asignacion Abreviada. +=. -=, *=, /=, %=
   q32,   // Identificador valido con ; al final
   q33,  // Numero valido con ; al final
   q34,   // Especial para el tipo de dato float
   q35,   // numero flotante con f al final
   q36,   // cte o id con f y ; final
   q37,   // posible metodo del lenguaje
   q38,   // " Comilla abierta, texto
   q39   // se recibe " texto entre comillas valido
};

unordered_set<Estado> validStates {
   Estado::q0, Estado::q1, Estado::q3, Estado::q5, Estado::q6, Estado::q8, Estado::q9, Estado::q10, Estado::q13, Estado::q15,Estado::q16, Estado::q17, Estado::q19, Estado::q20, Estado::q21,
   Estado::q23, Estado::q24, Estado::q25, Estado::q26, Estado::q27, Estado::q28, Estado::q29, Estado::q30, Estado::q31, Estado::q32, Estado::q33, Estado::q35, Estado::q34, Estado::q36, Estado::q37, Estado::q39
};
unordered_set<Estado> numsValidos {
   Estado::q3, Estado::q5, Estado::q6, Estado::q8, Estado::q9, Estado::q10, Estado::q13, Estado::q21, Estado::q32, Estado::q33, Estado::q34, Estado::q35, Estado::q36, Estado::q39
};

unordered_set<string> javaReservWords = {
   "abstract", "assert", "break", "byte", "case", "catch", "class", "const", "continue", "default","do",
   "else", "enum", "exports", "extends", "final", "finally", "for", "goto", "if", "implements","import", "instanceof",
   "interface", "native", "new", "package", "private", "protected", "public", "return", "static",
   "strictfp", "super", "switch", "synchronized", "this", "throw", "throws", "transient", "try", "void", "volatile", "while"
};

unordered_set<string> dataTypesJava = {"int", "double", "float", "char", "boolean", "long", "short", "String"};
unordered_set<char> octalChars = {'0', '1', '2', '3', '4', '5', '6', '7'};
unordered_set<char> hexaChars = {
   '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
   'a', 'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F'
};

unordered_set<char> caracteresAgrupacion = {'[', ']', '{', '}', '(', ')', '\''};
unordered_set<string> comparadores = {"<", ">", ">=", "<=", "==", "!="};
unordered_set<char> opBinarios = {'+', '-', '*', '/', '%'};


Estado tokenValidator(const string& actual_token, bool& isComMultiLine, Estado& token_st_prev);  // La funcion mega importante que va a intentar validar los tokens
bool stringIn(const string& actual_token, unordered_set<string>& conjuntoPalabras);
bool charIn(char character, const unordered_set<char>& charSet);
bool isvalidState(Estado EstadoToken);
string typeError(Estado EstadoToken);

void balancedBrackets(char GroupChar, stack<char>& brackets, const unordered_set<char>& caracteresAgrupacion);
string deleteBrackets(const string& linea_entrada, stack<char>& brackets, const unordered_set<char>& caracteresAgrupacion);
void validAssign(vector<Estado>& lineStates, bool& isComMultiLine, vector<string>& errorsInLine);

int main() {
   // string nombre_archivo_sr = "javaCien.java";
   string nombre_archivo = "ejemplo.java";

   ifstream archivo(nombre_archivo);   // ifstream: entrada de flujo de archivo

   if (!archivo.is_open()) {
      cerr << "Error al abrir el archivo " << nombre_archivo << endl;
      perror("Error");
      return 1;
   }

   string linea;
   string nueva_linea;
   string token;
   int lineCount = 1;
   bool isComMultiLine = false;
   int errorsInFile = 0;
   stack<char> brackets;

   while (getline(archivo, linea)) {   // guarda en "linea" la linea que getline "extrae" de archivo
      vector <string> tokens;
      vector<string> errorsInLine;
      vector<Estado> lineStates; 

      nueva_linea = deleteBrackets(linea, brackets, caracteresAgrupacion);   // Nueva linea sin signos de agrupacion

      istringstream stream(nueva_linea);

      while (stream >> token) {  // extraer tokens de stream
         tokens.push_back(token);
      }

      for (const auto& token : tokens) {
         Estado token_st_prev = Estado::q0;
         Estado token_st = tokenValidator(token, isComMultiLine, token_st_prev);  // Aqui mandar a llamar al verificador

         lineStates.push_back(token_st);

         if (token_st == Estado::q16) {   // Si se esta en // (comentario) olvidar toda la linea actual (break)
            break;
         }
         if((!isvalidState(token_st) && token_st != Estado::q2) && isComMultiLine == false) {
            errorsInLine.push_back("Error en el token: \"" + token + "\". " + typeError(token_st));
         }
         if((token_st == Estado::q2) && isComMultiLine == false) {
            errorsInLine.push_back("Error en el token: \"" + token + "\". " + typeError(token_st_prev));
         }
      }

      validAssign(lineStates, isComMultiLine, errorsInLine);

      if (errorsInLine.size() != 0) {
         errorsInFile++;
         cout << "\033[1;31m";
         cout << "Errores de la linea ";
         cout << "\033[1;34m";
         cout << lineCount;
         cout << "\033[0m";
         cout << ":" << endl;
         for (const auto& error : errorsInLine) {
            cout << "- " << error << endl;
         }
         cout << endl;
      }

      lineCount++;
   }

   // Advertencias
   if (errorsInFile == 0) {
      cout << "\033[1;36m";
      cout << endl << "No hay errores de análisis léxico en las constantes numéricas del archivo \"" + nombre_archivo + "\"." << endl;
      cout << "\033[0m";
   }

   if (isComMultiLine == true) {
      cout << "\033[1;38;5;215m";   // Código ANSI para cambiar el color del texto a anaranjado
      cout << "Advertencia: Comentario multilinea sin cerrar." << endl;
      cout << "\033[0m";   // Restaurar el color original (opcional)
   }
   if (!brackets.empty()) {
      cout << "\033[1;38;5;215m";
      cout << "Advertencia: Signos de agrupacion no balanceados." << endl;
      cout << "\033[0m";
   }
   
   archivo.close();

   return 0;
}

Estado tokenValidator(const string& actual_token, bool& isComMultiLine, Estado& token_st_prev) {
   unsigned int pos_char = 0; // Posicion actual en del token
   Estado actual_state = Estado::q0;

   while (actual_state != Estado::q2 && pos_char < actual_token.length()) {
      char actual_char = actual_token[pos_char];

      switch (actual_state) {
         case Estado::q0:
            if (actual_char == '/') {
               actual_state = Estado::q15;
            }
            else if (actual_char == ';') {
               actual_state = Estado::q0;
            }
            else if (actual_char == '%') {
               actual_state = Estado::q26;
            }
            else if (actual_char == '+') {
               actual_state = Estado::q1;
            }
            else if (actual_char == '-') {
               actual_state = Estado::q28;
            }
            
            else if (actual_char == '0') {   
               actual_state = Estado::q3;
            }
            else if (actual_char == '.') {
               actual_state = Estado::q11;
            }
            else if (isdigit(actual_char) && actual_char != '0') {
               actual_state = Estado::q8;
            }
            else if (stringIn(actual_token, javaReservWords)) {
               actual_state = Estado::q20;
            }
            else if (stringIn(actual_token, dataTypesJava) && actual_token != "float") {
               actual_state = Estado::q23;
            }
            else if (actual_token == "float") {
               actual_state = Estado::q34;
            }
            else if (stringIn(actual_token, comparadores)) {
               actual_state = Estado::q24;
            }
            else if (actual_char == '$' || isalpha(actual_char)) {
               actual_state = Estado::q21;
            }
            else if (actual_char == '_') {
               actual_state = Estado::q22;
            }
            else if (actual_char == '=') {
               actual_state = Estado::q25;
            }
            else if (actual_char == '"') {
               actual_state = Estado::q38;
            }
            
            else if (actual_char == '*') {
               if (isComMultiLine) {
                  actual_state = Estado::q18;
               } else {
                  actual_state = Estado::q27;
               }
            }
            else {
               actual_state = Estado::q2;
            }
            break;

         case Estado::q1:
            if (actual_char == '0') {
               actual_state = Estado::q3;
            }
            else if (actual_char == '.') {
               actual_state = Estado::q11;
            }
            else if (isdigit(actual_char) && actual_char != '0') {
               actual_state = Estado::q8;
            }
            else if (actual_char == '+') {
               actual_state = Estado::q29;
            }
            else if (actual_char == '=') {
               actual_state = Estado::q31;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q2 : // PURA BASURA/ESTADO MUERTO
            actual_state = Estado::q2;
            break;
            
         case Estado::q3:  // estamos en un 0
            if (actual_char == ',') {
               actual_state = Estado::q5;
            }
            else if (charIn(actual_char, octalChars)) {
               actual_state = Estado::q6;
            }
            else if (actual_char == ';') {
               actual_state = Estado::q33;
            }
            else if (actual_char == 'x' || actual_char == 'X') {
               actual_state = Estado::q7;
            }
            else if (actual_char == '.') {
               actual_state = Estado::q10;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q4 :
            break;

         case Estado::q5:
            if (actual_char == ';' || isdigit(actual_char) || actual_char == '-' || actual_char == '+') {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            else {
               actual_state = Estado::q0;
               break;
            }
            break;

         case Estado::q6:
            if (charIn(actual_char, octalChars)) {
               actual_state = Estado::q6;
            }
            else if (actual_char == ',') {
               actual_state = Estado::q5;
            }
            else if (actual_char == ';') {
               actual_state = Estado::q33;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q7:
            if (charIn(actual_char, hexaChars)) {
               actual_state = Estado::q9;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q8:  // Entero decimal valido
            if (isdigit(actual_char)) {
               actual_state = Estado::q8;
            }
            else if (actual_char == ',') {
               actual_state = Estado::q5;
            }
            else if (actual_char == ';') {
            }
            else if (actual_char == '.') {
               actual_state = Estado::q10;
            }
            else if (actual_char == 'e' || actual_char == 'E') {
               actual_state = Estado::q12;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q9:
            if (charIn(actual_char, hexaChars)) {
               actual_state = Estado::q9;
            }
            else if (actual_char == ',') {
               actual_state = Estado::q5;
            }
            else if (actual_char == ';') {
               actual_state = Estado::q33;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;


         case Estado::q10:
            if (isdigit(actual_char)) {
               actual_state = Estado::q10;
            }
            else if (actual_char == ';') {
               actual_state = Estado::q33;
            }
            else if (actual_char == ',') {
               actual_state = Estado::q5;
            }
            else if (actual_char == 'f') {
               actual_state = Estado::q35;
            }
            else if (actual_char == 'e' || actual_char == 'E') {
               actual_state = Estado::q12;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q11: // Estamos en un punto (.)
            if (isdigit(actual_char)) {
               actual_state = Estado::q10;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q12:
            if (actual_char == '+' || actual_char == '-') {
               actual_state = Estado::q14;
            }
            else if (isdigit(actual_char)) {
               actual_state = Estado::q13;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q13:
            if (isdigit(actual_char)) {
               actual_state = Estado::q13;
            }
            else if (actual_char == ',') {
               actual_state = Estado::q5;
            }
            else if (actual_char == ';') {
               actual_state = Estado::q33;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q14:
            if (isdigit(actual_char)) {
               actual_state = Estado::q13;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q15:
            if (actual_char == '/') {
               actual_state = Estado::q16;
            }
            else if (actual_char == '=') {
               actual_state = Estado::q31;
            }
            else if (actual_char == '*') {
               actual_state = Estado::q17;
               isComMultiLine = true;  // Sube la bandera cuando detecta el */
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q16: // Ignorar todo lo que falta de la linea
            actual_state = Estado::q16;
            break;

         case Estado::q17:
            actual_state = Estado::q17;   // Para todo se sigue quedando en comentario multilinea

            if (actual_char == '*') {  // formalmente no entraria a menos que sea un tipo /*blabla*/
               actual_state = Estado::q18;
            }
            break;
            
         case Estado::q18:
            actual_state = Estado::q18;
            
            if (actual_char == '/') {
               isComMultiLine = false;
               actual_state = Estado::q19;   // Se cierra el comentario multilinea
            }
            else {
               actual_state = Estado::q17;
            }
            break;

         case Estado::q19:
            break;

         case Estado::q20:
            break;

         case Estado::q21:
            if (actual_char == '_' || actual_char == '$' || isalpha(actual_char) || isdigit(actual_char)) {
               actual_state = Estado::q21;
            }
            else if (actual_char == ';') {
               actual_state = Estado::q32;
            }
            else if (actual_char == ',') {
               actual_state = Estado::q5;
            }
            else if (actual_char == '.') {
               actual_state = Estado::q37;
            }
            else if (actual_char == 'f') {
               actual_state = Estado::q35;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q22:
            if (actual_char == '_' || actual_char == '$' || isalpha(actual_char) || isdigit(actual_char)) {
               actual_state = Estado::q21;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;


         case Estado::q23:
            break;
         case Estado::q24:
            break;
         case Estado::q25:
            break;
         case Estado::q26:
            if (actual_char == '=') {
               actual_state = Estado::q31;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q27:
            if (actual_char == '=') {
               actual_state = Estado::q31;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q28:
            if (actual_char == '0') {
               actual_state = Estado::q3;
            }
            else if (actual_char == '.') {
               actual_state = Estado::q11;
            }
            else if (isdigit(actual_char) && actual_char != '0') {
               actual_state = Estado::q8;
            }
            else if (actual_char == '-') {
               actual_state = Estado::q30;
            }
            else if (actual_char == '=') {
               actual_state = Estado::q31;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q29:
            if (actual_char) {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q30:
            if (actual_char) {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q31:
            break;
         case Estado::q32:
            if (actual_char) {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q33:
            break;
         case Estado::q34: // caso especial del token float
            break;

         case Estado::q35:
            if (actual_char == ';') {
               actual_state = Estado::q36;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q36:
            break;

         case Estado::q37: // system.out. / ids con puntos entremedio
            if (actual_char == '_' || actual_char == '$' || isalpha(actual_char) || isdigit(actual_char)) {
               actual_state = Estado::q37;
            }
            else if (actual_char == '.') {
               actual_state = Estado::q37;
            }
            else {
               if (isComMultiLine == false) {
                  token_st_prev = actual_state;
               }
               actual_state = Estado::q2;
            }
            break;

         case Estado::q38:
            if (actual_char == '"') {
               actual_state = Estado::q39;
            }
            else {
               actual_state = Estado::q38;
            }
            break;
         case Estado::q39:
            break;
      }
      pos_char++; // pasamos al siguiente caracter del token
   }

   return actual_state;
}

bool stringIn(const string& actual_token, unordered_set<string>& conjuntoPalabras) {
   return conjuntoPalabras.find(actual_token) != conjuntoPalabras.end();
}

bool charIn(char character, const unordered_set<char>& charSet) {
   return charSet.find(character) != charSet.end();
}

bool isvalidState(Estado EstadoToken) {
   return validStates.find(EstadoToken) != validStates.end();
}
bool inNumStates(Estado EstadoToken) {
   return numsValidos.find(EstadoToken) != numsValidos.end();
}

void balancedBrackets(char GroupChar, stack<char>& brackets, const unordered_set<char>& caracteresAgrupacion) {
   if (caracteresAgrupacion.find(GroupChar) != caracteresAgrupacion.end()) {
      if (GroupChar == '(' || GroupChar == '{' || GroupChar == '[') {
         brackets.push(GroupChar);
      } else if (GroupChar == ')' || GroupChar == '}' || GroupChar == ']') {
         if (!brackets.empty()) {
            char openingBracket = brackets.top();
            brackets.pop();  // Desapilar siempre, incluso si hay un desequilibrio

            if ((GroupChar == ')' && openingBracket != '(') || (GroupChar == '}' && openingBracket != '{') || (GroupChar == ']' && openingBracket != '[')) {
               brackets.push('f');
            }
         } else {
            brackets.push('f');
         }
      }
   }
}
string deleteBrackets(const string& linea_entrada, stack<char>& brackets, const unordered_set<char>& caracteresAgrupacion) {
   string nueva_linea;
   for (char caracter : linea_entrada) {
      balancedBrackets(caracter, brackets, caracteresAgrupacion);
      if (caracteresAgrupacion.find(caracter) == caracteresAgrupacion.end()) {
         nueva_linea += caracter;
      }
   }
   return nueva_linea;
}

void validAssign(vector<Estado>& lineStates, bool& isComMultiLine, vector<string>& errorsInLine) {
   bool isValid = true;
   size_t tam = lineStates.size();
   size_t i = 0;

   while (i < tam) {
      switch (lineStates[i]) {
         case Estado::q23: // si es un tipo de dato
            if (lineStates[i+1] == Estado::q32) {  // Declaracion sin inicializacion;
               isValid = true;
            }
            else if (lineStates[i+1] == Estado::q21) {  // Declaracion sin inicializacion para funciones;
               isValid = true;
            }
            else if (lineStates[i+1] == Estado::q21 && (lineStates[i+2] == Estado::q25) && (inNumStates(lineStates[i+3]))) {   // Declaracion con incializacion; 
               isValid = true;
            }
            else if (lineStates[i+1] == Estado::q21 && (lineStates[i+2] == Estado::q25) && (inNumStates(lineStates[i+3]))) {   // Declaracion con incializacion; 
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  isValid = false;  // o no se si mejor valla fuera del if
                  errorsInLine.push_back("Error en la declaracion de variable.");
               }
            }
            break;
         
         case Estado::q34: // caso especial del tipo de dato float
            if (lineStates[i+1] == Estado::q32) {  // Declaracion sin inicializacion;
               isValid = true;
            }
            else if (inNumStates(lineStates[i+1])) {
               isValid = true;
            }
            else if ((lineStates[i+1] == Estado::q10 || lineStates[i+1] == Estado::q32 || lineStates[i+1] == Estado::q33)) {  // caso especial
               isValid = true;
            }
            else if (lineStates[i+1] == Estado::q21 && (lineStates[i+2] == Estado::q25) && (lineStates[i+3] == Estado::q34) && (inNumStates(lineStates[i+4]))) {   // Declaracion con incializacion (float); 
               isValid = true;
            }
            else if (lineStates[i+1] == Estado::q21 && (lineStates[i+2] == Estado::q25) && (lineStates[i+3] == Estado::q35 || lineStates[i+3] == Estado::q36)) {   // Declaracion con casteo xxf
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  isValid = false;  // o no se si mejor valla fuera del if
                  errorsInLine.push_back("Error en la declaracion de variable flotante.");
               }
            }
            break;

         case Estado::q25: // si es un operador de asignacion
            if (lineStates[i-1] == Estado::q21 && inNumStates(lineStates[i+1])) {   // debe tener en izq un id y en der un numValid o id
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  isValid = false;  // o no se si mejor valla fuera del if
                  errorsInLine.push_back("Error en la asignacion de variable.");
               }
            }
            break;

         case Estado::q24: // Algun operador de comparacion 
            if (inNumStates(lineStates[i-1]) && inNumStates(lineStates[i+1])) {  // verificar izq y der
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  isValid = false;  // o no se si mejor valla fuera del if
                  errorsInLine.push_back("Error en la comparacion. Revise valores.");
               }
            }
            break;

         case Estado::q31: // asignacion abreviada +=, -+ ...
            if (lineStates[i-1] == Estado::q21 && inNumStates(lineStates[i+1])) {
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  isValid = false;  // o no se si mejor valla fuera del if
                  errorsInLine.push_back("Error en la asignacion abreviada.");
               }
            }
            break;

         // De aqui al son para los operadores binarios aritmeticos
         case Estado::q1:  // suma
            if (isValid && inNumStates(lineStates[i-1]) && inNumStates(lineStates[i+1])) {
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  isValid = false;  // o no se si mejor valla fuera del if
                  errorsInLine.push_back("Error en la operacion suma. Revise valores.");
               }
            }
            break;
         case Estado::q28: // resta
            if (isValid && inNumStates(lineStates[i-1]) && inNumStates(lineStates[i+1])) {
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  isValid = false;  // o no se si mejor valla fuera del if
                  errorsInLine.push_back("Error en la operacion resta. Revise valores.");
               }
            }
            break;
         case Estado::q27: // producto
            if (isValid && inNumStates(lineStates[i-1]) && inNumStates(lineStates[i+1])) {
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  isValid = false;  // o no se si mejor valla fuera del if
                  errorsInLine.push_back("Error en la operacion producto. Revise valores.");
               }
            }
            break;
         case Estado::q15: // division /
            if (isValid && inNumStates(lineStates[i-1]) && inNumStates(lineStates[i+1])) {
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  isValid = false;  // o no se si mejor valla fuera del if
                  errorsInLine.push_back("Error en la operacion cociente. Revise valores.");
               }
            }
            break;
         case Estado::q26: // modulo %
            if (isValid && inNumStates(lineStates[i-1]) && inNumStates(lineStates[i+1])) {
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  isValid = false;  // o no se si mejor valla fuera del if
                  errorsInLine.push_back("Error en la operacion modulo. Revise valores.");
               }
            }
            break;
         // Aqui acaban los de aritmetica

         case Estado::q29: // si es ++
            if (lineStates[i-1] == Estado::q21) {
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  errorsInLine.push_back("Error en la operacion incremento.");
               }
            }
            break;

         case Estado::q30: // si es --
            if (lineStates[i-1] == Estado::q21) {
               isValid = true;
            }
            else {
               if (isComMultiLine == false) {
                  isValid = false;  // o no se si mejor valla fuera del if
                  errorsInLine.push_back("Error en la operacion incremento.");
               }
            }
            break;
         
         case Estado::q2:
            isValid = false;
            break;

         default:
            //isValid = true;
            break;
      }

      i++;
   }
}

string typeError(Estado EstadoToken) {
   string descError;

   switch (EstadoToken) {
      case Estado::q1:
         descError = "Signo \"+\" sin valor asociado.";
         break;

      case Estado::q3:  // Se usa con estado_previo
         descError = "Octal no valido.";
         break;

      case Estado::q5:  // Se usa con estado_previo
         descError = "Error en el caracter despues del numero con coma.";
         break;

      case Estado::q6:  // Se usa con estado_previo
         descError = "Octal no valido.";
         break;

      case Estado::q7:
         descError = "Hexadecimal invalido.";
         break;

      case Estado::q8:  // Se usa con estado_previo
         descError = "Entero decimal no valido";
         break;

      case Estado::q9:  // Se usa con estado_previo
         descError = "Hexadecimal invalido.";
         break;

      case Estado::q10:  // Se usa con estado_previo
         descError = "Errores en la parte decimal";
         break;

      case Estado::q11:
         descError = "Decimal flotante de tipo .xx NO valido.";
         break;

      case Estado::q12:
         descError = "Exponente no valido.";
         break;

      case Estado::q13:  // Se usa con estado_previo
         descError = "Exponente no valido.";
         break;

      case Estado::q14:
         descError = "Exponente no valido.";
         break;

      case Estado::q15:
         descError = "Division no valida. Debe estar separado el operador \'/\'.";
         break;
      ///////////////////////////////////////////////////////
      case Estado::q21:
         descError = "Identificador no valido.";
         break;

      case Estado::q22:
         descError = "Identificador no valido.";
         break;

      case Estado::q27:
         descError = "Producto no valido. Debe estar separado el operador \'*\'.";
         break;

      case Estado::q28:
         descError = "Signo \"-\" sin valor asociado.";
         break;
         
      case Estado::q29:
         descError = "Incremento invalido.";
         break;

      case Estado::q30:
         descError = "Decremento invalido.";
         break;
      case Estado::q35:
         descError = "flotante invalido. valores despues del casteo \'f\'.";
         break;

      default:
         descError = "error unknow.";
         break;
   }

   return descError;
}