#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "LibreriaModulos.h"
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

typedef char cadena[20];

struct datosVete
{
	char nomyApe[60];
	int matricula; //4 digitos como maximo
	int DNI;
	char telefono[25];
	int modulo; //1 Administrador  2 Veterinario  3 Asistente
	char contrasenia[10];
};

struct datosUsu
{
	char usuario[10];
	char contrasenia[10];
	char nomyApe[60];
	int modulo;
};

// Prototipos
void AbrirGenerarArchivo(FILE *archi, cadena NombreArchivo);
void registrarVeterinario(FILE *arch1);
void registrarUsuarioAsistente(FILE *arch1);

main()
{
	FILE *arch1, *arch2;
	cadena ArchivoUsuarios = "Usuarios.dat", ArchivoVeterinarios = "Veterinarios.dat";

	//Genera los archivos en caso de que no existan
	AbrirGenerarArchivo(arch1, ArchivoVeterinarios);
	AbrirGenerarArchivo(arch2, ArchivoUsuarios);

	int caso = 0;

	do
	{
		system("cls");
		printf("Modulo del Asistente\n");
		printf("======================\n\n");
		printf("1. Registrar Veterinario\n");
		printf("2. Registrar Usuario Asistente\n");
		printf("3. Atenciones por Veterinarios\n");
		printf("4. Ranking de Veterinarios por Atenciones\n\n");
		printf("5. Cerrar la aplicacion\n\n");
		printf("> ");

		scanf("%d", &caso);

		switch (caso)
		{
		case 1:
			system("cls");
			registrarVeterinario(arch1);
			break;
		case 2:
			system("cls");
			registrarUsuarioAsistente(arch1);
			break;
		case 3:
			break;
		case 4:
			break;
		}

	} while (caso != 5);
}

void AbrirGenerarArchivo(FILE *archi, cadena NombreArchivo)
{
	archi = fopen(NombreArchivo, "r+b");

	if (archi == NULL)
	{
		archi = fopen(NombreArchivo, "w+b");
	}
}

void registrarVeterinario(FILE *arch1)
{
	datosVete reg;
	cadena auxApeNom;
	bool contrasenaValida;
	int situacionContrasena[7];

	printf("\tR E G I S T R A R  V E T E R I N A R I O");

	printf("\n========================================\n");

	printf("\nIngrese Apellido: ");
	_flushall();
	gets(reg.nomyApe);

	printf("\nIngrese Nombre: ");
	_flushall();
	gets(auxApeNom);

	strcat(reg.nomyApe, ", ");
	strcat(reg.nomyApe, auxApeNom);

	do
	{
		printf("\nIngrese numero de matricula: ");
		scanf("%d", &reg.matricula);

		if (reg.matricula > 9999 or reg.matricula < 1000)
		{
			printf("Error: la matricula debe tener 4 digitos");
			getch();
		}
	} while (reg.matricula > 9999 or reg.matricula < 1000);

	do
	{
		contrasenaValida = false;

		printf("Ingrese Contrasena: ");
		_flushall();
		gets(reg.contrasenia);

		/*  Situaciones posibles

        situacion[0]=1 -> No tiene ninguna Mayuscula
        situacion[1]=1 -> No tiene ninguna Minuscula
        situacion[2]=1 -> No tiene ningun Digito
        situacion[3]=1 -> Tiene letras con tilde
        situacion[4]=1 -> Tiene menos de 6 caracteres
        situacion[5]=1 -> Tiene mas de 3 numeros consecutivos
        situacion[6]=1 -> Tiene 2 caracteres consecutivos alfabeticamente
    	*/

		if (!VerificarContrasenaNueva(reg.contrasenia, situacionContrasena))
		{
			printf("Error: ");
			if (situacionContrasena[0] == 1)
			{
				printf("\tDebe de tener al menos una mayuscula\n");
			}
			if (situacionContrasena[1] == 1)
			{
				printf("\tDebe de tener al menos una minuscula\n");
			}
			if (situacionContrasena[2] == 1)
			{
				printf("\tDebe de tener al menos un digito\n");
			}
			if (situacionContrasena[3] == 1)
			{
				printf("\tContiene caracteres con tilde\n");
			}
			if (situacionContrasena[4] == 1)
			{
				printf("\tDebe de tener 6 caracteres como minimo\n");
			}
			if (situacionContrasena[5] == 1)
			{
				printf("\tNo puede tener mas de 3 numeros consecutivos\n");
			}
			if (situacionContrasena[6] == 1)
			{
				printf("\tNo puede tener 2 caracteres consecutivos alfabeticamente\n");
			}
		}
		else
		{
			contrasenaValida = true;
		}

	} while (!contrasenaValida);

	printf("\nIngrese DNI: ");
	scanf("%d", &reg.DNI);

	printf("\nIngrese telefono: ");
	_flushall();
	gets(reg.telefono);

	reg.modulo = 2;

	fwrite(&reg, sizeof(reg), 1, arch1);

	printf("\n----Veterinario agregado con exito----");

	printf("\n\n");
	system("pause");
}

