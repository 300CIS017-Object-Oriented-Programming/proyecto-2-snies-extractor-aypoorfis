#ifndef VIEW_H
#define VIEW_H

#include "SNIESController.h"

// Recomendación Linter: Dejar de usar using namespace std y usar std::.
using namespace std;

class View {
private:
    SNIESController controlador;
    bool isConvetibleToInt(const string &);
    bool mostrarPantallaBienvenido();
    void mostrarDatosExtra();
    void buscarPorPalabraClaveYFormacion();
    void mostrarEstudiantesMatriculadosXAno(); //REVISAR Danilo
    void exportarDiferenciaPorcentualAnualNuevosEstudiantes(); //revisar danilo
    void exportarDatos(); // REVISAR danilo
    void mostrarCalculoDiferenciaPorcentualNuevosMatriculado();
    void salir();
public:
    View();
    ~View();
    // Estructura: El View debería tener solo una función pública.
    void runMenu();
};

#endif