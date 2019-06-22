			
				TURMA 1
				GRUPO 10
	
		Gon�alo Andr� Carneiro Teixeira 	up201806562
		Tiago Andr� Macedo Pinto		up201808907


	------	PROJETO 2 - Ag�ncia de Viagens �NiceHolidays� ------


	Classes:
		- Address 	(moradas)
		- Date 		(datas)
		- Client	(estrutura de informa��o de cada cliente)
		- Pack		(estrutura de informa��o de cada pacote)
		- Locations 	(estrutura para lidar com os locais referentes a cada pacote)
		- ManageClients	(gerir as informa��es dos clientes)
		- ManagePacks	(gerir as informa��es dos pacotes)
		- ProcessData 	(processar as informa��es de clients e pacotes)
		- Menu		(menus do programa)
		- Agency	(carregar informa��es acerca da ag�ncia)

	Erros:
		- Erro 1:	N�o foi poss�vel carregar o ficheiro da agencia
		- Erro 2:	N�o foi poss�vel carregar o ficheiro dos clientes
		- Erro 3: 	N�o foi poss�vel carregar o ficheiro dos pacotes

	Funcionalidades:
		
		Funcionalidades a Implementar
	
		A parte da aplica��o que deve implementar neste trabalho inclui as seguintes funcionalidades:
		
			1. Ler e guardar a informa��o da ag�ncia, dos clientes e dos pacotes tur�sticos armazenada em
		ficheiros.
			2. Gerir os clientes e pacotes tur�sticos: criar, alterar e remover um cliente ou um pacote tur�stico.
			3. Gerar e visualizar de modo formatado a informa��o de um cliente especificado.
			4. Gerar e visualizar de modo formatado a informa��o de todos os clientes da ag�ncia.
			5. Gerar e visualizar de modo formatado os pacotes tur�sticos dispon�veis (todos, todos relativos a
		um destino espec�fico, todos entre duas datas, todos os relativos a um destino espec�fico e entre
		duas datas).
			6. Gerar e visualizar de modo formatado os pacotes tur�sticos vendidos (a um cliente espec�fico, a
		todos os clientes).
			7. Efetuar a compra de um pacote tur�stico por um cliente.
			8. Calcular e visualizar o n�mero e o valor total de pacotes vendidos.
			9. Obter o nome dos N locais mais visitados (um pacote pode incluir visitas a v�rios locais), ordenados
		por ordem decrescente do n�mero de visitas ( = n�mero de pacotes vendidos que passam por esse
		local).
			10. Gerar uma listagem de todos os clientes na qual se indica, para cada cliente, um dos pacotes em
		que seja visitado um dos N locais mais visitados (ver ponto 9) que ele ainda n�o visitou.
	
		------------------------------------------------------------------------------------------------------------------

		REPORT

			1. Objetivo cumprido - A informa��o � lida e guardada em mem�ria. No fim, caso existam altera��es pendentes a serem guardadas em ficheiros,
		o utilizador � questionado para guardar ou n�o as altera��es feitas;
			2. Objetivo cumprido - O software � capaz de alterar/criar/remover os dados de um cliente ou um pacote tur�stico,
		fazendo uma verifica��o a nivel interno e externo da validade dos dados inseridos pelo utilizador.
			3. Objetivo cumprido - O utilizidador tem uma unica op��o para a visualiza��o de clientes, estes s�o apresentados
  		sob forma de tabela e de seguida pergunta-se ao utilizador se pretende visualizar um cliente em especifico, em caso afirmativo
		� pedido o VATnumber (NIF) do cliente pretendido, s�o apresentados os dados do cliente formatados, com op��o para altera��o
		ou remo��o do cliente em quest�o.
			4. Objetivo cumprido - Todos os clientes da ag�ncia s�o apresentados sob a forma de uma tabela.
			5. Objetivo cumprido - Depois de validados os dados inseridos pelo utilizador, os pacotes s�o apresentados sob a forma de tabela.
			6. Objetivo cumprido.
			7. Objetivo cumprido - � apresentada uma tabela com todos os clientes, o utilizador insere o NIF do cliente prentedido,
		e de seguida � apresentada uma tabela com os pacotes disponiveis para esse cliente, tendo em conta o agregado familiar (assumindo que o
		cliente compra um pacote para cada membro do seu agregado familiar), de seguida o pacote � comprado e os dados s�o atualizados.
			8. Objetivo cumprido - � apresentada na consola a informa��o acerca do numero de pacotes vendidos, no total, e o total de receitas
		com a venda de pacotes.
			9. Objetivo cumprido - � pedido ao utilizador que digite um numero N para calcular o tamanho da tabela a apresentar com os
		N destinos mais comprados.
		       10. Quando s�o apresentados os N destinos mais visitados, de seguida � sugerido ao utilizador que digite um ID de algum dos pacotes
		referidos para saber que clientes ainda n�o compraram um pacote relativo aquele destino.

