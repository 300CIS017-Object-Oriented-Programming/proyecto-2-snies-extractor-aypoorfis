//
// Created by User on 13/10/2024.
//

//
// Created by User on 13/10/2024.
//

#include "GestorJson.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

#include <string>
#include <vector>
#include <map>

using namespace std;

void GestorJson::exportarDatos(const string& filePath, const vector<map<string, string>>& datos) {
    try {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            throw std::ios_base::failure("No se pudo abrir el archivo JSON para exportar: " + filePath);
        }

        // Iniciar el array de JSON
        file << "[\n";

        // Procesar cada entrada de datos
        for (size_t i = 0; i < datos.size(); ++i) {
            file << "  {\n";
            const auto& entry = datos[i];
            size_t entryCount = 0;

            for (auto pairIter = entry.begin(); pairIter != entry.end(); ++pairIter) {
                const auto& key = pairIter->first;
                const auto& value = pairIter->second;
                file << "    \"" << key << "\": \"" << value << "\"";
                if (++entryCount < entry.size()) {
                    file << ",";
                }
                file << "\n";
            }

            file << "  }";
            if (i < datos.size() - 1) {
                file << ",";
            }
            file << "\n";
        }

        // Cerrar el array de JSON
        file << "]\n";

        file.close();
        cout << "Exportación a JSON exitosa: " << filePath << endl;
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "Error de archivo: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error inesperado: " << e.what() << endl;
    }
    catch (...) {
        std::cerr << "Ocurrió un error desconocido durante la exportación a JSON." << endl;
    }
}

