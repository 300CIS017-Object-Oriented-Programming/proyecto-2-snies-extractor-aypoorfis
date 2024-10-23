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
    vector<ProgramaAcademico*> resultados;

    for (auto& pair : programasAcademicos) {
        ProgramaAcademico* programa = pair.second;

        // Comparar el criterio y el valor con los datos del programa
        if (criterio == "totalMatriculados") {
            int totalMatriculados = stoi(programa->getDato("totalMatriculados"));
            if (totalMatriculados == valor) {
                resultados.push_back(programa);
            }
        } else if (criterio == "nuevosMatriculados") {
            int nuevosMatriculados = stoi(programa->getDato("nuevosMatriculados"));
            if (nuevosMatriculados == valor) {
                resultados.push_back(programa);
            }
        }
        // Agregar más criterios según sea necesario
    }

    // Imprimir los resultados de la búsqueda
    for (ProgramaAcademico* programa : resultados) {
        programa->mostrarIdentificadoresPrograma();
    }

    if (flag) {
        // Exportar resultados de búsqueda si la flag está activada
        map<string, ProgramaAcademico*> resultadosMap;
        for (ProgramaAcademico* programa : resultados) {
            resultadosMap[programa->getDato("codigosnies")] = programa;
        }
        gestorCsvObj.exportarDatos(resultadosMap);
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