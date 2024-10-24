#include "Settings.h"
#include <string>

using std::string;

// Inicialización de las variables estáticas
string Settings::BASE_PATH = "C:/SNIES_EXTRACTOR/inputs/";
string Settings::PROGRAMAS_FILTRAR_FILE_PATH = BASE_PATH + "programas.csv";
string Settings::ADMITIDOS_FILE_PATH = BASE_PATH + "admitidos";
string Settings::MATRICULADOS_FILE_PATH = BASE_PATH + "matriculados";
string Settings::INSCRITOS_FILE_PATH = BASE_PATH + "inscritos";
string Settings::GRADUADOS_FILE_PATH = BASE_PATH + "graduados";
string Settings::OUTPUT_FILE_PATH = "C:/SNIES_EXTRACTOR/outputs/output.csv";
string Settings::EXTENSION_ARCHIVOS = ".csv";
char Settings::DELIMITADOR = ';';
int Settings::ANIO_INICIAL = 2010;
int Settings::ANIO_FINAL = 2020;


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

void Settings::setDelimitador(const char& newDelimitador) {
    DELIMITADOR = newDelimitador;
}

void Settings::setAnioInicial(const string &newAnioInicial) {
    ANIO_INICIAL = stoi(newAnioInicial);
}

void Settings::setAnioFinal(const string &newAnioFinal) {
    ANIO_FINAL = stoi(newAnioFinal);
}

void Settings::setAnioAdmitidos(const string &newAnioRuta) {
    ADMITIDOS_FILE_PATH = BASE_PATH + "admitidos" + newAnioRuta + EXTENSION_ARCHIVOS;
}

void Settings::setAnioMatriculados(const string &newAnioRuta) {
    MATRICULADOS_FILE_PATH = BASE_PATH + "matriculados" + newAnioRuta + EXTENSION_ARCHIVOS;
}

void Settings::setAnioInscritos(const string &newAnioRuta) {
    INSCRITOS_FILE_PATH = BASE_PATH + "inscritos" + newAnioRuta + EXTENSION_ARCHIVOS;
}

void Settings::setAnioGraduados(const string &newAnioRuta) {
    GRADUADOS_FILE_PATH = BASE_PATH + "graduados" + newAnioRuta + EXTENSION_ARCHIVOS;
}

// Implementación de los métodos getters
string Settings::getAdmitidosFilePath() {
    return ADMITIDOS_FILE_PATH;
}

string Settings::getMatriculadosFilePath() {
    return MATRICULADOS_FILE_PATH;
}

string Settings::getInscritosFilePath() {
    return INSCRITOS_FILE_PATH;
}

string Settings::getProgramasFiltrarFilePath() {
    return PROGRAMAS_FILTRAR_FILE_PATH;
}

string Settings::getGraduadosFilePath() {
    return GRADUADOS_FILE_PATH;
}


