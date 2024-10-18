#ifndef SNIES_CONTROLLER_H
#define SNIES_CONTROLLER_H

#include <vector>
#include <map>
#include <string>
#include "ProgramaAcademico.h"
#include "GestorCsv.h"

using std::map;
using std::string;
#include "Settings.h"

class SNIESController {

private:
    map<long, ProgramaAcademico *> programasAcademicos;
    GestorCsv gestorCsvObj;
public:
    SNIESController() = default;
    ~SNIESController();
    void procesarDatosCsv(string &, string &);
    // Mantenimiento: Este método tiene un nombre confuso.
    void calcularDatosExtra(bool);
    void buscarProgramas(bool, string &, int);
};

#endif