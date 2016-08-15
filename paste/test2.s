
/*
** Testando primeiros scripts da Short Syntax language. 14/08/2016 - Coded by SysV.
*/

/*
** Desenvolver:
**   - corrigido - Suporte para abrimento de bloco de código de apenas uma linha, para não ser necessário utilizar chaves sempre.
**   - corrigido - Implementar suporte para definição de múltiplas variáveis na mesma linha separadas por vírgula.
**   - corrigido - Bug no comando 'ret', ao retornar somas, as variáveis não são formatadas corretamente.
**   - corrigido - Bug nos blocos de comando, formatar corretamente variáveis passadas como argumento.
**   - corrigido - Suporte a concatenação por ponto (como no PHP).
**   - corrigido - Bug ao utilizar variáveis sem inicializa-las no comando for, também ao utilizar múltiplas variáveis, formatar dados corretamente.
**   - corrigido - Bug no comando 'ret' ao utilizar parenteses na atribuição de valor do comando.
**   - corrigido - Bug ao especificar inteiros nos comandos condicionais.
**   - Suporte ao uso de qualquer caractere entre as strings.
**   - Analisar core da linguagem e melhorar os pontos necessários.
*/

def entry {
	
	// Chamada a função e exibe string.
	print("Hello World!!!\n\n")
	
	/*
	** Utilização de variáveis.
	*/
	variavel = null
	variavel = "String here!"      				/* Simples C string. */
	variavel = 100                  			/* Valor inteiro. */
	variavel = funcN()              			/* Armazena retorno da função na variável. */
	print(variavel)								/* Exibe resultado. */
	retFuncA = funcA("\nTeste\n")
	print(retFuncA)
	
	var1 = 0, var2 = null, var3 = "String here!", var4 = funcN(), var5 = funcA("\nTeste\n"), var6= 0, var7= 0, var8 = 100
	var9 = 20, var10 = null
	var9 = 20, var10 = 9
	var11 = null
	var12 = 0
	
	print("var1: ". var1 .", var2: ". var2 .", var3: ". var3 .", var4: ". var4 .", var5: ". var5 .", var6: ". var6 ."\n")
	print("var7: ". var7 .", var8: ". var8 .", var9: ". var9 .", var10: ". var10)
	print("\n")
	
	/*
	** Utilização de comandos condicionais.
	*/
	
	var1 = 10
	var2 = 10
	
	if (var1 > var2) 
		print("Var1 maior que Var2.\n")
	elif (var2 > var1) {
		print("Var2 maior que Var1.\n")
		print("Var2 maior que Var1.\n")
	} elif {
		print("Nenhuma opcao.\n")
		if (var2 == var1) {
			print("Valores iguais!\n")
		}
	}
	
	var = 17
	var2 = 10
	
	if (var > 1 && var < 5)
		print("var > 1\n")
	elif (var > 5 && var < 10) {
		print("var > 5 e ")
		print("var < 10\n")
	} elif {
		if (var2 == 10)
			if (var2 > 5 && var > 10) {
				var3 = 0
				for {
					if (var3 > 10) {
						break
					} elif {
						print ("Var3:". var3 ."\n")
						var3++
						continue
					}
				}
			}
	}
	
	var = 0
	for {
		if (var++ >= 7)
			break
		print("Valor: ". var ."\n")
	}
	
	/*
	** Utilização de comandos para repetições.
	*/
	
	var1 = 0
	var2 = 10 
	
	for {
		if (var1 > var2 ) {
			print("\nLoop finalizado!\n")
			break
		} elif {
			print(var1)
			print(" ")
		}
		var1++
		continue
	}
	
	var3 = 20
	for (var1=0, var2=0; var1 < 22; var1++, var2++) {
		print(var1)
		if (var1 > var3) {
			print("\nVar1 maior que 10.")
		}
	}
	print("\n")
	
	// for (a=1,b=2,c=0,d=0; d<10; a++,b++,c++,d++)
	// for (a=0,b=3,c=0,d=0; d<10 && b < 7; a++,b++,c++,d++)
	for (a=0,b=3,c=0,d=0; 
			d<10 && b < 7;
			a++,b++,c++,d++)
		print("a:".a." b:".b." c:".c." d:".d ."\n")
	
	/*
	** Operações...
	*/
	
	teste = 0
	teste++
	teste = teste + 100
	teste = teste + 100
	teste = teste * teste
	teste--
	teste++
	teste--
	teste++ 
	teste--
	teste += 10
	teste *= 10
	teste /= 10
	teste -= 10
	teste++
	teste--
	
	print("Valor: ". teste)
	print("\n")
	teste = 0
	print("Valor:". teste)
	print("\n")
	
	
	/*
	** Funções
	*/
	
	ret1 = func1("\nret of func1")
	print(ret1)
	
	ret2 = func2("\nret of func2")
	print(ret2)
	
	valor = "\nfuncTresss "
	ret3 = func3(valor, "lalala \n")
	ret3 = func3("lalala \n", valor)
	print ("Valor: ". ret3)
	
	valor = 10
	response = myPrint("lala", "lolo", valor)
	response = myPrint("lala", valor, "lelele")
	print (response ."\n")
	response = myPrint(valor, "lilili", "lelele")
	print( "response: ". response )
	
	valor = 10
	ret3 = func3("\nret of ", "llele")
	ret3 = func3("\nret of ", valor)
	print(ret3 ."\n")
	
	response = func3 ("\nret of ", valor)
	response .= "\n\n" // Concatena...
	print ( response ) /* Exibe resultado... */
	print ( "Response: ". response ) /* Exibe resultado... */
	
	funcT(0)
	
	print("\n")
}

def myPrint (param1, param2, param3) {
	ret param1 . param2 . param3
}

def funcT (x) { 
	ret x
}

def funcZ (a,b,c,d) { 
	ret (a + b) * (c + d)
}

def funcN { // function funcN...
	ret "resultado funcN"
}

def func1 (param) {
	ret param
}

def func2 (param) {
	final = param
	ret final
}

def func3 (param1, param2) {
	result = param1 . param2
	ret result
}

def func4(param1, 	param2,param3){
	ret param1 . param2 . param3
}

def funcA (valor) { /* function funcA... */
	ret valor
}

// Passagem de parâmetros para função.
def functionHere2 (valor1, valor2) {
     // valor3 = valor1 + valor2
     ret valor1 + valor2 + valor1 + valor3
     // ret valor3 // Retorna resultado da soma.
}
// Passagem de parâmetros para função.
def functionHere3 (a,b,c,d,e,f,g,h,i,j,k,l,m,n,o) {
     // valor3 = valor1 + valor2
     ret  ( a + ( ( a + b ) * c ) + ( e * 10 ) + ( 100 * 100 )) + (( k * l ) * ( m + n ))
     // ret valor3 // Retorna resultado da soma.
}

// EOF.
