//
// Created by User on 14/10/2024.
//
#include "GestorTxt.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

void GestorTxt::exportarDatos(map<string, ProgramaAcademico*> datos) {
    try {
        ofstream file("output.json");
        if (!file.is_open()) {
            throw ios_base::failure("No se pudo abrir el archivo JSON para exportar: output.json");
        }

        file << "{\n";
        for (auto it = datos.begin(); it != datos.end(); ++it) {
            ProgramaAcademico* programa = it->second;
            file << "  \"" << it->first << "\": {\n";
            file << "    \"codigoSNIES\": \"" << programa->getDato("codigosnies") << "\",\n";
            file << "    \"nombrePrograma\": \"" << programa->getDato("programaacademico") << "\",\n";
            file << "    \"consolidados\": [\n";
            programa->mostrarMatriculadosConsolidado({2010, 2020}); // Ejemplo de rango de años
            programa->mostrarDiferenciaPorcentualNuevosMatriculados({2010, 2020}); // Ejemplo de rango de años
            file << "    ]\n";
            file << "  }";
            if (std::next(it) != datos.end()) {
                file << ",";
            }
            file << "\n";
        }
        file << "}\n";

        file.close();
        cout << "Exportación a JSON exitosa: output.json" << std::endl;
    } catch (const std::ios_base::failure& e) {
        cerr << "Error de archivo: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        cerr << "Error inesperado: " << e.what() << std::endl;
    } catch (...) {
        cerr << "Ocurrió un error desconocido durante la exportación a JSON." << std::endl;
    }
}
