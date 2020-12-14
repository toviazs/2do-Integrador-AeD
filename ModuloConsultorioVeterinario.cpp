#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "LibreriaModulos.h"
#include <windows.h>

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

//prototipos
void evolucionMascota(FILE *archivo, FILE *archivo2);
void listaDeTurnos(FILE *archi, FILE *archi2, FILE *archi3);

main()
{
	FILE *archivo, *archivo2, *archivo3;
	int caso = 0, opc = 0, salirPrograma = 0;

	archivo = fopen("Mascotas.dat", "r+b");
	archivo2 = fopen("Turnos.dat", "r+b");
	archivo3 = fopen("Veterinarios.dat", "r+b");

	do
	{
		system("cls");

		printf("Modulo Veterinario\n");
		printf("==================\n\n");

		printf("1. Visualizar lista de espera\n");
		printf("2. Registrar evolucion mascota\n\n");

		printf("3. Cerrar sesion\n\n");

		printf("> ");
		scanf("%d", &caso);

		switch (caso)
		{
		case 1:
			listaDeTurnos(archivo2, archivo3, archivo);
			break;
		case 2:
			evolucionMascota(archivo, archivo2);
			break;
		case 3:
			printf("\n\tSeguro que desea salir?");
			printf("\n\n\t(1.Si  2.No)");
			printf("\n\t> ");

			scanf("%d", &salirPrograma);

			if (salirPrograma != 1)
			{
				caso = 1;
			}
			else
			{
				system("MenuPrincipal.exe");
			}

			break;
		}

	} while (caso != 3);

	fclose(archivo);
	fclose(archivo2);
	fclose(archivo3);
}

void listaDeTurnos(FILE *archi, FILE *archi2, FILE *archi3)
{
	turnos reg;
	veterinario regi;
	mascota masc;

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
		printf("\n\nMatricula veterinario: ");
		scanf("%d", &mat);

		if (mat == 0)
		{
			break;
		}

		VerificarMatricula(mat, situ);
		if (situ[0] == 0)
		{
			printf("\n\tError: la matricula no corresponde a un veterinario registrado");
			getch();
			matValida = false;
		}
	} while (!matValida);

	if (mat != 0)
	{
		archi3 = fopen("Mascotas.dat", "r+b");
		archi2 = fopen("Veterinarios.dat", "r+b");
		archi = fopen("Turnos.dat", "r+b");

		system("cls");

		fread(&regi, sizeof(veterinario), 1, archi2);

		while (!feof(archi2))
		{
			if (mat == regi.matricula)
			{
				matEncontrada = true;
				break;
			}

			fread(&regi, sizeof(veterinario), 1, archi2);
		}

		printf("\n\tVeterinario:\n");
		printf("\t%20s: %s\n", "Nombre", regi.nomyApe);
		printf("\t%20s: %d\n", "DNI", regi.DNI);

		printf("\n\tTurnos:\n");

		fread(&reg, sizeof(turnos), 1, archi);

		if (matEncontrada)
		{
			while (!feof(archi))
			{
				if (!feof(archi) and reg.matriculaVet == mat and !reg.borrado)
				{
					printf("\n\t\tTurno %d\n", i);
					
					fread(&masc, sizeof(mascota), 1, archi3);

					while (!feof(archi3))
					{
						if(reg.DNIduenio == masc.DNI_DUENIO)
						{
							printf("%30s: %s", "Mascota", masc.nombre);
							break;
						}

						fread(&masc, sizeof(mascota), 1, archi3);
					}
					
					printf("\n%30s: %d/%d/%d", "Fecha", reg.fec.dia, reg.fec.mes, reg.fec.anio);
					printf("\n%30s: %d\n", "Dni", reg.DNIduenio);
					printf("%30s: Pendiente\n", "Estado");

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
		fclose(archi3);
	}
}

void evolucionMascota(FILE *archivo, FILE *archivo2)
{
	system("cls");
	char apeynom[60], aux[380];
	int opc = 0, datos = 0;
	bool nombreValido = false; //veamos q onda
	bool turnoPendiente = false;

	printf("\t\tRegistrar Evolucion de Mascota");

	printf("\n\t\t==============================\n");

	archivo = fopen("Mascotas.dat", "r+b");
	archivo2 = fopen("Turnos.dat", "r+b");

	turnos reg;
	mascota regi;

	do
	{
		printf("\n(Ingrese un 0 para salir)");
		printf("\n\nNombre mascota: ");
		_flushall();
		gets(apeynom);

		if (strcmp(apeynom, "0") == 0)
		{
			return;
		}

		fread(&regi, sizeof(regi), 1, archivo);

		while (!feof(archivo))
		{
			if ((strcmp(regi.nombre, apeynom) == 0))
			{
				fread(&reg, sizeof(reg), 1, archivo2);

				while (!feof(archivo2))
				{
					if ((reg.DNIduenio == regi.DNI_DUENIO) and (reg.borrado == false) and (strcmp(regi.nombre, apeynom) == 0))
					{
						turnoPendiente = true;
						fseek(archivo2, (long)-sizeof(turnos), SEEK_CUR);
						break;
					}

					fread(&reg, sizeof(reg), 1, archivo2);
				}

				nombreValido = true;
				break;
			}

			fread(&regi, sizeof(regi), 1, archivo);
		}

		if (!nombreValido)
		{
			printf("\nError: el nombre no corresponde a una mascota registrada");
			getch();

			system("cls");
			InfoEvolucionActual(reg, regi, datos);
		}

	} while (!nombreValido);

	system("cls");
	datos = 1;
	InfoEvolucionActual(reg, regi, datos);

	if (turnoPendiente)
	{
		printf("\n\tInforme: ");
		_flushall();
		gets(aux);

		strcpy(reg.atencion, aux);

		system("cls");
		datos = 2;
		InfoEvolucionActual(reg, regi, datos);

		reg.borrado = true;

		fwrite(&reg, sizeof(reg), 1, archivo2);

		printf("\n\t----Registro completado con exito----");
	}
	else
	{
		printf("\n\t-La mascota no tiene turnos pendientes-");
	}

	fclose(archivo);
	fclose(archivo2);

	getch();
}