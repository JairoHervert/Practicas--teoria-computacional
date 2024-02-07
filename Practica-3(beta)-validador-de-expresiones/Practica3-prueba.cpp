#include <bits/stdc++.h>
using namespace std;

//Creacion de estados para el automata
enum Estado{
    q0, //Estado inicial
    q1, //Le llega un _ o una letra y da en ciclo para identificadores
    q2, //Le llega un "="
    //Estados de las constantes
    q3, //Constante entera con o sin signo (0-9, estado de aceptacion)
    q4, //Constante decimal con enteros y decimales (estado de aceptacion)
    q5, //constante decimal con o sin decimales donde se pone E o e
    q6, //constante decimal con o sin decimales y exponente positivo o negativo (estado de aceptacion)
    q7, //numero con signo para decimales, octales y hexadecimales
    q8, //numero con o sin signo para octales y hexadecimales
    q9,  //numero octal (estado de aceptacion)
    q10 //numero hexadecimal (estado de aceptacion)

};

void analizarParentesis(string linea);
void analizarIguales(string linea);


//verificadores
bool isNumber(char c);
bool isNumber2(char c);
bool isOctal(char c);
bool isHexadecimal(char c);
bool isOperator(char c);
bool isOperator2(char c);


//automata de pila

void automataPila(string linea);
void espacios(string linea);
void arbol();


Estado estado = q0;
string cadena2= "";

int main()
{
    //Declaracion de variables para dividir la cadena en tokens(palabras)
    string linea;
    string token;
    int i = 0;


    cout << "Ingrese la cadena: ";
    getline(cin, linea);



    cout << "La cadena es: " << linea << endl;

    string linea2 = linea;

    espacios(linea);


    analizarIguales(linea);


    analizarParentesis(linea);





    //quitar espacios en blanco
    for(int i = 0; i < linea.size(); i++){
        if(linea[i] == ' '){
            linea.erase(i, 1);
        }
    }

    automataPila(linea);


    //Imprimir arbol
    cout<< "<alfa>"<<endl;
    arbol();
    cout << cadena2<< endl ;


    return 0;
    
}


//Automata de pila
/*
    -------------------------------------------------------------------------------------
    DESCRIPCIÓN: Esta funcion es la que analiza la cadena de entrada y verifica si es valida o no
    ENTRADA: La cadena de entrada
    SALIDA: Un mensaje que indica si la cadena es valida o no
    ------------------------------------------------------------------------------------

*/

