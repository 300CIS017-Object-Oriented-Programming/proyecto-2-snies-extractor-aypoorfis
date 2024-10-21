#ifndef CONSOLIDADO_H
#define CONSOLIDADO_H

#include <string>
#include <map>

using std::string;
using std::map;

class Consolidado {
private:
    int idSexo = 0;
    string sexo;
    int anio = 0;
    int semestre = 0;
    int inscritos = 0;
    int admitidos = 0;
    int matriculados = 0;
    int matriculadosPrimerSemestre = 0;
    int graduados = 0;

    static bool verificarMapaValido(const map<string, string> &);
public:
    Consolidado() = default;
    Consolidado(int idSexo, string sexo, int ano, int semestre);

    // Mantenimiento: Gran cantidad de métodos get y set que tal vez no son estrictamente necesarios
    // Cambio: Se quitaron algunos sets de la clase.
    int getIdSexo() const;
    string getSexo() const;
    int getAnio() const;
    int getSemestre() const;
    int getInscritos() const;
    int getAdmitidos() const;
    int getMatriculados() const;
    int getMatriculadosPrimerSemestre() const;
    int getGraduados() const;
    // Este metodo se encarga de inicializar los atributos
    // (Inscritos, Admitidos, Matriculados, MatriculadosPrimerSemestre, Graduados)
    // de la clase con los valores que se encuentran en el vector de parametrosConsolidado
    void setParametros(const map<string, string> &parametros);
};

#endif // CONSOLIDADO_H
