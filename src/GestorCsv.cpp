#include "GestorCsv.h"
#include "Settings.h"
#include "ProgramaAcademico.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<string> GestorCsv::convertirVectorFormaEstandar(vector<string> &stringsIn) {
    static const unordered_map<char, char> tildesMap = {
        {'á', 'a'}, {'Á', 'a'},
        {'é', 'e'}, {'É', 'e'},
        {'í', 'i'}, {'Í', 'i'},
        {'ó', 'o'}, {'Ó', 'o'},
        {'ú', 'u'}, {'Ú', 'u'}
    };

    vector<string> resultado;


    for (int j = 0; j < stringsIn.size(); ++j) {
        string ans;
        string &stringIn = stringsIn[j];  // para saber el string actual

        for (int i = 0; i < stringIn.length(); ++i) {
            char letra = tolower(stringIn[i]);

            if (tildesMap.count(letra)) {
                letra = tildesMap.at(letra);
            }

            if (letra != ' ' && letra != '-') {
                ans += letra;
            }
        }

        resultado.push_back(ans);
    }
    return resultado;
}

void GestorCsv::leerProgramasCsv(map<string, ProgramaAcademico*> &datos) {
    ifstream archivoProgramasCsv(Settings::PROGRAMAS_FILTRAR_FILE_PATH);
    if (!archivoProgramasCsv.is_open()) {
        cout << "Archivo " << Settings::PROGRAMAS_FILTRAR_FILE_PATH << " no se pudo abrir correctamente" << std::endl;
        return;
    }

    string linea;
    vector<std::string> nombresColumnas;
    char delimitador = Settings::DELIMITADOR[0];

    // Leer la primera línea para obtener los nombres de las columnas
    if (getline(archivoProgramasCsv, linea)) {
        stringstream streamLinea(linea);
        string columna;

        while (getline(streamLinea, columna, delimitador)) {
            nombresColumnas.push_back(columna);
        }
        // Convertir los nombres de las columnas a su forma estándar
        nombresColumnas = convertirVectorFormaEstandar(nombresColumnas);
    }

    // Leer el resto del archivo
    while (getline(archivoProgramasCsv, linea)) {
        stringstream streamLinea(linea);
        vector<string> datosFila;
        string dato;

        while (getline(streamLinea, dato, delimitador)) {
            datosFila.push_back(dato);
        }

        if (datosFila.size() != nombresColumnas.size()) {
            cout << "Error: La cantidad de datos no coincide con la cantidad de columnas" << endl;
        }
        else {
            // Crear un ProgramaAcademico vacío
            ProgramaAcademico* programa = new ProgramaAcademico();

            // Agregar el programa al mapa usando el código SNIES como llave
            string codigoSnies = datosFila[0];
            datos[codigoSnies] = programa;

            // Agregar la información al programa académico
            for (size_t i = 0; i < nombresColumnas.size(); ++i) {
                programa->setDato(nombresColumnas[i], datosFila[i]);
            }
        }

        // Crear un ProgramaAcademico vacío
        ProgramaAcademico* programa = new ProgramaAcademico();

        // Agregar el programa al mapa usando el código SNIES como llave
        string codigoSnies = datosFila[0];
        datos[codigoSnies] = programa;

        // Agregar la información al programa académico
        for (size_t i = 0; i < nombresColumnas.size(); ++i) {
            programa->setDato(nombresColumnas[i], datosFila[i]);
        }
    }

    archivoProgramasCsv.close();
}

