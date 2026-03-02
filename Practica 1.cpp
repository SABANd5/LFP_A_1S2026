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
void generarReporte1(const vector<Curso> &listaCursos, const vector<Nota> &listaNotas)
{
    // Usamos la ruta relativa como sugeriste
    ofstream archivo("Reporte1_Estadisticas.html");

    if (!archivo.is_open())
    {
        cout << "Error: No se pudo crear el archivo HTML." << endl;
        return;
    }

    archivo << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<title>Reporte 1</title>\n";
    archivo << "<style>table { width: 100%; border-collapse: collapse; font-family: sans-serif; } th, td { border: 1px solid black; padding: 8px; text-align: center; } th { background-color: #2c3e50; color: white; }</style>\n";
    archivo << "</head>\n<body>\n";
    archivo << "<h2>Reporte 1: Estadisticas Generales por Curso</h2>\n";
    archivo << "<table>\n";
    archivo << "<tr><th>Curso</th><th>Estudiantes</th><th>Promedio</th><th>Nota Max</th><th>Nota Min</th><th>Desviacion Estandar</th><th>Mediana</th></tr>\n";

    for (const auto &curso : listaCursos)
    {
        vector<double> notasDelCurso;

        for (const auto &nota : listaNotas)
        {
            if (nota.codigo_curso == curso.codigo)
            {
                notasDelCurso.push_back(nota.valor_nota);
            }
        }

        int cantidad = notasDelCurso.size();

        // Si el curso no tiene alumnos asignados, llenamos con guiones
        if (cantidad == 0)
        {
            archivo << "<tr><td>" << curso.nombre << "</td><td>0</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr>\n";
            continue;
        }

        double suma = 0;
        double max_nota = notasDelCurso[0];
        double min_nota = notasDelCurso[0];

        for (double n : notasDelCurso)
        {
            suma += n;
            if (n > max_nota)
                max_nota = n;
            if (n < min_nota)
                min_nota = n;
        }

        double promedio = suma / cantidad;

        double sumaDiferencias = 0;
        for (double n : notasDelCurso)
        {
            sumaDiferencias += pow(n - promedio, 2);
        }
        double varianza = sumaDiferencias / cantidad;
        double desviacion = sqrt(varianza);

        vector<double> notasOrdenadas = notasDelCurso;
        sort(notasOrdenadas.begin(), notasOrdenadas.end());

        double mediana;
        if (cantidad % 2 == 0)
        {
            mediana = (notasOrdenadas[cantidad / 2 - 1] + notasOrdenadas[cantidad / 2]) / 2.0;
        }
        else
        {
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

void generarReporte2(const vector<Estudiante> &listaEstudiantes, const vector<Curso> &listaCursos, const vector<Nota> &listaNotas)
{
    ofstream archivo("Reporte2_Rendimiento.html");

    if (!archivo.is_open())
    {
        cout << "Error: No se pudo crear el archivo HTML del Reporte 2." << endl;
        return;
    }

    archivo << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<title>Reporte 2</title>\n";
    archivo << "<style>table { width: 100%; border-collapse: collapse; font-family: sans-serif; } th, td { border: 1px solid black; padding: 8px; text-align: center; } th { background-color: #27ae60; color: white; }</style>\n";
    archivo << "</head>\n<body>\n";
    archivo << "<h2>Reporte 2: Rendimiento por Estudiante</h2>\n";
    archivo << "<table>\n";
    archivo << "<tr><th>Carnet</th><th>Nombre Completo</th><th>Carrera</th><th>Semestre</th><th>Promedio General</th><th>Cursos Aprobados</th><th>Cursos Reprobados</th><th>Creditos Acumulados</th></tr>\n";

    // Recorremos estudiante por estudiante
    for (const auto &estudiante : listaEstudiantes)
    {
        double sumaNotas = 0;
        int aprobados = 0;
        int reprobados = 0;
        int creditosAcumulados = 0;
        int totalCursos = 0;

        // Buscamos todas las notas de este estudiante especifico
        for (const auto &nota : listaNotas)
        {
            if (nota.carnet == estudiante.carnet)
            {
                totalCursos++;
                sumaNotas += nota.valor_nota;

                // Verificamos si aprobo o reprobo (nota >= 61)
                if (nota.valor_nota >= 61.0)
                {
                    aprobados++;
                    // Como aprobo, buscamos cuantos creditos vale el curso para sumarlos
                    for (const auto &curso : listaCursos)
                    {
                        if (curso.codigo == nota.codigo_curso)
                        {
                            creditosAcumulados += curso.creditos;
                            break; // Ya encontramos el curso, salimos de este bucle
                        }
                    }
                }
                else
                {
                    reprobados++;
                }
            }
        }

        // Calculamos el promedio general (cuidado de no dividir por cero si no tiene notas)
        double promedio = 0;
        if (totalCursos > 0)
        {
            promedio = sumaNotas / totalCursos;
        }

        archivo << fixed << setprecision(2);
        archivo << "<tr>"
                << "<td>" << estudiante.carnet << "</td>"
                << "<td>" << estudiante.nombre << " " << estudiante.apellido << "</td>"
                << "<td>" << estudiante.carrera << "</td>"
                << "<td>" << estudiante.semestre << "</td>"
                << "<td>" << promedio << "</td>"
                << "<td>" << aprobados << "</td>"
                << "<td>" << reprobados << "</td>"
                << "<td>" << creditosAcumulados << "</td>"
                << "</tr>\n";
    }

    archivo << "</table>\n</body>\n</html>\n";
    archivo.close();

    cout << "\n==========================================================\n";
    cout << "EXITO: Reporte 2 generado como 'Reporte2_Rendimiento.html'\n";
    cout << "==========================================================\n";
}

// Estructura auxiliar para ordenar a los estudiantes en el Reporte 3
struct EstudiantePromedio
{
    Estudiante est;
    double promedio;
};

void generarReporte3(const vector<Estudiante> &listaEstudiantes, const vector<Nota> &listaNotas)
{
    ofstream archivo("Reporte3_Top10.html");

    if (!archivo.is_open())
    {
        cout << "Error: No se pudo crear el archivo HTML del Reporte 3." << endl;
        return;
    }

    archivo << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<title>Reporte 3</title>\n";
    archivo << "<style>table { width: 100%; border-collapse: collapse; font-family: sans-serif; } th, td { border: 1px solid black; padding: 8px; text-align: center; } th { background-color: #f39c12; color: white; }</style>\n";
    archivo << "</head>\n<body>\n";
    archivo << "<h2>Reporte 3: Top 10 Mejores Estudiantes</h2>\n";
    archivo << "<table>\n";
    archivo << "<tr><th>Posicion</th><th>Carnet</th><th>Nombre Completo</th><th>Carrera</th><th>Semestre</th><th>Promedio General</th></tr>\n";

    // 1. Calculamos los promedios y los guardamos en un vector auxiliar
    vector<EstudiantePromedio> listaPromedios;

    for (const auto &estudiante : listaEstudiantes)
    {
        double sumaNotas = 0;
        int totalCursos = 0;

        for (const auto &nota : listaNotas)
        {
            if (nota.carnet == estudiante.carnet)
            {
                sumaNotas += nota.valor_nota;
                totalCursos++;
            }
        }

        double promedio = 0;
        if (totalCursos > 0)
        {
            promedio = sumaNotas / totalCursos;
        }

        // Guardamos al estudiante y su promedio calculado
        listaPromedios.push_back({estudiante, promedio});
    }

    // 2. Ordenamos el vector de promedios de MAYOR a MENOR
    // Usamos una funcion lambda (el []...) para decirle a C++ como compararlos
    sort(listaPromedios.begin(), listaPromedios.end(), [](const EstudiantePromedio &a, const EstudiantePromedio &b)
         { return a.promedio > b.promedio; });

    // 3. Imprimimos en el HTML solo los primeros 10
    archivo << fixed << setprecision(2);
    int posicion = 1;

    for (const auto &ep : listaPromedios)
    {
        if (posicion > 10)
        {
            break; // Si ya llegamos a 10, cortamos el ciclo
        }

        archivo << "<tr>"
                << "<td>" << posicion << "</td>"
                << "<td>" << ep.est.carnet << "</td>"
                << "<td>" << ep.est.nombre << " " << ep.est.apellido << "</td>"
                << "<td>" << ep.est.carrera << "</td>"
                << "<td>" << ep.est.semestre << "</td>"
                << "<td>" << ep.promedio << "</td>"
                << "</tr>\n";

        posicion++;
    }

    archivo << "</table>\n</body>\n</html>\n";
    archivo.close();

    cout << "\n==========================================================\n";
    cout << "EXITO: Reporte 3 generado como 'Reporte3_Top10.html'\n";
    cout << "==========================================================\n";
}
// Estructura auxiliar para ordenar los cursos en el Reporte 4
struct CursoReprobacion
{
    int codigo;
    string nombre;
    int total_estudiantes;
    int aprobados;
    int reprobados;
    double porcentaje_reprobacion;
};

void generarReporte4(const vector<Curso> &listaCursos, const vector<Nota> &listaNotas)
{
    ofstream archivo("Reporte4_Reprobacion.html");

    if (!archivo.is_open())
    {
        cout << "Error: No se pudo crear el archivo HTML del Reporte 4." << endl;
        return;
    }

    archivo << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<title>Reporte 4</title>\n";
    // Le puse un tono rojizo al encabezado porque hablamos de reprobados 🚨
    archivo << "<style>table { width: 100%; border-collapse: collapse; font-family: sans-serif; } th, td { border: 1px solid black; padding: 8px; text-align: center; } th { background-color: #c0392b; color: white; }</style>\n";
    archivo << "</head>\n<body>\n";
    archivo << "<h2>Reporte 4: Cursos con Mayor Indice de Reprobacion</h2>\n";
    archivo << "<table>\n";
    archivo << "<tr><th>Codigo</th><th>Nombre del Curso</th><th>Total Estudiantes</th><th>Aprobados</th><th>Reprobados</th><th>% Reprobacion</th></tr>\n";

    // 1. Calculamos los datos y los guardamos en un vector auxiliar
    vector<CursoReprobacion> estadisticasCursos;

    for (const auto &curso : listaCursos)
    {
        int total = 0;
        int aprobados = 0;
        int reprobados = 0;

        for (const auto &nota : listaNotas)
        {
            if (nota.codigo_curso == curso.codigo)
            {
                total++;
                if (nota.valor_nota >= 61.0)
                {
                    aprobados++;
                }
                else
                {
                    reprobados++;
                }
            }
        }

        double porcentaje = 0.0;
        if (total > 0)
        {
            // Multiplicamos por 100.0 para forzar que la division sea decimal y no se coma los numeros
            porcentaje = (reprobados * 100.0) / total;
        }

        estadisticasCursos.push_back({curso.codigo, curso.nombre, total, aprobados, reprobados, porcentaje});
    }

    // 2. Ordenamos el vector por porcentaje de reprobacion de MAYOR a MENOR
    sort(estadisticasCursos.begin(), estadisticasCursos.end(), [](const CursoReprobacion &a, const CursoReprobacion &b)
         { return a.porcentaje_reprobacion > b.porcentaje_reprobacion; });

    // 3. Imprimimos en el HTML
    archivo << fixed << setprecision(2);

    for (const auto &cursoEst : estadisticasCursos)
    {
        archivo << "<tr>"
                << "<td>" << cursoEst.codigo << "</td>"
                << "<td>" << cursoEst.nombre << "</td>"
                << "<td>" << cursoEst.total_estudiantes << "</td>"
                << "<td>" << cursoEst.aprobados << "</td>"
                << "<td>" << cursoEst.reprobados << "</td>"
                << "<td>" << cursoEst.porcentaje_reprobacion << "%</td>"
                << "</tr>\n";
    }

    archivo << "</table>\n</body>\n</html>\n";
    archivo.close();

    cout << "\n==========================================================\n";
    cout << "EXITO: Reporte 4 generado como 'Reporte4_Reprobacion.html'\n";
    cout << "==========================================================\n";
}

void generarReporte5(const vector<Estudiante> &listaEstudiantes, const vector<Curso> &listaCursos, const vector<Nota> &listaNotas)
{
    ofstream archivo("Reporte5_Carreras.html");

    if (!archivo.is_open())
    {
        cout << "Error: No se pudo crear el archivo HTML del Reporte 5." << endl;
        return;
    }

    archivo << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<title>Reporte 5</title>\n";
    // Un color moradito para variar el diseno de los reportes
    archivo << "<style>table { width: 100%; border-collapse: collapse; font-family: sans-serif; } th, td { border: 1px solid black; padding: 8px; text-align: center; } th { background-color: #8e44ad; color: white; }</style>\n";
    archivo << "</head>\n<body>\n";
    archivo << "<h2>Reporte 5: Analisis por Carrera</h2>\n";
    archivo << "<table>\n";
    archivo << "<tr><th>Carrera</th><th>Total Estudiantes</th><th>Promedio General</th><th>Cursos Disponibles</th><th>Distribucion por Semestre</th></tr>\n";

    // 1. Encontrar todas las carreras unicas que existen en nuestra lista de estudiantes
    vector<string> carreras_unicas;
    for (const auto &est : listaEstudiantes)
    {
        // Si la carrera del estudiante no esta en nuestro vector de carreras_unicas, la agregamos
        if (find(carreras_unicas.begin(), carreras_unicas.end(), est.carrera) == carreras_unicas.end())
        {
            carreras_unicas.push_back(est.carrera);
        }
    }

    // 2. Por cada carrera encontrada, calculamos sus estadisticas
    for (const string &carrera : carreras_unicas)
    {
        int total_estudiantes = 0;
        int cursos_disponibles = 0;
        double suma_notas_carrera = 0;
        int total_notas_carrera = 0;

        // Un arreglo para contar cuantos estudiantes hay del semestre 1 al 10 (usamos tamano 11 para que el indice coincida con el semestre)
        int distribucion[11] = {0};

        // Contamos cuantos cursos pertenecen a esta carrera
        for (const auto &curso : listaCursos)
        {
            if (curso.carrera == carrera)
            {
                cursos_disponibles++;
            }
        }

        // Recopilamos los datos de los estudiantes de esta carrera
        for (const auto &est : listaEstudiantes)
        {
            if (est.carrera == carrera)
            {
                total_estudiantes++;

                // Sumamos 1 al contador del semestre correspondiente
                if (est.semestre >= 1 && est.semestre <= 10)
                {
                    distribucion[est.semestre]++;
                }

                // Buscamos las notas de este estudiante para el promedio general de la carrera
                for (const auto &nota : listaNotas)
                {
                    if (nota.carnet == est.carnet)
                    {
                        suma_notas_carrera += nota.valor_nota;
                        total_notas_carrera++;
                    }
                }
            }
        }

        // Calculamos el promedio general de la carrera
        double promedio_general = 0;
        if (total_notas_carrera > 0)
        {
            promedio_general = suma_notas_carrera / total_notas_carrera;
        }

        // Armamos un texto bonito con saltos de linea (<br>) para mostrar la distribucion de semestres en la tabla HTML
        string texto_distribucion = "";
        for (int i = 1; i <= 10; i++)
        {
            if (distribucion[i] > 0)
            {
                if (texto_distribucion != "")
                    texto_distribucion += "<br>";
                texto_distribucion += "Semestre " + to_string(i) + ": " + to_string(distribucion[i]) + " est.";
            }
        }

        if (texto_distribucion == "")
        {
            texto_distribucion = "Sin datos";
        }

        // 3. Imprimimos los datos en el HTML
        archivo << fixed << setprecision(2);
        archivo << "<tr>"
                << "<td>" << carrera << "</td>"
                << "<td>" << total_estudiantes << "</td>"
                << "<td>" << promedio_general << "</td>"
                << "<td>" << cursos_disponibles << "</td>"
                << "<td>" << texto_distribucion << "</td>"
                << "</tr>\n";
    }

    archivo << "</table>\n</body>\n</html>\n";
    archivo.close();

    cout << "\n==========================================================\n";
    cout << "EXITO: Reporte 5 generado como 'Reporte5_Carreras.html'\n";
    cout << "==========================================================\n";
}
void verificarDatos(const vector<Estudiante> &e, const vector<Curso> &c, const vector<Nota> &n)
{
    cout << "\n--- VERIFICACION DE DATOS EN MEMORIA ---" << endl;

    cout << "Estudiantes cargados: " << e.size() << endl;
    if (!e.empty())
        cout << "  -> Ejemplo: " << e[0].nombre << " " << e[0].apellido << " (Carrera: " << e[0].carrera << ")" << endl;

    cout << "\nCursos cargados: " << c.size() << endl;
    if (!c.empty())
        cout << "  -> Ejemplo: " << c[0].nombre << " (Creditos: " << c[0].creditos << ")" << endl;

    cout << "\nNotas cargadas: " << n.size() << endl;
    if (!n.empty())
        cout << "  -> Ejemplo: Carnet " << n[0].carnet << " saco " << n[0].valor_nota << endl;

    cout << "----------------------------------------\n"
         << endl;
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

        switch (opcion)
        {
        case 0:
            verificarDatos(listaEstudiantes, listaCursos, listaNotas);
            break;
        case 1:
            cout << "Ingrese la ruta del archivo de estudiantes: ";
            cin >> ws;          // Esto limpia los espacios basura antes de leer
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
            if (listaCursos.empty() || listaNotas.empty())
            {
                cout << "Advertencia: Debes cargar los archivos de cursos y notas primero.\n";
            }
            else
            {
                generarReporte1(listaCursos, listaNotas);
            }
            break;
        case 5:
            cout << "Generando Reporte 2...\n";
            if (listaEstudiantes.empty() || listaNotas.empty())
            {
                cout << "Advertencia: Debes cargar los archivos de estudiantes y notas primero.\n";
            }
            else
            {
                generarReporte2(listaEstudiantes, listaCursos, listaNotas);
            }
            break;
        case 6:
            cout << "Generando Reporte 3...\n";
            if (listaEstudiantes.empty() || listaNotas.empty())
            {
                cout << "Advertencia: Debes cargar los archivos de estudiantes y notas primero.\n";
            }
            else
            {
                generarReporte3(listaEstudiantes, listaNotas);
            }
            break;
        case 7:
            cout << "Generando Reporte 4...\n";
            if (listaCursos.empty() || listaNotas.empty())
            {
                cout << "Advertencia: Debes cargar los archivos de cursos y notas primero.\n";
            }
            else
            {
                generarReporte4(listaCursos, listaNotas);
            }
            break;
        case 8:
            cout << "Generando Reporte 5...\n";
            // Para este reporte necesitamos la informacion de los 3 archivos
            if (listaEstudiantes.empty() || listaCursos.empty() || listaNotas.empty())
            {
                cout << "Advertencia: Debes cargar todos los archivos (estudiantes, cursos y notas) primero.\n";
            }
            else
            {
                generarReporte5(listaEstudiantes, listaCursos, listaNotas);
            }
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
