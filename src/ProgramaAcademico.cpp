#include "ProgramaAcademico.h"
#include "Consolidado.h"
#include <iostream>


using std::string;
using std::cout;
using std::endl;


ProgramaAcademico::~ProgramaAcademico() {
    for (auto const &[key, value] : consolidados) {
        delete value;
    }
}


void ProgramaAcademico::setDato(string const &atributo, string valor) {
    datos[atributo] = std::move(valor);
}


string ProgramaAcademico::getDato(string const &atributo) {
    return datos[atributo];
}


bool ProgramaAcademico::sinMatriculasNuevas() const {
    bool sinMatriculas = false;
    int contador = 0;
    auto it = consolidados.begin();
    while (it != consolidados.end() && !sinMatriculas) {
        if (it->second->getMatriculados() == 0) {
            contador++;
            if (contador == 3) {
                sinMatriculas = true;
            }
        } else {
            contador = 0;
        }
        ++it;
    }
    return sinMatriculas;
}


void ProgramaAcademico::addConsolidado(int semestre, Consolidado *consolidado) {
    consolidados[semestre] = consolidado;
}


int ProgramaAcademico::getTotalMatriculadosPorAnio(int anio) {
    int semestre1 = anio * 10 + 1;
    int semestre2 = semestre1 + 1;
    int cantidadMatriculados = 0;

    if (auto it1 = consolidados.find(semestre1) && it1 != consolidados.end()) {
        cantidadMatriculados += it1->second->getMatriculados();
    }

    if (auto it2 = consolidados.find(semestre2) && it2 != consolidados.end()) {
        cantidadMatriculados += it2->second->getMatriculados();
    }
    return cantidadMatriculados;
}


int ProgramaAcademico::getNuevosMatriculadosPorAnio(int anio) {
    int semestre1 = anio * 10 + 1;
    int semestre2 = semestre1 + 1;
    int cantidadNuevosMatriculados = 0;

    if (auto it1 = consolidados.find(semestre1) && it1 != consolidados.end()) {
        cantidadNuevosMatriculados += it1->second->getNuevosMatriculados();
    }

    if (auto it2 = consolidados.find(semestre2) && it2 != consolidados.end()) {
        cantidadNuevosMatriculados += it2->second->getNuevosMatriculados();
    }
    return cantidadNuevosMatriculados;
}


void ProgramaAcademico::mostrarMatriculadosConsolidado(const pair<int, int> &aniosAnalisis) {
    const int limiteInferior = aniosAnalisis.first;
    const int limiteSuperior = aniosAnalisis.second;
    string const LLAVENOMBREPROGRAMA = "programaacademico";
    cout << "El número de matriculados registrados para el programa " << this->getDato(LLAVENOMBREPROGRAMA) << " entre los años ";
    cout << limiteInferior << " y " << limiteSuperior << "es :" << endl;
    for(int i = limiteInferior; i <= limiteSuperior; i++) {
        cout << i << ": " << getTotalMatriculadosPorAnio(i) << endl;
    }
}


void ProgramaAcademico::mostrarDiferenciaPorcentualNuevosMatriculados(const pair<int, int> &aniosAnalisis) {
    const int limiteInferior = aniosAnalisis.first;
    const int limiteSuperior = aniosAnalisis.second;
    const int n = limiteSuperior - limiteInferior + 1;

    int cantMatriculadosAnterior = 0;
    int cantMatriculadosActual = getNuevosMatriculadosPorAnio(limiteInferior);
    int porcentaje = 0;

    for (int i = 1; i < n; i++) {
        cantMatriculadosAnterior = cantMatriculadosActual;
        cantMatriculadosActual = getTotalMatriculadosPorAnio(limiteInferior + i);
        porcentaje = (cantMatriculadosActual * 100) / cantMatriculadosAnterior;

        cout << "La diferencia porcentual de nuevos matriculados entre los años "
             << limiteInferior + i - 1 << " y " << limiteInferior + i << " es: "
             << porcentaje << "%" << endl;
    }
}


void ProgramaAcademico::mostrarIdentificadoresPrograma() {
    string const LLAVECODIGOSNIES = "codigosnies";
    string const LLAVENOMBREPROGRAMAACADEMICO = "programaacademico";
    cout << "Código SNIES: " << this->getDato(LLAVECODIGOSNIES) << endl;
    cout << "Nombre del programa académico: " << this->getDato(LLAVENOMBREPROGRAMAACADEMICO) << endl;
}