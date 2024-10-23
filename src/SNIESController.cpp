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


void SNIESController::buscarProgramas(bool flag, const string& criterio, int valor) {
    vector<ProgramaAcademico*> resultados;

    for (auto& pair : programasAcademicos) {
        ProgramaAcademico* programa = pair.second;

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
    }

    for (ProgramaAcademico* programa : resultados) {
        programa->mostrarIdentificadoresPrograma();
    }

    if (flag) {
        map<string, ProgramaAcademico*> resultadosMap;
        for (ProgramaAcademico* programa : resultados) {
            resultadosMap[programa->getDato("codigosnies")] = programa;
        }
        gestorCsvObj.exportarDatos(resultadosMap);
    }
}

void SNIESController::filtrarProgramas(const string& palabraClave, const string& nivelFormacion, bool exportarCSV) {
    vector<ProgramaAcademico*> resultados;

    for (auto& pair : programasAcademicos) {

        ProgramaAcademico* programa = pair.second;
        string nombrePrograma = programa->getDato("programaacademico");
        string nivel = programa->getDato("nivelformacion");

        if (nombrePrograma.find(palabraClave) != string::npos &&   nivel == nivelFormacion) {
            resultados.push_back(programa);
        }
    }

    for (ProgramaAcademico* programa : resultados) {
        cout << "Código SNIES: " << programa->getDato("codigosnies") << endl;
        cout << "Nombre del Programa: " << programa->getDato("programaacademico") << endl;
        cout << "Código de la Institución: " << programa->getDato("codigoinstitucion") << endl;
        cout << "Nombre de la Institución: " << programa->getDato("nombreinstitucion") << endl;
        cout << "Metodología: " << programa->getDato("metodologia") << endl;
        cout << "----------------------------------------" << endl;
    }

    if (exportarCSV) {
        map<string, ProgramaAcademico*> resultadosMap;
        for (ProgramaAcademico* programa : resultados) {
            resultadosMap[programa->getDato("codigosnies")] = programa;
        }
        gestorCsvObj.exportarDatos(resultadosMap);
    }
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