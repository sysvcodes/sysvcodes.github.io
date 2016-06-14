
// Teste com comentários e funções.

// Testando ...
// comentários ...
//

req io			// say
req windows		// MessageBoxA

		// dados fora das funções sao dado como dados globais.
		
def functionFF (a,b) { c="functionFF"; say c }
		
def entry () {  // entry point
			// Inicialização 
		
	s1 = "str 1", s2 = "str 2"
		s3 	= 	"str 3"
	n1 = 10, n2 = 20
	n3 = 30
	n3 = 40
	s3 = "str 4" /* comentário de 
	multiplas
	linhas... */
	str = "teste"
	
	retz = functionZero
	jret = functionFF s2, n3
	xret = functionTwo s3	  ,   n3 , n2;
	
	xret = 10
	xret = "string n..."
	

	n1 = 50
	xret = "oie"
	
	var1 = 20
	var2 = 10
	vret = functionSix var1, var2
	if (var1 == var2) 					// *** Condições.
		say "Iguais!\n" 
	elif var1 >= var2					// else if
		say "Maior...\n" 
	elif								// else
	{
		say "Nao igual!"
		say "\n"
	}
	
										// *** Repetições
	for {								// Loop infinito.
		if (# > 10)						// & = variável interna.
			break
		say "Valor: " # '\n'
	}
	
	for (a=0; a<5; a++) 				// Uso do for sem chaves...
		say "Valor: " a '\n'
		
	for (a=0; a<5; a++) {				// Uso do for com chaves...
		say "Valor: " a
		say '\n'
	}
	
	for (a=0; a<5; a++) {				// Concatenado...
		say "Valor: " a
		say '\n'
		for (b=0; b<15; b++) {
			say "Valor: " b '\n'
			for
				if # > 10 && b < 15  break		// encerra...
		}
	}
	
	do (var1 == 20) 					// Funcinamento parecido com do while...
		say "do for here!\n"  			// Executa bloco ao menos uma vez...
										// Maniopulando arrays...
	
										// *** Execução de comandos/linhas.
	say "hello "; say "world!"; say '\n';	// Mais de um comando em
										// uma unica linha...
	say "hello "; say "world!"; say '\n'	// ...
	
										// *** Funções.
	say "Called...\n"
	functionOne							// Chamada funções...
	functionTwo "valor 1", "valor 2"	
	functionTwo 'valor 1', 'valor 2'	
	functionThree
	
	ret 10
}

// Outras funções...
def functionZero{str="functionZero";say str}
// def functionOne 
// { say "Hello world!" ; say '\n' }
def functionTwo (valor1, valor2, stra) {
	say "Hello world!\n"
	var = "asas asas"
	var = 100, str2="str2..."
	var = 200
	str = "teste!", lele = "aff"
	str = "teste!"
	str = "teste!"
	str = "teste!"
	str = "teste!"
		
		str = "functionTwo"
	say str

	//ret valor1 + valor2
}

def
functionThree 
(lala, lele, lolo) {
	// MessageBoxA NULL, "Teste!", "Teste!", MB_OK
	// say 'teste!\n'; say 'lala'
	// say '\n'
	str = "functionThree"
	say str
}

// ...
def functionFour
(valora, 
valorb)
	MessageBoxA NULL, "Teste 2!", "Teste 2!", MB_OK
//end		// Fim da função...
	str = "functionFour"
	say str
}

def
functionFive 
(lala, lele) {
	str = "functionFive"
	say str

	//MessageBoxA NULL, "Teste!", "Teste!", MB_OK
}

def functionSix
(valora, 
valorb) {
		str = "functionSix"
	say str

	//MessageBoxA NULL, "Teste 2!", "Teste 2!", MB_OK
}		// Fim da função...

def functionSeven 
{ say "Hello world!" ; say '\n'; say 'lel\n'
	//say ''
 	str = "functionSeven"
	say str
 }
 
/* EOF */
