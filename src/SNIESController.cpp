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

void SNIESController::calcularDatosExtra(bool flag) {
    for (auto& pair : programasAcademicos) {
        ProgramaAcademico* programa = pair.second;

        int totalMatriculados = 0;
        int nuevosMatriculados = 0;

        for (const auto& consolidadoPair : programa->consolidados) {
            Consolidado* consolidado = consolidadoPair.second;
            totalMatriculados += consolidado->getMatriculados();
            nuevosMatriculados += consolidado->getMatriculadosPrimerSemestre();
        }

        // Guardar los datos calculados en el programa académico
        programa->setDato("totalMatriculados", to_string(totalMatriculados));
        programa->setDato("nuevosMatriculados", to_string(nuevosMatriculados));
    }

    if (flag) {
        // Exportar datos adicionales si la flag está activada
        gestorCsvObj.exportarDatos(programasAcademicos);
    }
}

void SNIESController::buscarProgramas(bool flag, const string& criterio, int valor) {
    // Implementación de búsqueda de programas académicos
    for (auto& pair : programasAcademicos) {
        ProgramaAcademico* programa = pair.second;
        // Lógica para buscar programas basados en el criterio y valor
        // ...
    }

    if (flag) {
        // Exportar resultados de búsqueda si la flag está activada
        // ...
    }
}

void SNIESController::procesarConsolidados(ProgramaAcademico* programa, int i, int& sumaNeosSemestre) {
    // Implementación de procesamiento de consolidados
    // ...
}

void SNIESController::exportarDatos(const string& rutaOutput, const vector<vector<string>>& matrizFinal, const string& formato) {
    if (formato == "CSV") {
        gestorCsvObj.exportarDatos(programasAcademicos);
    } else if (formato == "TXT") {
        gestorTxtObj.exportarDatos(programasAcademicos);
    } else if (formato == "JSON") {
        gestorJsonObj.exportarDatos(programasAcademicos);
    }
}