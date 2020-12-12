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

struct datosVete
{
	char nomyApe[60];
	int matricula;
	int DNI;
	char telefono[25];
	int modulo; //1- Administrador. 2- Veterinario. 3- Asistente
	char contrasenia[10];
};

//prototipos
void evolucionMascota(FILE *archivo, FILE *archivo2);
void listaDeTurnos(FILE *archivo2, FILE *archivo3);

main()
{
	FILE *archivo, *archivo2, *archivo3;
	int caso = 0, opc = 0;

	archivo = fopen("Mascotas.dat", "r+b");
	archivo2 = fopen("Turnos.dat", "r+b");
	archivo3 = fopen("Veterinarios.dat", "r+b");

	do
	{
		system("cls");

		printf("Modulo Consultorio Veterinario\n");
		printf("================================\n\n");

		printf("1.- Visualizar Lista de Espera de Turnos (Informe)\n");
		printf("2.- Registrar Evolucion de la Mascota\n\n");

		printf("3.- Cerrar sesion\n\n");

		printf("> ");
		scanf("%d", &caso);

		switch (caso)
		{
		case 1:
		{
			listaDeTurnos(archivo2, archivo3);
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
	fclose(archivo3);
}

void listaDeTurnos(FILE *archi, FILE *archi2)
{
	turnos reg;
	datosVete regi;

	int mat = 0; //matricula del veterinario
	int situ[2], i = 1;
	bool matEncontrada = false; //bandera
	bool matValida = false;

	do
	{
		matValida = true;
		system("cls");
		printf("\tListado de Turnos");
		printf("\n\t==================\n");

		printf("\n(Ingrese 0 para salir)");
		printf("\n\nIngrese matricula de Veterinario: ");
		scanf("%d", &mat);

		if (mat == 0)
		{
			break;
		}

		if (VerificarMatricula(mat, situ))
		{
			printf("Error: la matricula no corresponde a un veterinario registrado");
			getch();
			matValida = false;
		}
	} while (!matValida);

	if (mat != 0)
	{
		archi2 = fopen("Veterinarios.dat", "r+b");
		archi = fopen("Turnos.dat", "r+b");

		system("cls");

		fread(&regi, sizeof(datosVete), 1, archi2);

		while (!feof(archi2))
		{
			if (mat == regi.matricula)
			{
				matEncontrada = true;
				break;
			}

			fread(&regi, sizeof(datosVete), 1, archi2);
		}

		printf("Veterinario:\n");
		printf("\t%20s: %s\n", "Nombre", regi.nomyApe);
		printf("\t%20s: %d\n", "DNI", regi.DNI);

		fread(&reg, sizeof(turnos), 1, archi);

		if (matEncontrada)
		{
			while (!feof(archi))
			{
				if (!feof(archi) and reg.matriculaVet == mat and !reg.borrado)
				{
					printf("\nTurno %d\n", i);
					printf("=========================\n");
					printf("Fecha: %d/%d/%d", reg.fec.dia, reg.fec.mes, reg.fec.anio);
					printf("\nDNI: %d", reg.DNIduenio);
					i++;
				}

				fread(&reg, sizeof(turnos), 1, archi);
			}

			if (i == 1)
			{
				printf("\n\tNo se encontraron turnos");
			}
		}

		getch();

		fclose(archi);
		fclose(archi2);
	}
}

void InfoEvolucionActual(turnos InfoTurno, mascota InfoMascota, int datos)
{
	printf("\tRegistrar Evolucion de Mascota");

	printf("\n\t=================================\n");

	if (datos >= 1)
	{
		printf("\n%25s - %s\n", "Nombre mascota", InfoMascota.nombre);

		if (datos >= 2)
		{
			printf("%25s - %s\n", "Detalles", InfoTurno.atencion);
		}
	}
}

void evolucionMascota(FILE *archivo, FILE *archivo2)
{
	system("cls");
	char apeynom[60], aux[380];
	int opc = 0, datos = 0;
	bool nombreValido = false, regEncontrado = false;

	printf("\tRegistrar Evolucion de Mascota");

	printf("\n\t=================================\n");

	archivo = fopen("Mascotas.dat", "rb");
	archivo2 = fopen("Turnos.dat", "r+b");

	turnos reg;
	mascota regi;

	do
	{
		printf("\nIngrese Apellido y Nombre de la mascota: ");
		_flushall();
		gets(apeynom);

		rewind(archivo);
		fread(&regi, sizeof(mascota), 1, archivo);

		while (!feof(archivo))
		{
			if ((strcmp(regi.nombre, apeynom) == 0))
			{
				nombreValido = true;
				break;
			}

			fread(&regi, sizeof(mascota), 1, archivo);
		}

		if (nombreValido)
		{
			continue;
		}

		printf("\nEl apellido y nombre seleccionado no coincide con una mascota. Ingrese nuevamente");
		getch();

		system("cls");
		InfoEvolucionActual(reg, regi, datos);

	} while (!nombreValido);

	system("cls");
	datos = 1;
	InfoEvolucionActual(reg, regi, datos);

	printf("\nDesea registrar un nuevo informe o dar de Alta (1- Dar de Alta) / 2 - (Registrar Nuevo Informe)): ");
	scanf("%d", &opc);

	do
	{
		rewind(archivo2);
		fread(&reg, sizeof(turnos), 1, archivo2);

		while (!feof(archivo2))
		{
			if (!reg.borrado)
			{
				regEncontrado = true;
				break;
			}

			fread(&reg, sizeof(turnos), 1, archivo2);
		}

		if (regEncontrado)
		{
			if (opc == 1)
			{
				reg.borrado = true;
		
				fseek(archivo2, (long)-sizeof(turnos), SEEK_CUR);
				fwrite(&reg, sizeof(turnos), 1, archivo2);

				printf("\n\t----Mascota dada de alta con exito----");
				
				break;
			}

			if (opc == 2)
			{
				printf("\nIngrese registro de la mascota: ");
				_flushall();
				gets(aux);

				strcpy(reg.atencion, aux);

				system("cls");
				datos = 2;
				InfoEvolucionActual(reg, regi, datos);

				reg.borrado = true;

				fseek(archivo2, (long)-sizeof(turnos), SEEK_CUR);
				fwrite(&reg, sizeof(turnos), 1, archivo2);

				printf("\n\t----Registro completado con exito----");

				break;
			}
		}
	} while (!regEncontrado);

	fclose(archivo);
	fclose(archivo2);
}
