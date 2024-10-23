//
// Created by User on 13/10/2024.
//
#ifndef GESTOR_JSON_H
#define GESTOR_JSON_H

#include "GestorDatos.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::map;
using std::vector;


class GestorJson : public GestorDatos {
public:
    void exportarDatos(map<string, ProgramaAcademico*> datos) override;
};

#endif // GESTOR_JSON_H
