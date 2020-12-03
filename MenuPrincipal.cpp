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

typedef char cadena[10];

main()
{
    cadena Usuario, Clave;
    int opcion, matricula;
    bool admin, veterinario, asistente;

    system("cls");
    printf("\t\tMenu Principal");
    printf("\n\t\t..............");
    printf("\n\nBienvenido al sistema! para continuar, inicie sesion\ncompletando las casillas con sus datos, el programa\n");
    printf("lo derivara al modulo que le corresponda");

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
        printf("\n> ");

        scanf("%d", &opcion);

        system("cls");

        switch (opcion)
        {
        case 1:
            printf("\n\n\tUsuario\n\t> ");
            _flushall();
            gets(Usuario);
            printf("\n\n\tClave\n\t> ");
            _flushall();
            gets(Clave);

            if (LoginAdminAsistente(Usuario, Clave, 1)) //el parametro 1 es para especificar que es un administrador
            {
                printf("Sesion iniciada correctamente...");
                admin = true;
            }
            else
            {
                printf("Error: usuario o contrasena incorrectos");
            }

            break;
        case 2:
            printf("\n\n\tMatricula\n\t> ");
            scanf("%d", &matricula);

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
                printf("Error: matricula o contrasena incorrecta");
            }

            break;
        case 3:
            printf("\n\n\tUsuario\n\t> ");
            _flushall();
            gets(Usuario);

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
            break;
        }

    } while (true);
}