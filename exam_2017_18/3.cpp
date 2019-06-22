#include <iostream>

using namespace std;

/* 3.a1)
A função float average(const int grades[], int
numStudents)faz parte de um programa que permite
calcular a média das classificações obtidas pelos estudantes
numa prova. Escreva o código da função average().
Considere que numStudents é sempre um valor maior ou
igual que 1.
*/

float average(const int grades[], int numStudents)
{
	float sum = 0;

	for (int i = 0; i < numStudents; i++)
		sum += grades[i];

	return sum / numStudents;
}

/* 3.a2)
O número de estudantes que realiza cada prova é
variável. Pretende‐se que o programa use o espaço estrita‐
mente necessário para guardar as classificações. Escreva o
pedaço de código que lê do teclado o número de estudantes
e as suas classificações (após reservar o espaço necessário
para estas), e mostra no ecrã a média das classificações.
Nota: considere que o programa tem uma função, já imple‐
mentada, que lê as classificações:
void readGrades(int grades[], int numStudents)
*/

/*
int numStudents;
int* g;
cout << "N: ";cin >> numStudents;
readGrades(g, numStudents);
cout << avarage(g, numStudents) << endl;
*/

/* 3.b)
A STL de C++ disponibiliza uma função find() cujo template é o seguinte:
template <class InputIterator, class T>
InputIterator find (InputIterator first, InputIterator last, const T& val);
em que o parâmetro val é o valor a procurar. Diga se é possível usar esta função para procurar um valor numa variável v, do tipo
vector<string>. Em caso afirmativo escreva o pedaço de código que permite procurar o valor "31" em v, escrevendo uma
mensagem adequada, que indique se o valor foi ou não encontrado. Justifique a sua resposta.
*/

//if (find(v.begin(), v.end(), "31") != v.end())		// metodo para encontrar um valor num vetor ! IMPORTANTE
//{
//	cout << "Found!" << endl;				
//}
//else
//{
//	cout << "Not found!" << endl;
//}

/* 3.d)
Um programador queria usar num programa uma estrutura de dados do tipo set<Position>, em que Position é o tipo de
dados declarado no código da pergunta 2, mas verificou que acontecia um erro de compilação quando declarava variáveis deste
tipo de set. Indique uma possível causa deste problema e aponte uma solução. Não escreva código.

Uma possível causa seria que é necessário uma maneira de ordenar os elementos do set.
Para isso teria de se dar overload ao operador < para a struct Position, uma vez que é
o usado pelo set na sua estrutura interna, ou então usar um unordered_set.
*/


int main()
{
	
}
