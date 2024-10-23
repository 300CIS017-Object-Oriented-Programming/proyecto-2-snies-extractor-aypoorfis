#include "SNIESController.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;

using namespace std;

SNIESController::~SNIESController() {
    for (auto& pair : programasAcademicos) {
        delete pair.second;
    }
}

void SNIESController::procesarDatosCsv() {
    // Inicializar programas de análisis desde el archivo CSV
    GestorCsv::inicializarProgramasDeAnalisisCsv(programasAcademicos);

    // Adjuntar datos de todos los archivos CSV a los programas académicos
    GestorCsv::adjuntarTodosLosDatos(programasAcademicos);
}

void SNIESController::filtrarProgramas(const string& palabraClave, const string& nivelFormacion, bool exportarCSV) {
    vector<ProgramaAcademico*> resultados;

    for (auto& pair : programasAcademicos) {
        ProgramaAcademico* programa = pair.second;

        if (programa->contienePalabraClave(palabraClave) && programa->tieneNivelDeFormacion(nivelFormacion)) {
            resultados.push_back(programa);
        }
    }

    for (ProgramaAcademico* programa : resultados) {
        programa->mostrarInformacionPrincipalPrograma();
    }

    if (exportarCSV) {
        map<string, ProgramaAcademico*> resultadosMap;
        for (ProgramaAcademico* programa : resultados) {
            resultadosMap[programa->getDato("codigosnies")] = programa;
        }
        gestorCsvObj.exportarDatos(resultadosMap);
    }
}

void SNIESController::exportarDatos(const string& formato) {
    if (formato == "CSV") {
        gestorCsvObj.exportarDatos(programasAcademicos);
    } else if (formato == "TXT") {
        gestorTxtObj.exportarDatos(programasAcademicos);
    } else if (formato == "JSON") {
        gestorJsonObj.exportarDatos(programasAcademicos);
    }
}