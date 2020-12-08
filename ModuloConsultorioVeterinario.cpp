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
	bool borrado;
};

struct mascota
{
    char nombre[60];
    char direcc[60];
    int DNI_DUENIO;
    char localidad[60];
    fecha Fecha;
    float peso;
    char numeroTel[25];
};

//prototipos
void listaDeTurnos(FILE *archivo);
void evolucionMascota(FILE *archivo, FILE *archivo2)

main()
{
	FILE *archivo;
	FILE *archivo2;
	int caso = 0, opc = 0;

	archivo = fopen("Mascotas.dat", "r+b");
	archivo2 = fopen("Turnos.dat", "r+b");
	
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
			evolucionMascota(archivo, archivo2);
			getch();
			break;
		}
		}

	} while (caso != 3);

	fclose(archivo);
	fclose(archivo2);
}

void listaDeTurnos(FILE *archivo)
{
	system("cls");
	turnos reg;
	archivo = fopen("Turnos.dat", "rb");

	printf("----Lista de Turnos----\n");
	printf("================================\n\n");

	fread(&reg, sizeof(turnos), 1, archivo);

	if (reg.borrado == false)
	{
		while (!feof(archivo))
		{
			if (!feof(archivo))
			{
				printf("\nLa matricula es:  %d", reg.matriculaVet);
				printf("\nFecha ");
				printf("\nDia: %d", reg.fec.dia);
				printf("\nMes: %d", reg.fec.mes);
				printf("\nAnio: %d", reg.fec.anio);
				printf("\nDni del duenio: %d\n", reg.DNIduenio);
			}
			fread(&reg, sizeof(reg), 1, archivo);
		}
	}

	fclose(archivo);
}

void evolucionMascota(FILE *archivo, FILE *archivo2)
{
	system("cls");
	turnos reg;
	mascota regi;

	char apeynom;

	printf("\t----Evolucion de la mascota----\n");
	printf("\t================================\n\n");
	archivo = fopen("Turnos.dat", "a+b");
	archivo2 = fopen("Mascotas.dat", "rb");

	fread(&regi, sizeof(mascota), 1, archivo2);
	fread(&reg, sizeof(turnos), 1, archivo);

	printf("\nIngrese Apellido y Nombre de la mascota: ");
	_flushall();
	gets(apeynom);

	do
	{
		printf("\nEl apellido y nombre seleccionado no coincide con un usuario. Ingrese nuevamente");
		printf("\nIngrese Apellido y Nombre de la mascota: ");
		gets(apeynom);
	} while (strcmp(apeynom, regi.nombre) != 0);

	printf("\nDesea registrar un nuevo informe o dar de Alta (1- Dar de Alta) / 2 - (Registrar Nuevo Informe)): ");
	scanf("%d", &opc);

	if (opc == 1)
	{
		reg.borrado = true;

		fseek(archivo, (long)-sizeof(turnos), SEEK_CUR);
		fwrite(&reg, sizeof(turnos), 1, archivo);
	}

	if(opc == 2)
	{
		printf("\nIngrese registro de la mascota: ");
		_flushall();
		gets(reg.atencion);

		fwrite(&reg, sizeof(turnos), 1, archivo);
	}

	fclose(archivo);
	fclose(archivo2);
}

