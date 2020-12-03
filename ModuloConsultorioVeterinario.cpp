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

struct fecha
{
    int dia;
    int mes;
    int anio;
};
struct turnos
{
    int matricula;
    fecha fec;
    int DNIduenio;
    char atencion[380];
};

//prototipos
void listaDeTurnos (FILE *archivo);
void evolucionMascota(FILE *archivo);

main()
{
	FILE *archivo;
    int caso = 0;
    
	archivo = fopen("Turnos.dat", "r+b");
    if (archivo == NULL)
    {
        printf("El archivo Turnos.dat no existe. Se intentara crearlo.\n\n");
        archivo = fopen("Turnos.dat", "w+b");

        if (archivo == NULL)
        {
            printf("Error. No se pudo crear");
            exit(1);
        }

        printf("El archivo se creo exitosamente.\n");
        getch();
    }
    else
    {
        printf("El archivo Turnos.dat fue abierto correctamente...");
        getch();
    }

    do
    {
    	system ("cls");
    	
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
void listaDeTurnos (FILE *archivo)
{
	system ("cls");
	turnos reg;
	archivo = fopen("Turnos.dat", "rb");
	
	printf("================================\n\n");
	
	fread(&reg, sizeof(reg), 1, archivo);
	while (!feof(archivo))
	{
		if(!feof(archivo))
		{
			printf ("\nLa matricula es:  %d",reg.matricula);
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
	
	archivo = fopen("Turnos.dat", "a+b");
	
	printf("\nIngrese evolucion de la mascota con un maximo de 380 caracteres: ");
	_flushall();
	gets(reg.atencion);
	fwrite(&reg, sizeof(reg), 1, archivo);
	
	fclose(archivo);
}

