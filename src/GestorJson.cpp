#include "GestorJson.h"
#include "Settings.h"
#include <fstream>
#include <iostream>

using std::ofstream;

void GestorJson::exportarDatos(map<string, ProgramaAcademico*> &datos) {
    const string nombreArchivoOutput = Settings::OUTPUT_FILE_PATH;
    // Crear el archivo de salida
    std::ofstream archivoSalida(nombreArchivoOutput);

    if (!archivoSalida.is_open()) {
        throw std::ios_base::failure("Error al abrir el archivo " + nombreArchivoOutput);
    }

    archivoSalida << "{\n";
    // Aquí se recorre el mapa de datos, donde it->first es el código SNIES e it->second es el programa académico
    for (auto it = datos.begin(); it != datos.end(); ++it) {
        archivoSalida << "  \"" << it->first << "\": " << it->second->toJson();
        archivoSalida << (std::next(it) != datos.end() ? ",\n" : "\n");
    }
    archivoSalida << "}";

    archivoSalida.close();

    std::cout << "Los datos han sido exportados exitosamente al archivo: " << nombreArchivoOutput << "\n";
}
