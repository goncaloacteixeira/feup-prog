#include "e2.h"
#include <iostream>
#include <vector>

/* 1.

A seguinte classe foi definida para guardar a informação relevante acerca da classificação final dos estudantes de uma
dada unidade curricular. A classificação final depende das classificações obtidas no mini - teste, no projeto e no exame.

a)[2.0] Escreva o código do método setGrades. Para além dos atributos indicados nos seus parâmetros, este método
também deve atualizar o valor do atributo finalGrade, tendo em conta os valores dos parâmetros e a influência dos
pesos das componentes shortExam, project, e exam, no valor de finalGrade, que são, respetivamente,
weightShortExam, weightProject e weightExam. O valor calculado deve ser arredondado para o inteiro mais
próximo; quando a parte decimal for 0.5, finalGrade deve ser arredondado para o inteiro superior.
Justifique o uso do qualificativo static em weightShortExam, weightProject e weightExam, e inicialize estas
variáveis por forma a conterem os valores 20, 30 e 50, respetivamente.
*/

int Student::weightShortExam = 20;
int Student::weightProject = 30;
int Student::weightExam = 50;

void Student::setGrades(double shortExam, double project, double exam)
{
	this->shortExam = shortExam;
	this->project = project;
	this->exam = exam;

	double grade = (shortExam * Student::shortExam + project * Student::weightProject + exam * Student::weightExam) / 100;
	
	grade = round(grade);
	grade = (int)grade;

	this->finalGrade = grade;
}


/* 2.b)
Escreva um pedaço de código que leia, do
teclado, o código, o nome e as classificações de um
estudante (no mini-teste, projeto e exame) e que crie um
objeto s do tipo Student, tendo como atributos os valores
lidos do teclado. À direita, é apresentado um exemplo de
um possível diálogo com o utilizador, durante a execução
deste pedaço de código.

Examplo de execução do referido código:

Student code? up20141007
Student name? Ana Silva
Short exam grade? 13.5 Project grade? 17
Exam grade? 15.7

(no código, após este diálogo,
 deve ser criado o objeto s)
*/
void createStudent()
{
	string code;
	string name;
	double shortExam;
	double project;
	double exam;

	cout << "Student code? ";
	cin >> code;
	cout << "Student name? ";
	cin >> name;
	cout << "Short exam grade? ";
	cin >> shortExam;
	cout << "Project grade? ";
	cin >> project;
	cout << "Exam grade? ";
	cin >> exam;

	Student s;
	s.setGrades(shortExam, project, exam);
}

/* 2.c)
Considerando que a informação acerca dos estudantes que frequentam uma unidade curricular é guardada
num vector<Student>, escreva o código da função que recebe como parâmetros uma stream de saída e um vetor do
tipo referido e que escreve nessa stream o nome e a classificação final dos estudantes que foram aprovados. Os
nomes e classificações deve surgir alinhados verticalmente; considere que o comprimento máximo de um nome é 50
carateres.
*/

#include <iomanip>
 
void showApproved(ostream& out, const vector<Student>& students)
{
	for (int i = 0; i < students.size(); i++)
	{
		out << students[i].getName() << setw(50) << students[i].getFinalGrade() << endl;
	}
}


int	main()
{
	return 0;
}