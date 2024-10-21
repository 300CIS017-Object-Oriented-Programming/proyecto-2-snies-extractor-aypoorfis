//
// Created by User on 14/10/2024.
//

#include "GestorTxt.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

using std::string;
using std::map;
using std::vector;

void GestorTxt::exportarDatos(const string& filePath, const vector<map<string, string>>& datos) {
    try {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            throw std::ios_base::failure("No se pudo abrir el archivo TXT para exportar: " + filePath);
        }

        for (auto entryIter = datos.begin(); entryIter != datos.end(); ++entryIter) {
            const auto& entry = *entryIter;
            for (auto pairIter = entry.begin(); pairIter != entry.end(); ++pairIter) {
                const auto& key = pairIter->first;
                const auto& value = pairIter->second;
                file << key << ": " << value << "\n";
            }
            file << "--------------------------\n"; // Separador de entradas
        }


        file.close();
        cout << "Exportación a TXT exitosa: " << filePath << endl;
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "Error de archivo: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error inesperado: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Ocurrió un error desconocido durante la exportación a TXT." << std::endl;
    }
}
