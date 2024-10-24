#include "Settings.h"

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
vector<string> Settings::ETIQUETAS_COLUMNAS = {"Código de la institución", "IES padre",
    "institución principal o seccional", "ID sector IES", "sector IES",
    "ID carácter", "carácter IES", "código del departamento (IES)", "departamento de domicilio de la IES",
    "código del municipio IES", "municipio de domicilio de la IES", "Código SNIES del programa", "programa académico",
    "núcleo básico del conocimiento", "ID nivel académico", "nivel académico", "ID nivel de formación",
    "nivel de formación", "ID metodología", "metodología", "ID área", "área de conocimiento", "ID núcleo",
    "núcleo básico del conocimiento (NBC)", "ID CINE campo amplio", "descripción CINE campo amplio",
    "ID CINE campo específico", "descripción CINE campo específico", "ID CINE código detallado",
    "descripción CINE código detallado", "código del departamento (programa)", "departamento de oferta del programa",
    "código del municipio (programa)", "municipio de oferta del programa", "Inscritos", "admitidos",
    "nuevos matriculados", "graduados", "género", "año", "semestre"};

vector<string> Settings::LLAVES_DATOS = {"codigodelainstitucion", "iespadre", "institucionprincipaloseccional", "idsectories", "sectories",
    "idcaracter", "caracteries", "codigodeldepartamentoies", "departamentodedomiciliodelaies",
    "codigodelmunicipioies", "municipiodedomiciliodelaies", "codigosniesdelprograma", "programaacademico",
    "nucleobasicodelconocimiento", "idnivelacademico", "nivelacademico", "idniveldeformacion",
    "niveldeformacion", "idmetodologia", "metodologia", "idarea", "areadeconocimiento", "idnucleo",
    "nucleobasicodelconocimientonbc", "idcinecampoamplio", "descripcioncinecampoamplio",
    "idcinecampoespecifico", "descripcioncinecampoespecifico", "idcinecodigodetallado",
    "descripcioncinecodigodetallado", "codigodeldepartamentoprograma", "departamentodeofertadelprograma",
    "codigodelmunicipioprograma", "municipiodeofertadelprograma", "inscritos", "admitidos",
    "nuevosmatriculados", "graduados", "genero", "ano", "semestre"};


// Implementación de los métodos setters
void Settings::setBasePath(const string& newPath) {
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