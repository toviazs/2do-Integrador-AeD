#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
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

struct datosVete
{

	char nomyApe[60];
	int matricula;
	int DNI;
	char telefono[25];
};
struct datosUsu
{

	char usuario[10];
	char contrasenia[10];
	char nomyApe[60];
};

// Prototipos
void registrarVeterinario(FILE *arch1);
void registrarUsuario(FILE *arch1);

main()
{
	FILE *arch1;
	int caso = 0;

	arch1 = fopen("Veterinarios.dat.", "r+b");
	if (arch1 == NULL)
	{
		printf("El archivo Veterinarios.dat no existe. Se intentara crearlo...\n");
		arch1 = fopen("Veterinarios.dat.", "a+b");
		if (arch1 == NULL)
		{
			printf("Error. No se pudo crear el archivo.");
			exit(1);
		}
		printf("El archivo se creo exitosamente...\n\n");
		system("pause");
	}

	do
	{
		system("cls");
		printf("Modulo del Asistente\n");
		printf("======================\n\n");

		printf("1.- Registrar Veterinario\n");
		printf("2.- Registrar Usuario Asistente\n");
		printf("3.- Atenciones por Veterinarios\n");
		printf("4.- Ranking de Veterinarios por Atenciones\n\n");

		printf("5.- Cerrar la aplicacion\n\n");

		printf("> ");
		scanf("%d", &caso);

		switch (caso)
		{
		case 1:
		{
			system("cls");
			registrarVeterinario(arch1);
			break;
		}
		case 2:
		{
			system("cls");
			registrarUsuario(arch1);
			break;
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
void registrarVeterinario(FILE *arch1)
{
	datosVete reg;
	printf("\tR E G I S T R A R  V E T E R I N A R I O");

	printf("\n========================================\n");

	printf("\nIngrese nombre y apellido: ");
	_flushall();
	gets(reg.nomyApe);

	printf("\nIngrese numero de matricula: ");
	scanf("%d", &reg.matricula);

	printf("\nIngrese DNI: ");
	scanf("%d", &reg.DNI);

	printf("\nIngrese telefono: ");
	_flushall();
	gets(reg.telefono);

	fwrite(&reg, sizeof(reg), 1, arch1);

	printf("\n----Veterinario agregado con exito----");

	printf("\n\n");
	system("pause");
}
void registrarUsuario(FILE *arch1)
{
	datosUsu reg1;

	printf("\tR E G I S T R A R  U S U A R I O");

	printf("\n========================================\n");

	printf("\nIngrese Usuario: ");
	_flushall();
	gets(reg1.usuario);

	printf("\nIngrese contrasenia: ");
	_flushall();
	gets(reg1.contrasenia);

	printf("\nIngrese Nombre y apellido: ");
	_flushall();
	gets(reg1.nomyApe);

	fwrite(&reg1, sizeof(reg1), 1, arch1);

	printf("\n----Usuario agregado con exito----");

	printf("\n\n");
	system("pause");
}
