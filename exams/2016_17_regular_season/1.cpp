#include <iostream>

using namespace std;

/* 1.
Pretende-se desenvolver um programa para processar os nomes de um conjunto de pessoas contidos num ficheiro de
texto, guardando os resultados do processamento noutro ficheiro de texto. O processamento consiste em simplificar o
nome original de cada pessoa, de modo a que o nome simplificado tenha apenas a primeira e a última palavra (se
existente) do nome original. Em ambos os ficheiros, cada nome ocupa uma linha de texto (ver exemplo abaixo).
*/

/* 1.a)
Considerando que lhe é fornecida uma função void simplify(const string &name, string &sName) que
converte um nome original, name, num nome simplificado, sName, escreva o código completo de um programa que
faz o seguinte:

- abre o ficheiro people1.txt para leitura e o ficheiro people2.txt para escrita; o primeiro contém os nomes
originais; no segundo serão guardados os nomes simplificados; se não for possível abrir com sucesso o ficheiro
people1.txt o programa deve escrever a mensagem "people1.txt not found" na saída de erro padrão e terminar
imediatamente com um exit code igual a 1; considere que o ficheiro people2.txt é sempre criado com sucesso;

- lê o nome de cada pessoa contido no ficheiro people1.txt, simplifica o nome, usando a função simplify, e
escreve o nome simplificado no ficheiro people2.txt.
NOTAS: 1) Indique as header files a incluir; 2) Não implemente ainda a função simplify.

Exemplo de conteúdo do ficheiro people1.txt:
Franclim da Horta e Jardim
Maria
Salvador Socorro
Caio Passos Dias Aguiar Mota
...

Exemplo de conteúdo do ficheiro people2.txt:
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
Escreva o código da função simplify cujo protótipo foi definido na questão anterior. Considere que o nome
original pode ter um número de palavras variável, em particular, apenas uma palavra (ex: Maria) e não tem espaços
antes da primeira nem depois da última palavra.
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