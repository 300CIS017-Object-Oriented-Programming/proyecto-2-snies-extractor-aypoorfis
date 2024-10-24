#include "GestorTxt.h"
#include "Settings.h"
#include <fstream>
#include <iostream>

using std::ofstream;

void GestorTxt::exportarDatos(map<string, ProgramaAcademico *> &datos) {
    const string nombreArchivoOutput = Settings::OUTPUT_FILE_PATH;
    // Crear un archivo de salida
    ofstream archivoSalida(nombreArchivoOutput);

    if (!archivoSalida.is_open()) {
        throw std::ios_base::failure("Error al abrir el archivo " + nombreArchivoOutput);
    }

    for (const auto &[codigoSnies, programaAcademico] : datos) {
        archivoSalida << "Programa Académico: " << codigoSnies << "\n";
        archivoSalida << programaAcademico->toTxt();
        archivoSalida << "\n";
    }
    archivoSalida.close();

    std::cout << "Los datos han sido exportados exitosamente al archivo: " << nombreArchivoOutput << "\n";
}


