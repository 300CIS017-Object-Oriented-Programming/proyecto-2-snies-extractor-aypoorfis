//
// Created by User on 13/10/2024.
//
#include "Settings.h"
#include <string>

using namespace std;


// Inicialización de las variables estáticas
string Settings::BASE_PATH = "C:/SNIES_EXTRACTOR/inputs/";
string Settings::PROGRAMAS_FILTRAR_FILE_PATH = BASE_PATH + "programas.csv";
string Settings::ADMITIDOS_FILE_PATH = BASE_PATH + "admitidos";
string Settings::MATRICULADOS_FILE_PATH = BASE_PATH + "matriculados";
string Settings::INSCRITOS_FILE_PATH = BASE_PATH + "inscritos";
char Settings::DELIMITADOR = ";";

string Settings::GRADUADOS_FILE_PATH = BASE_PATH + "graduados";

// Implementación de los métodos setters
void Settings::setBasePath(const string& newPath) {
    BASE_PATH = newPath;
    // Actualiza las rutas que dependen de BASE_PATH
    PROGRAMAS_FILTRAR_FILE_PATH = BASE_PATH + "programas.csv";
    ADMITIDOS_FILE_PATH = BASE_PATH + "admitidos";
    MATRICULADOS_FILE_PATH = BASE_PATH + "matriculados";
    INSCRITOS_FILE_PATH = BASE_PATH + "inscritos";
    GRADUADOS_FILE_PATH = BASE_PATH + "graduados";
}

void Settings::setDelimitador(const std::string& newDelimitador) {
    DELIMITADOR = newDelimitador; // Modificar el delimitador
}

