#include "ProgramaAcademico.h"

using namespace std;

ProgramaAcademico::ProgramaAcademico()
{
    consolidados = vector<Consolidado *>(8);
}

void ProgramaAcademico::setCodigoDeLaInstitucion(int nuevoCodigoDeLaInstitucion)
{
    codigoDeLaInstitucion = nuevoCodigoDeLaInstitucion;
}

int ProgramaAcademico::getCodigoDeLaInstitucion()
{
    return codigoDeLaInstitucion;
}

void ProgramaAcademico::setIesPadre(int nuevoIesPadre)
{
    iesPadre = nuevoIesPadre;
}

int ProgramaAcademico::getIesPadre()
{
    return iesPadre;
}

void ProgramaAcademico::setInstitucionDeEducacionSuperiorIes(string &nuevoInstitucionDeEducacionSuperiorIes)
{
    institucionDeEducacionSuperiorIes = nuevoInstitucionDeEducacionSuperiorIes;
}
string ProgramaAcademico::getInstitucionDeEducacionSuperiorIes()
{
    return institucionDeEducacionSuperiorIes;
}

void ProgramaAcademico::setPrincipalOSeccional(string &nuevoPrincipalOSeccional)
{
    principalOSeccional = nuevoPrincipalOSeccional;
}

string ProgramaAcademico::getPrincipalOSeccional()
{
    return principalOSeccional;
}

void ProgramaAcademico::setIdSectorIes(int nuevoIdSectorIes)
{
    idSectorIes = nuevoIdSectorIes;
}

int ProgramaAcademico::getIdSectorIes()
{
    return idSectorIes;
}

void ProgramaAcademico::setSectorIes(string &nuevoSectorIes)
{
    sectorIes = nuevoSectorIes;
}

string ProgramaAcademico::getSectorIes()
{
    return sectorIes;
}

void ProgramaAcademico::setIdCaracter(int nuevoIdCaracter)
{
    idCaracter = nuevoIdCaracter;
}

int ProgramaAcademico::getIdCaracter()
{
    return idCaracter;
}

void ProgramaAcademico::setCaracterIes(string &nuevoCaracterIes)
{
    caracterIes = nuevoCaracterIes;
}

string ProgramaAcademico::getCaracterIes()
{
    return caracterIes;
}

void ProgramaAcademico::setCodigoDelDepartamentoIes(int nuevoCodigoDelDepartamentoIes)
{
    codigoDelDepartamentoIes = nuevoCodigoDelDepartamentoIes;
}

int ProgramaAcademico::getCodigoDelDepartamentoIes()
{
    return codigoDelDepartamentoIes;
}

void ProgramaAcademico::setDepartamentoDeDomicilioDeLaIes(string &nuevoDepartamentoDeDomicilioDeLaIes)
{
    departamentoDeDomicilioDeLaIes = nuevoDepartamentoDeDomicilioDeLaIes;
}

string ProgramaAcademico::getDepartamentoDeDomicilioDeLaIes()
{
    return departamentoDeDomicilioDeLaIes;
}

void ProgramaAcademico::setCodigoDelMunicipioIes(int nuevoCodigoDelMunicipioIes)
{
    codigoDelMunicipioIes = nuevoCodigoDelMunicipioIes;
}

int ProgramaAcademico::getCodigoDelMunicipioIes()
{
    return codigoDelMunicipioIes;
}

void ProgramaAcademico::setMunicipioDeDomicilioDeLaIes(string &nuevoMunicipioDeDomicilioDeLaIes)
{
    municipioDeDomicilioDeLaIes = nuevoMunicipioDeDomicilioDeLaIes;
}

string ProgramaAcademico::getMunicipioDeDomicilioDeLaIes()
{
    return municipioDeDomicilioDeLaIes;
}

void ProgramaAcademico::setCodigoSniesDelPrograma(int nuevoCodigoSniesDelPrograma)
{
    codigoSniesDelPrograma = nuevoCodigoSniesDelPrograma;
}

