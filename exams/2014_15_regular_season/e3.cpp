#include "e3.h"

/* 3.
O Instituto de Meteorologia pretende registar a pluviosidade em algumas localidades, ao longo do ano. Para isso, foi
definida uma classe, Pluviosity. Apresenta-se a seguir uma definição parcial dessa classe. (header file)

a) Escreva o código do construtor com parâmetro. Este construtor deve inicializar a pluviosidade de cada
dia/mês do ano indicado com o valor zero. Nota: o número de dias de cada mês não é constante, depende do mês e
do ano. Considere que lhe é fornecida uma função global que retorna o número de dias de um dado par de valores
(month, year); o protótipo desta função é int numDaysOfMonth(int month, int year), onde month deve tomar um
valor entre 1 e 12.
*/

int numDaysOfMonth(int month, int year);

Pluviosity::Pluviosity(int year)
{
	vector<vector<int>> result;

	for (int month = 1; month <= 12; month++)
	{
		int numDays = numDaysOfMonth(month, year);
		vector<int> monthVec;
		for (int day = 1; day <= numDays; day++)
		{
			monthVec.push_back(0);
		}
		result.push_back(monthVec);
	}

	this->year = year;
	this->pluv = result;
}

/* 3.b)
Escreva o código do método maxPluv da classe Pluviosity que retorna o valor máximo da pluviosidade.
*/

int Pluviosity::maxPluv()
{
	int max = 0;
	for (int month = 1; month <= 12; month++)
	{
		for (int day = 1; day < pluv[month].size(); day++)
		{
			if (pluv[month][day] > max)
			{
				max = pluv[month][day];
			}
		}
	}
	return max;
}

/* 3.c)
Defina a estrutura de dados que usaria para associar a pluviosidade a diferentes localidades e aceder
facilmente à pluviosidade numa dada localidade, por exemplo, Porto, Lisboa, Penhas Douradas, etc. . Note que, para
cada localidade, será necessário representar a pluviosidade referente a vários anos. Justifique a sua resposta.
*/


/*
Usaria um struct para guardar o nome do local e para guardar um vetor com todos os registos de pluviosidade de cada ano.
*/

#include <string>

struct LocalPluv
{
	string local;
	vector<Pluviosity> pluvYears;
};


int main()
{
	return 0;
}