void automataPila(string linea){
    //creacion de la pila para el automata
    stack<char> pila;
    //se agrega el inicio de la pila
    pila.push('Z');

    int i = 0, longitud = linea.size(), caracter;


    while (i<longitud)
    {
        caracter = linea[i];
        switch (estado){
            case q0:
                if (caracter == '(' || caracter == ')'){
                    estado = q0;
                    //PILA no se modifica
                }
                else if(caracter == '_' || isalpha(caracter) || caracter == '$'){
                    estado = q1;
                    cadena2 += "<id>";
                    //PILA no se modifica    
                }
            
                else{
                    estado = q0;
                    cout << "Cadena no valida" << endl;
                    exit(0);
                }
                break;
            case q1:
                if (caracter == '(' || caracter == ')'){
                    estado = q1;
                    //PILA no se modifica
                }
                
                else if(caracter == '='){
                    estado = q2;
                    cadena2 += "=";
                    //PILA no se modifica
                }
                
                else if(caracter == '_' || isalpha(caracter) || isNumber(caracter) || caracter == '$'){
                    estado = q1;
                    //PILA no se modifica
                }
                else{
                    estado = q0;
                    cout << "Cadena no valida (q1)" << endl;
                    exit(0);
                }
                break;
            case q2:
                if (caracter == '(' || caracter == ')'){
                    estado = q2;
                    if (caracter == '('){
                        cadena2 += "(";
                    }
                    else{
                        cadena2 += ")";
                    }
                    //PILA no se modifica
                }
                else if(isNumber2(caracter) && pila.top() == 'Z'){
                    estado = q3;
                    cadena2 += "Decimal";
                    //se queda igual la pila
                }
                else if((caracter == '+' || caracter == '-') && pila.top() == 'Z'){
                    estado = q6;
                    //se agrega el + o - a la pila
                    pila.push(caracter);
                    cadena2 += "<Signo>";
                }
                else if(caracter == '0'){
                    estado = q7;
                    //se agrega caracter a la pila
                    //Numero 0
                    pila.push(caracter);
                }
                else if (caracter == '_' || isalpha(caracter) || caracter == '$'){
                    estado = q10;
                    //se agrega caracter a la pila

                    cadena2 += "ID";
                }
                else{
                    cout << "Cadena no valida (q2)" << endl;
                    exit(0);
                }
                break;

            case q3:
                if (caracter == '(' || caracter == ')'){
                    estado = q3;
                    if (caracter == '('){
                        cadena2 += "(";
                    }
                    else{
                        cadena2 += ")";
                    }
                    //PILA no se modifica
                }
                else if(isNumber(caracter) && (pila.top() == '+')){
                    pila.pop();
                    estado = q3;
                    //se quita el caracter de la pila
                }
                else if(isNumber(caracter) && pila.top() == 'Z'){
                    estado = q3;
                    //la pila no se modifica

                }
                else if(caracter == '.' && pila.top()=='Z') {
                    estado = q4;
                    //se agrega caracter a la pila
                    //Punto
                    pila.push(caracter);
                }
                else if(isOperator(caracter) && pila.top() == 'Z') {
                    estado = q2;
                    //Se queda igual la pila
                    cadena2 += "<Operador>";
                }
                else if(caracter == ';' && pila.top()=='Z'){
                    //vaciar pila
                    pila.pop();

                }
                else {
                    cout << "Cadena no valida (q3)" << endl;
                    exit(0);
                }
                break;
            case q4:
                if (caracter == '(' || caracter == ')'){
                    estado = q4;
                    //PILA no se modifica
                    if (caracter == '('){
                        cadena2 += "(";
                    }
                    else{
                        cadena2 += ")";
                    }
                }
                else if(isNumber(caracter) && pila.top() == '.'){
                    estado = q4;
                    //se elimina el punto de la pila
                    pila.pop();
                }
                else if(isNumber(caracter) && pila.top() == 'Z') { 
                    estado = q4;
                    //se queda igual la pila
                }
                else if ((caracter == 'E' || caracter == 'e') && pila.top() == 'Z') {
                    estado = q5;
                    //se agrega caracter a la pila
                    //E o e
                    pila.push(caracter);
                }
                else if(isOperator(caracter) && pila.top() == 'Z') {
                    estado = q2;
                    //Se queda igual la pila
                    cadena2 += "<Operador>";


                }
                else if(caracter == ';' && pila.top()=='Z'){
                    //vaciar pila
                    pila.pop();

                }
                else {
                    cout << "Cadena no valida (q4)" << endl;
                    exit(0);

                }
                break;
            case q5:
                if (caracter == '(' || caracter == ')'){
                    if (caracter == '('){
                        cadena2 += "(";
                    }
                    else{
                        cadena2 += ")";
                    }
                    estado = q5;
                    //PILA no se modifica
                }
                else if((caracter == '+' || caracter == '-') && (pila.top() == 'E' || pila.top() == 'e')){
                    estado = q5;
                    //se agrega caracter a la pila
                    //+ o -
                    pila.push(caracter);
                }             
                else if(isNumber(caracter) && (pila.top() == '+' || pila.top() == '-')){
                    estado = q5;
                    //se quita el caracter de la pila
                    pila.pop();

                }
                else if(isNumber(caracter) && (pila.top() == 'E' || pila.top() == 'e')){
                    estado = q5;
                    //se quita el caracter de la pila
                    pila.pop();
                }
                else if (isNumber(caracter) && pila.top() == 'Z') {
                    estado = q5;
                    //se queda igual la pila
                }
                else if(isOperator(caracter) && pila.top() == 'Z') {
                    estado = q2;
                    //Se queda igual la pila
                    cadena2 += "<Operador>";

                }
                else if(caracter == ';' && pila.top()=='Z'){
                    //vaciar pila
                    pila.pop();

                }
                else {
                    cout << "Cadena no valida (q5)" << endl;
                    exit(0);
                }
                break;
            case q6:
                if (caracter == '(' || caracter == ')'){
                    estado = q6;
                    //PILA no se modifica
                }
                else if(isNumber2(caracter) && (pila.top() == '+' || pila.top() == '-')){
                    estado = q3;
                    //se quita el caracter de la pila
                    pila.pop();
                    //PILA no se modifica
                    cadena2 += "Decimal";
                }
                else if(caracter == '0' && (pila.top() == '+' || pila.top() == '-')){
                    estado = q7;
                    //pila no se modifica
                }
                else {
                    cout << "Cadena no valida (q6)" << endl;
                    exit(0);
                }
                break;
            case q7:
                if (caracter == '(' || caracter == ')'){
                    estado = q7;
                    //PILA no se modifica
                }
                else if (isOctal(caracter) && (pila.top() == '0' || pila.top() == '+' || pila.top() == '-')){
                    estado = q8;
                    //Se quita el 0, + o - de la pila
                    pila.pop();

                    cadena2 += "Octal";
                }
                else if((caracter == 'X'  || caracter == 'x') && (pila.top() == '0' || pila.top() == '+' || pila.top() == '-') ) {
                    estado = q9;
                    //sse quita el 0, + o - de la pila
                    pila.pop();

                    cadena2 += "Hexadecimal" ;
                }
                else {
                    cout << "Cadena no valida (q7)" << endl;
                    exit(0);
                }
                break;
            case q8:           
                if (caracter == '(' || caracter == ')'){
                    estado = q8;                    
                    if (caracter == '('){
                        cadena2 += "(";
                    }
                    else{
                        cadena2 += ")";
                    }
                    //PILA no se modifica
                }
                else if (isOctal(caracter) && pila.top() =='Z'){
                    estado = q8;
                    //PILA no se modifica

                }
                else if(isOperator(caracter) && pila.top() == 'Z') {
                    estado = q2;

                    cadena2 += "<Operador>" ;
                    //Se queda igual la pila
                }
                else if(caracter == ';' && pila.top()=='Z'){
                    //vaciar pila
                    pila.pop();

                }
                else {
                    cout << "Cadena no valida (q8)" << endl;
                    exit(0);
                }
                
                break;
                
            case q9:                
                if (caracter == '(' || caracter == ')'){
                    estado = q9;
                    if (caracter == '('){
                        cadena2 += "(";
                    }
                    else{
                        cadena2 += ")";
                    }
                    //PILA no se modifica
                }
                else if (isHexadecimal(caracter) && pila.top() == 'Z'){
                    estado = q9;
                    //PILA no se modifica
                }

                else if(isOperator(caracter) && pila.top() == 'Z') {
                    estado = q2;
                    //Se queda igual la pila

                    cadena2 += "<Operador>";
                }
                else if(caracter == ';' && pila.top()=='Z'){
                    //vaciar pila
                    pila.pop();

                }
                else {
                    cout << "Cadena no valida (q9)" << endl;
                    exit(0);
                }
                break;

            case q10:                
                if (caracter == '(' || caracter == ')'){
                    estado = q10;
                    if (caracter == '('){
                        cadena2 += "(";
                    }
                    else{
                        cadena2 += ")";
                    }
                    //PILA no se modifica
                }
                else if((isalpha(caracter) || isNumber(caracter) || caracter == '_' || caracter == '$' ||(caracter =='+' && linea[i+1] =='+')||(caracter =='-' && linea[i+1] =='-')) && pila.top() == 'Z') {
                    estado = q10;
                    //Se queda igual la pila
                }
                else if(isOperator2(caracter) && pila.top() == 'Z') {
                    if(caracter != '=')
                    cadena2 += "<Operador>" ;
                    else{
                        cadena2 += "=";
                    }
                    estado = q2;
                    //Se queda igual la pila

                }
                else if(caracter == ';'){
                    //vaciar pila
                    pila.pop();

                }
                else {
                    cout << "Cadena no valida (q10)" << endl;
                    exit(0);
                }
                break;
            

                
        }
        i++;

            
    }
    
    if((estado == q3 || estado == q4 || estado == q5|| estado == q8 || estado == q9 || estado == q10) && pila.empty() ){
        cout << "Cadena valida" << endl;

        //mostrar la pila
 
    }
    else{

        cout << "Cadena no valida" << endl;
        exit(0);
    }

}

