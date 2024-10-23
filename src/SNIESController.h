#ifndef SNIES_CONTROLLER_H
#define SNIES_CONTROLLER_H

#include <vector>
#include <map>
#include <string>
#include "ProgramaAcademico.h"
#include "GestorCsv.h"
#include "GestorTxt.h"
#include "GestorJson.h"

using std::map;
using std::string;
using std::vector;

class SNIESController {
private:
    map<string, ProgramaAcademico *> &programasAcademicos;
    GestorCsv gestorCsvObj;
    GestorTxt gestorTxtObj;
    GestorJson gestorJsonObj;

public:

    SNIESController() = default;

    ~SNIESController();

    void procesarDatosCsv();

    // Si el bool está activada, exporta los datos procesados a un archivo CSV,
    // de lo contrario, solo los calcula.
    void filtrarProgramas(const string &palabraClave, const string &nivelFormacion, bool exportarCSV);

    static void consolidarMatriculadosPorAno();

    static void categorizarMatriculadosPorAno(map<int, int> &matriculadosVirtual, map<int, int> &matriculadosPresencial);

    static void mostrarResultados(const map<int, int> &matriculadosVirtual, const map<int, int> &matriculadosPresencial);

    static void exportarConsolidadoCSV(const map<int, int> &matriculadosVirtual, const map<int, int> &matriculadosPresencial);

    // Métodos auxiliares
    void exportarDatos(const string &formato);
};

#endif // SNIES_CONTROLLER_H