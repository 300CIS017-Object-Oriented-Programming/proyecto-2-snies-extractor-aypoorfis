#ifndef PROGRAMA_ACADEMICO_H
#define PROGRAMA_ACADEMICO_H

#include <string>
#include <map>
#include "Consolidado.h"

using std::string;
using std::map;
using std::pair;

class ProgramaAcademico {
    map<string, string> datos;
    map<string, Consolidado *> consolidados;
    int getTotalMatriculadosPorAnio(int);
    int getNuevosMatriculadosPorAnio(int);
public:
    ProgramaAcademico() = default;
    ~ProgramaAcademico();
    void setDato(string const &, string);
    string getDato(string const &);
    int getMatriculasNuevasSemestre(string &);
    bool sinMatriculasNuevas() const;
    void addConsolidado(string const &, Consolidado *);
    void modificarConsolidado(string const &);

    // Estas funciones se encargan de mostrar los datos de los consolidados en los años correspondientes.
    void mostrarMatriculadosConsolidado();
    void mostrarDiferenciaPorcentualNuevosMatriculados();
    // Esta función muestra el código SNIES y el nombre del programa académico.
    void mostrarIdentificadoresPrograma();
};

#endif

/*
    1. El mapa datos es un mapá que contiene los datos del programa académico, teniendo como llaves
    los nombres de los datos o columnas donde se ubican en minúsculas y sin espacios.

*/