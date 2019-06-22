#include "e3.h"

/* 3.a)
Complete a declara��o da classe, escrevendo o prot�tipo (apenas o prot�tipo) do m�todo getPixel que retorna
o valor de um pixel da imagem cujas coordenadas (linha e coluna) recebe como par�metros.
*/

// int getPixel(size_t lin, size_t col) const;

/* 3.b)
Escreva o c�digo do m�todo getRegion(size_t lin, size_t col, size_t nLins, size_t nCols) que
retorna uma (sub-)imagem que representa uma regi�o/por��o retangular da imagem. Os par�metros lin e col s�o as
coordenadas (linha e coluna) do canto superior esquerdo da regi�o selecionada; nLins e nCols s�o as dimens�es
(n�mero de linhas e n�mero de colunas) dessa regi�o. Considere que todos os par�metros tomam valores v�lidos.
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
Pretende-se desenvolver um programa que guarde, numa estrutura de dados, em mem�ria principal, um
conjunto de imagens organizadas por datas, permitindo aceder de forma eficiente �s imagens adquiridas numa
determinada data. A uma data podem estar associadas v�rias imagens. As imagens s�o representadas por objetos da
classe Image; as datas s�o representadas por objetos da classe Date (ver quest�o 2). Declare a estrutura de dados
que usaria para representar a referida informa��o.
*/

/* resposta do Eduardo
map<Date, vector<Image>> ou multimap<Date, Image>

Esta estrutura de dados permite que a cada data possam corresponder v�rias imagens e que se possa aceder facilmente
a uma determinada imagem a partir da data correspondente.
*/

/* 3.d)
Escreva a parte do c�digo do referido programa que, usando as classes Date e Image e a estrutura de dados
escolhida em c), faz o seguinte: 1) l� uma data; 2) l� do teclado, um por um, os nomes dos ficheiros que cont�m as
imagens adquiridas nessa data (as entradas terminam quando for lida uma string vazia) e 3) l� as imagens contidas
nos ficheiros indicados e insere-as na referida estrutura de dados, associando-as � data lida. Use os m�todos declarados
nas classes Date e Image; considere que est�o todos implementados. Considere tamb�m que todas as imagens s�o
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
Na classe Image declarada anteriormente os valores dos pixels s�o n�meros inteiros. Indique as altera��es a
introduzir na declara��o da classe Image de modo e transform�-la numa template class que possa ser usada para
representar imagens com outros tipos de pixeis, por exemplo float, double ou char. Indique apenas as modifica��es.

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