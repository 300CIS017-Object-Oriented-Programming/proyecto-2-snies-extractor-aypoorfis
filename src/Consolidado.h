#ifndef CONSOLIDADO_H
#define CONSOLIDADO_H

#include <string>
#include <map>
#include <bits/stl_vector.h>

using std::string;
using std::map;
using std::vector;

class Consolidado {
private:
    // Este mapa contendría los valores de los atributos de la clase:
    // idsexo, genero, anio, semestre, inscritos, admitidos, matriculados, matriculadosprimersemestre, graduados
    map<string, string>datosConsolidado;

public:
    Consolidado() = default;
    Consolidado(const vector<string> &etiquetas);
    // Mantenimiento: Gran cantidad de métodos get y set que tal vez no son estrictamente necesarios
    // Cambio: Se quitaron algunos sets de la clase Consolidado

    // Este metodo se encarga de devolver el valor del atributo idsexo, que es el único que no es un número
    string getGenero() const;
    int getDatoNumerico(string const &dato) const;

    // Este metodo se encarga de inicializar los atributos
    // (Inscritos, Admitidos, Matriculados, MatriculadosPrimerSemestre, Graduados)
    // de la clase con los valores que se encuentran en el vector de parametrosConsolidado
    void setDato(string dato, string valor);
};

#endif // CONSOLIDADO_H
