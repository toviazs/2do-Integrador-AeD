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

bool VerificarMatricula(int matricula)
{
    FILE *archi = fopen("Veterinarios.dat", "rb");

    veterinario vet;

    fread(&vet, sizeof(vet), 1, archi);

    while (!feof(archi))
    {
        if (matricula == vet.matricula)
        {
            return false;
        }
        fread(&vet, sizeof(vet), 1, archi);
    }

    return true;
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