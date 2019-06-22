#include "e3.h"

/* 3.
O Instituto de Meteorologia pretende registar a pluviosidade em algumas localidades, ao longo do ano. Para isso, foi
definida uma classe, Pluviosity. Apresenta-se a seguir uma defini��o parcial dessa classe. (header file)

a) Escreva o c�digo do construtor com par�metro. Este construtor deve inicializar a pluviosidade de cada
dia/m�s do ano indicado com o valor zero. Nota: o n�mero de dias de cada m�s n�o � constante, depende do m�s e
do ano. Considere que lhe � fornecida uma fun��o global que retorna o n�mero de dias de um dado par de valores
(month, year); o prot�tipo desta fun��o � int numDaysOfMonth(int month, int year), onde month deve tomar um
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
Escreva o c�digo do m�todo maxPluv da classe Pluviosity que retorna o valor m�ximo da pluviosidade.
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
facilmente � pluviosidade numa dada localidade, por exemplo, Porto, Lisboa, Penhas Douradas, etc. . Note que, para
cada localidade, ser� necess�rio representar a pluviosidade referente a v�rios anos. Justifique a sua resposta.
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
