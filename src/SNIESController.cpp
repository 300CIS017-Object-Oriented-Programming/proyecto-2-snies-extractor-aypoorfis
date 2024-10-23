#include "SNIESController.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Settings.h"
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
void SNIESController::consolidarMatriculadosPorAno() {
    map<int, int> matriculadosVirtual;
    map<int, int> matriculadosPresencial;

    categorizarMatriculadosPorAno(matriculadosVirtual, matriculadosPresencial);

    mostrarResultados(matriculadosVirtual, matriculadosPresencial);

    exportarConsolidadoCSV(matriculadosVirtual, matriculadosPresencial);
}


void SNIESController::categorizarMatriculadosPorAno(map<int, int>& matriculadosVirtual, map<int, int>& matriculadosPresencial) {
    for (const auto& pair : programasAcademicos) {
        ProgramaAcademico* programa = pair.second;
        string metodologia = programa->getDato("metodoformacion");

        for (int anio = Settings::ANIO_INICIAL; anio <= Settings::ANIO_FINAL; ++anio) {
            if (metodologia == "Virtual") {
                matriculadosVirtual[anio] += programa->getMatriculadosPorAnio(anio);
            } else if (metodologia == "Presencial") {
                matriculadosPresencial[anio] += programa->getMatriculadosPorAnio(anio);
            }
        }
    }
}

void SNIESController::mostrarResultados(const map<int, int>& matriculadosVirtual, const map<int, int>& matriculadosPresencial) {
    cout << "Consolidado de estudiantes matriculados por año en programas virtuales:" << endl;
    for (const auto& entry : matriculadosVirtual) {
        cout << "Año " << entry.first << ": " << entry.second << " matriculados" << endl;
    }

    cout << "\nConsolidado de estudiantes matriculados por año en programas presenciales:" << endl;
    for (const auto& entry : matriculadosPresencial) {
        cout << "Año " << entry.first << ": " << entry.second << " matriculados" << endl;
    }
}

void SNIESController::exportarConsolidadoCSV(const map<int, int>& matriculadosVirtual, const map<int, int>& matriculadosPresencial) {
    string filePath = Settings::BASE_PATH + "consolidado_matriculados.csv";
    ofstream outFile(filePath);

    if (outFile.is_open()) {
        outFile << "Año,Virtual,Presencial\n";
        for (int anio = Settings::ANIO_INICIAL; anio <= Settings::ANIO_FINAL; ++anio) {
            outFile << anio << "," << matriculadosVirtual.at(anio) << "," << matriculadosPresencial.at(anio) << "\n";
        }
        outFile.close();
        cout << "\nConsolidado exportado a " << filePath << endl;
    } else {
        cerr << "Error al abrir el archivo para exportar los datos." << endl;
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