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
    map<long, ProgramaAcademico *> programasAcademicos;
    GestorCsv gestorCsvObj;
    GestorTxt gestorTxtObj;
    GestorJson gestorJsonObj;

    // Métodos auxiliares
    void procesarConsolidados(ProgramaAcademico* programa, int i, int& sumaNeosSemestre);
    void exportarDatos(const string& rutaOutput, const vector<vector<string>>& matrizFinal, const string& formato);

public:
    SNIESController() = default;

    ~SNIESController();

    void procesarDatosCsv(const string& rutaInput, const string& rutaOutput);
    void calcularDatosExtra(bool flag);
    void buscarProgramas(bool flag, const string& criterio, int valor);
};

#endif // SNIES_CONTROLLER_H