void analizarParentesis(string linea){

    int balanceo = 0;
    string nuevaLinea = "";

   
    //quitar espacios en blanco
    for(int i = 0; i < linea.size(); i++){
        if(linea[i] == ' '){
            linea.erase(i, 1);
        }
    }

    //analizar los parentesis y verificar que esten balanceados

    for(int i = 0; i < linea.size(); i++){
        if(linea[i] == '('){
            if ((!isOperator2(linea[i - 1]) && linea[i - 1] != '(' && linea[i-1] != '=' )|| ((linea[i + 1] == '*' && linea[i+1] != '/' && linea[i+1] == '%') && 
            !isalpha(linea[i+2]) && linea[i+2] != '_' || linea[i + 1] == ')')) {
                        cout << "error de sintaxis (" << endl;
                exit(0);
            }
            balanceo++;

        }
        else if(linea[i] == ')'){
            if (isOperator(linea[i - 1]) || linea[i - 1] == '(' || (i + 1 < linea.length() && (isalpha(linea[i + 1]) || isNumber(linea[i + 1])))){                
                cout << "error de sintaxis )" << endl;
                exit(0);
            }
            balanceo--;
        }
        else{
            nuevaLinea += linea[i];
        }
    }
 
    if(balanceo != 0){
        cout << "Error: Los parentesis no estan balanceados" << endl;
        exit(0);
    }

}


