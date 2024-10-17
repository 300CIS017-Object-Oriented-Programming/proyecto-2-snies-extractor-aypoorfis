[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/QApazJy0)

## SNIES Extractor
Gracias al grupo que me presetó el código fuente de este proyecto

## Presentación general
En este proyecto se utilizarán 5 clases para cumplir el propósito de extraer la información del Sistema Nacional de Información de Educación Superior. Para el usuario, este tendrá una interfaz por terminal que le indicará los pasos a seguir y la información que necesita digitar.

## Cumplimiento de Requerimientos

1. **Solicitar rango de años a analizar**  
   En el menú, se le pregunta al usuario cuál es el primer año de búsqueda, tomando en cuenta que los rangos de años siempre son consecutivos, el segundo año de búsqueda se calcula a partir del primero.

2. **Lectura de archivos .csv correspondientes**  
   A partir de los años ingresados por el usuario, el controlador (clase `SNIESController`) leerá la información de los archivos apropiados uno por uno.

3. **Calcular admitidos, inscritos, graduados, matriculados y matriculados de primer semestre por programa y por año**  
   El SNIES-Extractor, mediante su controlador, calculará estos datos por cada programa y año a partir de los datos en bruto que extrae de los archivos .csv apropiados.

4. **Generación de Archivos de Salida**  
   Al terminar de extraer la información y procesarla, el SNIES-Extractor generará un archivo de resultados en la siguiente carpeta que ya debería estar parametrizada en el disco duro:  
   `C:\SNIES_EXTRACTOR\outputs\resultados.csv`.

5. **Visualización de Datos**  
   El SNIES-Extractor muestra al usuario el consolidado de estudiantes por año en programas presenciales o virtuales, la diferencia porcentual anual entre la cantidad de nuevos matriculados durante los años de búsqueda por programa y la lista de programas sin nuevos matriculados en 3 semestres consecutivos. Además, permitirá al usuario exportar esta información en un archivo ubicado en la carpeta ya parametrizada:  
   `C:\SNIES_EXTRACTOR\outputs\extras.csv`.

6. **Filtrado de Programas**  
   Se le pregunta al usuario si desea hacer una búsqueda con 2 filtros entre los programas solicitados: una palabra clave para buscar según los nombres de programas y el nivel de formación de los programas.

7. **Validación de Datos**  
   El SNIES-Extractor es un programa de C++ robusto que puede detectar errores a la hora de recibir información fuera de rangos esperados, tanto de parte del usuario como de la lectura de los archivos .csv.

Más abajo podrán encontrar el diagrama UML de las clases.


# Diagrama Mermaid

