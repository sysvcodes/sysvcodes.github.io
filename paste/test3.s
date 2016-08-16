
// Aqui neste código ficam as características de uso geral da Short Syntax, sendo essas suportadas em todas as áreas de desenvolvimento suportadas.
// Toda sintaxe descrita neste arquivo de código é suportada em todas as áreas de desenvolvimento também suportadas até então.
// Manipulação da memória necessária apenas se a linguagem final requerir.
/*
** Sintaxe utilizada para desenvolvimento: Web, Desktop e Mobile.
*/

// Ponto de inicialização do arquivo de código.
def entry {
	
	/*
	** Variáveis. 
	*/
	
	// Variáveis simples: números e textos.
	numeroA = 10, numeroB = 20, numeroC = 30
	numeroD = 40
	numeroE = 50
	
	textoA = "Meu texto 1", textoB = "Meu texto 2"
	textoC = "Meu texto 3"
	textoD = "Meu texto 4"
	
	// Uso de constantes.
	valorA = null, valorB = null
	valorC = true, valorD = false
	
	// Chamada a funções
	valorE = alloc( 256 ), valorD = alloc(1024)
	valorF = callMeFunction(), valorG = callMeFunction (   )
	
	/* 
	** Condicionais. 
	*/
	
	// Equivalentes aos coandos: if, else if e else.
	if (!check(textoA))
		say("textoA: null\n")
	elif ((content = getStringContent(textoB)) != null && numeroC == 30)
		say("content: {content}\n")
	elif  
		say("default option...\n")
	
	// Concatenação de comandos.
	if (check(textoA)) 
		if (!check(textoA))
			say("textoA: null\n")
		elif ((content = getStringContent(textoB)) != null && numeroC == 30) {
			if ((result = mysqlConnect("host.com", 3306, "username", "password")) != false) {
				say("Connection success!\n")
				mysqlClose(result)
			} elif
				say("Connection failed.\n")
		} elif  
			say("default option...\n")
	
	/* 
	** Repetições. 
	*/
	
	for ( a,b=0; b<5; b++,a++ ) {
		say("Valor (a): {a}, (b): {b}\n")
		if (b > 5) 
			break
		elif
			continue
	}
	
	for ( a = callMeFunction(),b=0; b<5; b++) 
		say("Valor (a): {a}, (b): {b}\n")
	
	for ( a = "String here!", c=callMeFunction(),b=0; b<5; b++) 
		say("Valor (a): {a}, (b): {b}, (c): {c}\n")
	
	for (a=0; a<1; a++) // Executa condição antes da execução do bloco de código.
		say("Valor: {a}\n")
	
	do (a=0; a<1; a++)  // Executa condição após a execução do bloco de código.
		say("Valor: {a}\n")
	
	// Exemplos de loop infinito.
	a = 0
	do {
		if (a >= 10)
			break
		say("Loop index: {a}\n")
		a++
	}
	
	a = 0
	for {
		if (a >= 10)
			break
		say("Loop index: {a}\n")
		a++
	}
	
	// Concatenação de comandos.
	for (a=0; a<5; a++)
		for (b=0; b<5; b++)
			say("a: {a}, b: {b}\n")
	
	for (a=0; a<10; a++) {
		for (b=0; b<5; b++)
			say("a: {a}, b: {b}\n")
		if (a > 5)
			break
	}
	
	/*
	** Chamada a funções. 
	*/
	testFunction("tesando ", "a ", "sintaxe...\n")
	say("Valor: {numeroA}\n") // Obs: concatenação de variáveis em strings.
	
	/*
	** Operações.
	*/
	a1 = 10, a2 = 20, a3 = 0, a4 = 0, a5 = 10, a6 = 40
	
	a3 = a1 + a2
	say("a1 + a2 = {a3}\n")
	
	a4 = ( (( a5+a6 )*( a6*a1 )) + (( a1+a2 )*( a2*a1 )) ) + 100
	say("a4 = {a4}\n")
	
	a1++, a1--
	a1++
	a2++
	a2--
	a1 += 10
	a1 - = 10
	a1 * = 10
	a1 / = 10
	
	a1 >> a2
	
	/*
	** Utilização recomendável ao gerar códigos para linguagens C e ASM. Equivalente ao comando: return. 
	*/
	ret 0 
}

/*
** Funções. O uso do comando: ret; não é obrigatório.
*/

def callMeFunction () {
	ret "String here!"
}

def testFunction ( lal, lele, lelo ) { say("{lal}, {lele}, {lelo}") }

// Exemplo 1
def functionZero{/* Code here... */}

// Exemplo 2
def functionOne 
{ /* Code here... */ }

// Exemplo 3
def functionTwo (valor1, valor2) {
     ret valor1 + valor2
}

// Exemplo 4
def
functionThree 
(param1, param2, paramN) {
     // Code here...
}

// Exemplo 5
def functionFour
(valora, 
valorb)
{
     // Code here...
}

// Passagem de parâmetros para função.
def functionHere (valor1, valor2) {
     valor3 = valor1 + valor2
     ret valor3 // Retorna resultado da soma.
}

// Teste comentário 1
// Teste comentário 2
// Teste comentário 3
// Teste comentário 4

/* lalalala teste comentário ...
** lalalala teste comentário ...
** lalalala teste comentário ... **/

/* lalalala teste comentário ...
		lalalala teste comentário ...
		
	lalalala teste comentário ...
	
	lalalala teste comentário ... *
	/
*/

// lalala teste 

def funcUnkn (paramN) {
	if (!paramN)
		ret 0
	ret 1
}
