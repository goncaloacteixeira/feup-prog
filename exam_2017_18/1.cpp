#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

//1.a) ) A fun��o toUpperStr() converte todas as letras da string, s, que recebe como par�metro, para mai�sculas. O resultado da
//convers�o deve ser guardado na mesma string.Complete o prot�tipo e escreva o c�digo desta fun��o

void toUpperStr(string& s)
{
	for (int i = 0; i < s.length(); i++)
	{
		s[i] = toupper(s[i]);
	}
}

/* 1.b)
A fun��o transformLine() recebe como par�metro uma string, s, constitu�da por letras, espa�os e outros carateres e retorna
uma string constitu�da apenas por letras mai�sculas e espa�os, substituindo os carateres que n�o s�o letras nem espa�os pelo
car�ter espa�o, '  '. Complete o prot�tipo e escreva o c�digo desta fun��o. A string recebida como par�metro n�o ser� modificada.
Nota: para fazer a convers�o para mai�sculas deve usar a fun��o toUpperStr(), da al�nea anterior.
Exemplo: se a string s for "  A very, very short sentence!" a string retornada dever� ser "  A VERY  VERY SHORT SENTENCE "
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
A fun��o decomposeLine() recebe como par�metro uma linha de texto, line (uma string), e devolve atrav�s de outro
par�metro, words (um vector<string>), as palavras constituintes dessa linha de texto. Esta fun��o deve come�ar por invocar
transformLine() para substituir por espa�os todos os carateres da linha de texto que n�o sejam letras nem espa�os. Complete o
prot�tipo e escreva o c�digo daquela fun��o.   Nota: pode haver mais do que um espa�o entre palavras (ver exemplo da al�nea
anterior).   Sugest�o: recorra a uma stringstream para fazer a decomposi��o.
Exemplo: o vetor resultante da decomposi��o da string do exemplo ser� {"A", "VERY", "VERY", "SHORT","SENTENCE"}.
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
Escreva o c�digo de um programa que, usando a fun��o decomposeLine(), gera uma lista com todas as palavras contidas no
ficheiro "text.txt", guardado na pasta "C:\docs", e grava as palavras resultantes no ficheiro "words.txt", na pasta atual. As palavras
resultantes devem ser escritas por ordem alfab�tica, uma palavra por cada linha do ficheiro. Notas: 1) omita os ficheiros de
inclus�o; 2) considere que � sempre poss�vel abrir/ler/escrever os ficheiros com sucesso; 3) se houver palavras repetidas, elas
dever�o ser mantidas na lista de palavras resultantes; 4) n�o repita o c�digo das fun��es descritas nas al�neas anteriores; indique
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
Indique a(s) altera��o(�es) a introduzir no programa da al�nea anterior de modo que, na lista de palavras, n�o surjam
palavras repetidas.
*/

// no decomposeLine podemos fazer a seguinte altera��o:
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
