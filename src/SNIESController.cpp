#include "SNIESController.h"
#include "Settings.h"
#include "GestorDatos.h"
#include "GestorCsv.h"
#include "GestorTxt.h"
#include "GestorJson.h"
#include <fstream>
#include <iostream>
#include <string>


using std::cout;
using std::endl;
using std::ifstream;

SNIESController::~SNIESController() {
    for (auto& pair : programasAcademicos) {
        delete pair.second;
    }
}

void SNIESController::setGestorDatos(GestorDatos* gestor) {
    gestorDatosObj = gestor;
}

SNIESController::SNIESController(GestorDatos* gestor) : programasAcademicos(), gestorDatosObj(gestor) {}

void SNIESController::procesarDatosCsv() const {
    // Inicializar programas de análisis desde el archivo CSV
    GestorCsv::inicializarProgramasDeAnalisisCsv(programasAcademicos);

    // Adjuntar datos de todos los archivos CSV a los programas académicos
    GestorCsv::adjuntarTodosLosDatos(programasAcademicos);
}

void SNIESController::filtrarProgramas(const string& palabraClave, const string& nivelFormacion, bool exportarCSV) const {
    vector<ProgramaAcademico*> programasFiltrados;
    string const LLAVE_CODIGO_SNIES = "codigosnies";

    GestorDatos* gestorCsvObj = new GestorCsv();
    setGestorDatos(gestorCsvObj);

    for (const auto& [key, programa] : programasAcademicos) {
        if (programa->contienePalabraClave(palabraClave) && programa->tieneNivelDeFormacion(nivelFormacion)) {
            programasFiltrados.push_back(programa);
        }
    }

    for (const auto& programa : programasFiltrados) {
        programa->mostrarInformacionPrincipalPrograma();
    }

    if (exportarCSV) {
        map<string, ProgramaAcademico*> programasFiltradosMap;
        for (const auto& programa : programasFiltrados) {
            programasFiltradosMap[programa->getDato("codigosnies")] = programa;
        }
        gestorDatosObj->exportarDatos(programasFiltradosMap);
    }
}

void SNIESController::consolidarMatriculadosPorAno(bool exportarCsv) const {
    string const LLAVE_METODOLOGIA = "metodoformacion";
    int anioInicial = Settings::ANIO_INICIAL;
    int anioFinal = Settings::ANIO_FINAL;

    map<int, int> matriculadosVirtual;
    map<int, int> matriculadosPresencial;

    if (programasAcademicos.empty()) {
        throw std::domain_error("Error: 'programasAcademicos' is not initialized or contains no data.");
    }

    for (const auto &[key, value] : this->programasAcademicos) {
        ProgramaAcademico* programa = value;
        string metodologia = programa->getDato(LLAVE_METODOLOGIA);

        for (int anio = anioInicial; anio <= anioFinal; ++anio) {
            int matriculados = programa->getMatriculadosPorAnio(anio);

            if (metodologia == "Virtual") {
                matriculadosVirtual[anio] += matriculados;
            } else if (metodologia == "Presencial") {
                matriculadosPresencial[anio] += matriculados;
            }
        }
    }

    for (const auto& [anio, matriculados] : matriculadosVirtual) {
        cout << "Año " << anio << ": " << matriculados << " matriculados" << endl;
    }

    for (const auto& [anio, matriculados] : matriculadosPresencial) {
        cout << "Año " << anio << ": " << matriculados << " matriculados" << endl;
    }
}

void SNIESController::exportarDatos(const string& formato) const {
    if (formato == "CSV") {
        gestorDatosObj->exportarDatos(programasAcademicos);
    } else if (formato == "TXT") {
        gestorDatosObj->exportarDatos(programasAcademicos);
    } else if (formato == "JSON") {
        gestorDatosObj->exportarDatos(programasAcademicos);
    }
}

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