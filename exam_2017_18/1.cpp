#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

//1.a) ) A função toUpperStr() converte todas as letras da string, s, que recebe como parâmetro, para maiúsculas. O resultado da
//conversão deve ser guardado na mesma string.Complete o protótipo e escreva o código desta função

void toUpperStr(string& s)
{
	for (int i = 0; i < s.length(); i++)
	{
		s[i] = toupper(s[i]);
	}
}

/* 1.b)
A função transformLine() recebe como parâmetro uma string, s, constituída por letras, espaços e outros carateres e retorna
uma string constituída apenas por letras maiúsculas e espaços, substituindo os carateres que não são letras nem espaços pelo
caráter espaço, '  '. Complete o protótipo e escreva o código desta função. A string recebida como parâmetro não será modificada.
Nota: para fazer a conversão para maiúsculas deve usar a função toUpperStr(), da alínea anterior.
Exemplo: se a string s for "  A very, very short sentence!" a string retornada deverá ser "  A VERY  VERY SHORT SENTENCE "
*/

string transformLine(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (!isalpha(s[i]))
		{
			s[i] = ' ';
		}
	}

	toUpperStr(s);
	
	return s;
}

/* 1.c)
A função decomposeLine() recebe como parâmetro uma linha de texto, line (uma string), e devolve através de outro
parâmetro, words (um vector<string>), as palavras constituintes dessa linha de texto. Esta função deve começar por invocar
transformLine() para substituir por espaços todos os carateres da linha de texto que não sejam letras nem espaços. Complete o
protótipo e escreva o código daquela função.   Nota: pode haver mais do que um espaço entre palavras (ver exemplo da alínea
anterior).   Sugestão: recorra a uma stringstream para fazer a decomposição.
Exemplo: o vetor resultante da decomposição da string do exemplo será {"A", "VERY", "VERY", "SHORT","SENTENCE"}.
*/

void decomposeLine(string& line, vector<string>& words)
{
	line = transformLine(line);
	stringstream foo;
	string word;

	foo << line;

	while (foo >> word)
	{
		words.push_back(word);
	}
}

/* 1.d)
Escreva o código de um programa que, usando a função decomposeLine(), gera uma lista com todas as palavras contidas no
ficheiro "text.txt", guardado na pasta "C:\docs", e grava as palavras resultantes no ficheiro "words.txt", na pasta atual. As palavras
resultantes devem ser escritas por ordem alfabética, uma palavra por cada linha do ficheiro. Notas: 1) omita os ficheiros de
inclusão; 2) considere que é sempre possível abrir/ler/escrever os ficheiros com sucesso; 3) se houver palavras repetidas, elas
deverão ser mantidas na lista de palavras resultantes; 4) não repita o código das funções descritas nas alíneas anteriores; indique
apenas onde deveriam ser colocadas, no programa.
*/

void writeToFile()
{
	ifstream file1;
	ofstream file2;

	vector<string> words;

	file1.open("C:\docs\text.txt");
	if (file1.is_open())
	{
		string line;
		while (getline(file1, line))
		{
			decomposeLine(line, words);
		}
		file1.close();
	}
	else cout << "file1 not open";

	sort(words.begin(), words.end());

	file2.open("C:\docs\words.txt");
	if (file2.is_open())
	{
		for (int i = 0; i < words.size(); i++)
		{
			file2 << words[i] << endl;
		}
		file2.close();
	}
	else cout << "file2 not open";
}

/* 1.e)
Indique a(s) alteração(ões) a introduzir no programa da alínea anterior de modo que, na lista de palavras, não surjam
palavras repetidas.
*/

// no decomposeLine podemos fazer a seguinte alteração:
/*
while (foo >> word)
{
	bool ctr = false;

	for (int = 0; i < size(words); i++)
	{
		if (words[i] == word)
		{
			ctr = true;
			break;
		}
	}
	if (!ctr)
		words.push_back(word)
}
*/

int main()
{
	return 0;
}
