/*Libreria correspondiente a todas las funcionas utilizadas por los diferentes modulos de este trabajo Integrador*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

struct user
{
    char usuario[10];
    char contrasenia[10];
    char ApeNom[60];
    int modulo;
};

struct veterinario
{
    char nomyApe[60];
    int matricula; //4 digitos como maximo
    int DNI;
    char telefono[25];
    int modulo; //1 Administrador   2 Veterinario   3 Asistente
    char contrasenia[10];
};

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

struct mascota
{
    char nombre[60];
    char direcc[60];
    int DNI_DUENIO;
    char localidad[60];
    fecha fec;
    float peso;
    char numeroTel[25];
    float edad;
};

struct rank
{
    char ApeNomVet[60];
    int turnosAtendidos;
    int matricula;
};

struct nodo
{
    rank info;
    nodo *sig;
};

bool VerificarUsuarioNuevo(char Usuario[30], int situacion[5])
{
    /*  Situaciones posibles

        situacion[0]=1 -> Nombre de usuario ya utilizado
        situacion[1]=1 -> El primer digito no está en minúscula
        situacion[2]=1 -> Tiene menos de 2 mayúsculas
        situacion[3]=1 -> Tiene más de 3 digitos
        situacion[4]=1 -> Tiene más de 9 caracteres

    */

    for (int i = 0; i < 5; i++) //me aseguro que todo el vector tiene 0s
    {
        situacion[i] = 0;
    }

    FILE *archi = fopen("Usuarios.dat", "rb");
    user usuarioRegistrado;
    int contadorMayusculas = 0, contadorDigitos = 0;

    fread(&usuarioRegistrado, sizeof(user), 1, archi);

    while (!feof(archi))
    {
        if (strcmp(usuarioRegistrado.usuario, Usuario) == 0)
        {
            situacion[0] = 1;
        }

        fread(&usuarioRegistrado.usuario, sizeof(user), 1, archi);
    }

    if (isalpha(Usuario[0]))
    {
        if (!islower(Usuario[0]))
        {
            situacion[1] = 1;
        }
    }

    for (int i = 0; i < strlen(Usuario); i++)
    {
        if (isupper(Usuario[i]))
        {
            contadorMayusculas++;
        }
        else if (isdigit(Usuario[i]))
        {
            contadorDigitos++;
        }
    }

    if (contadorMayusculas < 2)
    {
        situacion[2] = 1;
    }

    if (contadorDigitos > 3)
    {
        situacion[3] = 1;
    }

    if (strlen(Usuario) > 9)
    {
        situacion[4] = 1;
    }

    if (situacion[0] == 1 or situacion[1] == 1 or situacion[2] == 1 or situacion[3] == 1 or situacion[4] == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool VerificarContrasenaNueva(char Clave[30], int situacion[8])
{
    /*  Situaciones posibles

        situacion[0]=1 -> No tiene ninguna Mayuscula
        situacion[1]=1 -> No tiene ninguna Minuscula
        situacion[2]=1 -> No tiene ningun Digito
        situacion[3]=1 -> Tiene letras con tilde
        situacion[4]=1 -> Tiene menos de 6 caracteres
        situacion[5]=1 -> Tiene mas de 3 numeros consecutivos
        situacion[6]=1 -> Tiene 2 caracteres consecutivos alfabeticamente
        situacion[7]=1 -> Tiene más de 9 caracteres

    */

    for (int i = 0; i < 8; i++)
    {
        situacion[i] = 0;
    }

    int contadorMayusculas = 0, contadorMinusculas = 0, contadorDigitos = 0, contadorTildes = 0;

    for (int i = 0; i < strlen(Clave); i++)
    {
        if (isupper(Clave[i]))
        {
            contadorMayusculas++;
        }
        else if (islower(Clave[i]))
        {
            contadorMinusculas++;
        }
        else if (isdigit(Clave[i]))
        {
            contadorDigitos++;
        }
        else if (!isprint(Clave[i]))
        {
            contadorTildes++;
        }
    }

    if (contadorMayusculas < 1)
    {
        situacion[0] = 1;
    }

    if (contadorMinusculas < 1)
    {
        situacion[1] = 1;
    }

    if (contadorDigitos < 1)
    {
        situacion[2] = 1;
    }

    if (contadorTildes > 0)
    {
        situacion[3] = 1;
    }

    if (strlen(Clave) < 6)
    {
        situacion[4] = 1;
    }
    else
    {
        for (int i = 0; i < strlen(Clave) - 3; i++)
        {
            if (Clave[i] == (Clave[i + 1] - 1) and Clave[i + 1] == (Clave[i + 2] - 1) and Clave[i + 2] == (Clave[i + 3] - 1) and Clave[i + 3] == (Clave[i + 4] - 1))
            {
                situacion[5] = 1;
            }
        }
    }

    char ch1, ch2; //declaro los chars para no modificar la clave en si, y poder pasarlos a minuscula

    if (strlen(Clave) >= 2)
    {
        for (int i = 0; i < strlen(Clave) - 1; i++)
        {
            if (isalpha(Clave[i]) and isalpha(Clave[i + 1]))
            {
                ch1 = Clave[i];
                ch2 = Clave[i + 1];

                strlwr(&ch1);
                strlwr(&ch2);

                if (ch1 == (ch2 - 1))
                {
                    situacion[6] = 1;
                }
            }
        }
    }

    if (strlen(Clave) > 9)
    {
        situacion[7] = 1;
    }

    bool error = false;

    for (int i = 0; i < 8; i++) //recorro el vector de situacion para ver si hay algun error
    {
        if (situacion[i] == 1)
        {
            error = true;
        }
    }

    return (error) ? false : true;
}

bool LoginAdminAsistente(char Usuario[10], char Clave[10], int modulo)
{
    FILE *archi = fopen("Usuarios.dat", "rb");

    user datosUsuario;

    fread(&datosUsuario, sizeof(user), 1, archi);

    while (!feof(archi))
    {
        if ((strcmp(Usuario, datosUsuario.usuario) == 0) and (strcmp(Clave, datosUsuario.contrasenia) == 0) and (datosUsuario.modulo == modulo))
        {
            return true;
        }

        fread(&datosUsuario, sizeof(user), 1, archi);
    }

    return false;
}

bool LoginVeterinario(int matricula, char Clave[10])
{
    FILE *archi = fopen("Veterinarios.dat", "rb");

    veterinario vet;

    fread(&vet, sizeof(vet), 1, archi);

    while (!feof(archi))
    {
        if (matricula == vet.matricula and strcmp(Clave, vet.contrasenia) == 0)
        {
            return true;
        }
        fread(&vet, sizeof(vet), 1, archi);
    }

    return false;
}

bool VerificarMatricula(int matricula, int situacion[2])
{
    /*
    Situaciones Posibles
    =================================================
    situacion[0]=1 -> La matricula ya esta en uso
    situacion[1]=1 -> La matricula no tiene 4 digitos
    =================================================
    */

    for (int i = 0; i < 2; i++) //vaciar el vector por las dudas
    {
        situacion[i] = 0;
    }

    FILE *archi = fopen("Veterinarios.dat", "rb");

    veterinario vet;

    fread(&vet, sizeof(vet), 1, archi);

    while (!feof(archi))
    {
        if (matricula == vet.matricula)
        {
            situacion[0] = 1;
        }
        fread(&vet, sizeof(vet), 1, archi);
    }

    if (matricula > 9999 or matricula < 1000)
    {
        situacion[1] = 1;
    }

    if (situacion[0] == 1 or situacion[1] == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void AbrirGenerarArchivo(FILE *archi, char NombreArchivo[20])
{
    archi = fopen(NombreArchivo, "r+b");

    if (archi == NULL)
    {
        archi = fopen(NombreArchivo, "w+b");

        if (archi == NULL)
        {
            printf("Error: el archivo %s no existe y no se pudo crear", NombreArchivo);
            getch();
            exit(1);
        }
    }
}

void InsertarNodo(nodo *&puntero, rank valor)
{
    nodo *nuevo = new nodo();
    nuevo->info = valor;

    nodo *aux1 = puntero;
    nodo *aux2;

    while ((aux1 != NULL) and (aux1->info.turnosAtendidos > valor.turnosAtendidos))
    {
        aux2 = aux1;
        aux1 = aux1->sig;
    }

    if (puntero == aux1)
    {
        puntero = nuevo;
    }
    else
    {
        aux2->sig = nuevo;
    }

    nuevo->sig = aux1;
}

void RecorrerLista(nodo *puntero)
{
    nodo *p = puntero;

    int posicion = 1;

    while (p != NULL)
    {
        printf("\n#%d _ \tVeterinario: %s", posicion, p->info.ApeNomVet);
        printf("\n\tMatricula: %d", p->info.matricula);
        printf("\n\tTurnos atendidos: %d\n", p->info.turnosAtendidos);
        p = p->sig;
        posicion++;
    }
}

void InfoMascotaActual(mascota InfoMasc, int datos)
{
    printf("\t\tRegistrar Mascota");

    printf("\n\t\t=================\n");

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
                        int auxiliar = InfoMasc.edad;
                        float auxiliar2 = (InfoMasc.edad - auxiliar) * 12;

                        printf("%25s - %d/%d/%d\n", "Fecha", InfoMasc.fec.dia, InfoMasc.fec.mes, InfoMasc.fec.anio);
                        printf("%25s - %d anio/s y %d mes/es\n", "Edad", (int)InfoMasc.edad, (int)auxiliar2);

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

void InfoEvolucionActual(turnos InfoTurno, mascota InfoMascota, int datos)
{
    printf("\t\tRegistrar Evolucion de Mascota");

    printf("\n\t\t==============================\n");

    if (datos >= 1)
    {
        printf("\n%25s - %s\n", "Nombre mascota", InfoMascota.nombre);

        if (datos >= 2)
        {
            printf("%25s - %s\n", "Detalles", InfoTurno.atencion);
        }
    }
}

void InfoVetActual(veterinario infoVet, int datos)
{
    printf("\t\tRegistrar Veterinario");

    printf("\n\t\t=====================\n");

    if (datos >= 1)
    {
        printf("\n%25s - %s\n", "Nombre", infoVet.nomyApe);

        if (datos >= 2)
        {
            printf("%25s - %d\n", "Matricula", infoVet.matricula);

            if (datos >= 3)
            {
                printf("%25s - %s\n", "Clave", infoVet.contrasenia);

                if (datos >= 4)
                {
                    printf("%25s - %d\n", "DNI", infoVet.DNI);

                    if (datos >= 5)
                    {
                        printf("%25s - %s\n", "Telefono", infoVet.telefono);
                    }
                }
            }
        }
    }
}

void InfoUserActual(user infoUser, int datos, int modulo)
{
    printf("\t\tRegistrar ");
    if (modulo == 1)
    {
        printf("Administrador");
        printf("\n\t\t=======================\n");
    }
    else
    {
        printf("Asistente");
        printf("\n\t\t===================\n");
    }

    if (datos >= 1)
    {
        printf("\n%25s - %s\n", "Usuario", infoUser.usuario);

        if (datos >= 2)
        {
            printf("%25s - %s\n", "Clave", infoUser.contrasenia);

            if (datos >= 3)
            {
                printf("%25s - %s\n", "Nombre", infoUser.ApeNom);
            }
        }
    }
}