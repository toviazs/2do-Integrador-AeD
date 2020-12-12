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
void ListarTurno(FILE *archi, FILE *archi2);

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
            printf("\tListar Mascotas");
            printf("\n\t===============\n\n");
            ListarAnimales(archivo);
            break;

        case 3:
            system("cls");
            RegistrarTurno(archivo2, archivo3, archivo);
            break;

        case 4:
            system("cls");
            ListarTurno(archivo2, archivo3);
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
            else
            {
                system("MenuPrincipal.exe");
            }

            break;
        }

    } while (caso != 5);
}

void AgregarMascota(FILE *archi)
{
    int datos = 0; //contabiliza los datos validados para ir mostrandolos durante el ingreso

    archi = fopen("Mascotas.dat", "r+b");
    mascota vec;

    system("cls");
    printf("\tRegistrar Mascota");

    printf("\n\t=================\n");

    printf("\n(Ingrese un 0 para salir)\n");

    printf("\nNombre mascota: ");
    _flushall();
    gets(vec.nombre);

    if (strcmp(vec.nombre, "0") == 0)
    {
        return;
    }

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
    scanf("%d", &vec.fec.dia);

    printf("\tMes: ");
    scanf("%d", &vec.fec.mes);

    printf("\tAnio: ");
    scanf("%d", &vec.fec.anio);

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
    int contadorAnimales = 0;

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
            printf("FECHA: %d/%d/%d\n", vec.fec.dia, vec.fec.mes, vec.fec.anio);
            printf("\nPeso de la Mascota: %.2f", vec.peso);
            printf("\nNumero de telefono: %s", vec.numeroTel);
            printf("\n============================\n");

            contadorAnimales++;
        }

        fread(&vec, sizeof(vec), 1, archi);
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
    mascota vec;
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

    strcpy(reg.atencion, "-Sin observacion-");

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
    veterinario regi;

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
            return;
        }

        if (VerificarMatricula(mat, situ))
        {
            printf("\n\tError: la matricula no corresponde a un veterinario registrado");
            getch();
            matValida = false;
        }
    } while (!matValida);

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

    getch();

    fclose(archi);
    fclose(archi2);
}
