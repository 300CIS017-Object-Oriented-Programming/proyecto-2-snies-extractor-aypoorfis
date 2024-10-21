#ifndef PROGRAMA_ACADEMICO_H
#define PROGRAMA_ACADEMICO_H

#include <string>
#include <map>
#include <iostream>
#include "Consolidado.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;

class ProgramaAcademico {
    map<string, string> datos;
    map<int, Consolidado *> consolidado;

public:
    ProgramaAcademico();
    ~ProgramaAcademico();
    void setDato(string, string);
    string getDato(string);
    Consolidado *getConsolidado(int);
};

#endif