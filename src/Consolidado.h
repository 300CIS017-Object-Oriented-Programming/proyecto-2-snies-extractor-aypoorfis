#ifndef CONSOLIDADO_H
#define CONSOLIDADO_H

#include <string>
#include <vector>
#include <iostream>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


class Consolidado {
private:
    int idSexo;
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
    Consolidado();
    // Mantenimiento: Gran cantidad de atributos en la firma del constructor
    Consolidado(int, string, int, int, int, int, int, int, int);

    // Mantenimiento: Gran cantidad de métodos get y set que tal vez no son estrictamente necesarios
    int getIdSexo();
    void setIdSexo(int);

    string getSexo();
    void setSexo(string &);

    int getAno();
    void setAno(int);

    int getSemestre();
    void setSemestre(int);

    int getInscritos();
    void setInscritos(int);

    int getAdmitidos();
    void setAdmitidos(int);

    int getMatriculados();
    void setMatriculados(int);

    int getMatriculadosPrimerSemestre();
    void setMatriculadosPrimerSemestre(int);

    int getGraduados();
    void setGraduados(int);
};

#endif // CONSOLIDADO_H
