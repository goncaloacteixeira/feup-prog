# PROJECT 1 - PROG
	
**Funcionalidades a Implementar**
	
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
	
------------------------------------------------------------------------------------------------------------------

**REPORT**

		1. Objetivo cumprido - A informação é lida e guardada em memória: os dados da agência são guardados num struct "Agency"; os dados de cada cliente
	ocupam uma posição num vetor de structs "Client"; os dados dos pacotes são ocupam uma posição num vetor de structs "TravelPack".
		2. Objetivo cumprido - O software é capaz de alterar/criar/remover os dados de um cliente ou um pacote turístico, fazendo uma verificação a nivel interno
	e externo da validade dos dados inseridos pelo utilizador. Imediatamente após essa verificação, caso os dados sejam válidos e aprovados pelo utilizador
	são escritos nos ficheiros.
		3. Objetivo cumprido - O utilizidador identifica o cliente com o NIF e os seus dados são apresentados..
		4. Objetivo cumprido - Todos os clientes da agência são apresentados sob a forma de uma tabela.
		5. Objetivo cumprido - Depois de validados os dados inseridos pelo utilizador, os pacotes são apresentados sob a forma de tabela.
		6. Objetivo cumprido.
		7. Objetivo cumprido - O utilizador insere o NIF do cliente, e de seguida é apresentada uma tabela com os pacotes disponiveis para aquele cliente, tendo
	em conta o agregado familiar (assumindo que o cliente compra um pacote para cada membro do seu agregado familiar), de seguida o pacote é comprado e imediatamente é 
	atualizado o ficheiro, com o novo numero de pacotes disponiveis para aquele ID.
		8. Objetivo cumprido - É apresentada na consola a informação acerca do numero de pacotes vendidos, no total, e o toal de receitas com a venda de pacotes.


			--- Todos os objetivos cumpridos ---
------------------------------------------


**ERROR LIST**
	
	Error 1: Agency file couldn't be found.
	Error 2: Clients file couldn't be found.
	Error 3: Packs file couldn't be found.









