#include "ProgramaAcademico.h"
#include "Consolidado.h"
#include "Settings.h"
#include <iostream>
#include <string>
#include <map>


using std::string;
using std::cout;
using std::endl;
using std::to_string;

ProgramaAcademico::~ProgramaAcademico() {
    for (auto const &[key, value] : consolidados) {
        delete value;
    }
    consolidados.clear();
    datos.clear();
}


void ProgramaAcademico::setDato(string const &atributo, string valor) {
    datos[atributo] = std::move(valor);
}


string ProgramaAcademico::getDato(string const &atributo) {
    return datos[atributo];
}

int ProgramaAcademico::getMatriculadosNuevosPorSemestre(int const anioSemestre) const{
    int resultado = 0;
    string const LLAVEGENEROS = "matriculados";
    // Este vector contiene los géneros M: Masculino, F: Femenino, T: Transgénero, O: Otro
    vector<string> generos = {"M", "F", "T", "O"};

    for (const auto &genero : generos) {
        auto it = consolidados.find(to_string(anioSemestre) + genero);
        if (it != consolidados.end()) {
            resultado += it->second->getDatoNumerico(LLAVEGENEROS);
        }
    }
    return resultado;
}

int ProgramaAcademico::getMatriculadosNuevosPorAnio(int const anio) const {
    const int semestre1 = anio * 10 + 1;
    int semestre2 = semestre1 + 1;
    int cantidadNuevosMatriculados = 0;
    cantidadNuevosMatriculados += getMatriculadosNuevosPorSemestre(semestre1);
    cantidadNuevosMatriculados += getMatriculadosNuevosPorSemestre(semestre2);
    return cantidadNuevosMatriculados;
}

bool ProgramaAcademico::sinMatriculasNuevas() const {
    int ANIOINICIAL = Settings::ANIO_INICIAL;
    int ANIOFINAL = Settings::ANIO_INICIAL;
    int contador = 0;
    int anio = ANIOINICIAL;

    while (anio <= ANIOFINAL) {
        for (int semestre = 1; semestre <= 2; semestre++) {
            int anioSemestre = anio * 10 + semestre;
            contador = (getMatriculadosPorSemestre(anioSemestre) == 0) ? contador + 1 : 0;
            if (contador == 3) {
                return true;
            }
        }
        anio++;
    }
    return false;
}

void ProgramaAcademico::addConsolidado(string const &anioSemestreGenero, Consolidado *consolidado) {
    consolidados[anioSemestreGenero] = consolidado;
}

void ProgramaAcademico::modificarConsolidado(string const &anioSemestreGenero, string const &llave, string const &valor) {
    auto it = consolidados.find(anioSemestreGenero);
    if (it != consolidados.end()) {
        it->second->setDato(llave, valor);
    } else {
        throw std::invalid_argument("No se encontró el consolidado para el año, semestre y género indicado");
    }
}

int ProgramaAcademico::getMatriculadosPorSemestre(int anioSemestre) const{
    int resultado = 0;
    string const LLAVEMATRICULADOS = "matriculados";
    // Este vector contiene los géneros M: Masculino, F: Femenino, T: Transgénero, O: Otro
    vector<string> generos = {"M", "F", "T", "O"};

    for (const auto &genero : generos) {
        auto it = consolidados.find(to_string(anioSemestre) + genero);
        if (it != consolidados.end()) {
            resultado += it->second->getDatoNumerico(LLAVEMATRICULADOS);
        }
    }
    return resultado;
}

int ProgramaAcademico::getMatriculadosPorAnio(int anio) const {
    int semestre1 = anio * 10 + 1;
    int semestre2 = semestre1 + 1;
    int cantidadMatriculados = 0;
    cantidadMatriculados += getMatriculadosPorSemestre(semestre1);
    cantidadMatriculados += getMatriculadosPorSemestre(semestre2);
    return cantidadMatriculados;
}

void ProgramaAcademico::mostrarMatriculadosConsolidado() {
    const int limiteInferior = Settings::ANIO_INICIAL;
    const int limiteSuperior = Settings::ANIO_FINAL;
    string const LLAVENOMBREPROGRAMA = "programaacademico";
    cout << "El número de matriculados registrados para el programa " << this->getDato(LLAVENOMBREPROGRAMA) << " entre los años ";
    cout << limiteInferior << " y " << limiteSuperior << "es :" << endl;
    for(int i = limiteInferior; i <= limiteSuperior; i++) {
        cout << i << ": " << getMatriculadosPorAnio(i) << endl;
    }
}

void ProgramaAcademico::mostrarDiferenciaPorcentualNuevosMatriculados() const{
    const int limiteInferior = Settings::ANIO_INICIAL;
    const int limiteSuperior = Settings::ANIO_FINAL;
    const int n = limiteSuperior - limiteInferior + 1;

    int cantMatriculadosAnterior = 0;
    int cantMatriculadosActual = getMatriculadosNuevosPorAnio(limiteInferior);
    int porcentaje = 0;

    for (int i = 1; i < n; i++) {
        cantMatriculadosAnterior = cantMatriculadosActual;
        cantMatriculadosActual = getMatriculadosNuevosPorAnio(limiteInferior + i);
        if (cantMatriculadosAnterior != 0) {
            porcentaje = (cantMatriculadosActual * 100) / cantMatriculadosAnterior;
        } else {
            porcentaje = 100; // No hay matriculados anteriores
        }

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