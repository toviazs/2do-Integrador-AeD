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

Perez Lucas Gustavo
43564887
lucas.perez@alu.frt.utn.edu.ar

Paz Bruno Leonel
43648810
Bruno.Paz@alu.frt.utn.edu.ar

Posse Ricardo
43567498
Ricardo.Posse@alu.frt.utn.edu.ar
*/

const int TAMANO = 60;
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
    int matriculaVet; //la matricula del veterinario que lo atiende
    bool borrado;
};

struct datosUsuario
{
    char usuario[10];
    char contrasena[10];
    char ApeyNom[60];
    int modulo;
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

//P R O T O T I P O S
void AgregarMascota(FILE *archi);
void ListarAnimales(FILE *archi);
void RegistrarTurno(FILE *archi, FILE *archi2, FILE *archi3);
void ListarTurno(FILE *archi, FILE *archi2);

main()
{
    FILE *archivo, *archivo2, *archivo3;
    int opcion, idx = 0, idxTurnos = 0, caso = 0;

    nombreArchi archivoMascotas = "Mascotas.dat", archivoTurnos = "Turnos.dat", archivoVeterinarios = "Veterinarios.dat";

    AbrirGenerarArchivo(archivo, archivoMascotas);
    AbrirGenerarArchivo(archivo2, archivoTurnos);
    AbrirGenerarArchivo(archivo3, archivoVeterinarios);

    do
    {
        system("cls");

        printf("M o d u l o  d e  A s i s t e n c i a\n");
        printf("===========================================\n\n");

        printf("1.- R e g i s t r a r   M a s c o t a\n");
        printf("2.- L i s t a r   A n i m a l e s\n");
        printf("3.- R e g i s t r a r   T u r n o\n");
        printf("4.- L i s t a d o  d e   A t e n c i o n e s   p o r   V e t e r i n a r i o   y   F e c h a\n\n");

        printf("5.- C e r r a r   S e s i o n\n\n");
        printf("===========================================\n\n");
        printf("> ");
        scanf("%d", &caso);

        system("cls");

        switch (caso)
        {

        case 1:
            AgregarMascota(archivo);
            break;

        case 2:
            printf("\tL I S T A R  M A S C O T A S");
            printf("\n========================================\n");
            ListarAnimales(archivo);
            break;

        case 3:

            system("cls");
            printf("\nRegistrar Turnos");
            RegistrarTurno(archivo2, archivo3, archivo);
            break;

        case 4:

            ListarTurno(archivo2, archivo3);

            break;
        }

    } while (caso != 5);
}

void AgregarMascota(FILE *archi)
{
    archi = fopen("Mascotas.dat", "r+b");
    mascota vec;

    system("cls");
    printf("\tR E G I S T R A R  M A S C O T A");

    printf("\n========================================\n");

    printf("\nIngrese el nombre de la mascota: ");
    _flushall();
    gets(vec.nombre);

    printf("\nIngrese la direccion: ");
    _flushall();
    gets(vec.direcc);

    printf("\nIngrese el DNI del duenio: ");
    scanf("%d", &vec.DNI_DUENIO);

    printf("\nIngrese la localidad: ");
    _flushall();
    gets(vec.localidad);

    printf("\nIngrese la fecha de ingreso: ");

    printf("\nDIA: ");
    scanf("%d", &vec.Fecha.dia);

    printf("\nMES: ");
    scanf("%d", &vec.Fecha.mes);

    printf("\nANIO: ");
    scanf("%d", &vec.Fecha.anio);

    printf("\nIngrese el peso de la mascota: ");
    scanf("%f", &vec.peso);

    printf("\nIngrese el numero de telefono: ");
    _flushall();
    gets(vec.numeroTel);

    fseek(archi, 0, SEEK_END);

    fwrite(&vec, sizeof(vec), 1, archi);

    fclose(archi);
    system("cls");
}

void ListarAnimales(FILE *archi)
{
    archi = fopen("Mascotas.dat", "r+b");
    mascota vec;

    rewind(archi);

    fread(&vec, sizeof(vec), 1, archi);

    while (!feof(archi))
    {
        if (!feof(archi))
        {

            printf("Nombre de la Mascota: %s\n", vec.nombre);
            printf("Direccion: %s", vec.direcc);
            printf("\nDNI del duenio: %d", vec.DNI_DUENIO);
            printf("\nLocalidad: %s\n", vec.localidad);
            printf("FECHA: %d/%d/%d\n", vec.Fecha.dia, vec.Fecha.mes, vec.Fecha.anio);
            printf("\nPeso de la Mascota: %.2f", vec.peso);
            printf("\nNumero de telefono: %s", vec.numeroTel);
            printf("\n\n========================================\n");
        }

        fread(&vec, sizeof(vec), 1, archi);
    }

    fclose(archi);
    getch();
    system("cls");
}

void RegistrarTurno(FILE *archi, FILE *archi2, FILE *archi3)
{
    archi = fopen("Turnos.dat", "r+b");
    archi2 = fopen("Veterinarios.dat", "r+b");
    archi3 = fopen("Mascotas.dat", "r+b");
    
    mascota vec;
    turnos reg;
    datosVete regi;

    int dni = 0, situacion[2];
    bool matCorrecta;

    fread(&vec, sizeof(mascota), 1, archi3);

    do
    {
        matCorrecta = true;
        printf("\n\nMatricula del Veterinario: ");
        scanf("%d", &reg.matriculaVet);

        if (VerificarMatricula(reg.matriculaVet, situacion))
        {
            printf("Error: la matricula no corresponde a un veterinario registrado");
            matCorrecta = false;
            getch();
        }

    } while (!matCorrecta);

    printf("\nFecha de Turno: \n");
    printf("Dia: ");
    scanf("%d", &reg.fec.dia);
    printf("\nMes: ");
    scanf("%d", &reg.fec.mes);
    printf("\nAnio: ");
    scanf("%d", &reg.fec.anio);

    printf("\n\nDNI Duenio: ");
    scanf("%d", &dni);

    if (dni != vec.DNI_DUENIO)
    {
        do
        {
            printf("\nEl DNI no coincide con el duenio. Ingrese el DNI correspondiente");
            printf("\nDNI Duenio: ");
            scanf("%d", &dni);


        } while (dni != vec.DNI_DUENIO);
    }
    else
    {
        reg.DNIduenio = dni;
    }

    reg.borrado = false;

    fseek(archi, 0, SEEK_END);
    fwrite(&reg, sizeof(reg), 1, archi);
    
    fclose(archi);
    fclose(archi2);
    fclose(archi3);

    system("cls");
}

void ListarTurno(FILE *archi, FILE *archi2)
{
    archi2 = fopen("Veterinarios.dat", "r+b");
    archi = fopen("Turnos.dat", "r+b");
    turnos reg;
    datosVete regi;

    int mat = 0, situ[2];                //matricula
    bool matEncontrada = false; //bandera
    bool matValida = false;

    fread(&reg, sizeof(turnos), 1, archi);

    do
    {
        matValida = true;
        system("cls");
        printf("\tL I S T A D O   D E   T U R N O S");
        printf("\n=============================================\n");

        printf("Ingrese matricula de Veterinario: ");
        scanf("%d", &mat);

        if (VerificarMatricula(mat, situ))
        {
            printf("Error: la matricula no corresponde a un veterinario registrado");
            getch();
            matValida = false;
        }
    } while (!matValida);

    system("cls");

    fread(&regi, sizeof(datosVete), 1, archi2);

    while (!feof(archi2))
    {
        if (mat == regi.matricula)
        {
            matEncontrada = true;
        }

        fread(&regi, sizeof(datosVete), 1, archi2);
    }

    if (matEncontrada)
    {
        while (!feof(archi))
        {
            if (!feof(archi) and reg.matriculaVet == mat)
            {
                printf("\nFecha de Turno \n");
                printf("=========================\n");
                printf("Dia: %d", reg.fec.dia);
                printf("\nMes: %d", reg.fec.mes);
                printf("\nAnio: %d", reg.fec.anio);
                printf("\nDNI: %d", reg.DNIduenio);
                printf("\nDetalles: ");
                puts(reg.atencion);
                printf("\n=========================\n");
            }
            fread(&reg, sizeof(turnos), 1, archi);
        }
    }
    else
    {
        printf("No se encontraron turnos");
    }

    getch();

    fclose(archi);
    fclose(archi2);

    system("cls");
}