*El vector de Consolidados tendrá siempre 8 posiciones [0-7] donde:*
*vector[0] es primer año, primer semestre, hombres*
*vector[1] es primer año, segundo semestre, hombres*
*vector[2] es primer año, primer semestre, mujeres*
*vector[3] es primer año, segundo semestre, mujeres*
*vector[4] es segundo año, primer semestre, hombres*
*vector[5] es segundo año, segundo semestre, hombres*
*vector[6] es segundo año, primer semestre, mujeres*
*vector[7] es segundo año, segundo semestre, mujeres*
```mermaid
classDiagram
direction BT
    class ProgramaAcademico {
        -int codigoDeLaInstitucion
        -int iesPadre
        -string institucionDeEducacionSuperiorIes
        -string principalOSeccional
        -int idSectorIes
        -string sectorIes
        -int idCaracter
        -string caracterIes
        -int codigoDelDepartamentoIes
        -string departamentoDeDomicilioDeLaIes
        -int codigoDelMunicipioIes
        -string municipioDeDomicilioDeLaIes
        -int codigoSniesDelPrograma
        -string programaAcademico
        -int idNivelAcademico
        -string nivelAcademico
        -int idNivelDeFormacion
        -string nivelDeFormacion
        -int idMetodologia
        -string metodologia
        -int idArea
        -string areaDeConocimiento
        -int idNucleo
        -string nucleoBasicoDelConocimientoNbc
        -int idCineCampoAmplio
        -string descCineCampoAmplio
        -int idCineCampoEspecifico
        -string descCineCampoEspecifico
        -int idCineCodigoDetallado
        -string descCineCodigoDetallado
        -int codigoDelDepartamentoPrograma
        -string departamentoDeOfertaDelPrograma
        -int codigoDelMunicipioPrograma
        -string municipioDeOfertaDelPrograma
        -Vector<Consolidado*> consolidados
        +ProgramaAcademico()
        +~ProgramaAcademico()
        +setCodigoDeLaInstitucion(int)
        +setIesPadre(int)
        +setInstitucionDeEducacionSuperiorIes(string)
        +setPrincipalOSeccional(string)
        +setIdSectorIes(int)
        +setSectorIes(string)
        +setIdCaracter(int)
        +setCaracterIes(string)
        +setCodigoDelDepartamentoIes(int)
        +setDepartamentoDeDomicilioDeLaIes(string)
        +setCodigoDelMunicipioIes(int)
        +setMunicipioDeDomicilioDeLaIes(string)
        +setCodigoSniesDelPrograma(int)
        +setProgramaAcademico(string)
        +setIdNivelAcademico(int)
        +setNivelAcademico(string)
        +setIdNivelDeFormacion(int)
        +setNivelDeFormacion(string)
        +setIdMetodologia(int)
        +setMetodologia(string)
        +setIdArea(int)
        +setAreaDeConocimiento(string)
        +setIdNucleo(int)
        +setNucleoBasicoDelConocimientoNbc(string)
        +setIdCineCampoAmplio(int)
        +setDescCineCampoAmplio(string)
        +setIdCineCampoEspecifico(int)
        +setDescCineCampoEspecifico(string)
        +setIdCineCodigoDetallado(int)
        +setDescCineCodigoDetallado(string)
        +setCodigoDelDepartamentoPrograma(int)
        +setDepartamentoDeOfertaDelPrograma(string)
        +setCodigoDelMunicipioPrograma(int)
        +setMunicipioDeOfertaDelPrograma(string)
        +getCodigoDeLaInstitucion()
        +getIesPadre()
        +getInstitucionDeEducacionSuperiorIes()
        +getPrincipalOSeccional()
        +getIdSectorIes()
        +getSectorIes()
        +getIdCaracter()
        +getCaracterIes()
        +getCodigoDelDepartamentoIes()
        +getDepartamentoDeDomicilioDeLaIes()
        +getCodigoDelMunicipioIes()
        +getMunicipioDeDomicilioDeLaIes()
        +getCodigoSniesDelPrograma()
        +getProgramaAcademico()
        +getIdNivelAcademico()
        +getNivelAcademico()
        +getIdNivelDeFormacion()
        +getNivelDeFormacion()
        +getIdMetodologia()
        +getMetodologia()
        +getIdArea()
        +getAreaDeConocimiento()
        +getIdNucleo()
        +getNucleoBasicoDelConocimientoNbc()
        +getIdCineCampoAmplio()
        +getDescCineCampoAmplio()
        +getIdCineCampoEspecifico()
        +getDescCineCampoEspecifico()
        +getIdCineCodigoDetallado()
        +getDescCineCodigoDetallado()
        +getCodigoDelDepartamentoPrograma()
        +getDepartamentoDeOfertaDelPrograma()
        +getCodigoDelMunicipioPrograma()
        +getMunicipioDeOfertaDelPrograma()
        +pushConsolidado(Consolidado*)
        +getConsolidado()
    }
    class Consolidado {
        -int inscritos
        -int admitidos
        -int matriculadosPrimerSemestre
        -int matriculados
        -int graduados
        -int idSexo
        -string sexo
        -int ano
        -int semestre
        +setIdSexo(int)
        +setSexo(string)
        +setAno(int)
        +setSemestre(int)
        +getIdSexo()
        +getSexo()
        +getAno()
        +getSemestre()
        +setInscritos(int)
        +setAdmitidos(int)
        +setMatriculadosPrimerSemestre(int)
        +setMatriculados(int)
        +setGraduados(int)
        +getInscritos()
        +getAdmitidos()
        +getMatriculadosPrimerSemestre()
        +getMatriculados()
        +getGraduados()
    }
    class GestorCsv {
        +GestorCsv() = default
        +vector<int> leerProgramasCsv(string &ruta)
        +vector<vector<string>> leerArchivoPrimera(string &rutaBase, string &ano, vector<int> &codigosSnies)
        +vector<vector<string>> leerArchivoSegunda(string &rutaBase, string &ano, vector<int> &codigosSnies)
        +vector<vector<string>> leerArchivo(string &rutaBase, string &ano, vector<int> &codigosSnies, int colmunaCodigoSnies)
        +bool crearArchivo(string &ruta, map <int, ProgramaAcademico*> &mapadeProgramasAcademicos, vector<string> etiquetasColumnas)
        +bool crearArchivoBuscados(string &ruta, list<ProgramaAcademico*> &programasBuscados, vector<string> etiquetasColumnas)
        +bool crearArchivoExtra(string &ruta,vector<vector<string>> datosAImprimir)
    }
    class SNIESController {
        -map <int, ProgramaAcademico*> programasAcademicos
        -GestorCsv gestorCsvObj
        -vector<string> etiquetasColumnas
        -string rutaProgramasCsv
        -string rutaAdmitidos
        -string rutaGraduados
        -string rutaInscritos
        -string rutaMatriculados
        -string rutaMatriculadosPrimerSemestre
        -string rutaOutput
        +SNIESController("incializar con strings de rutas")
        +~SNIESController()
        +void procesarDatosCsv(string &ano1, string &ano2)
        +void calcularDatosExtra(bool)
        +void buscarProgramas(bool, string &, int)
    }
    class View {
        SNIESController controlador
        +View()
        +~View()
        +bool pantallaBienvenido()
        +void visualizacionDatosExtra()
        +void buscarPorPalabraClaveYFormacion()
        +void salir()
        +bool isConvetibleToInt()
    }
    class Main {
        + int main()
    }

ProgramaAcademico o-- Consolidado : tiene varios
View <.. Main : usa
View --> SNIESController : tiene un
SNIESController --> GestorCsv: tiene un
SNIESController o-- Consolidado
Consolidado <.. GestorCsv: usa
```