// After
#ifndef GESTOR_CSV_H
#define GESTOR_CSV_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <unordered_map>
#include "ProgramaAcademico.h"
#include "GestorDatos.h"

using std::string;
using std::vector;
using std::map;
using std::list;
using std::unordered_map;

class GestorCsv : public GestorDatos {
private:
    // Esta función convierte un string a minúsculas y elimina los espacios en blanco y tildes.
    static string convertirStringFormaEstandar(const string &);
    // Esta función divide una línea de un archivo CSV en un vector de strings.
    static vector<string> dividirLineaCSV(string &);
    // Esta función convierte un vector de strings a minúsculas y elimina los espacios en blanco y tildes.
    static vector<string> convertirVectorFormaEstandar(vector<string> &);
    // Esta función adjunta los datos de un programa académico (en forma de vector) a un Programa Académico adentro
    // de un mapa.
    static void adjuntarDatosProgramaAcademico(vector<string> &, vector<string> &, ProgramaAcademico &);
    // Esta función adjunta los datos de un archivo CSV a un map<string, ProgramaAcademico*>,
    // es decir, adjunta la información de todas las ocurrencias de los programas de análisis.
    static void adjuntarDatosArchivo(string &ruta, map<string, ProgramaAcademico*> &);
public:
    GestorCsv() = default;
    ~GestorCsv() = default;
    // Esta función inicializa los programas de análisis de un archivo CSV, agregandolos como Programas vacíos
    // en el mapa.
    static void inicializarProgramasDeAnalisisCsv(map<string, ProgramaAcademico*> &);
    // Esta función adjunta todos los datos de los programas de análisis de todos los archivos CSV a un mapa.
    static void adjuntarTodosLosDatos(map<string, ProgramaAcademico*> &);
    // Esta función exporta los datos de los programas de análisis a un archivo CSV.
    void exportarDatos(map<string, ProgramaAcademico*> &);
};

#endif