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

Consolidado::Consolidado(const vector<string> &etiquetas) {
    int NUMERO_DE_ETIQUETAS = 9;
    if(etiquetas.size() == NUMERO_DE_ETIQUETAS) {
        for(auto const &etiqueta : etiquetas) {
            datosConsolidado[etiqueta] = "";
        }
    }
    else {
        throw std::invalid_argument("El número de etiquetas para el consolidado no es el correcto.");
    }
}

int Consolidado::getDatoNumerico(string const &etiquetaDato) const {
    string LLAVE_DATO = etiquetaDato;
    auto it = datosConsolidado.find(LLAVE_DATO);
    if(it != datosConsolidado.end()) {
        return stoi(it->second);
    }
    const string mensajeError = "El atributo " + etiquetaDato + " no está en el mapa de datos del consolidado.";
    throw std::invalid_argument(mensajeError);
}

string Consolidado::getGenero() const {
    string LLAVE_SEXO = "genero";
    auto it = datosConsolidado.find(LLAVE_SEXO);
    if(it != datosConsolidado.end()) {
        return it->second;
    }
    throw std::invalid_argument("El atributo genero no está en el mapa de datos del consolidado");
}
