#include <iostream>

using namespace std;

/* 1.
Pretende-se desenvolver um programa para processar os nomes de um conjunto de pessoas contidos num ficheiro de
texto, guardando os resultados do processamento noutro ficheiro de texto. O processamento consiste em simplificar o
nome original de cada pessoa, de modo a que o nome simplificado tenha apenas a primeira e a �ltima palavra (se
existente) do nome original. Em ambos os ficheiros, cada nome ocupa uma linha de texto (ver exemplo abaixo).
*/

/* 1.a)
Considerando que lhe � fornecida uma fun��o void simplify(const string &name, string &sName) que
converte um nome original, name, num nome simplificado, sName, escreva o c�digo completo de um programa que
faz o seguinte:

- abre o ficheiro people1.txt para leitura e o ficheiro people2.txt para escrita; o primeiro cont�m os nomes
originais; no segundo ser�o guardados os nomes simplificados; se n�o for poss�vel abrir com sucesso o ficheiro
people1.txt o programa deve escrever a mensagem "people1.txt not found" na sa�da de erro padr�o e terminar
imediatamente com um exit code igual a 1; considere que o ficheiro people2.txt � sempre criado com sucesso;

- l� o nome de cada pessoa contido no ficheiro people1.txt, simplifica o nome, usando a fun��o simplify, e
escreve o nome simplificado no ficheiro people2.txt.
NOTAS: 1) Indique as header files a incluir; 2) N�o implemente ainda a fun��o simplify.

Exemplo de conte�do do ficheiro people1.txt:
Franclim da Horta e Jardim
Maria
Salvador Socorro
Caio Passos Dias Aguiar Mota
...

Exemplo de conte�do do ficheiro people2.txt:
Franclim Jardim
Maria
Salvador Socorro
Caio Mota
...
*/

#include <vector>
#include <string>
#include <fstream>

void simplify(const string& name, string& sName);

#include <algorithm>

int main() // exercicio 1.a)
{
	ifstream file1;
	ofstream file2;
	string line;

	vector<string> sNamesVec;

	file1.open("people1.txt");
	if (file1.is_open()) {
		while (getline(file1, line))
		{
			simplify(line, line);
			sNamesVec.push_back(line);
		}
		file1.close();

		// para escrever por ordem alfabetica: (alinea c)
		// sort(sNamesVec.begin(), sNamesVec.end());

		file2.open("people2.txt");
		for (int i = 0; i < sNamesVec.size(); i++)
		{
			file2 << sNamesVec[i] << endl;
		}
		file2.close();
	}
	else
	{
		cerr << "people1.txt not found";
		return 1;
	}
	return 0;
}

/* 1.b)
Escreva o c�digo da fun��o simplify cujo prot�tipo foi definido na quest�o anterior. Considere que o nome
original pode ter um n�mero de palavras vari�vel, em particular, apenas uma palavra (ex: Maria) e n�o tem espa�os
antes da primeira nem depois da �ltima palavra.
*/

#include <sstream>

void simplify(const string& name, string& sName)
{
	stringstream fullName;
	string word;
	
	fullName << name;

	vector<string> nameVec;

	while (fullName >> word)
	{
		nameVec.push_back(word);
	}

	if (nameVec.size() > 1)
	{
		sName = nameVec[0] + " " + nameVec[nameVec.size() - 1];
	}
	else
	{
		sName = nameVec[0];
	}
}