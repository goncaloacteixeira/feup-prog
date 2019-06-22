# PROJETO 2 - Agência de Viagens “NiceHolidays”	
				
				TURMA 1
				GRUPO 10
	
		Gonçalo André Carneiro Teixeira 	up201806562
		Tiago André Macedo Pinto		up201808907
---------------------------------
**Descrição do Projeto**

	Classes:
		- Address 	(moradas)
		- Date 		(datas)
		- Client	(estrutura de informação de cada cliente)
		- Pack		(estrutura de informação de cada pacote)
		- Locations 	(estrutura para lidar com os locais referentes a cada pacote)
		- ManageClients	(gerir as informações dos clientes)
		- ManagePacks	(gerir as informações dos pacotes)
		- ProcessData 	(processar as informações de clients e pacotes)
		- Menu		(menus do programa)
		- Agency	(carregar informações acerca da agência)

	Erros:
		- Erro 1:	Não foi possível carregar o ficheiro da agencia
		- Erro 2:	Não foi possível carregar o ficheiro dos clientes
		- Erro 3: 	Não foi possível carregar o ficheiro dos pacotes

	Funcionalidades:
		
		Funcionalidades a Implementar
	
		A parte da aplicação que deve implementar neste trabalho inclui as seguintes funcionalidades:
		
			1. Ler e guardar a informação da agência, dos clientes e dos pacotes turísticos armazenada em
		ficheiros.
			2. Gerir os clientes e pacotes turísticos: criar, alterar e remover um cliente ou um pacote turístico.
			3. Gerar e visualizar de modo formatado a informação de um cliente especificado.
			4. Gerar e visualizar de modo formatado a informação de todos os clientes da agência.
			5. Gerar e visualizar de modo formatado os pacotes turísticos disponíveis (todos, todos relativos a
		um destino específico, todos entre duas datas, todos os relativos a um destino específico e entre
		duas datas).
			6. Gerar e visualizar de modo formatado os pacotes turísticos vendidos (a um cliente específico, a
		todos os clientes).
			7. Efetuar a compra de um pacote turístico por um cliente.
			8. Calcular e visualizar o número e o valor total de pacotes vendidos.
			9. Obter o nome dos N locais mais visitados (um pacote pode incluir visitas a vários locais), ordenados
		por ordem decrescente do número de visitas ( = número de pacotes vendidos que passam por esse
		local).
			10. Gerar uma listagem de todos os clientes na qual se indica, para cada cliente, um dos pacotes em
		que seja visitado um dos N locais mais visitados (ver ponto 9) que ele ainda não visitou.

------------------------------------------------------------------------------------------------------------------

**REPORT**

			1. Objetivo cumprido - A informação é lida e guardada em memória. No fim, caso existam alterações pendentes a serem guardadas em ficheiros,
		o utilizador é questionado para guardar ou não as alterações feitas;
			2. Objetivo cumprido - O software é capaz de alterar/criar/remover os dados de um cliente ou um pacote turístico,
		fazendo uma verificação a nivel interno e externo da validade dos dados inseridos pelo utilizador.
			3. Objetivo cumprido - O utilizidador tem uma unica opção para a visualização de clientes, estes são apresentados
  		sob forma de tabela e de seguida pergunta-se ao utilizador se pretende visualizar um cliente em especifico, em caso afirmativo
		é pedido o VATnumber (NIF) do cliente pretendido, são apresentados os dados do cliente formatados, com opção para alteração
		ou remoção do cliente em questão.
			4. Objetivo cumprido - Todos os clientes da agência são apresentados sob a forma de uma tabela.
			5. Objetivo cumprido - Depois de validados os dados inseridos pelo utilizador, os pacotes são apresentados sob a forma de tabela.
			6. Objetivo cumprido.
			7. Objetivo cumprido - É apresentada uma tabela com todos os clientes, o utilizador insere o NIF do cliente prentedido,
		e de seguida é apresentada uma tabela com os pacotes disponiveis para esse cliente, tendo em conta o agregado familiar (assumindo que o
		cliente compra um pacote para cada membro do seu agregado familiar), de seguida o pacote é comprado e os dados são atualizados.
			8. Objetivo cumprido - É apresentada na consola a informação acerca do numero de pacotes vendidos, no total, e o total de receitas
		com a venda de pacotes.
			9. Objetivo cumprido - É pedido ao utilizador que digite um numero N para calcular o tamanho da tabela a apresentar com os
		N destinos mais comprados.
		       10. Quando são apresentados os N destinos mais visitados, de seguida é sugerido ao utilizador que digite um ID de algum dos pacotes
		referidos para saber que clientes ainda não compraram um pacote relativo aquele destino.

