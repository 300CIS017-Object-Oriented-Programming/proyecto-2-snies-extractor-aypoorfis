//
// Created by User on 13/10/2024.
//

#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include <string>
#include <vector>
#include <map>

#include "Settings.h" // lo agrego pero no se muy bien como utilizara la clase aqui.

using std::string;
using std::map;
using std::vector;


class GestorDatos {
public:
    // Destructor
    virtual ~GestorDatos() = default;
    // Metodo para escribir datos procesados en un archivo
    virtual void exportarDatos(const string& filePath, const vector<map<string, string>>& datos) = 0;

protected:
    // Metodo de ayuda para manejar errores comunes
    void manejarErrores(const string& mensaje);
};

#endif // GESTOR_DATOS_H