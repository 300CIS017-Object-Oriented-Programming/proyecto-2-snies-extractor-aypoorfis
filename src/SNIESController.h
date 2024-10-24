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
    map<string, ProgramaAcademico*>& programasAcademicos;
    GestorDatos* gestorDatosObj;
public:

    SNIESController() = default;
    SNIESController(GestorDatos *);
    ~SNIESController();

    void setGestorDatos(GestorDatos *);
    void procesarDatosCsv() const;
    // Si el bool está activada, exporta los datos procesados a un archivo CSV,
    // de lo contrario, solo los calcula.
    void filtrarProgramas(const string &, const string &n, bool) const;

    void calcularDiferenciaPorcentualNuevosMatriculados();

    void consolidarMatriculadosPorAno(bool) const;

    // Métodos auxiliares
    void exportarDatos(const string &formato) const;
};

#endif // SNIES_CONTROLLER_H