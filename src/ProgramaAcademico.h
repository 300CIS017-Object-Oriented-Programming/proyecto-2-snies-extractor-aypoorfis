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
    map<int, Consolidado *> consolidados;
    int getTotalMatriculadosPorAnio(int);
    int getNuevosMatriculadosPorAnio(int);
public:
    ProgramaAcademico() = default;
    ~ProgramaAcademico();
    void setDato(string const &, string);
    string getDato(string const &);
    bool sinMatriculasNuevas() const;
    void addConsolidado(int, Consolidado *);

    // Estas funciones se encargan de mostrar los datos de los consolidados en los años correspondientes
    // donde el primer entero de la pareja es el límite inferior y el segundo el límite superior, incluyendolos.
    void mostrarMatriculadosConsolidado(const pair<int, int> &);
    void mostrarDiferenciaPorcentualNuevosMatriculados(const pair<int, int> &);
    // Esta función muestra el código SNIES y el nombre del programa académico.
    void mostrarIdentificadoresPrograma();
};

#endif

/*
    1. El mapa datos es un mapá que contiene los datos del programa académico, teniendo como llaves
    los nombres de los datos o columnas donde se ubican en minúsculas y sin espacios.

*/