void GestorCsv::leerArchivos(map<string, ProgramaAcademico*> &datos) {
    // File paths from Settings
    vector<string> filePaths = {
        Settings::ADMITIDOS_FILE_PATH,
        Settings::MATRICULADOS_FILE_PATH,
        Settings::INSCRITOS_FILE_PATH,
        Settings::GRADUADOS_FILE_PATH
    };

    for (const string &filePath : filePaths) {
        ifstream file(filePath);
        if (!file.is_open()) {
            cout << "Archivo " << filePath << " no se pudo abrir correctamente" << endl;
            continue;
        }

        string line;
        vector<string> columnNames;
        char delimiter = Settings::DELIMITADOR[0];

        // Read the first line to get column names
        if (getline(file, line)) {
            stringstream lineStream(line);
            string column;

            while (getline(lineStream, column, delimiter)) {
                columnNames.push_back(column);
            }
            // Convert column names to their standard form
            columnNames = convertirVectorFormaEstandar(columnNames);
        }

        // Read the rest of the file
        while (getline(file, line)) {
            stringstream lineStream(line);
            vector<string> rowData;
            string data;

            while (getline(lineStream, data, delimiter)) {
                rowData.push_back(data);
            }

            if (rowData.size() != columnNames.size()) {
                cout << "Error: La cantidad de datos no coincide con la cantidad de columnas" << endl;
                continue;
            }

            // Se toma la primera posición, ya que es la key (codigoSnies)
            string key = rowData[0];
            if (datos.find(key) == datos.end()) {
                // Si la key no se encuentra, se crea un new ProgramaAcademico
                datos[key] = new ProgramaAcademico();
            }

            // se llena el ProgramaAcademico con los datos
            ProgramaAcademico* program = datos[key];
            for (size_t i = 0; i < columnNames.size(); ++i) {
                program->setDato(columnNames[i], rowData[i]);
            }
        }

        file.close();
    }
}


bool GestorCsv::crearArchivo(string &ruta, map<int, ProgramaAcademico *> &mapadeProgramasAcademicos, vector<string> etiquetasColumnas)
{
    // Este bool nos ayudará a saber si se creo exitosamente el archivo
    bool estadoCreacion = false;
    string rutaCompleta = ruta + "resultados.csv";
    ofstream archivoResultados(rutaCompleta);
    if (archivoResultados.is_open())
    {
        // Imprimimos en el archivo las etiquetas (Primera fila)
        for (int i = 0; i < etiquetasColumnas.size(); i++)
        {
            archivoResultados << etiquetasColumnas[i] << ";";
        }
        archivoResultados << "GRADUADOS;INSCRITOS;MATRICULADOS;NEOS" << endl;

        map<int, ProgramaAcademico *>::iterator it;
        // Leemos todos los programas del mapa para imprimirlos en el archivo
        for (it = mapadeProgramasAcademicos.begin(); it != mapadeProgramasAcademicos.end(); it++)
        {
            // Imprimimos cada uno de los 8 consolidados por programa
            for (int i = 0; i < 8; i++)
            {
                // Imprimimos toda la información base del programa academico
                archivoResultados << (it->second)->getCodigoDeLaInstitucion() << ";";
                archivoResultados << (it->second)->getIesPadre() << ";";
                archivoResultados << (it->second)->getInstitucionDeEducacionSuperiorIes() << ";";
                archivoResultados << (it->second)->getPrincipalOSeccional() << ";";
                archivoResultados << (it->second)->getIdSectorIes() << ";";
                archivoResultados << (it->second)->getSectorIes() << ";";
                archivoResultados << (it->second)->getIdCaracter() << ";";
                archivoResultados << (it->second)->getCaracterIes() << ";";
                archivoResultados << (it->second)->getCodigoDelDepartamentoIes() << ";";
                archivoResultados << (it->second)->getDepartamentoDeDomicilioDeLaIes() << ";";
                archivoResultados << (it->second)->getCodigoDelMunicipioIes() << ";";
                archivoResultados << (it->second)->getMunicipioDeDomicilioDeLaIes() << ";";
                archivoResultados << (it->second)->getCodigoSniesDelPrograma() << ";";
                archivoResultados << (it->second)->getProgramaAcademico() << ";";
                archivoResultados << (it->second)->getIdNivelAcademico() << ";";
                archivoResultados << (it->second)->getNivelAcademico() << ";";
                archivoResultados << (it->second)->getIdNivelDeFormacion() << ";";
                archivoResultados << (it->second)->getNivelDeFormacion() << ";";
                archivoResultados << (it->second)->getIdMetodologia() << ";";
                archivoResultados << (it->second)->getMetodologia() << ";";
                archivoResultados << (it->second)->getIdArea() << ";";
                archivoResultados << (it->second)->getAreaDeConocimiento() << ";";
                archivoResultados << (it->second)->getIdNucleo() << ";";
                archivoResultados << (it->second)->getNucleoBasicoDelConocimientoNbc() << ";";
                archivoResultados << (it->second)->getIdCineCampoAmplio() << ";";
                archivoResultados << (it->second)->getDescCineCampoAmplio() << ";";
                archivoResultados << (it->second)->getIdCineCampoEspecifico() << ";";
                archivoResultados << (it->second)->getDescCineCampoEspecifico() << ";";
                archivoResultados << (it->second)->getIdCineCodigoDetallado() << ";";
                archivoResultados << (it->second)->getDescCineCodigoDetallado() << ";";
                archivoResultados << (it->second)->getCodigoDelDepartamentoPrograma() << ";";
                archivoResultados << (it->second)->getDepartamentoDeOfertaDelPrograma() << ";";
                archivoResultados << (it->second)->getCodigoDelMunicipioPrograma() << ";";
                archivoResultados << (it->second)->getMunicipioDeOfertaDelPrograma() << ";";

                // Imprimimos la información del consolidado: (ID SEXO;SEXO;AÑO;SEMESTRE;ADMITIDOS;GRADUADOS;INSCRITOS;MATRICULADOS;NEOS)
                Consolidado *consolidadoActual = (it->second)->getConsolidado(i);
                archivoResultados << consolidadoActual->getIdSexo() << ";";
                archivoResultados << consolidadoActual->getSexo() << ";";
                archivoResultados << consolidadoActual->getAno() << ";";
                archivoResultados << consolidadoActual->getSemestre() << ";";
                archivoResultados << consolidadoActual->getAdmitidos() << ";";
                archivoResultados << consolidadoActual->getGraduados() << ";";
                archivoResultados << consolidadoActual->getInscritos() << ";";
                archivoResultados << consolidadoActual->getMatriculados() << ";";
                archivoResultados << consolidadoActual->getMatriculadosPrimerSemestre();
                // Saltamos de linea para la siguiente fila
                archivoResultados << endl;
            }
        }

        // Cambiamos el valor del booleano si logramos llegar hasta este punto
        estadoCreacion = true;
        // Imprimimos ruta donde quedo el archivo
        cout << "Archivo Creado en: " << rutaCompleta << endl;
    }

    archivoResultados.close();
    return estadoCreacion;
}

