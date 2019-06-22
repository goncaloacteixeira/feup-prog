#include "e3.h"

/* 3.a)
Complete a declaração da classe, escrevendo o protótipo (apenas o protótipo) do método getPixel que retorna
o valor de um pixel da imagem cujas coordenadas (linha e coluna) recebe como parâmetros.
*/

// int getPixel(size_t lin, size_t col) const;

/* 3.b)
Escreva o código do método getRegion(size_t lin, size_t col, size_t nLins, size_t nCols) que
retorna uma (sub-)imagem que representa uma região/porção retangular da imagem. Os parâmetros lin e col são as
coordenadas (linha e coluna) do canto superior esquerdo da região selecionada; nLins e nCols são as dimensões
(número de linhas e número de colunas) dessa região. Considere que todos os parâmetros tomam valores válidos.
*/

Image Image::getRegion(size_t lin, size_t col, size_t nLins, size_t nCols) const
{
	Image result(nLins, nCols, 0);
	
	for (int y = 0; y < nCols) {
		for (int x = 0; x < nLins; x++)
		{
			result.setPixel(x, y, img[lin][col]);
		}
	}
	return result;
}

/* 3.c)
Pretende-se desenvolver um programa que guarde, numa estrutura de dados, em memória principal, um
conjunto de imagens organizadas por datas, permitindo aceder de forma eficiente às imagens adquiridas numa
determinada data. A uma data podem estar associadas várias imagens. As imagens são representadas por objetos da
classe Image; as datas são representadas por objetos da classe Date (ver questão 2). Declare a estrutura de dados
que usaria para representar a referida informação.
*/

/* resposta do Eduardo
map<Date, vector<Image>> ou multimap<Date, Image>

Esta estrutura de dados permite que a cada data possam corresponder várias imagens e que se possa aceder facilmente
a uma determinada imagem a partir da data correspondente.
*/

/* 3.d)
Escreva a parte do código do referido programa que, usando as classes Date e Image e a estrutura de dados
escolhida em c), faz o seguinte: 1) lê uma data; 2) lê do teclado, um por um, os nomes dos ficheiros que contêm as
imagens adquiridas nessa data (as entradas terminam quando for lida uma string vazia) e 3) lê as imagens contidas
nos ficheiros indicados e insere-as na referida estrutura de dados, associando-as à data lida. Use os métodos declarados
nas classes Date e Image; considere que estão todos implementados. Considere também que todas as imagens são
lidas com sucesso.
*/

int main() // reposta do Eduardo
{
	map<Date, vector<Image>> data;
	Date UserDate;
	string filename;
	vector<Image> images;

	cin >> UserDate;

	while (cin >> filename && filename != "") {
		Image Image;

		Image.read(filename);
		images.push_back(Image);
	}

	data.insert(pair<Date, vector<Image>>(UserDate, images));

	return 0;
}

/* 3.e)
Na classe Image declarada anteriormente os valores dos pixels são números inteiros. Indique as alterações a
introduzir na declaração da classe Image de modo e transformá-la numa template class que possa ser usada para
representar imagens com outros tipos de pixeis, por exemplo float, double ou char. Indique apenas as modificações.

resposta do Eduardo
*/

template <class T>
class Image {
public:
	void setPixel(size_t lin, size_t col, T pixVal);
	//...
private:
	vector <vector<T>> img; // image representation
	//...
};