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

struct fec
{
	int dia;
	int mes;
	int anio;
};

struct turns
{
	fec fecha;
	int dniDuenio;
	char atencion[380];
	int matriculaVet;
	bool borrado;
};

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

// Prototipos
void RegistrarVeterinario(FILE *arch1, nombreArchi archiVets);
void RegistrarUsuario(FILE *arch1, int tipoUsuario, nombreArchi archiUsuarios);
void InfoVetActual(datosVete infoVet, int datos);
void BuscarTurnosAtendidos(FILE *arch1, FILE *arch2, nombreArchi archiVeterinario, nombreArchi archiTurno);
void InsertarNodo(nodo *&puntero, rank valor);
void RankingVeterinarios(FILE *arch1, FILE *arch2, nombreArchi archiVeterinarios, nombreArchi archiTurnos);
void RecorrerLista(nodo *puntero);

main()
{
	FILE *arch1, *arch2, *arch3;
	nombreArchi ArchivoUsuarios = "Usuarios.dat", ArchivoVeterinarios = "Veterinarios.dat", ArchivoTurnos = "Turnos.dat";

	//Genera los archivos en caso de que no existan
	AbrirGenerarArchivo(arch1, ArchivoVeterinarios);
	AbrirGenerarArchivo(arch2, ArchivoUsuarios);
	AbrirGenerarArchivo(arch3, ArchivoTurnos);

	int caso = 0;
	int registrarVet;
	int registrarAsistente;
	int registrarAdmin;

	do
	{
		system("cls");
		printf("Modulo Administracion\n");
		printf("======================\n\n");
		printf("1. Registrar Veterinario\n");
		printf("2. Registrar Usuario Asistente\n");
		printf("3. Registrar Administrador\n");
		printf("==========================\n");
		printf("4. Ranking de Veterinarios por Atenciones\n");
		printf("5. Atenciones por Veterinarios\n");
		printf("==========================\n");
		printf("6. Cerrar sesion\n\n");
		printf("> ");

		scanf("%d", &caso);

		switch (caso)
		{
		case 1:
			system("cls");

			printf("\n\t|| Esta seguro que desea registrar un Veterinario? ||\n");
			printf("\n\tEste usuario podra ver la lista de mascotas y darlas de alta...");
			getch();
			printf("\n\n\t(1.Si  2.No)\n\t> ");

			scanf("%d", &registrarVet);

			if (registrarVet == 1)
			{
				system("cls");
				RegistrarVeterinario(arch1, ArchivoVeterinarios);
			}

			break;
		case 2:
			system("cls");

			printf("\n\t|| Esta seguro que desea registrar un Asistente? ||\n");
			printf("\n\tEste usuario podra registrar y listar mascotas y turnos...");
			getch();
			printf("\n\n\t(1.Si  2.No)\n\t> ");

			scanf("%d", &registrarAsistente);

			if (registrarAsistente == 1)
			{
				system("cls");
				RegistrarUsuario(arch2, 3, ArchivoUsuarios); //El argumento 3 indica que es un asistente
			}

			break;
		case 3:
			system("cls");

			printf("\n\t|| Esta seguro que desea registrar un Administrador? ||\n");
			printf("\n\tEste usuario podra registrar mas usuarios en el sistema");
			getch();
			printf("\n\n\tAdemas de que puede revisar los turnos atendidos y el ranking de veterinarios");
			getch();
			printf("\n\n\tHagalo solo en caso de estar muy seguro...");
			getch();
			printf("\n\n\t(1.Si  2.No)\n\t> ");

			scanf("%d", &registrarAdmin);

			if (registrarAdmin == 1)
			{
				system("cls");
				RegistrarUsuario(arch2, 1, ArchivoUsuarios); //El argumento 1 indica que es un administrador
			}

			break;
		case 4:
			RankingVeterinarios(arch1, arch3, ArchivoVeterinarios, ArchivoTurnos);
			break;
		case 5:
			BuscarTurnosAtendidos(arch1, arch3, ArchivoVeterinarios, ArchivoTurnos);
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

void BuscarTurnosAtendidos(FILE *arch1, FILE *arch2, nombreArchi archiVeterinario, nombreArchi archiTurnos)
{
	bool matriculaExistente;
	int matricula;
	int situacionMatricula[2];

	/*
    Situaciones Posibles
    =================================================
    situacion[0]=1 -> La matricula existe
    situacion[1]=1 -> La matricula no tiene 4 digitos
    =================================================
    */

	do
	{
		matriculaExistente = false;

		system("cls");
		printf("\tAtenciones por Veterinario\n");
		printf("\t==========================\n");

		printf("\n\t(Ingrese 0 para salir)\n");
		printf("\nMatricula: ");
		scanf("%d", &matricula);

		if (matricula == 0) //con 0 se sale de la funcion
		{
			break;
		}

		VerificarMatricula(matricula, situacionMatricula);

		if (situacionMatricula[0] == 0)
		{
			printf("\nError: ");

			printf("\tMatricula no existente\n");

			getch();
		}
		else
		{
			matriculaExistente = true;
		}

	} while (!matriculaExistente);

	if (matricula != 0)
	{
		arch1 = fopen(archiVeterinario, "r+b");

		datosVete infoVet;

		fread(&infoVet, sizeof(infoVet), 1, arch1);

		while (!feof(arch1))
		{
			if (matricula == infoVet.matricula)
			{
				break;
			}

			fread(&infoVet, sizeof(infoVet), 1, arch1);
		}

		printf("Veterinario:\n");
		printf("\t%20s: %s\n", "Nombre", infoVet.nomyApe);
		printf("\t%20s: %d\n", "DNI", infoVet.DNI);

		fclose(arch1);

		printf("\n\nTurnos atendidos:\n\n");

		arch2 = fopen(archiTurnos, "r+b");

		turns infoTurno;
		int contadorTurnosAtendidos = 0;

		fread(&infoTurno, sizeof(turns), 1, arch2);

		while (!feof(arch2))
		{
			if (infoTurno.matriculaVet == matricula and infoTurno.borrado == true)
			{
				contadorTurnosAtendidos++;
				printf("\n%d_", contadorTurnosAtendidos);
				printf("\t%20s: %d/%d/%d\n", "Fecha", infoTurno.fecha.dia, infoTurno.fecha.mes, infoTurno.fecha.anio);
				printf("\t%20s: %d\n", "Dni duenio", infoTurno.dniDuenio);
				printf("\t%20s: %s\n", "Observaciones", infoTurno.atencion);
			}

			fread(&infoTurno, sizeof(turns), 1, arch2);
		}

		if (contadorTurnosAtendidos == 0)
		{
			printf("\nEste veterinario no tiene turnos atendidos");
		}

		fclose(arch2);

		getch();
	}
}

void RankingVeterinarios(FILE *arch1, FILE *arch2, nombreArchi archiVeterinarios, nombreArchi archiTurnos)
{
	datosVete infoVet;
	turns infoTurno;
	int atendidos; //contador de turnos atendidos por x veterinario
	rank rankingVet;

	arch1 = fopen(archiVeterinarios, "r+b");

	arch2 = fopen(archiTurnos, "r+b");

	nodo *lista;

	lista = NULL;

	fread(&infoVet, sizeof(datosVete), 1, arch1);

	while (!feof(arch1))
	{
		fread(&infoTurno, sizeof(turns), 1, arch2);
		atendidos = 0;

		while (!feof(arch2))
		{
			if (infoVet.matricula == infoTurno.matriculaVet and infoTurno.borrado == true)
			{
				atendidos++;
			}

			fread(&infoTurno, sizeof(turns), 1, arch2);
		}

		rankingVet.matricula = infoVet.matricula;
		strcpy(rankingVet.ApeNomVet, infoVet.nomyApe);
		rankingVet.turnosAtendidos = atendidos;

		InsertarNodo(lista, rankingVet);

		fread(&infoVet, sizeof(datosVete), 1, arch1);
	}

	fclose(arch1);
	fclose(arch2);

	system("cls");

	printf("\tRanking de Veterinarios\n");
	printf("\t=======================\n");

	if (lista == NULL)
	{
		printf("\nNo hay veterinarios registrados...");
	}

	RecorrerLista(lista);

	getch();
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
