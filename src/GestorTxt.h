//
// Created by User on 14/10/2024.
//

#ifndef GESTORTXT_H
#define GESTORTXT_H

#include "GestorDatos.h"

using std::string;
using std::map;
using std::vector;

class GestorTxt : public GestorDatos {
public:

    void exportarDatos(map<string, ProgramaAcademico*> datos) override;
};



#endif //GESTORTXT_H
