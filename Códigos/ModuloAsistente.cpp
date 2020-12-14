#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "LibreriaModulos.h"
#include <windows.h>
#include <time.h>

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

//P R O T O T I P O S
void AgregarMascota(FILE *archi);
void ListarAnimales(FILE *archi);
void RegistrarTurno(FILE *archi, FILE *archi2, FILE *archi3);
void ListarTurno(FILE *archi, FILE *archi2, FILE *archi3);

main()
{
    FILE *archivo, *archivo2, *archivo3;
    int opcion, idx = 0, idxTurnos = 0, caso = 0, salirPrograma;

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

        switch (caso)
        {

        case 1:
            system("cls");
            AgregarMascota(archivo);
            break;

        case 2:
            system("cls");
            printf("\t\tListar Mascotas");
            printf("\n\t\t===============\n\n");
            ListarAnimales(archivo);
            break;

        case 3:
            system("cls");
            RegistrarTurno(archivo2, archivo3, archivo);
            break;

        case 4:
            system("cls");

            ListarTurno(archivo2, archivo3, archivo);
            break;
        case 5:
            printf("\n\tSeguro que desea salir?");
            printf("\n\n\t(1.Si  2.No)");
            printf("\n\t> ");

            scanf("%d", &salirPrograma);

            if (salirPrograma != 1)
            {
                caso = 1;
            }

            break;
        }

    } while (caso != 5);
}

void AgregarMascota(FILE *archi)
{
    int datos = 0; //contabiliza los datos validados para ir mostrandolos durante el ingreso
    float anios;   //edad de la mascota calculada automaticamente

    archi = fopen("Mascotas.dat", "r+b");
    mascota reg;

    system("cls");
    printf("\t\tRegistrar Mascota");

    printf("\n\t\t=================\n");

    printf("\n(Ingrese un 0 para salir)\n");

    printf("\nNombre mascota: ");
    _flushall();
    gets(reg.nombre);

    if (strcmp(reg.nombre, "0") == 0)
    {
        return;
    }

    system("cls");
    datos = 1;
    InfoMascotaActual(reg, datos);

    printf("\nDireccion: ");
    _flushall();
    gets(reg.direcc);

    system("cls");
    datos = 2;
    InfoMascotaActual(reg, datos);

    printf("\nDNI duenio: ");
    scanf("%d", &reg.DNI_DUENIO);

    system("cls");
    datos = 3;
    InfoMascotaActual(reg, datos);

    printf("\nLocalidad: ");
    _flushall();
    gets(reg.localidad);

    system("cls");
    datos = 4;
    InfoMascotaActual(reg, datos);

    printf("\nFecha nacimiento");

    printf("\n\tDia: ");
    scanf("%d", &reg.fec.dia);

    printf("\tMes: ");
    scanf("%d", &reg.fec.mes);

    printf("\tAnio: ");
    scanf("%d", &reg.fec.anio);

    /*struct de la libreria time.h para calcular la edad segun la fecha actual
    ========================================================================*/
    time_t t = time(NULL);

    struct tm tm = *localtime(&t);

    anios = (float)(((tm.tm_year + 1900) * 365) + ((tm.tm_mon + 1) * 30) + (tm.tm_mday) - ((reg.fec.anio) * 365) - ((reg.fec.mes) * 30) - (reg.fec.dia)) / 365;

    reg.edad = anios;

    system("cls");
    datos = 5;
    InfoMascotaActual(reg, datos);

    printf("\nPeso mascota: ");
    scanf("%f", &reg.peso);

    system("cls");
    datos = 6;
    InfoMascotaActual(reg, datos);

    printf("\nNro de telefono: ");
    _flushall();
    gets(reg.numeroTel);

    system("cls");
    datos = 7;
    InfoMascotaActual(reg, datos);

    fseek(archi, 0, SEEK_END);

    fwrite(&reg, sizeof(reg), 1, archi);

    fclose(archi);
    printf("\n\t----Mascota agregada con exito----");
    getch();
}

