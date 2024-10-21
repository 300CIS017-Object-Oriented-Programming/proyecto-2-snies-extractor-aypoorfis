#include "Consolidado.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using std::stoi;
using std::string;
using std::map;
using std::vector;
using std::cerr;
using std::endl;
using std::cout;

Consolidado::Consolidado(const int idSexo, string sexo, int anio, const int semestre) :
idSexo(idSexo), sexo(std::move(sexo)), anio(anio), semestre(semestre), inscritos(0), admitidos(0), matriculados(0), matriculadosPrimerSemestre(0), graduados(0) {}

int Consolidado::getIdSexo() const {
    return idSexo;
}

string Consolidado::getSexo() const {
    return sexo;
}

int Consolidado::getAnio() const {
    return anio;
}

int Consolidado::getSemestre() const {
    return semestre;
}

int Consolidado::getInscritos() const {
    return inscritos;
}

int Consolidado::getAdmitidos() const {
    return admitidos;
}

int Consolidado::getMatriculados() const {
    return matriculados;
}

int Consolidado::getMatriculadosPrimerSemestre() const {
    return matriculadosPrimerSemestre;
}

int Consolidado::getGraduados() const {
    return graduados;
}

bool Consolidado::verificarMapaValido(const map<string, string> &parametros) const{
    const vector<string> LLAVESVALIDAS  = {"inscritos", "admitidos", "matriculados", "matriculadosprimersemestre", "graduados"};
    int i = 0;
    bool esValido = true;
    while(i < LLAVESVALIDAS.size() && esValido) {
        if(parametros.find(LLAVESVALIDAS[i]) == parametros.end()) {
            esValido = false;
        }
        i++;
    }
    return esValido;
}

void Consolidado::setParametros(const map<string,string> &parametros) {
    if(verificarMapaValido(parametros)) {
        inscritos = stoi(parametros.at("inscritos"));
        admitidos = stoi(parametros.at("admitidos"));
        matriculados = stoi(parametros.at("matriculados"));
        matriculadosPrimerSemestre = stoi(parametros.at("matriculadosprimersemestre"));
        graduados = stoi(parametros.at("graduados"));
    } else {
       throw std::invalid_argument("Los parámetros del consolidado no están donde deberían estar.");
    }

}