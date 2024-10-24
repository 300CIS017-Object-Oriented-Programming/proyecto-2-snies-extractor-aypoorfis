#include "Consolidado.h"
#include "Settings.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "sstream"

using std::stoi;
using std::string;
using std::map;
using std::vector;
using std::cerr;
using std::endl;
using std::cout;
using std::ostringstream;

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
    const string& LLAVE_DATO = etiquetaDato;
    if(const auto it = datosConsolidado.find(LLAVE_DATO); it != datosConsolidado.end()) {
        return stoi(it->second);
    }
    const string mensajeError = "El atributo " + etiquetaDato + " no está en el mapa de datos del consolidado.";
    throw std::invalid_argument(mensajeError);
}

string Consolidado::getGenero() const {
    const string LLAVE_SEXO = "genero";
    if(const auto it = datosConsolidado.find(LLAVE_SEXO); it != datosConsolidado.end()) {
        return it->second;
    }
    throw std::invalid_argument("El atributo genero no está en el mapa de datos del consolidado");
}

void Consolidado::setDato(string const &dato, string const &valor) {
    if(const auto it = datosConsolidado.find(dato); it != datosConsolidado.end()) {
        it->second = valor;
    }
    else {
        throw std::invalid_argument("El dato " + dato + " no está en el mapa de datos del consolidado.");
    }
}

string Consolidado::toTxt() const {
    ostringstream ossTxt;
    for(const auto &[key, value] : datosConsolidado) {
        ossTxt << key << ": " << value << "\n";
    }
    return ossTxt.str();
}


string Consolidado::toJson() const {
    ostringstream ossJson;
    ossJson << "{\n";
    for (auto it = datosConsolidado.begin(); it != datosConsolidado.end(); ++it) {
        ossJson << "  \"" << it->first << "\": \"" << it->second << "\"";
        ossJson << (std::next(it) != datosConsolidado.end() ? ",\n" : "\n");
    }
    ossJson << "}";
    return ossJson.str();
}

string Consolidado::toCsv() const {
    std::ostringstream ossCsv;
    bool isFirst = true;
    const char delimitador = Settings::DELIMITADOR;
    for (const auto& [key, value] : datosConsolidado) {
        ossCsv << (isFirst ? "" : delimitador) << "\"" << value << "\"";
        isFirst = false;
    }
    return ossCsv.str();
}