//funcion para analizar la estructura de los identificadores que se igualan a un valor
//estructura: id1 = id2 = id3 = valor
/*
    -------------------------------------------------------------------------------------
    DESCRIPCIÓN: Esta funcion ira en un bucle de la cadena de entrada de atrás hacia adelante hasta que encuentre un '='
    y  cuando encuentre un operador de operacion o un numero en una posicion i y un '=' en la posicion i-1 se marcará error
    ENTRADA: La cadena de entrada
    SALIDA: Un mensaje de error si la cadena no es valida
    ------------------------------------------------------------------------------------

*/

void analizarIguales(string linea) {
    int i, aux1 =0, aux2=0;

    i = 0;
    while (i < linea.size()) {

        if (linea[i] == '=') 
        aux1=i;
        else if (isOperator(linea[i])){
        aux2 = i; 
        }
        
        i++;
    }
    //cout << aux1 << endl;
    //cout << aux2 << endl;
    if (aux2>0 && (aux2 < aux1)) {
        cout << "Error de sintaxis 2.1  xd" << endl;
        exit(0);
    }


        //quitar espacios en blanco
    for(i = 0; i < linea.size(); i++){
        if(linea[i] == ' '){
            linea.erase(i, 1);
        }
    }

    i=0;
    while (i < linea.size()) {

        if (linea[i] == '=') {
            if (isNumber(linea[i + 1]) && linea[i + 2] == '=')  {
                cout << "Error de sintaxis 1" << endl;
                exit(0);
            }
        }
        // Moverse al siguiente carácter
        i++;
    }

}




