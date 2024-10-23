#include "GestorJson.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>


using namespace std;

void GestorJson::exportarDatos(map<string, ProgramaAcademico*> datos) {
    try {
        ofstream file("output.json");
        if (!file.is_open()) {
            throw ios_base::failure("No se pudo abrir el archivo JSON para exportar: output.json");
        }

        file << "{\n";
        for (auto it = datos.begin(); it != datos.end(); ++it) {
            ProgramaAcademico* programa = it->second;
            file << "  \"" << it->first << "\": {\n";
            file << "    \"datos\": {\n";
            for (auto dataIt = programa->datos.begin(); dataIt != programa->datos.end(); ++dataIt) {
                file << "      \"" << dataIt->first << "\": \"" << dataIt->second << "\"";
                if (next(dataIt) != programa->datos.end()) {
                    file << ",";
                }
                file << "\n";
            }
            file << "    },\n";
            file << "    \"consolidados\": {\n";
            for (auto consIt = programa->consolidados.begin(); consIt != programa->consolidados.end(); ++consIt) {
                Consolidado* consolidado = consIt->second;
                file << "      \"" << consIt->first << "\": {\n";
                file << "        \"idSexo\": " << consolidado->getIdSexo() << ",\n";
                file << "        \"sexo\": \"" << consolidado->getSexo() << "\",\n";
                file << "        \"anio\": " << consolidado->getAnio() << ",\n";
                file << "        \"semestre\": " << consolidado->getSemestre() << ",\n";
                file << "        \"inscritos\": " << consolidado->getInscritos() << ",\n";
                file << "        \"admitidos\": " << consolidado->getAdmitidos() << ",\n";
                file << "        \"matriculados\": " << consolidado->getMatriculados() << ",\n";
                file << "        \"matriculadosPrimerSemestre\": " << consolidado->getMatriculadosPrimerSemestre() << ",\n";
                file << "        \"graduados\": " << consolidado->getGraduados() << "\n";
                file << "      }";
                if (std::next(consIt) != programa->consolidados.end()) {
                    file << ",";
                }
                file << "\n";
            }
            file << "    }\n";
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