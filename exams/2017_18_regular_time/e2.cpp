#include "e2.h"
#include <iostream>

using namespace std;

/* 2.b)
Implemente o construtor da classe Board, o qual deve preencher todos os elementos do atributo board com o valor ‐1 que
indica que a célula respetiva corresponde a "mar livre" (isto é, sem "navios").
*/



Board::Board(size_t numLines, size_t numColumns)
{
	vector<int> line;

	for (int i = 0; i < numLines; i++)			// por cada linha
	{
		for (int j = 0; i < numColumns; j++)	// por cada coluna escrever um 1, para preencher uma linha inteira
		{
			line.push_back(-1);			
		}
		
		board.push_back(line);					// juntar todas as linhas no vetor privado 'board'
		line.clear();							// reseta o vetor
	}

	this->numLines = numLines;
	this->numColumns = numColumns;
}

/* 2.c)
O método canPutShip(), da classe Board, determina se o "navio" pode ser colocado na posição pos (posição do canto
superior esquerdo do "navio") e na direção dir. Para isso, é necessário verificar que não ultrapassa os limites do tabuleiro e que
todas as células que vai ocupar estão livres (valor = ‐1). Complete o código abaixo apresentado, nas partes assinaladas.   Nota: a
direção do "navio" é indicada por uma das letras maiúsculas seguintes: H (=horizontal) ou V (=vertical).
*/

bool Board::canPutShip(Position pos, char dir, size_t size)
{
	switch (dir)
	{
	case 'H':			// TO DO: test if ship with length 'size' can be put at 'pos', in horizontal direction
		if (pos.col + size - 1 >= board[0].size() || pos.lin >= board.size())	// a posição na coluna + offset (size) - 1 é index da ultima casa ocupada pelo navio, que tem que ser menor ou igual ao tamanho da linha.
		{
			return false;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (board[pos.lin][pos.col + i] != -1)		// retornar falso caso a casa ja esteja ocupada
				{
					return false;
				}
			}
		}
		break;
	case 'V':			// TO DO, just this line: test if ship ... can be put in vertical direction
		if (pos.lin + size - 1 >= board.size() || pos.col >= board[0].size())
		{
			return false;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (board[pos.lin + 1][pos.col] != -1)
				{
					return false;
				}
			}
		}
		break;
	}
	return true;
}

/* 2.d)
O método putShip() tenta colocar no tabuleiro (modificando os atributos board e ships) o "navio", s, que recebe como
parâmetro. A posição onde se pretende colocar o navio é a que for retornada pelo método pos() de Ship. Escreva o código deste
método, o qual retorna true ou false, consoante tenha sido possível ou não colocar o "navio" no tabuleiro. Nota: use o método
canPutShip(), mesmo que não o tenha implementado, para verificar se o "navio" pode ou não ser colocado no tabuleiro.
*/

bool Board::putShip(const Ship& s)
{
	if (canPutShip(s.pos(), s.dir(), s.size()))
	{
		switch (s.dir())
		{
		case 'H':
			for (int i = 0; i < s.size(); i++)
			{
				board[s.pos().lin][s.pos().col + 1] = s.id();
			}
			break;
		case 'V':
			for (int i = 0; i < s.size(); i++)
			{
				board[s.pos().lin + 1][s.pos().col] = s.id();
			}
			break;
		}
		return true;
	}
	return false;
}


int main()
{
    // 2.e)
	/*
	Escreva um pedaço de código que cria um tabuleiro com 10x20 células, lê do teclado os dados de um "navio"(identificador,
	símbolo, posição, direção e tamanho) e tenta colocar esse "navio" no tabuleiro. Se isso não for possível, lança um exceção,
	arremessando a string "Can't put ship!".Nota: considere que todos os valores lidos para os atributos do "navio" são válidos, isto é,
	do tipo correto.
	*/

	Board board(10, 20);
	//Ship(unsigned int identifier, char symbol,
	//	Position position, char direction,
	//	size_t size);

	unsigned int id;
	char symbol;
	Position pos;
	char dir;
	size_t size;

	cout << "ID: ";
	cin >> id;
	cout << "Symbol: ";
	cin >> symbol;
	cout << "Line: ";
	cin >> pos.lin;
	cout << "Column: ";
	cin >> pos.col;
	cout << "Direction: ";
	cin >> dir;
	cout << "Size: ";
	cin >> size;

	Ship ship(id, symbol, pos, dir, size);

	if (!board.putShip(ship))
	{
		throw exception("Can't put ship!");
	}
}
