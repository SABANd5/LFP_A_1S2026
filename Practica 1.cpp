#include <iostream> // para la entrada y salida de datos
#include <string>   // manejo de cadenas de texto
#include <vector>   // arreglo dinámico para almacenar estudiantes, cursos y notas
#include <fstream>  //para leer y escribir archivos
#include <sstream>  // para usar el stringstream en nuestro split

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

struct Nota // Estructura para almacenar informacion de las notas.lfp
{
    int carnet;
    int codigo_curso;
    double valor_nota;
    string ciclo;
    int ano;
};

// Función auxiliar para simular el split() separando por comas
vector<string> split(const string &linea, char delimitador)
{
    vector<string> tokens;
    stringstream ss(linea);
    string token;

    // getline lee hasta encontrar el delimitador (la coma)
    while (getline(ss, token, delimitador))
    {
        tokens.push_back(token);
    }
    return tokens;
}

// Cargar Estudiantes
void cargarEstudiantes(vector<Estudiante> &listaEstudiantes, string ruta)
{
    ifstream archivo(ruta); // Permite abrir el archivo ubicado en la ruta especificada y leer su contenido.
    if (!archivo.is_open())
    {
        cout << "Error: No se pudo abrir el archivo de estudiantes" << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea))
    {
        vector<string> datos = split(linea, ',');

        // Validamos que la línea tenga exactamente los 5 campos esperados
        if (datos.size() == 5)
        {
            Estudiante est;
            est.carnet = stoi(datos[0]); // stoi convierte string a int
            est.nombre = datos[1];
            est.apellido = datos[2];
            est.carrera = datos[3];
            est.semestre = stoi(datos[4]);

            listaEstudiantes.push_back(est);
        }
    }
    archivo.close();
    cout << "Exito: Archivo de estudiantes cargado correctamente." << endl;
}

//  Cargar Cursos
void cargarCursos(vector<Curso> &listaCursos, string ruta)
{
    ifstream archivo(ruta);
    if (!archivo.is_open())
    {
        cout << "Error: No se pudo abrir el archivo de cursos" << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea))
    {
        vector<string> datos = split(linea, ',');

        if (datos.size() == 5)
        {
            Curso c;
            c.codigo = stoi(datos[0]);
            c.nombre = datos[1];
            c.creditos = stoi(datos[2]);
            c.semestre = stoi(datos[3]);
            c.carrera = datos[4];

            listaCursos.push_back(c);
        }
    }
    archivo.close();
    cout << "Exito: Archivo de cursos cargado correctamente." << endl;
}

//  Cargar Notas
void cargarNotas(vector<Nota> &listaNotas, string ruta)
{
    ifstream archivo(ruta);
    if (!archivo.is_open())
    {
        cout << "Error: No se pudo abrir el archivo de notas " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea))
    {
        vector<string> datos = split(linea, ',');

        if (datos.size() == 5)
        {
            Nota n;
            n.carnet = stoi(datos[0]);
            n.codigo_curso = stoi(datos[1]);
            n.valor_nota = stod(datos[2]); // stod convierte string a double (decimal)
            n.ciclo = datos[3];
            n.ano = stoi(datos[4]);

            listaNotas.push_back(n);
        }
    }
    archivo.close();
    cout << "Exito: Archivo de notas cargado correctamente." << endl;
}

int main()
{
    // Vectores principales para almacenar toda la información en memoria
    vector<Estudiante> listaEstudiantes;
    vector<Curso> listaCursos;
    vector<Nota> listaNotas;

    int opcion = 0;
    string ruta;

    // Ciclo principal del programa (\n = salto de línea)
    do
    {
        cout << "\n========================================\n";
        cout << "   SISTEMA DE ANALISIS ACADEMICO\n";
        cout << "========================================\n";
        cout << "1. Cargar archivo de estudiantes\n";
        cout << "2. Cargar archivo de cursos\n";
        cout << "3. Cargar archivo de notas\n";
        cout << "4. Generar Reporte: Estadisticas por Curso\n";
        cout << "5. Generar Reporte: Rendimiento por Estudiante\n";
        cout << "6. Generar Reporte: Top 10 Mejores Estudiantes\n";
        cout << "7. Generar Reporte: Cursos con Mayor Reprobacion\n";
        cout << "8. Generar Reporte: Analisis por Carrera\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Ingrese el nombre/ruta del archivo de estudiantes (ej. estudiantes.lfp): ";
            cin >> ruta;
            cargarEstudiantes(listaEstudiantes, ruta);
            break;
        case 2:
            cout << "Ingrese el nombre/ruta del archivo de cursos (ej. cursos.lfp): ";
            cin >> ruta;
            cargarCursos(listaCursos, ruta);
            break;
        case 3:
            cout << "Ingrese el nombre/ruta del archivo de notas (ej. notas.lfp): ";
            cin >> ruta;
            cargarNotas(listaNotas, ruta);
            break;
        case 4:
            cout << "Generando Reporte 1...\n";
            // Aqui llamaremos a la funcion del Reporte 1
            break;
        case 5:
            cout << "Generando Reporte 2...\n";
            // Aqui llamaremos a la funcion del Reporte 2
            break;
        case 6:
            cout << "Generando Reporte 3...\n";
            // Aqui llamaremos a la funcion del Reporte 3
            break;
        case 7:
            cout << "Generando Reporte 4...\n";
            // Aqui llamaremos a la funcion del Reporte 4
            break;
        case 8:
            cout << "Generando Reporte 5...\n";
            // Aqui llamaremos a la funcion del Reporte 5
            break;
        case 9:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opcion no valida. Por favor, intente de nuevo.\n";
            break;
        }
    } while (opcion != 9);

    return 0;
}
