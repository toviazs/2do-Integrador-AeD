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

        printf("Modulo de Asistente\n");
        printf("===================\n\n");

        printf("1. Registrar mascota\n");
        printf("2. Listar mascotas\n");
        printf("3. Registrar turno\n");
        printf("4. Listar turnos por veterinario y fecha\n\n");

        printf("5. Cerrar Sesion\n\n");

        printf("> ");
        scanf("%d", &caso);

        system("cls");

        switch (caso)
        {

        case 1:
            AgregarMascota(archivo);
            break;

        case 2:
            printf("\tListar Mascotas");
            printf("\n\t===============\n\n");
            ListarAnimales(archivo);
            break;

        case 3:
            RegistrarTurno(archivo2, archivo3, archivo);
            break;

        case 4:

            ListarTurno(archivo2, archivo3);

            break;
        }

    } while (caso != 5);
}

void InfoMascotaActual(mascota InfoMasc, int datos)
{
    printf("\tRegistrar Mascota");

    printf("\n\t=================\n");

    if (datos >= 1)
    {
        printf("\n%25s - %s\n", "Nombre mascota", InfoMasc.nombre);

        if (datos >= 2)
        {
            printf("%25s - %s\n", "Direccion", InfoMasc.direcc);

            if (datos >= 3)
            {
                printf("%25s - %d\n", "Dni duenio", InfoMasc.DNI_DUENIO);

                if (datos >= 4)
                {
                    printf("%25s - %s\n", "Localidad", InfoMasc.localidad);

                    if (datos >= 5)
                    {
                        printf("%25s - %d/%d/%d\n", "Fecha", InfoMasc.Fecha.dia, InfoMasc.Fecha.mes, InfoMasc.Fecha.anio);

                        if (datos >= 6)
                        {
                            printf("%25s - %.2f kg\n", "Peso", InfoMasc.peso);

                            if (datos >= 7)
                            {
                                printf("%25s - %s\n", "Telefono", InfoMasc.numeroTel);
                            }
                        }
                    }
                }
            }
        }
    }
}

void InfoTurnoActual(turnos InfoTurno, int datos)
{
    printf("\t\tRegistrar Turno");

    printf("\n\t\t=================\n");

    if (datos >= 1)
    {
        printf("\n%25s - %d\n", "Matricula veterinario", InfoTurno.matriculaVet);

        if (datos >= 2)
        {
            printf("%25s - %d/%d/%d\n", "Fecha", InfoTurno.fec.dia, InfoTurno.fec.mes, InfoTurno.fec.anio);

            if (datos >= 3)
            {
                printf("%25s - %d\n", "Dni duenio", InfoTurno.DNIduenio);
            }
        }
    }
}

void AgregarMascota(FILE *archi)
{
    int datos = 0; //contabiliza los datos validados para ir mostrandolos durante el ingreso

    archi = fopen("Mascotas.dat", "r+b");
    mascota vec;

    system("cls");
    printf("\tRegistrar Mascota");

    printf("\n\t=================\n");

    printf("\nNombre mascota: ");
    _flushall();
    gets(vec.nombre);

    system("cls");
    datos = 1;
    InfoMascotaActual(vec, datos);

    printf("\nDireccion: ");
    _flushall();
    gets(vec.direcc);

    system("cls");
    datos = 2;
    InfoMascotaActual(vec, datos);

    printf("\nDNI duenio: ");
    scanf("%d", &vec.DNI_DUENIO);

    system("cls");
    datos = 3;
    InfoMascotaActual(vec, datos);

    printf("\nLocalidad: ");
    _flushall();
    gets(vec.localidad);

    system("cls");
    datos = 4;
    InfoMascotaActual(vec, datos);

    printf("\nFecha ingreso");

    printf("\n\tDia: ");
    scanf("%d", &vec.Fecha.dia);

    printf("\tMes: ");
    scanf("%d", &vec.Fecha.mes);

    printf("\tAnio: ");
    scanf("%d", &vec.Fecha.anio);

    system("cls");
    datos = 5;
    InfoMascotaActual(vec, datos);

    printf("\nPeso mascota: ");
    scanf("%f", &vec.peso);

    system("cls");
    datos = 6;
    InfoMascotaActual(vec, datos);

    printf("\nNro de telefono: ");
    _flushall();
    gets(vec.numeroTel);

    system("cls");
    datos = 7;
    InfoMascotaActual(vec, datos);

    fseek(archi, 0, SEEK_END);

    fwrite(&vec, sizeof(vec), 1, archi);

    fclose(archi);
    printf("\n\t----Mascota agregada con exito----");
    getch();
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
            printf("\n============================\n");
        }

        fread(&vec, sizeof(vec), 1, archi);
    }

    fclose(archi);
    getch();
}

