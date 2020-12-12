#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include "LibreriaModulos.h"
/*
Universidad Tecnologica Nacional
Facultad Regional Tucuman
Ingenieria en Sistemas de Informacion
Paz Posse Tob�as	
43562927
Tobias.PazPosse@alu.frt.utn.edu.ar
P�rez Lucas Gustavo
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
    char Usuario[10], Clave[10];
    int opcion, matricula, salirPrograma;
    bool admin, veterinario, asistente;

    system("cls");
    printf("\t\tMenu Principal");
    printf("\n\t\t..............");
    printf("\n\n\tBienvenido al sistema! para continuar, inicie sesion");
    printf("\n\tcompletando las casillas con sus datos, el programa\n");
    printf("\tlo derivara al modulo que le corresponda");

    getch();

    do
    {
        system("cls");
        printf("\t\tMenu Principal");
        printf("\n\t\t..............");

        printf("\n\n1. Ingresar como Administrador");
        printf("\n2. Ingresar como Veterinario");
        printf("\n3. Ingresar como Asistente");
        printf("\n\n4. Salir del programa");
        printf("\n\n> ");

        scanf("%d", &opcion);

        system("cls");

        switch (opcion)
        {
        case 1:
            printf("\tLogin Administrador\n");
            printf("\t===================\n");

            printf("\n\t(Ingrese un 0 para salir)");

            printf("\n\n\tUsuario\n\t> ");
            _flushall();
            gets(Usuario);

            if (strcmp(Usuario, "0") == 0)
            {
                break;
            }

            printf("\n\n\tClave\n\t> ");
            _flushall();
            gets(Clave);

            if (LoginAdminAsistente(Usuario, Clave, 1)) //el parametro 1 es para especificar que es un administrador
            {
                printf("\n\tSesion iniciada correctamente...");
                admin = true;
            }
            else
            {
                printf("\n\tError: usuario o contrasena incorrectos");
            }

            getch();

            break;
        case 2:
            printf("\tLogin Veterinario\n");
            printf("\t=================\n");

            printf("\n\t(Ingrese un 0 para salir)");

            printf("\n\n\tMatricula\n\t> ");
            scanf("%d", &matricula);

            if (matricula == 0)
            {
                break;
            }

            printf("\n\n\tClave\n\t> ");
            _flushall();
            gets(Clave);

            if (LoginVeterinario(matricula, Clave))
            {
                printf("Sesion iniciada correctamente...");
                veterinario = true;
            }
            else
            {
                printf("\n\tError: matricula o contrasena incorrecta");
            }

            getch();

            break;
        case 3:
            printf("\tLogin Asistente\n");
            printf("\t===============\n");

            printf("\n\t(Ingrese un 0 para salir)");

            printf("\n\n\tUsuario\n\t> ");
            _flushall();
            gets(Usuario);

            if (strcmp(Usuario, "0") == 0)
            {
                break;
            }

            printf("\n\n\tClave\n\t> ");
            _flushall();
            gets(Clave);

            if (LoginAdminAsistente(Usuario, Clave, 3)) //el parametro 3 es para especificar que es un asistente
            {
                printf("Sesion iniciada correctamente...");
                asistente = true;
            }
            else
            {
                printf("Error: usuario o contrasena incorrectos");
            }

            getch();

            break;
        case 4:
            printf("\n\tSeguro que desea salir?");
            printf("\n\n\t(1.Si  2.No)");
            printf("\n\t> ");

            scanf("%d", &salirPrograma);

            if (salirPrograma != 1)
            {
                opcion = 1;
            }
            break;
        }

    } while (opcion != 4);
}