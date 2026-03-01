#include <iostream>  // para la entrada y salida de datos
#include <string>    // manejo de cadenas de texto
#include <vector>    // arreglo dinámico para almacenar estudiantes, cursos y notas
#include <fstream>   //para leer y escribir archivos
#include <sstream>   // para usar el stringstream en nuestro split
#include <cmath>     // Para sqrt() y pow() en la desviacion estandar
#include <algorithm> // Para sort() en la mediana
#include <iomanip>   // Para std::fixed y std::setprecision en los decimales del HTML

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

// --- FUNCIONES PARA REPORTES HTML ---
void generarReporte1(const vector<Curso>& listaCursos, const vector<Nota>& listaNotas) {
    // Usamos la ruta relativa como sugeriste
    ofstream archivo("Reporte1_Estadisticas.html");
    
    if (!archivo.is_open()) {
        cout << "Error: No se pudo crear el archivo HTML." << endl;
        return;
    }

    archivo << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<title>Reporte 1</title>\n";
    archivo << "<style>table { width: 100%; border-collapse: collapse; font-family: sans-serif; } th, td { border: 1px solid black; padding: 8px; text-align: center; } th { background-color: #2c3e50; color: white; }</style>\n";
    archivo << "</head>\n<body>\n";
    archivo << "<h2>Reporte 1: Estadisticas Generales por Curso</h2>\n";
    archivo << "<table>\n";
    archivo << "<tr><th>Curso</th><th>Estudiantes</th><th>Promedio</th><th>Nota Max</th><th>Nota Min</th><th>Desviacion Estandar</th><th>Mediana</th></tr>\n";

    for (const auto& curso : listaCursos) {
        vector<double> notasDelCurso;
        
        for (const auto& nota : listaNotas) {
            if (nota.codigo_curso == curso.codigo) {
                notasDelCurso.push_back(nota.valor_nota);
            }
        }

        int cantidad = notasDelCurso.size();

        // Si el curso no tiene alumnos asignados, llenamos con guiones
        if (cantidad == 0) {
            archivo << "<tr><td>" << curso.nombre << "</td><td>0</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr>\n";
            continue;
        }

        double suma = 0;
        double max_nota = notasDelCurso[0];
        double min_nota = notasDelCurso[0];
        
        for (double n : notasDelCurso) {
            suma += n;
            if (n > max_nota) max_nota = n;
            if (n < min_nota) min_nota = n;
        }
        
        double promedio = suma / cantidad;

        double sumaDiferencias = 0;
        for (double n : notasDelCurso) {
            sumaDiferencias += pow(n - promedio, 2);
        }
        double varianza = sumaDiferencias / cantidad;
        double desviacion = sqrt(varianza);

        vector<double> notasOrdenadas = notasDelCurso;
        sort(notasOrdenadas.begin(), notasOrdenadas.end());
        
        double mediana;
        if (cantidad % 2 == 0) {
            mediana = (notasOrdenadas[cantidad / 2 - 1] + notasOrdenadas[cantidad / 2]) / 2.0;
        } else {
            mediana = notasOrdenadas[cantidad / 2];
        }

        archivo << fixed << setprecision(2);
        archivo << "<tr>"
                << "<td>" << curso.nombre << "</td>"
                << "<td>" << cantidad << "</td>"
                << "<td>" << promedio << "</td>"
                << "<td>" << max_nota << "</td>"
                << "<td>" << min_nota << "</td>"
                << "<td>" << desviacion << "</td>"
                << "<td>" << mediana << "</td>"
                << "</tr>\n";
    }

    archivo << "</table>\n</body>\n</html>\n";
    archivo.close();
    
    cout << "\n==========================================================\n";
    cout << "EXITO: Reporte 1 generado como 'Reporte1_Estadisticas.html'\n";
    cout << "Buscate el archivo en el panel izquierdo de VS Code.\n";
    cout << "==========================================================\n";
}

 
void verificarDatos(const vector<Estudiante>& e, const vector<Curso>& c, const vector<Nota>& n) {
    cout << "\n--- VERIFICACION DE DATOS EN MEMORIA ---" << endl;
    
    cout << "Estudiantes cargados: " << e.size() << endl;
    if(!e.empty()) cout << "  -> Ejemplo: " << e[0].nombre << " " << e[0].apellido << " (Carrera: " << e[0].carrera << ")" << endl;
    
    cout << "\nCursos cargados: " << c.size() << endl;
    if(!c.empty()) cout << "  -> Ejemplo: " << c[0].nombre << " (Creditos: " << c[0].creditos << ")" << endl;
    
    cout << "\nNotas cargadas: " << n.size() << endl;
    if(!n.empty()) cout << "  -> Ejemplo: Carnet " << n[0].carnet << " saco " << n[0].valor_nota << endl;
    
    cout << "----------------------------------------\n" << endl;
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
        cout << "0. Verificar datos cargados en memoria\n";
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

        switch (opcion) {
            case 0:
                verificarDatos(listaEstudiantes, listaCursos, listaNotas);
                break;
            case 1:
                cout << "Ingrese la ruta del archivo de estudiantes: ";
                cin >> ws; // Esto limpia los espacios basura antes de leer
                getline(cin, ruta); // Lee toda la linea, incluyendo espacios
                cargarEstudiantes(listaEstudiantes, ruta);
                break;
            case 2:
                cout << "Ingrese la ruta del archivo de cursos: ";
                cin >> ws;
                getline(cin, ruta);
                cargarCursos(listaCursos, ruta);
                break;
            case 3:
                cout << "Ingrese la ruta del archivo de notas: ";
                cin >> ws;
                getline(cin, ruta);
                cargarNotas(listaNotas, ruta);
                break;
            case 4:
                cout << "Generando Reporte 1...\n";
                // Verificamos que al menos existan cursos y notas cargados
                if (listaCursos.empty() || listaNotas.empty()) {
                    cout << "Advertencia: Debes cargar los archivos de cursos y notas primero.\n";
                } else {
                    generarReporte1(listaCursos, listaNotas);
                }
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
