
/*
** Teste 2...
*/

def entry {
	say("Hello World.\n")
	
	// Realiza soma de dois inteiros...
	resultado = soma(10, 20)
	say("Resultado da soma: ". resultado ."\n")
	
	say("EOF.\n")
}

/* Soma dois valores */
def soma (v1, v2) { 
	ret v1 + v2 // Retorna dados.
}
