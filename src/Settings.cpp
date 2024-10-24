#include "Settings.h"

// Define static member variables
string Settings::ADMITIDOS_FILE_PATH;
string Settings::MATRICULADOS_FILE_PATH;
string Settings::INSCRITOS_FILE_PATH;
string Settings::PROGRAMAS_FILTRAR_FILE_PATH;
string Settings::GRADUADOS_FILE_PATH;
string Settings::BASE_PATH;
string Settings::EXTENSION_ARCHIVOS;
char Settings::DELIMITADOR;
int Settings::ANIO_INICIAL;
int Settings::ANIO_FINAL;

void Settings::setBasePath(const string &newPath) {
    BASE_PATH = newPath;
}

void Settings::setDelimitador(const char &newDelimitador) {
    DELIMITADOR = newDelimitador;
}

void Settings::setAnioInicial(const string &newAnioInicial) {
    ANIO_INICIAL = std::stoi(newAnioInicial);
}

void Settings::setAnioFinal(const string &newAnioFinal) {
    ANIO_FINAL = std::stoi(newAnioFinal);
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