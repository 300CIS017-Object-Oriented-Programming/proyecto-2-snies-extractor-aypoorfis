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

    // Métodos auxiliares
    // Procesa los consolidados de los programas académicos, "i" es el índice del consolidado actual.
    void procesarConsolidados(ProgramaAcademico* programa, int i, int& sumaNeosSemestre);
    void exportarDatos(const string& rutaOutput, const vector<vector<string>>& matrizFinal, const string& formato);

public:


    SNIESController() = default;

    ~SNIESController();

    void procesarDatosCsv();
    // Si el flag está activada, exporta los datos procesados a un archivo CSV,
    // de lo contrario, solo los calcula.
    void calcularDatosExtra(bool flag);
    void buscarProgramas(bool flag, const string& criterio, int valor);
};

#endif // SNIES_CONTROLLER_H