#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

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

		printf("> : ");
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
void listaDeTurnos(FILE *arhicvo2,FILE *archivo3);
{
	int mat = 0;                //matricula
    bool matEncontrada = false; //bandera
    bool matValida = false;

	archi2 = fopen("Turnos.dat", "r+b");
	archi3 = fopen("Veterinarios.dat", "r+b");

    turnos reg;
    datosVete regi;


	do
    {
        matValida = true;
        system("cls");

        printf("\t----LISTA DE ESPERA DE TURNOS ----\n");
        printf("\n=============================================\n");

        printf("Ingrese matricula de Veterinario: ");
        scanf("%d", &mat);

        if (VerificarMatricula(mat))
        {
            printf("Error: la matricula no corresponde a un veterinario registrado");
            getch();
            matValida = false;
        }
    } while (!matValida);

	fread(&reg, sizeof(turnos), 1, archi2);
    fread(&regi, sizeof(datosVete), 1, archi3);

    while (!feof(archi3))
    {
        if (mat == regi.matricula)
        {
            matEncontrada = true;
        }

        fread(&regi, sizeof(datosVete), 1, archi2);
    }

    if (matEncontrada)
    {
        while (!feof(archi2))
        {
            if (!feof(archi2) and reg.matriculaVet == mat)
            {
                printf("\nFecha de Turno: \n");
                printf("=========================\n");
                printf("Dia: %d", reg.fec.dia);
                printf("\nMes: %d", reg.fec.mes);
                printf("\nAnio: %d", reg.fec.anio);
 
                printf("\n=========================\n");
            }
            fread(&reg, sizeof(turnos), 1, archi2);
        }
    }
    else
    {
        printf("No se encontraron turnos");
    }

	fclose(archivo2);
	fclose(archivo3);

	
}
void evolucionMascota(FILE *archivo, FILE *archivo2)
{
	system("cls");
	char apeynom[60];
	int opc = 0;

	printf("\t----Evolucion de la mascota----\n");
	printf("\t================================\n\n");
	archivo = fopen("Mascotas.dat", "rb");
	archivo2 = fopen("Turnos.dat", "r+b"); 

	turnos reg;
	mascota regi;

	fread(&reg, sizeof(turnos), 1, archivo2);
	fread(&regi, sizeof(mascota), 1, archivo);

	printf("\nIngrese Apellido y Nombre de la mascota: ");
	_flushall();
	gets(apeynom);

	if ((strcmp(regi.nombre, apeynom) != 0))
	{
		do
		{
			printf("\nEl apellido y nombre seleccionado no coincide con un usuario. Ingrese nuevamente");
			printf("\nIngrese Apellido y Nombre de la mascota: ");
			_flushall();
			gets(apeynom);

		} while (strcmp(regi.nombre, apeynom) != 0);
	}

	printf("\nDesea registrar un nuevo informe o dar de Alta (1- Dar de Alta) / 2 - (Registrar Nuevo Informe)): ");
	scanf("%d", &opc);

	if (opc == 1)
	{
		reg.borrado = true;

		fseek(archivo2, (long)-sizeof(turnos), SEEK_CUR);
		fwrite(&reg, sizeof(turnos), 1, archivo2);
	}

	if (opc == 2)
	{
		printf("\nIngrese registro de la mascota: ");
		_flushall();
		gets(reg.atencion);
		fwrite(&reg, sizeof(turnos), 1, archivo2);
	}

	fclose(archivo);
	fclose(archivo2);
}