int ProgramaAcademico::getCodigoSniesDelPrograma()
{
    return codigoSniesDelPrograma;
}

void ProgramaAcademico::setProgramaAcademico(string &nuevoProgramaAcademico)
{
    programaAcademico = nuevoProgramaAcademico;
}

string ProgramaAcademico::getProgramaAcademico()
{
    return programaAcademico;
}

void ProgramaAcademico::setIdNivelAcademico(int nuevoIdNivelAcademico)
{
    idNivelAcademico = nuevoIdNivelAcademico;
}

int ProgramaAcademico::getIdNivelAcademico()
{
    return idNivelAcademico;
}

void ProgramaAcademico::setNivelAcademico(string &nuevoNivelAcademico)
{
    nivelAcademico = nuevoNivelAcademico;
}

string ProgramaAcademico::getNivelAcademico()
{
    return nivelAcademico;
}

void ProgramaAcademico::setIdNivelDeFormacion(int nuevoIdNivelDeFormacion)
{
    idNivelDeFormacion = nuevoIdNivelDeFormacion;
}

int ProgramaAcademico::getIdNivelDeFormacion()
{
    return idNivelDeFormacion;
}

void ProgramaAcademico::setNivelDeFormacion(string &nuevoNivelDeFormacion)
{
    nivelDeFormacion = nuevoNivelDeFormacion;
}

string ProgramaAcademico::getNivelDeFormacion()
{
    return nivelDeFormacion;
}

void ProgramaAcademico::setIdMetodologia(int nuevoIdMetodologia)
{
    idMetodologia = nuevoIdMetodologia;
}

int ProgramaAcademico::getIdMetodologia()
{
    return idMetodologia;
}

void ProgramaAcademico::setMetodologia(string &nuevaMetodologia)
{
    metodologia = nuevaMetodologia;
}

string ProgramaAcademico::getMetodologia()
{
    return metodologia;
}

void ProgramaAcademico::setIdArea(int nuevoIdArea)
{
    idArea = nuevoIdArea;
}

int ProgramaAcademico::getIdArea()
{
    return idArea;
}

void ProgramaAcademico::setAreaDeConocimiento(string &areaConocimiento)
{
    areaDeConocimiento = areaConocimiento;
}
string ProgramaAcademico::getAreaDeConocimiento()
{
    return areaDeConocimiento;
}

void ProgramaAcademico::setIdNucleo(int nuevoIdNucleo)
{
    idNucleo = nuevoIdNucleo;
}
int ProgramaAcademico::getIdNucleo()
{
    return idNucleo;
}

void ProgramaAcademico::setNucleoBasicoDelConocimientoNbc(string &nuevoNucleoBasicoDelConocimientoNbc)
{
    nucleoBasicoDelConocimientoNbc = nuevoNucleoBasicoDelConocimientoNbc;
}
string ProgramaAcademico::getNucleoBasicoDelConocimientoNbc()
{
    return nucleoBasicoDelConocimientoNbc;
}

void ProgramaAcademico::setIdCineCampoAmplio(int nuevoIdCineCampoAmplio)
{
    idCineCampoAmplio = nuevoIdCineCampoAmplio;
}
int ProgramaAcademico::getIdCineCampoAmplio()
{
    return idCineCampoAmplio;
}

void ProgramaAcademico::setDescCineCampoAmplio(string &nuevoDescCineCampoAmplio)
{
    descCineCampoAmplio = nuevoDescCineCampoAmplio;
}
string ProgramaAcademico::getDescCineCampoAmplio()
{
    return descCineCampoAmplio;
}

void ProgramaAcademico::mostrarIdentificadoresPrograma() {
    cout << "Código SNIES: " << this->getDato("codigosnies") << endl;
    cout << "Nombre del programa académico: " << this->getDato("programaacademico") << endl;
}