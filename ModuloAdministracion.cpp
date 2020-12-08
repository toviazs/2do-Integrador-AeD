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
typedef char nombreArchi[20];

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
	char ApeNom[60];
	int modulo;
};

// Prototipos
void RegistrarVeterinario(FILE *arch1, nombreArchi archiVets);
void RegistrarUsuario(FILE *arch1, int tipoUsuario, nombreArchi archiUsuarios);
void InfoVetActual(datosVete infoVet, int datos);

main()
{
	FILE *arch1, *arch2;
	nombreArchi ArchivoUsuarios = "Usuarios.dat", ArchivoVeterinarios = "Veterinarios.dat";

	//Genera los archivos en caso de que no existan
	AbrirGenerarArchivo(arch1, ArchivoVeterinarios);
	AbrirGenerarArchivo(arch2, ArchivoUsuarios);

	int caso = 0;

	do
	{
		system("cls");
		printf("Modulo Administracion\n");
		printf("======================\n\n");
		printf("1. Registrar Veterinario\n");
		printf("2. Registrar Usuario Asistente\n");
		printf("3. Atenciones por Veterinarios\n");
		printf("4. Ranking de Veterinarios por Atenciones\n\n");
		printf("5. Registrar Administrador\n\n");
		printf("6. Cerrar sesion\n\n");
		printf("> ");

		scanf("%d", &caso);

		switch (caso)
		{
		case 1:
			system("cls");
			RegistrarVeterinario(arch1, ArchivoVeterinarios);
			break;
		case 2:
			system("cls");
			RegistrarUsuario(arch2, 3, ArchivoUsuarios); //El argumento 3 indica que es un asistente
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			RegistrarUsuario(arch2, 1, ArchivoUsuarios); //El argumento 1 indica que es un administrador
			break;
		}

	} while (caso != 6);
}