void RegistrarTurno(FILE *archi, FILE *archi2, FILE *archi3)
{
    archi = fopen("Turnos.dat", "r+b");
    archi2 = fopen("Veterinarios.dat", "r+b");
    archi3 = fopen("Mascotas.dat", "r+b");

    int datos = 0;
    mascota vec;
    turnos reg;
    datosVete regi;

    int dni = 0, situacion[2];
    bool matCorrecta, dniValido = false;

    system("cls");

    printf("\t\tRegistrar Turno");

    printf("\n\t\t=================\n");

    do
    {
        matCorrecta = true;
        printf("\nMatricula del Veterinario: ");
        scanf("%d", &reg.matriculaVet);

        VerificarMatricula(reg.matriculaVet, situacion);

        if (situacion[0] == 0 and situacion[1] == 1)
        {
            printf("\n\tError: la matricula no corresponde a un veterinario registrado");
            matCorrecta = false;
            getch();

            system("cls");
            InfoTurnoActual(reg, datos);
        }

    } while (!matCorrecta);

    system("cls");
    datos = 1;
    InfoTurnoActual(reg, datos);

    printf("\nFecha turno: \n");
    printf("\tDia: ");
    scanf("%d", &reg.fec.dia);
    printf("\tMes: ");
    scanf("%d", &reg.fec.mes);
    printf("\tAnio: ");
    scanf("%d", &reg.fec.anio);

    system("cls");
    datos = 2;
    InfoTurnoActual(reg, datos);

    do
    {
        printf("\n\nDNI Duenio: ");
        scanf("%d", &dni);

        rewind(archi3);

        fread(&vec, sizeof(mascota), 1, archi3);

        while (!feof(archi3))
        {
            if (vec.DNI_DUENIO == dni)
            {
                dniValido = true;
                break;
            }

            fread(&vec, sizeof(mascota), 1, archi3);
        }

        if (dniValido)
        {
            continue;
        }

        printf("\n\tError: Dni no valido");
        getch();

        system("cls");
        InfoTurnoActual(reg, datos);
    } while (!dniValido);

    reg.DNIduenio = dni;

    system("cls");
    datos = 3;
    InfoTurnoActual(reg, datos);

    reg.borrado = false; //dado que el turno recien se crea, no puede haber sido atendido

    fseek(archi, 0, SEEK_END);
    fwrite(&reg, sizeof(reg), 1, archi);

    fclose(archi);
    fclose(archi2);
    fclose(archi3);

    printf("\n\t----Turno agregado con exito----");
    getch();
}

void ListarTurno(FILE *archi, FILE *archi2)
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
                if (!feof(archi) and reg.matriculaVet == mat)
                {
                    printf("\nTurno %d\n", i);
                    printf("=========================\n");
                    printf("Fecha: %d/%d/%d", reg.fec.dia, reg.fec.mes, reg.fec.anio);
                    printf("\nDNI: %d", reg.DNIduenio);
                    printf("\nDetalles: ");
                    puts(reg.atencion);
                    printf("\n=========================\n");

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