void registrarUsuarioAsistente(FILE *arch1)
{
	datosUsu reg;
	int situacionUsuario[4], situacionContrasena[7];
	bool usuarioValido, contrasenaValida;
	cadena auxApeNom;

	/*  Situaciones posibles

        situacion[0]=1 -> Nombre de usuario ya utilizado
        situacion[1]=1 -> El primer digito no está en minúscula
        situacion[2]=1 -> Tiene menos de 2 mayúsculas
        situacion[3]=1 -> Tiene más de 3 digitos

    */

	printf("\tR E G I S T R A R  A S I S T E N T E");

	printf("\n========================================\n");

	do
	{
		usuarioValido = false;

		printf("\nIngrese Usuario: ");
		_flushall();
		gets(reg.usuario);

		//Verifica si el usuario es valido y muestra el error especifico

		if (!VerificarUsuarioNuevo(reg.usuario, situacionUsuario))
		{
			printf("Error:");
			if (situacionUsuario[0] == 1)
			{
				printf("\tEl nombre de usuario ya esta en uso\n");
			}
			if (situacionUsuario[1] == 1)
			{
				printf("\tEl primer caracter debe de estar en minuscula\n");
			}
			if (situacionUsuario[2] == 1)
			{
				printf("\tDebe de tener al menos 2 mayusculas\n");
			}
			if (situacionUsuario[3] == 1)
			{
				printf("\tNo puede tener mas de 3 numeros\n");
			}
		}
		else
		{
			usuarioValido = true;
		}

	} while (!usuarioValido);

	do
	{
		contrasenaValida = false;

		printf("Ingrese Contrasena: ");
		_flushall();
		gets(reg.contrasenia);

		/*  Situaciones posibles

        situacion[0]=1 -> No tiene ninguna Mayuscula
        situacion[1]=1 -> No tiene ninguna Minuscula
        situacion[2]=1 -> No tiene ningun Digito
        situacion[3]=1 -> Tiene letras con tilde
        situacion[4]=1 -> Tiene menos de 6 caracteres
        situacion[5]=1 -> Tiene mas de 3 numeros consecutivos
        situacion[6]=1 -> Tiene 2 caracteres consecutivos alfabeticamente
    	*/

		if (!VerificarContrasenaNueva(reg.contrasenia, situacionContrasena))
		{
			printf("Error: ");
			if (situacionContrasena[0] == 1)
			{
				printf("\tDebe de tener al menos una mayuscula\n");
			}
			if (situacionContrasena[1] == 1)
			{
				printf("\tDebe de tener al menos una minuscula\n");
			}
			if (situacionContrasena[2] == 1)
			{
				printf("\tDebe de tener al menos un digito\n");
			}
			if (situacionContrasena[3] == 1)
			{
				printf("\tContiene caracteres con tilde\n");
			}
			if (situacionContrasena[4] == 1)
			{
				printf("\tDebe de tener 6 caracteres como minimo\n");
			}
			if (situacionContrasena[5] == 1)
			{
				printf("\tNo puede tener mas de 3 numeros consecutivos\n");
			}
			if (situacionContrasena[6] == 1)
			{
				printf("\tNo puede tener 2 caracteres consecutivos alfabeticamente\n");
			}
		}
		else
		{
			contrasenaValida = true;
		}

	} while (!contrasenaValida);

	printf("\nApellido: ");
	_flushall();
	gets(reg.nomyApe);

	printf("\nNombre");
	_flushall();
	gets(auxApeNom);

	strcat(reg.nomyApe, ", ");
	strcat(reg.nomyApe, auxApeNom);

	reg.modulo = 3; //le asigna el modulo de asistente

	fwrite(&reg, sizeof(reg), 1, arch1);

	printf("\n----Usuario agregado con exito----");
	getch();
}
