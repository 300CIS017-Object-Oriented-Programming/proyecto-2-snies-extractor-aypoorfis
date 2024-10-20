// After
#ifndef GESTOR_CSV_H
#define GESTOR_CSV_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <unordered_map>
#include <cctype>
#include "ProgramaAcademico.h"


using std::string;
using std::vector;
using std::map;
using std::list;
using std::unordered_map;

class GestorCsv {
private:
    static vector<string> convertirVectorFormaEstandar(vector<string> &);

public:
    GestorCsv() = default;
    static void leerProgramasCsv(map<string, ProgramaAcademico*> &);
    // Mantenimiento: Se puede mejorar la firma y nombre de los metodos para que sea más descriptiva
    vector<vector<string>> leerArchivoPrimera(string &rutaBase, string &ano, vector<int> &codigosSnies);
    vector<vector<string>> leerArchivoSegunda(string &rutaBase, string &ano, vector<int> &codigosSnies);
    vector<vector<string>> leerArchivo(string &rutaBase, string &ano, vector<int> &codigosSnies, int colmunaCodigoSnies);

    bool crearArchivo(string &ruta, map <int, ProgramaAcademico *> &mapadeProgramasAcademicos, vector<string> etiquetasColumnas);
    bool crearArchivoBuscados(string &ruta, list<ProgramaAcademico *> &programasBuscados, vector<string> etiquetasColumnas);
    bool crearArchivoExtra(string &ruta, vector<vector<string>> datosAImprimir);


};

#endif