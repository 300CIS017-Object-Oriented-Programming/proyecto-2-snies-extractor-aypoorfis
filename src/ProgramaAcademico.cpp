#include "ProgramaAcademico.h"
#include "Consolidado.h"
#include "Settings.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::ostringstream;

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

bool ProgramaAcademico::contienePalabraClave(string const &palabraClave) const {
    bool respuesta = false;
    for (const auto &[key, value] : datos) {
        if (value.find(palabraClave) != string::npos) {
            respuesta = true;
        }
    }
    return respuesta;
}

bool ProgramaAcademico::tieneNivelDeFormacion(string const &nivelFormacion) const {
    string const LLAVENIVELFORMACION = "niveldeformacion";
    if (const auto it = datos.find(LLAVENIVELFORMACION); it != datos.end()) {
        return it->second == nivelFormacion;
    }
    throw std::invalid_argument("El atributo 'niveldeformacion' no está en el mapa de datos del programa académico.");
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

void ProgramaAcademico::mostrarInformacionPrincipalPrograma() {
    string const LLAVECODIGOINSTITUCION = "codigoinstitucion";
    string const LLAVENOMBREINSTITUCION = "nombreinstitucion";
    string const LLAVEMETODOLOGIAFORMACION = "metodoformacion";
    mostrarIdentificadoresPrograma();
    cout << "Código de la institución: " << this->getDato(LLAVECODIGOINSTITUCION) << endl;
    cout << "Nombre de la institución: " << this->getDato(LLAVENOMBREINSTITUCION) << endl;
    cout << "Metodología de formación: " << this->getDato(LLAVEMETODOLOGIAFORMACION) << endl;
}

string ProgramaAcademico::toTxt() const {
    ostringstream ossTxt;
    // Exportar los datos del programa académico
    for (const auto &[key, value] : datos) {
        ossTxt << key << ": " << value << "\n";
    }

    // Exportar los consolidados
    ossTxt << "\nConsolidados:\n";
    for (const auto &[key, consolidado] : consolidados) {
        ossTxt << "Consolidado " << key << ":\n";
        ossTxt << consolidado->toTxt();  // Llamar a toTxt() de cada Consolidado
        ossTxt << "\n";  // Añadir una nueva línea entre consolidados para mejor legibilidad
    }
    return ossTxt.str();
}

string ProgramaAcademico::toJson() const {
    ostringstream ossJson;
    ossJson << "{\n";

    // Exportar los datos del programa académico
    ossJson << "  \"datos\": {\n";
    for (auto it = datos.begin(); it != datos.end(); ++it) {
        ossJson << "    \"" << it->first << "\": \"" << it->second << "\"";
        ossJson << (std::next(it) != datos.end() ? ",\n" : "\n");
    }
    ossJson << "  },\n";

    // Exportar los consolidados
    ossJson << "  \"consolidados\": {\n";
    for (auto it = consolidados.begin(); it != consolidados.end(); ++it) {
        ossJson << "    \"" << it->first << "\": " << it->second->toJson();
        ossJson << (std::next(it) != consolidados.end() ? ",\n" : "\n");
    }
    ossJson << "  }\n";
    ossJson << "}";

    return ossJson.str();
}

string ProgramaAcademico::toCsv() const {
    ostringstream ossCsv;
    // Exportar los datos del programa académico como primeras columnas
    bool isFirst = true;
    const char delimitador = Settings::DELIMITADOR;
    for (const auto& [key, value] : datos) {
        ossCsv << (isFirst ? "" : delimitador) << "\"" << value << "\"";
        isFirst = false;
    }
    // Exportar los consolidados como columnas adicionales, incluyendo la key
    for (const auto& [key, consolidado] : consolidados) {
        ossCsv << delimitador + "\"" << key << "\"" + delimitador << consolidado->toCsv();  // Incluir la key y llamar a toCsv() de cada Consolidado
    }
    return ossCsv.str();
}


