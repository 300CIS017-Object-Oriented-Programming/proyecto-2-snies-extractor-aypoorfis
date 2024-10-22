#include "GestorCsv.h"
#include "Settings.h"
#include "ProgramaAcademico.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <algorithm>
using std::vector;
using std::string;
using std::ifstream;
using std::stringstream;
using std::unordered_map;
using std::cout;
using std::endl;

using namespace std;


string GestorCsv::convertirStringFormaEstandar(const string &input) {
    static const unordered_map<char, char> tildesMap = {
        {'á', 'a'}, {'Á', 'a'},
        {'é', 'e'}, {'É', 'e'},
        {'í', 'i'}, {'Í', 'i'},
        {'ó', 'o'}, {'Ó', 'o'},
        {'ú', 'u'}, {'Ú', 'u'}
    };
    string resultado;
    for (int i = 0; i < input.length(); ++i) {
        auto letra = static_cast<char>(tolower(input[i]));
        if (tildesMap.count(letra)) {
            letra = tildesMap.at(letra);
        }
        else if (letra != ' ' && letra != '-') {
            resultado += letra;
        }
    }
    return resultado;
}

vector<string> GestorCsv::dividirLineaCSV(string &linea) {
    vector<string> resultado;
    stringstream streamLinea(linea);
    string dato;
    while (getline(streamLinea, dato, Settings::DELIMITADOR)) {
        resultado.push_back(dato);
    }
    if(linea.back() != Settings::DELIMITADOR) {
        resultado.push_back(dato);
    }
    return resultado;
}

vector<string> GestorCsv::convertirVectorFormaEstandar(vector<string> &vecDatos) {
    vector<string> resultado;
    for (const string &dato : vecDatos) {
        resultado.push_back(convertirStringFormaEstandar(dato));
    }
    return resultado;
}

void GestorCsv::inicializarProgramasDeAnalisisCsv(map<string, ProgramaAcademico*> &datos) {
    ifstream archivoProgramasCsv(Settings::PROGRAMAS_FILTRAR_FILE_PATH);
    if (!archivoProgramasCsv.is_open()) {
        cout << "Archivo " << Settings::PROGRAMAS_FILTRAR_FILE_PATH << " no se pudo abrir correctamente" << std::endl;
        return;
    }

    string linea;
    vector<std::string> nombresColumnas;
    char delimitador = Settings::DELIMITADOR;

    // Leer la primera línea para obtener los nombres de las columnas
    if (getline(archivoProgramasCsv, linea)) {
        stringstream streamLinea(linea);
        string columna;

        while (getline(streamLinea, columna, delimitador)) {
            nombresColumnas.push_back(columna);
        }
        // Convertir los nombres de las columnas a su forma estándar
        nombresColumnas = convertirVectorFormaEstandar(nombresColumnas);
    }

    // Leer el resto del archivo
    while (getline(archivoProgramasCsv, linea)) {
        stringstream streamLinea(linea);
        vector<string> datosFila;
        string dato;

        while (getline(streamLinea, dato, delimitador)) {
            datosFila.push_back(dato);
        }

        if (datosFila.size() != nombresColumnas.size()) {
            cout << "Error: La cantidad de datos no coincide con la cantidad de columnas" << endl;
        }
        else {
            // Crear un ProgramaAcademico vacío
            ProgramaAcademico* programa = new ProgramaAcademico();

            // Agregar el programa al mapa usando el código SNIES como llave
            string codigoSnies = datosFila[0];
            datos[codigoSnies] = programa;

            // Agregar la información al programa académico
            for (size_t i = 0; i < nombresColumnas.size(); ++i) {
                programa->setDato(nombresColumnas[i], datosFila[i]);
            }
        }

        // Crear un ProgramaAcademico vacío
        ProgramaAcademico* programa = new ProgramaAcademico();

        // Agregar el programa al mapa usando el código SNIES como llave
        string codigoSnies = datosFila[0];
        datos[codigoSnies] = programa;

        // Agregar la información al programa académico
        for (size_t i = 0; i < nombresColumnas.size(); ++i) {
            programa->setDato(nombresColumnas[i], datosFila[i]);
        }
    }

    archivoProgramasCsv.close();
}

void adjuntarDatosProgramaAcademico(vector<string> &llaves, vector<string> &valores, ProgramaAcademico &programa) {

    vector<string> llavesEspeciales = { "inscritos", "admitidos", "matriculados",
                                        "matriculadosPrimerSemestre", "graduados" };
    
    // Un Consolidado para almacenar los datos especiales
    Consolidado* consolidado = new Consolidado();

    // Es suficiente con recorrer las llavees ya que los dos vectoes tiene el mismo tamaño
    for (int i = 0; i < llaves.size(); ++i) {
        string &llave = llaves[i];
        string &valor = valores[i];

        // Verificar si la llave es especial
        if (find(llavesEspeciales.begin(), llavesEspeciales.end(), llave) != llavesEspeciales.end()) {
            // Agregar al Consolidado
            map<string, string> parametros;
            parametros[llave] = valor;

            consolidado->setParametros(parametros);

        } else {
            // Agregar el dato directamente al ProgramaAcademico
            programa.setDato(llave, valor);
        }
    }

    // Agregar el Consolidado al programa (asumiendo semestre 0 para este ejemplo)
    programa.addConsolidado(0, consolidado);
}

    
void GestorCsv::adjuntarTodosLosDatos(map<string, ProgramaAcademico*> &datos) {
    // File paths from Settings
    vector<string> filePaths = {
        Settings::ADMITIDOS_FILE_PATH,
        Settings::MATRICULADOS_FILE_PATH,
        Settings::INSCRITOS_FILE_PATH,
        Settings::GRADUADOS_FILE_PATH
    };

    for (const string &filePath : filePaths) {
        ifstream file(filePath);
        if (!file.is_open()) {
            cout << "Archivo " << filePath << " no se pudo abrir correctamente" << endl;
            continue;
        }

        string line;
        vector<string> columnNames;
        char delimiter = Settings::DELIMITADOR[0];

        // Read the first line to get column names
        if (getline(file, line)) {
            stringstream lineStream(line);
            string column;

            while (getline(lineStream, column, delimiter)) {
                columnNames.push_back(column);
            }
            // Convert column names to their standard form
            columnNames = convertirVectorFormaEstandar(columnNames);
        }

        // Read the rest of the file
        while (getline(file, line)) {
            stringstream lineStream(line);
            vector<string> rowData;
            string data;

            while (getline(lineStream, data, delimiter)) {
                rowData.push_back(data);
            }

            if (rowData.size() != columnNames.size()) {
                cout << "Error: La cantidad de datos no coincide con la cantidad de columnas" << endl;
                continue;
            }

            // Se toma la primera posición, ya que es la key (codigoSnies)
            string key = rowData[0];
            if (datos.find(key) == datos.end()) {
                // Si la key no se encuentra, se crea un new ProgramaAcademico
                datos[key] = new ProgramaAcademico();
            }

            // se llena el ProgramaAcademico con los datos
            ProgramaAcademico* program = datos[key];
            for (size_t i = 0; i < columnNames.size(); ++i) {
                program->setDato(columnNames[i], rowData[i]);
            }
        }

        file.close();
    }
}









