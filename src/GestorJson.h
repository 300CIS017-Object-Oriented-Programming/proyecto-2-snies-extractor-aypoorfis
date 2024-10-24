
#ifndef GESTOR_JSON_H
#define GESTOR_JSON_H

#include "GestorDatos.h"

#include <string>
#include <map>

using std::string;
using std::map;
using std::vector;


class GestorJson : public GestorDatos {
public:
    void exportarDatos(map<string, ProgramaAcademico *> &) override;
};

#endif // GESTOR_JSON_H
