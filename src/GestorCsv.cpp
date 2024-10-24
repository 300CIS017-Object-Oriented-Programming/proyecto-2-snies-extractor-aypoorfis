#include "GestorCsv.h"
#include "Settings.h"
#include "ProgramaAcademico.h"
#include <fstream>
#include <sstream>
#include <iostream>
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
            auto programa = new ProgramaAcademico();

            // Agregar el programa al mapa usando el código SNIES como llave
            string codigoSnies = datosFila[0];
            datos[codigoSnies] = programa;

            // Agregar la información al programa académico
            for (size_t i = 0; i < nombresColumnas.size(); ++i) {
                programa->setDato(nombresColumnas[i], datosFila[i]);
            }
        }

        // Crear un ProgramaAcademico vacío
        auto programa = new ProgramaAcademico();

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
    vector<string> llavesEspeciales = { "inscritos", "admitidos", "matriculados", "matriculadosprimersemestre", "graduados" };
    Consolidado consolidado;

    for (size_t i = 0; i < llaves.size(); ++i) {
        const string &llave = llaves[i];
        const string &valor = valores[i];

        if (std::find(llavesEspeciales.begin(), llavesEspeciales.end(), llave) != llavesEspeciales.end()) {
            consolidado.setDato(llave, valor);
        } else {
            programa.setDato(llave, valor);
        }
    }
    programa.addConsolidado(nullptr, &consolidado);
}

void GestorCsv::adjuntarDatosArchivo(const string &ruta, map<string, ProgramaAcademico*> &programas) {
    string linea;
    string LLAVE_CODIGO_SNIES = "codigosnies";
    vector<string> nombresColumnas;
    bool primeraLinea = true;

    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        throw std::ios_base::failure("Archivo " + ruta + " no se pudo abrir correctamente");
    }

    auto it = programas.end();

    while (getline(archivo, linea)) {
        vector<string> datosFila = dividirLineaCSV(linea);

        if (primeraLinea) {
            nombresColumnas = datosFila;
            vector<string> llavesDatos = convertirVectorFormaEstandar(nombresColumnas);
            it = programas.end(); // Declarar it aquí;
            primeraLinea = false;
            continue;
        }

        vector<string> datosEstandarizados = convertirVectorFormaEstandar(datosFila);

        if (it != programas.end()) {
            adjuntarDatosProgramaAcademico(nombresColumnas, datosEstandarizados, *(it->second));
        } else {
            string msjError = "No se encontró el programa académico con código SNIES: " + it->first;
            throw std::out_of_range(msjError);
        }
    }

    archivo.close();
}

void GestorCsv::exportarDatos(map<string, ProgramaAcademico*> &datos) {
    const string nombreArchivoOutput = Settings::OUTPUT_FILE_PATH;
    const char delimitador = Settings::DELIMITADOR;
    vector<string> etiquetasColumnas = Settings::ETIQUETAS_COLUMNAS;
    vector<string> llavesDatos = Settings::LLAVES_DATOS;
    std::ofstream archivoSalida(nombreArchivoOutput);

    if (!archivoSalida.is_open()) {
        throw std::ios_base::failure("No se pudo abrir el archivo CSV para exportar: " + nombreArchivoOutput);
    }

    // Imprimir las etiquetas de las columnas
    for (int i = 0; i < etiquetasColumnas.size(); ++i) {
        archivoSalida << etiquetasColumnas[i];
        if (i < etiquetasColumnas.size() - 1) {
            archivoSalida << delimitador;
        }
    }
    archivoSalida << "\n";

    // Imprimir los datos de cada ProgramaAcadémico
    for (auto const &[key, value] : datos) {
        ProgramaAcademico* programa = value;
        for (int i = 0; i < llavesDatos.size(); ++i) {
            archivoSalida << programa->getDato(llavesDatos[i]);
            if (i < llavesDatos.size() - 1) {
                archivoSalida << delimitador;
            }
        }
        archivoSalida << "\n";
    }
    archivoSalida.close();

    std::cout << "Exportación a CSV exitosa: " << nombreArchivoOutput << "\n";
}









