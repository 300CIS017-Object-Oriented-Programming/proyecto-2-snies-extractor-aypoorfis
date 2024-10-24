#ifndef GESTORTXT_H
#define GESTORTXT_H

#include "GestorDatos.h"

using std::string;
using std::map;

class GestorTxt : public GestorDatos {
public:
    GestorTxt() = default;
    ~GestorTxt() = default;
    void exportarDatos(map<string, ProgramaAcademico*> &datos) override;
};

#endif //GESTORTXT_H
