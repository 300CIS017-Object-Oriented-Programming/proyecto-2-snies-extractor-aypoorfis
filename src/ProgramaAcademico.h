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
    int getMatriculadosNuevosPorSemestre(int) const;
    int getMatriculadosNuevosPorAnio(int) const;
    int getMatriculadosPorSemestre(int) const;

    void calcularDiferenciaPorcentualNuevosMatriculados() const;

public:
    int getMatriculadosPorAnio(int) const;
    ProgramaAcademico() = default;
    ~ProgramaAcademico();
    void setDato(string const &, string);
    string getDato(string const &);

    bool sinMatriculasNuevas() const;
    bool contienePalabraClave(string const &) const;
    bool tieneNivelDeFormacion(string const &) const;
    void addConsolidado(string const &, Consolidado *);
    void modificarConsolidado(string const &, string const &, string const &);

    // Estas funciones se encargan de mostrar los datos de los consolidados en los años correspondientes.
    void mostrarMatriculadosConsolidado();
    void mostrarDiferenciaPorcentualNuevosMatriculados() const;
    // Esta función muestra el código SNIES y el nombre del programa académico.
    void mostrarIdentificadoresPrograma();
    // Esta función muestra el código SNIES, nombre del programa, código de la institución, nombre de la institución
    // y metodologia de formación.
    void mostrarInformacionPrincipalPrograma();
};

#endif

/*
    1. El mapa datos es un mapá que contiene los datos del programa académico, teniendo como llaves
    los nombres de los datos o columnas donde se ubican en minúsculas y sin espacios.

*/