#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Universidad Tecnologica Nacional
Facultad Regional Tucuman
Ingenieria en Sistemas de Informacion

Paz Posse Tobías	
43562927
Tobias.PazPosse@alu.frt.utn.edu.ar

Pérez Lucas Gustavo
43564887
lucas.perez@alu.frt.utn.edu.ar

Paz Bruno Leonel
43648810
Bruno.Paz@alu.frt.utn.edu.ar

Posse Ricardo
43567498
Ricardo.Posse@alu.frt.utn.edu.ar
*/

main()
{
    int caso = 0;

    do
    {
        printf("Modulo del Asistente\n");
        printf("======================\n\n");

        printf("1.- Iniciar Sesión\n");
        printf("2.- Registrar Mascota\n");
        printf("3.- Registrar Turno\n");
        printf("4.- Listado de Atenciones por Veterinario y Fecha\n\n");

        printf("5.- Cerrar la aplicacion\n\n");
        
        printf("> Seleccion: ");
        scanf("%d", &caso);

        switch (caso)
        {
        case 1:
        {

        }
        case 2:
        {

        }
        case 3:
        {

        }
        case 4:
        {
            
        }
        }

    } while (caso != 5);
}