#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "LibreriaModulos.h"

/*
Universidad Tecnologica Nacional
Facultad Regional Tucuman
Ingenieria en Sistemas de Informacion

Paz Posse Tobias	
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

typedef char nombreArchi[20];

struct fecha
{
    int dia;
    int mes;
    int anio;
};
struct turnos
{
    fecha fec;
    int DNIduenio;
    char atencion[380];
    int matriculaVet;
};

//prototipos
void listaDeTurnos(FILE *archivo);
void evolucionMascota(FILE *archivo);

main()
{
    FILE *archivo;
    int caso = 0;
    nombreArchi archivoTurnos = "Turnos.dat";

    AbrirGenerarArchivo(archivo, archivoTurnos);

    do
    {
        system("cls");

        printf("Modulo Consultorio Veterinario\n");
        printf("================================\n\n");

        printf("1.- Visualizar Lista de Espera de Turnos (Informe)\n");
        printf("2.- Registrar Evolucion de la Mascota\n\n");

        printf("3.- Cerrar la aplicacion\n\n");

        printf("> : ");
        scanf("%d", &caso);

        switch (caso)
        {
        case 1:
        {
            listaDeTurnos(archivo);
            getch();
            break;
        }
        case 2:
        {
            evolucionMascota(archivo);
            getch();
            break;
        }
        }

    } while (caso != 3);

    fclose(archivo);
}

void listaDeTurnos(FILE *archivo)
{
	system ("cls");
	turnos reg;
	archivo = fopen("Turnos.dat", "rb");
	
	printf("----Lista de turnos----\n");
	printf("================================\n\n");
	
	fread(&reg, sizeof(turnos), 1, archivo);
	while (!feof(archivo))
	{
		if(!feof(archivo))
		{
			printf ("\nLa matricula es:  %d",reg.matriculaVet);
			printf("\nFecha ");
			printf("\nDia: %d",reg.fec.dia);
			printf("\nMes: %d",reg.fec.mes);
			printf("\nAnio: %d",reg.fec.anio);
			printf("\nDni del duenio: %d\n",reg.DNIduenio);
			
		}
		fread(&reg, sizeof(reg), 1, archivo);
	}
	fclose(archivo);


}
 
void evolucionMascota(FILE *archivo)
{
	system ("cls");
	turnos reg;
	int dni;
	
	printf("----Evolucion de la mascota----\n");
	printf("================================\n\n");
	archivo = fopen("Turnos.dat", "a+b");
	
	fread(&reg, sizeof(turnos), 1, archivo);
	printf ("\nIngrese DNI del duenio: ");
	scanf ("%d",&dni);
	do
	{
		printf ("\nEl DNI seleccionado no coincide con un usuario. Ingrese nuevamente");
		printf ("\nIngrese DNI del duenio: ");
		scanf ("%d",&dni);
	}
	while (dni!=reg.DNIduenio);
	
	printf ("\nIngrese registro de la mascota: ");
	_flushall();
	gets(reg.atencion);
	
	fwrite(&reg, sizeof(turnos), 1, archivo);	
	fclose(archivo);
}
