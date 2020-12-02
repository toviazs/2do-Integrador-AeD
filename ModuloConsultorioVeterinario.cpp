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
        printf("Modulo Consultorio Veterinario\n");
        printf("================================\n\n");

        printf("1.- Iniciar Sesión\n");
        printf("2.- Visualizar Lista de Espera de Turnos (Informe)\n");
        printf("3.- Registrar Evolución de la Mascota\n\n");

        printf("4.- Cerrar la aplicacion\n\n");
        
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
        }

    } while (caso != 4);
}