void ListarAnimales(FILE *archi)
{
    int contadorAnimales = 0;

    archi = fopen("Mascotas.dat", "r+b");

    mascota reg;

    rewind(archi);

    fread(&reg, sizeof(reg), 1, archi);

    while (!feof(archi))
    {
        if (!feof(archi))
        {
            printf("%25s: %s\n", "Nombre mascota", reg.nombre);
            printf("%25s: %s", "Direccion", reg.direcc);
            printf("\n%25s: %d", "Dni duenio", reg.DNI_DUENIO);
            printf("\n%25s: %s\n", "Localidad", reg.localidad);
            printf("%25s: %d/%d/%d\n", "Fecha nacimiento", reg.fec.dia, reg.fec.mes, reg.fec.anio);
            //Calculo de la edad en anios y meses
            //===========================================
            int auxiliar = reg.edad;
            float auxiliar2 = (reg.edad - auxiliar) * 12;
            //==========================================
            printf("%25s: %d anio/s y %d mes/es", "Edad", (int)reg.edad, (int)auxiliar2);
            printf("\n%25s: %.2f kg", "Peso", reg.peso);
            printf("\n%25s: %s", "Nro de Telefono", reg.numeroTel);
            printf("\n\n\t======================================\n\n");

            contadorAnimales++;
        }

        fread(&reg, sizeof(reg), 1, archi);
    }

    if (contadorAnimales == 0)
    {
        printf("\tNo hay mascotas registradas");
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
    mascota masc;
    turnos reg;
    veterinario regi;

    int dni = 0, situacion[2];
    bool matCorrecta, dniValido = false;

    system("cls");

    printf("\t\tRegistrar Turno");

    printf("\n\t\t=================\n");

    printf("\n(Ingrese un 0 para salir)\n");

    do
    {
        matCorrecta = true;
        printf("\nMatricula del Veterinario: ");
        scanf("%d", &reg.matriculaVet);

        if (reg.matriculaVet == 0)
        {
            return;
        }

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

    printf("\nFecha turno \n");
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

        fread(&masc, sizeof(mascota), 1, archi3);

        while (!feof(archi3))
        {
            if (masc.DNI_DUENIO == dni)
            {
                dniValido = true;
                break;
            }

            fread(&masc, sizeof(mascota), 1, archi3);
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

    strcpy(reg.atencion, "-Sin observacion-");

    fseek(archi, 0, SEEK_END);
    fwrite(&reg, sizeof(reg), 1, archi);

    fclose(archi);
    fclose(archi2);
    fclose(archi3);

    printf("\n\t----Turno agregado con exito----");
    getch();
}

void ListarTurno(FILE *archi, FILE *archi2, FILE *archi3)
{
    turnos reg;
    veterinario regi;
    mascota masc;

    int mat = 0; //matricula del veterinario
    int situ[2], i = 1, mes = 0, anio = 0;
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
            return;
        }

        VerificarMatricula(mat, situ);
        if (situ[0] == 0)
        {
            printf("\n\tError: la matricula no corresponde a un veterinario registrado");
            getch();
            matValida = false;
        }
    } while (!matValida);

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

    do
    {
        printf("\tListado de Turnos");
        printf("\n\t==================\n");
        printf("\n\tVeterinario:\n");
        printf("\t%20s: %s\n", "Nombre", regi.nomyApe);
        printf("\t%20s: %d\n", "DNI", regi.DNI);

        printf("\n\tMes y anio del turno");
        printf("\n\n\t\tMes: ");
        scanf("%d", &mes);
        printf("\t\tAnio: ");
        scanf("%d", &anio);

        if ((mes < 1 or mes > 12) or (anio > 2021 or anio < 2010))
        {
            printf("\n\tError: ingrese una fecha valida (mm/aaaa)");
            getch();
        }

        system("cls");
    } while (mes < 1 or mes > 12);

    printf("\tListado de Turnos");
    printf("\n\t==================\n");

    printf("\n\tVeterinario:\n");
    printf("\t%20s: %s\n", "Nombre", regi.nomyApe);
    printf("\t%20s: %d\n", "DNI", regi.DNI);

    printf("\n\tTurnos en el mes de ");

    switch (mes)
    {
    case 1:
        printf("enero");
        break;
    case 2:
        printf("febrero");
        break;
    case 3:
        printf("marzo");
        break;
    case 4:
        printf("abril");
        break;
    case 5:
        printf("mayo");
        break;
    case 6:
        printf("junio");
        break;
    case 7:
        printf("julio");
        break;
    case 8:
        printf("agosto");
        break;
    case 9:
        printf("septiembre");
        break;
    case 10:
        printf("octubre");
        break;
    case 11:
        printf("noviembre");
        break;
    case 12:
        printf("diciembre");
        break;
    }

    printf(" del anio %d\n", anio);

    fread(&reg, sizeof(turnos), 1, archi);

    if (matEncontrada)
    {
        while (!feof(archi))
        {
            if (!feof(archi) and reg.matriculaVet == mat and reg.fec.mes == mes and reg.fec.anio == anio)
            {
                printf("\nTurno %d\n", i);
                printf("=========================\n");

                fread(&masc, sizeof(mascota), 1, archi3);

                while (!feof(archi3))
                {
                    if (reg.DNIduenio == masc.DNI_DUENIO)
                    {
                        printf("Mascota: %s", masc.nombre);
                        break;
                    }

                    fread(&masc, sizeof(mascota), 1, archi3);
                }

                printf("\nFecha: %d/%d/%d", reg.fec.dia, reg.fec.mes, reg.fec.anio);
                printf("\nDNI: %d", reg.DNIduenio);
                printf("\nDetalles: ");
                puts(reg.atencion);
                printf("Estado: ");

                if (reg.borrado == true)
                {
                    printf("Atendido");
                }
                else
                {
                    printf("Pendiente");
                }
                printf("\n=========================\n\n");

                i++;
            }

            fread(&reg, sizeof(turnos), 1, archi);
        }

        if (i == 1)
        {
            printf("\n\tNo se encontraron turnos");
        }
    }
    else
    {
        printf("\n\tNo hay turnos registrados");
    }

    getch();

    fclose(archi);
    fclose(archi2);
    fclose(archi3);
}
