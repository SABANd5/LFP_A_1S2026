#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Estudiante // Estructura para almacenar información de los estudiantes.lfp
{
    int carnet;
    string nombre;
    string apellido;
    string carrera;
    int semestre;
};

struct Curso // Estructura para almacenar información de los cursos.lfp
{
    int codigo;
    string nombre;
    int creditos;   
    int semestre;
    string carrera;
};

struct Nota //Estructura para almacenar informacion de las notas.lfp
{
    int carnet;
    int codigo_curso;
    double valor_nota;
    string ciclo;
    int ano;
};

int main (){ //vectores globales para almacenar los datos de estudiantes, cursos y notas.lfp
    vector<Estudiante> listaEstudiantes;
    vector<Curso> listaCursos;
    vector<Nota> listaNotas;    
    cout<<"Sistema iniciado correctamente."<<endl;
    //Menu siguiente...

    return 0;

}