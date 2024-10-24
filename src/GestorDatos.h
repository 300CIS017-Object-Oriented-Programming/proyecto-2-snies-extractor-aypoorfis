//
// Created by User on 13/10/2024.
//

#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include <string>
#include <vector>
#include <map>
#include "ProgramaAcademico.h"

using std::string;
using std::map;
using std::vector;

class GestorDatos {
public:
    GestorDatos() = default;
    // Destructor
    virtual ~GestorDatos() = default;
    // Metodo para escribir datos procesados en un archivo
    virtual void exportarDatos(map<string, ProgramaAcademico*> &) = 0;
};

#endif // GESTOR_DATOS_H