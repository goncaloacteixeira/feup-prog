#include "e2.h"
#include <iostream>
#include <vector>

/* 1.

A seguinte classe foi definida para guardar a informa��o relevante acerca da classifica��o final dos estudantes de uma
dada unidade curricular. A classifica��o final depende das classifica��es obtidas no mini - teste, no projeto e no exame.

a)[2.0] Escreva o c�digo do m�todo setGrades. Para al�m dos atributos indicados nos seus par�metros, este m�todo
tamb�m deve atualizar o valor do atributo finalGrade, tendo em conta os valores dos par�metros e a influ�ncia dos
pesos das componentes shortExam, project, e exam, no valor de finalGrade, que s�o, respetivamente,
weightShortExam, weightProject e weightExam. O valor calculado deve ser arredondado para o inteiro mais
pr�ximo; quando a parte decimal for 0.5, finalGrade deve ser arredondado para o inteiro superior.
Justifique o uso do qualificativo static em weightShortExam, weightProject e weightExam, e inicialize estas
vari�veis por forma a conterem os valores 20, 30 e 50, respetivamente.
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
Escreva um peda�o de c�digo que leia, do
teclado, o c�digo, o nome e as classifica��es de um
estudante (no mini-teste, projeto e exame) e que crie um
objeto s do tipo Student, tendo como atributos os valores
lidos do teclado. � direita, � apresentado um exemplo de
um poss�vel di�logo com o utilizador, durante a execu��o
deste peda�o de c�digo.

Examplo de execu��o do referido c�digo:

Student code? up20141007
Student name? Ana Silva
Short exam grade? 13.5 Project grade? 17
Exam grade? 15.7

(no c�digo, ap�s este di�logo,
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
Considerando que a informa��o acerca dos estudantes que frequentam uma unidade curricular � guardada
num vector<Student>, escreva o c�digo da fun��o que recebe como par�metros uma stream de sa�da e um vetor do
tipo referido e que escreve nessa stream o nome e a classifica��o final dos estudantes que foram aprovados. Os
nomes e classifica��es deve surgir alinhados verticalmente; considere que o comprimento m�ximo de um nome � 50
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