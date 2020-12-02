/*Libreria correspondiente a todas las funcionas utilizadas por los diferentes modulos de este trabajo Integrador*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
struct user
{
    char usuario[10];
    char contrasena[10];
    char ApeNom[60];
};

bool VerificarUsuario(char Usuario[10], int situacion[4])
{
    /*  Situaciones posibles

        situacion[0]=1 -> Nombre de usuario ya utilizado
        situacion[1]=1 -> El primer digito no está en minúscula
        situacion[2]=1 -> Tiene menos de 2 mayúsculas
        situacion[3]=1 -> Tiene más de 3 digitos

    */

    for (int i = 0; i < strlen(Usuario); i++) //me aseguro que todo el vector tiene 0s
    {
        Usuario[i] = 0
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

    if (!islower(Usuario[0]))
    {
        situacion[1] = 1;
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

    if (situacion[0] == 1 or situacion[1] == 1 or situacion[2] == 1 or situacion[3] == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool VerificarContrasenas(char Clave[10], int situacion[??])
{
    /*  Situaciones posibles

        situacion[0]=1 -> No tiene ninguna Mayuscula
        situacion[1]=1 -> No tiene ninguna Minuscula
        situacion[2]=1 -> No tiene ningun Digito
        situacion[3]=1 -> Tiene letras con tilde
        situacion[4]=1 -> Tiene menos de 6 caracteres
        situacion[5]=1 -> Tiene mas de 3 numeros consecutivos
        situacion[6]=1 -> Tiene 2 caracteres consecutivos alfabeticamente

    */

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
        else if (Clave[i] == 'á' or Clave[i] == 'é' or Clave[i] == 'í' or Clave[i] == 'ó' or Clave[i] == 'ú' or Clave[i] == 'Á' or Clave[i] == 'É' or Clave[i] == 'Í' or Clave[i] == 'Ó' or Clave[i] == 'Ú')
        {
            contadorTildes++;
        }
    }

    if (contadorMayusculas < 1)
    {
        situacion[0] = 1;
    }
    else if (contadorMinusculas < 1)
    {
        situacion[1] = 1;
    }
    else if (contadorDigitos < 1)
    {
        situacion[2] = 1;
    }
    else if (contadorTildes > 0)
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
            if (Clave[i] == (Clave[i + 1] + 1) and Clave[i + 1] == (Clave[i + 2] + 1) and Clave[i + 2] == (Clave[i + 3] + 1) and Clave[i + 3] == (Clave[i + 4] + 1))
            {
                situacion[5] = 1;
            }
        }
    }

    if (strlen(Clave) >= 2)
    {
        for (int i = 0; i < strlen(Clave) - 1; i++)
        {
            if (strcmp(&Clave[i], &Clave[i + 1]) > 0)
            {
                situacion[6] = 1;
            }
        }
    }
}