bool GestorCsv::crearArchivoBuscados(string &ruta, list<ProgramaAcademico *> &programasBuscados, vector<string> etiquetasColumnas)
{
    // Este bool nos ayudará a saber si se creo exitosamente el archivo
    bool estadoCreacion = false;
    string rutaCompleta = ruta + "buscados.csv";
    ofstream archivoBuscados(rutaCompleta);
    if (archivoBuscados.is_open())
    {

        // Imprimimos en el archivo las etiquetas (Primera fila)
        for (int i = 0; i < etiquetasColumnas.size(); i++)
        {
            archivoBuscados << etiquetasColumnas[i] << ";";
        }
        archivoBuscados << "GRADUADOS;INSCRITOS;MATRICULADOS;NEOS" << endl;

        list<ProgramaAcademico *>::iterator it;
        // Leemos todos los programas de la lista de los programas buscados para imprimirlos
        for (it = programasBuscados.begin(); it != programasBuscados.end(); it++)
        {
            // Imprimimos los 8 consolidados del programa
            for (int i = 0; i < 8; i++)
            {
                // Imprimimos la informacion base del programa
                archivoBuscados << (*it)->getCodigoDeLaInstitucion() << ";";
                archivoBuscados << (*it)->getIesPadre() << ";";
                archivoBuscados << (*it)->getInstitucionDeEducacionSuperiorIes() << ";";
                archivoBuscados << (*it)->getPrincipalOSeccional() << ";";
                archivoBuscados << (*it)->getIdSectorIes() << ";";
                archivoBuscados << (*it)->getSectorIes() << ";";
                archivoBuscados << (*it)->getIdCaracter() << ";";
                archivoBuscados << (*it)->getCaracterIes() << ";";
                archivoBuscados << (*it)->getCodigoDelDepartamentoIes() << ";";
                archivoBuscados << (*it)->getDepartamentoDeDomicilioDeLaIes() << ";";
                archivoBuscados << (*it)->getCodigoDelMunicipioIes() << ";";
                archivoBuscados << (*it)->getMunicipioDeDomicilioDeLaIes() << ";";
                archivoBuscados << (*it)->getCodigoSniesDelPrograma() << ";";
                archivoBuscados << (*it)->getProgramaAcademico() << ";";
                archivoBuscados << (*it)->getIdNivelAcademico() << ";";
                archivoBuscados << (*it)->getNivelAcademico() << ";";
                archivoBuscados << (*it)->getIdNivelDeFormacion() << ";";
                archivoBuscados << (*it)->getNivelDeFormacion() << ";";
                archivoBuscados << (*it)->getIdMetodologia() << ";";
                archivoBuscados << (*it)->getMetodologia() << ";";
                archivoBuscados << (*it)->getIdArea() << ";";
                archivoBuscados << (*it)->getAreaDeConocimiento() << ";";
                archivoBuscados << (*it)->getIdNucleo() << ";";
                archivoBuscados << (*it)->getNucleoBasicoDelConocimientoNbc() << ";";
                archivoBuscados << (*it)->getIdCineCampoAmplio() << ";";
                archivoBuscados << (*it)->getDescCineCampoAmplio() << ";";
                archivoBuscados << (*it)->getIdCineCampoEspecifico() << ";";
                archivoBuscados << (*it)->getDescCineCampoEspecifico() << ";";
                archivoBuscados << (*it)->getIdCineCodigoDetallado() << ";";
                archivoBuscados << (*it)->getDescCineCodigoDetallado() << ";";
                archivoBuscados << (*it)->getCodigoDelDepartamentoPrograma() << ";";
                archivoBuscados << (*it)->getDepartamentoDeOfertaDelPrograma() << ";";
                archivoBuscados << (*it)->getCodigoDelMunicipioPrograma() << ";";
                archivoBuscados << (*it)->getMunicipioDeOfertaDelPrograma() << ";";

                // Imprimimos la información del consolidado: (ID SEXO;SEXO;AÑO;SEMESTRE;ADMITIDOS;GRADUADOS;INSCRITOS;MATRICULADOS;NEOS)
                Consolidado *consolidadoActual = (*it)->getConsolidado(i);
                archivoBuscados << consolidadoActual->getIdSexo() << ";";
                archivoBuscados << consolidadoActual->getSexo() << ";";
                archivoBuscados << consolidadoActual->getAno() << ";";
                archivoBuscados << consolidadoActual->getSemestre() << ";";
                archivoBuscados << consolidadoActual->getAdmitidos() << ";";
                archivoBuscados << consolidadoActual->getGraduados() << ";";
                archivoBuscados << consolidadoActual->getInscritos() << ";";
                archivoBuscados << consolidadoActual->getMatriculados() << ";";
                archivoBuscados << consolidadoActual->getMatriculadosPrimerSemestre();
                // Saltamos de linea para la siguiente fila
                archivoBuscados << endl;
            }
        }

        // Cambiamos el valor del booleano si logramos llegar hasta este punto
        estadoCreacion = true;
        // Imprimimos ruta donde quedo el archivo
        cout << "Archivo Creado en: " << rutaCompleta << endl;
    }

    archivoBuscados.close();
    return estadoCreacion;
}

bool GestorCsv::crearArchivoExtra(string &ruta, vector<vector<string>> datosAImprimir)
{
    // Este bool nos ayudará a saber si se creo el archivo exitosamente
    bool estadoCreacion = false;
    string rutaCompleta = ruta + "extras.csv";
    ofstream archivoExtra(rutaCompleta);
    if (archivoExtra.is_open())
    {
        // Imprimimos la matriz de datos que queremos imprimir
        for (int i = 0; i < datosAImprimir.size(); i++)
        {
            // Imprimimos cada fila
            for (int j = 0; j < datosAImprimir[i].size(); j++)
            {
                // Imprimimos cada dato separado por ';'
                archivoExtra << datosAImprimir[i][j];
                if (j != (datosAImprimir[i].size() - 1))
                {
                    archivoExtra << ";";
                }
            }
            // Saltamos de linea al terminar una fila
            archivoExtra << endl;
        }

        // Cambiamos el valor del booleano si logramos llegar hasta este punto
        estadoCreacion = true;
        // Imprimimos ruta donde quedo el archivo
        cout << "Archivo Creado en: " << rutaCompleta << endl;
    }

    archivoExtra.close();
    return estadoCreacion;
}