void InfoVetActual(datosVete infoVet, int datos)
{
	printf("\tRegistrar Veterinario");

	printf("\n\t=====================\n");

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

void InfoUserActual(datosUsu infoUser, int datos, int modulo)
{
	printf("\tRegistrar ");
	if (modulo == 1)
	{
		printf("Administrador");
		printf("\n\t=======================\n");
	}
	else
	{
		printf("Asistente");
		printf("\n\t===================\n");
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

void RegistrarVeterinario(FILE *arch1, nombreArchi archiVets)
{
	datosVete reg;
	cadena auxApeNom;
	bool contrasenaValida, matriculaValida;
	int situacionContrasena[7], datos = 0; //datos almacena cuantos campos del registro ya han sido guardados
	int situacionMatricula[2];

	InfoVetActual(reg, datos);

	printf("\nApellido: ");
	_flushall();
	gets(reg.nomyApe);

	printf("Nombre: ");
	_flushall();
	gets(auxApeNom);

	strcat(reg.nomyApe, ", ");
	strcat(reg.nomyApe, auxApeNom);

	datos = 1;
	system("cls");
	InfoVetActual(reg, datos);

	/*
    Situaciones Posibles
    =================================================
    situacion[0]=1 -> La matricula ya esta en uso
    situacion[1]=1 -> La matricula no tiene 4 digitos
    =================================================
    */

	do
	{
		matriculaValida = false;

		printf("\nNro de matricula: ");
		scanf("%d", &reg.matricula);

		if (!VerificarMatricula(reg.matricula, situacionMatricula))
		{
			printf("Error:");

			if (situacionMatricula[0] == 1)
			{
				printf("\tLa matricula ya esta en uso\n");
			}
			if (situacionMatricula[1] == 1)
			{
				printf("\tDebe tener 4 digitos\n");
			}

			getch();
		}
		else
		{
			datos = 2;
			matriculaValida = true;
		}

		system("cls");
		InfoVetActual(reg, datos);
	} while (!matriculaValida);

	do
	{
		contrasenaValida = false;

		printf("\nContrasena: ");
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

			getch();
		}
		else
		{
			contrasenaValida = true;
			datos = 3;
		}

		system("cls");
		InfoVetActual(reg, datos);

	} while (!contrasenaValida);

	printf("\nDNI: ");
	scanf("%d", &reg.DNI);

	datos = 4;
	system("cls");
	InfoVetActual(reg, datos);

	printf("\nTelefono: ");
	_flushall();
	gets(reg.telefono);

	datos = 5;
	system("cls");
	InfoVetActual(reg, datos);

	reg.modulo = 2;

	arch1 = fopen(archiVets, "r+b");

	fseek(arch1, 0, SEEK_END);

	fwrite(&reg, sizeof(reg), 1, arch1);

	fclose(arch1);

	printf("\n\t----Veterinario agregado con exito----");
	getch();
}

void RegistrarUsuario(FILE *arch1, int tipoUsuario, nombreArchi archiUsuarios)
{
	datosUsu reg;
	int situacionUsuario[5], situacionContrasena[8];
	bool usuarioValido, contrasenaValida;
	cadena auxApeNom;
	char auxUsuario[20]; //auxiliar con elementos extra para registrar posibles usuarios que se excedan del limite
	char auxClave[20];	 //auxiliar con elementos extra para registrar posibles claves que se excedan del limte
	int datos = 0;		 //para saber cuantos datos validos van siendo ingresados al registro

	/*  Situaciones posibles
		=======================================================
        situacion[0]=1 -> Nombre de usuario ya utilizado
        situacion[1]=1 -> El primer digito no está en minúscula
        situacion[2]=1 -> Tiene menos de 2 mayúsculas
        situacion[3]=1 -> Tiene más de 3 digitos
		situacion[4]=1 -> Tiene más de 9 caracteres
		=======================================================
    */

	system("cls");
	InfoUserActual(reg, datos, tipoUsuario);

	do
	{
		usuarioValido = false;

		printf("\nUsuario: ");
		_flushall();
		gets(auxUsuario);

		//Verifica si el usuario es valido y muestra el error especifico

		if (!VerificarUsuarioNuevo(auxUsuario, situacionUsuario))
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
			if (situacionUsuario[4] == 1)
			{
				printf("\tEs demasiado largo (9 caracteres maximo)\n");
			}

			getch();
		}
		else
		{
			usuarioValido = true;
			_flushall();
			strcpy(reg.usuario, auxUsuario);
			datos = 1;
		}

		system("cls");
		InfoUserActual(reg, datos, tipoUsuario);

	} while (!usuarioValido);

	do
	{
		contrasenaValida = false;

		printf("\nContrasena: ");
		_flushall();
		gets(auxClave);

		/*  Situaciones posibles
		=================================================================
        situacion[0]=1 -> No tiene ninguna Mayuscula
        situacion[1]=1 -> No tiene ninguna Minuscula
        situacion[2]=1 -> No tiene ningun Digito
        situacion[3]=1 -> Tiene letras con tilde
        situacion[4]=1 -> Tiene menos de 6 caracteres
        situacion[5]=1 -> Tiene mas de 3 numeros consecutivos
        situacion[6]=1 -> Tiene 2 caracteres consecutivos alfabeticamente
		situacion[7]=1 -> Tiene más de 9 caracteres
		=================================================================
    	*/

		if (!VerificarContrasenaNueva(auxClave, situacionContrasena))
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
			if (situacionContrasena[7] == 1)
			{
				printf("\tEs demasiado larga (9 caracteres maximo)\n");
			}

			getch();
		}
		else
		{
			contrasenaValida = true;
			_flushall();
			strcpy(reg.contrasenia, auxClave);
			datos = 2;
		}

		system("cls");
		InfoUserActual(reg, datos, tipoUsuario);
	} while (!contrasenaValida);

	printf("\nApellido: ");
	_flushall();
	gets(reg.ApeNom);

	printf("Nombre: ");
	_flushall();
	gets(auxApeNom);

	strcat(reg.ApeNom, ", ");
	strcat(reg.ApeNom, auxApeNom);

	datos = 3;
	system("cls");
	InfoUserActual(reg, datos, tipoUsuario);

	if (tipoUsuario == 1)
	{
		reg.modulo = 1;
	}
	else if (tipoUsuario == 3)
	{
		reg.modulo = 3;
	}

	arch1 = fopen(archiUsuarios, "r+b");

	fseek(arch1, 0, SEEK_END);

	fwrite(&reg, sizeof(datosUsu), 1, arch1);

	fclose(arch1);

	printf("\n\t----Usuario agregado con exito----");
	getch();
}
