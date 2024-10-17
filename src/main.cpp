#include "View.h"

int main()
{
    View menu;
    bool archivosParametrizados = menu.mostrarPantallaBienvenido();
    // Estructura: El main debería tener solo el llamado a una función.
    if (archivosParametrizados)
    {
        menu.mostrarDatosExtra();
        menu.buscarPorPalabraClaveYFormacion();
    }
    menu.salir();
    return 0;
}