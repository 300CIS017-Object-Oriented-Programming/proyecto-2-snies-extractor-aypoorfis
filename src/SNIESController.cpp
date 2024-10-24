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

void SNIESController::procesarDatosCsv() const {
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
void SNIESController::consolidarMatriculadosPorAno() const {
    map<int, int> matriculadosVirtual;
    map<int, int> matriculadosPresencial;

    if (programasAcademicos.empty()) {
        cout << "Error: programasAcademicos is not initialized." << endl;
        return;
    }

    for (const auto& pair : this->programasAcademicos) {
        ProgramaAcademico* programa = pair.second;
        string metodologia = programa->getDato("metodoformacion");

        for (int anio = Settings::ANIO_INICIAL; anio <= Settings::ANIO_FINAL; ++anio) {
            int matriculados = programa->getMatriculadosPorAnio(anio);

            if (metodologia == "Virtual") {
                matriculadosVirtual[anio] += matriculados;
            } else if (metodologia == "Presencial") {
                matriculadosPresencial[anio] += matriculados;
            }
        }
    }

    for (const auto& entry : matriculadosVirtual) {
        cout << "Año " << entry.first << ": " << entry.second << " matriculados" << endl;
    }

    for (const auto& entry : matriculadosPresencial) {
        cout << "Año " << entry.first << ": " << entry.second << " matriculados" << endl;
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

#include <fstream>

// Función auxiliar para exportar datos a un archivo CSV
void exportarDiferenciaPorcentualNuevosMatriculados(const std::vector<std::tuple<int, int, int>>& datos, const std::string& rutaArchivo) {
    std::ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        throw std::ios_base::failure("No se pudo abrir el archivo CSV para exportar: " + rutaArchivo);
    }

    archivo << "Año Anterior,Año Actual,Diferencia Porcentual\n";
    for (const auto& [anioAnterior, anioActual, porcentaje] : datos) {
        archivo << anioAnterior << "," << anioActual << "," << porcentaje << "%\n";
    }

    archivo.close();
    std::cout << "Exportación a CSV exitosa: " << rutaArchivo << std::endl;
}

void ProgramaAcademico::calcularDiferenciaPorcentualNuevosMatriculados() const {
    const int limiteInferior = Settings::ANIO_INICIAL;
    const int limiteSuperior = Settings::ANIO_FINAL;
    const int n = limiteSuperior - limiteInferior + 1;

    int cantMatriculadosAnterior = 0;
    int cantMatriculadosActual = getMatriculadosNuevosPorAnio(limiteInferior);
    int porcentaje = 0;

    std::vector<std::tuple<int, int, int>> datos;

    for (int i = 1; i < n; i++) {
        cantMatriculadosAnterior = cantMatriculadosActual;
        cantMatriculadosActual = getMatriculadosNuevosPorAnio(limiteInferior + i);
        if (cantMatriculadosAnterior != 0) {
            porcentaje = (cantMatriculadosActual * 100) / cantMatriculadosAnterior;
        } else {
            porcentaje = 100; // No hay matriculados anteriores
        }

        std::cout << "La diferencia porcentual de nuevos matriculados entre los años "
                  << limiteInferior + i - 1 << " y " << limiteInferior + i << " es: "
                  << porcentaje << "%" << std::endl;

        datos.emplace_back(limiteInferior + i - 1, limiteInferior + i, porcentaje);
    }

    // Exportar los datos a un archivo CSV
    std::string rutaArchivo = Settings::BASE_PATH + "outputs/diferencia_porcentual_nuevos_matriculados.csv";
    exportarDiferenciaPorcentualNuevosMatriculados(datos, rutaArchivo);
}

vector<string> obtenerProgramasSinMatriculasNuevas(const map<string, ProgramaAcademico*> &programas) {
    vector<string> programasSinMatriculas;

    for (const auto &[codigo, programa] : programas) {
        if (programa->sinMatriculasNuevas()) {
            programasSinMatriculas.push_back(programa->getDato("programaacademico"));
        }
    }
    return programasSinMatriculas;

}

void mostrarProgramasSinMatriculasNuevas(const map<string, ProgramaAcademico*> &programas) {
    vector<string> programasSinMatriculas = obtenerProgramasSinMatriculasNuevas(programas);

    cout << "Programas sin matrículas nuevas en tres semestres consecutivos:" << endl;
    for (const auto &nombrePrograma : programasSinMatriculas) {
        cout << nombrePrograma << endl;
    }
}