//funcion para saber si una letra es numero
bool isNumber(char c){
    return (c >= '0' && c <= '9');
}

bool isNumber2(char c){
    return (c >= '1' && c <= '9');
}


//funcion para saber si es un numero octal
bool isOctal(char c){
    return (c >= '0' && c <= '7');
}

//funcion para saber si es un numero hexadecimal
bool isHexadecimal(char c){
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F');
}

//funcion para saber si es un operador
bool isOperator(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}
bool isOperador(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}
bool isOperator2 (char c){
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=');
}

void espacios(string linea){
    for(int i = 0; i < linea.size(); i++){
        if(linea[i] == ' ' && (isNumber(linea[i-1]) || isalpha(linea[i-1]))){
            if((isalpha(linea[i+1]) || isNumber(linea[i+1]))){
                cout << "Error de sintaxis XD" << endl;
                exit(0);
            }
        }
    }
}


void arbol() {

	vector<string> v;
	string aux = cadena2;
	
	while (true) {
		size_t pos = aux.find("ID");
		if(pos == string::npos) {break;}
		aux.replace(pos, 2, "<Componente3>");
		v.push_back(aux);
	}

	while (true) {
		size_t pos = aux.find("Decimal");
		if(pos == string::npos) {break;}
		aux.replace(pos, 7, "<Componente3>");
		v.push_back(aux);
	}
	while (true) {
		size_t pos = aux.find("Octal");
		if(pos == string::npos) {break;}
		aux.replace(pos, 5, "<Componente3>");
		v.push_back(aux);
	}

	while (true) {
		size_t pos = aux.find("Hexadecimal");
		if(pos == string::npos) {break;}
		aux.replace(pos, 11, "<Componente3>");
		v.push_back(aux);
	}

    while (true) {
		size_t pos = aux.find("<Signo>Decimal");
		if(pos == string::npos) {break;}
		aux.replace(pos, 14, "<Componente3>");
		v.push_back(aux);
	}
    while (true) {
		size_t pos = aux.find("<Signo>Hexadecimal");
		if(pos == string::npos) {break;}
		aux.replace(pos, 17, "<Componente3>");
		v.push_back(aux);
	}
    while (true) {
		size_t pos = aux.find("<Signo>Octal");
		if(pos == string::npos) {break;}
		aux.replace(pos, 12, "<Componente3>");
		v.push_back(aux);
	}

    while(true) {

		string aux3 = aux;

		while (true) {
			size_t pos = aux.find("<Componente3>");
			if(pos == string::npos) {break;}
			aux.replace(pos, 13, "<Componente2>");
			v.push_back(aux);
		}

		while (true) {
			size_t pos = aux.find("<Componente2><Operador><Componente2>");
			if(pos == string::npos) {break;}
			string aux2 = "<Componente2><Operador><Componente2>";
			aux.replace(pos, aux2.length(), "<Componente2>");
			v.push_back(aux);
		}

		while (true) {
			size_t pos = aux.find("(<Componente2>)");
			if(pos == string::npos) {break;}
			aux.replace(pos, 15, "<Componente3>");
			v.push_back(aux);
		}

		if(aux3 == aux) {
			break;
		}

	}
    
    while (true) {
		size_t pos2 = aux.find("<Componente2>");
		if(pos2 == string::npos) {break;}
		aux.replace(pos2, 13, "<Componente1>");
		v.push_back(aux);
	}

    while (true) {
		size_t pos2 = aux.find("<Componente1>=<Componente1>");
		if(pos2 == string::npos) {break;}
		aux.replace(pos2, 27, "<Componente1>");
		v.push_back(aux);
	}




	for(int i = v.size()-1; i >= 0; i--) {
		cout << v.at(i) << (char)26 << endl;
	}

}