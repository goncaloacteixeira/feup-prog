#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

/* 1
Um ficheiro de texto cont�m as classifica��es de um
exame no formato ilustrado � direita. Cada linha
cont�m o c�digo de um estudante e as classifica��es
que obteve em cada uma das N quest�es do exame.
O valor de N est� gravado na primeira linha do
ficheiro (10, no exemplo apresentado). Considere
que pretende desenvolver um programa para
processar um ficheiro deste tipo.

10
up20141007  -	2.0 1.0 1.0 1.0 1.5 1.5 1.5 2.0 1.0 1.0
ei12903     -	1.7 1.7 1.5 1.8 1.6 1.7 1.3 1.7 1.9 1.2
up20143001  -	1.7 1.7 1.8 2.0 1.6 1.7 1.8 1.5 1.6 1.7
up20132345  -	0.0 1.1 1.9 2.0 2.0 1.2 1.4 1.9 1.7 1.5
ee12105		-	1.4 1.7 1.5 1.6 1.7 1.0 1.5 1.0 1.5 1.4
...

a) [2.5] Escreva o c�digo de uma fun��o que recebe dois par�metros de entrada, uma string, code_grades, contendo
o c�digo e as classifica��es de um estudante (o conte�do de code_grades dever� ser semelhante a uma das linhas do
ficheiro que est�o abaixo da primeira linha), e um inteiro, num_grades, contendo o n�mero de quest�es/
/classifica��es, e retorna, atrav�s dos seus par�metros de sa�da, o c�digo do estudante (uma string, code) e a soma
das suas classifica��es (um double, sum). Nota: considere que code_grades cont�m sempre uma sequ�ncia de valores
v�lidos, no formato ilustrado, e que todos os valores est�o separados por, pelo menos, um espa�o. Sugest�o: use uma
stringstream para decompor code_grades nos seus elementos.
*/

void get_code_sum(const string& code_grades, int num_grades, string& code, double& sum)
{
	stringstream ss;
	ss << code_grades;

	string aux;

	int i = 0;
	while (ss >> aux)
	{
		if (i == 0)
		{
			code = aux;
		}
		if (i > 1)
		{
			sum += stod(aux);
		}
		i++;
	}
}

/* 1.b)
Escreva um programa completo (omita as diretivas #include) que permita processar
um ficheiro de texto, com um conte�do semelhante ao descrito na introdu��o deste problema,
e que produza, como resultado, outro ficheiro de texto contendo a classifica��o total obtida por
cada estudante. O conte�do do ficheiro resultante deve ser semelhante ao apresentado �
direita.

up20141007	-	13.5
ei12903		-	16.1
up20143001	-	17.1
...
Requisitos adicionais do programa:
- a "ra�z" do nome dos ficheiros de entrada e de sa�da deve ser perguntada ao utilizador; o nome do ficheiro de entrada
� obtido acrescentando ".txt" � "ra�z"; o nome do ficheiro de sa�da � obtido acrescentando "_final.txt" � "ra�z"
(exemplo: se a "ra�z" for "grades", o nome do ficheiro de entrada ser� "grades.txt" e o nome do ficheiro de sa�da
ser� "grades_final.txt")
- se a abertura do ficheiro de entrada falhar, o programa deve terminar imediatamente, com c�digo de termina��o
igual a 1;
- use a fun��o definida na al�nea a) para obter a classifica��o total, mas n�o repita aqui o seu c�digo; indique apenas
em que local do programa colocaria o c�digo da fun��o.
*/

#include <fstream>

int main()
{
	string fileName1;
	string fileName2;

	cout << "Ficheiro 1: ";
	cin >> fileName1;

	fileName2 += fileName1 + "_final.txt";
	fileName1 += ".txt";

	ifstream file1(fileName1);
	ofstream file2(fileName2);

	if (file1.is_open())
	{
		string line;
		vector<string> gradesVec;
		int ctr = 0;
		int num_grades;
		while (getline(file1, line))
		{
			if (ctr == 0)
			{
				num_grades = stoi(line);
			}
			else
			{
				gradesVec.push_back(line);
			}
			ctr++;
		}
		file1.close();

		if (file2.is_open())
		{
			for (int i = 0; i < gradesVec.size(); i++)
			{
				string code;
				double sum = 0;
				get_code_sum(gradesVec[i], num_grades, code, sum);
				file2 << code << " - " << sum << endl;
			}
			file2.close();
		}
	}
	else
	{
		return 1;
	}
	return 0;
}
