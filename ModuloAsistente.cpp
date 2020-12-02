#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

/*
Universidad Tecnologica Nacional
Facultad Regional Tucuman
Ingenieria en Sistemas de Informacion

Paz Posse Tobías	
43562927
Tobias.PazPosse@alu.frt.utn.edu.ar

Pérez Lucas Gustavo
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

struct fecha
{
    int dia;
    int mes;
    int anio;
};


struct datosUsuario
{
    char usuario[10];
    char contrasena[10];
    char ApeyNom[60];

};

struct datosVete
{
    char nomyApe[80];
    int matricula;
    int DNI;
    char telefono [25];
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
void AgregarMascota(mascota vec[TAMANO], int &indice);
void ListarAnimales(mascota vec[TAMANO], int &indice);

main()
{
    int opcion;
    int idx = 0;
    int caso = 0;
    setlocale(LC_ALL, "");
    fecha reg[TAMANO];
    datosUsuario reg2[TAMANO];
    datosVete reg3[TAMANO];
    mascota reg4[TAMANO];
    do
    {
        
        printf("M ó d u l o  d e  A s i s t e n c i a\n");
        printf("===========================================\n\n");

        printf("1.- I n i c i a r  S e s i ó n\n");
        printf("2.- R e g i s t r a r  M a s c o t a\n");
        printf("3.- R e g i s t r a r  T u r n o\n");
        printf("4.- L i s t a d o  d e  A t e n c i o n e s  p o r  V e t e r i n a r i o  y  F e c h a\n\n");

        printf("5.- C e r r a r  l a  a p l i c a c i ó n\n\n");
        printf("===========================================\n\n");
        printf("> Selección: ");
        scanf("%d", &caso);

        switch (caso)
        {
        case 1:
        {

        }
        case 2:
        {
            system("cls");
            AgregarMascota(reg4, idx);
            printf("\n¿Desea ver el listado? (1- SI / 0- NO)");
            scanf("%d", &opcion);

            if(opcion == 1)
            {
                ListarAnimales(reg4, idx);
            }
            if((opcion < -1) || (opcion > 1))
            {
                printf("ERROR. INGRESE UNA OPCIÓN VALIDA");
            }
            

            break;
        }
        case 3:
        {

        }
        case 4:
        {
            
        }
        }

    } while (caso != 5);

}

void AgregarMascota(mascota vec[TAMANO], int &indice)
{
    system("cls");
    printf("\tR E G I S T R A R  M A S C O T A");
    
    printf("\n========================================\n");
    
    printf("Ingrese el nombre de la mascota: ");
    _flushall();
    gets(vec[indice].nombre);
    
    printf("\nIngrese la dirección: ");
    _flushall();
    gets(vec[indice].direcc);
    
    printf("\nIngrese el DNI del dueño: ");
    scanf("%d",&vec[indice].DNI_DUENIO);
    
    printf("\nIngrese la localidad: ");
    _flushall();
    gets(vec[indice].localidad);
    
    printf("\nIngrese la fecha de ingreso: ");
    
    printf("\nDIA: ");
    scanf("%d", &vec[indice].Fecha.dia);
    
    printf("\nMES: ");
    scanf("%d", &vec[indice].Fecha.mes);
    
    printf("\nAÑO: ");
    scanf("%d", &vec[indice].Fecha.anio);
    
    printf("\nIngrese el peso de la mascota: ");
    scanf("%f", &vec[indice].peso);
    
    printf("\nIngrese el numero de teléfono: ");
    _flushall();
    gets(vec[indice].numeroTel);
    
    indice++;
}

void ListarAnimales(mascota vec[TAMANO], int &indice)
{
    for (int i = 1; i <= indice; i++)
    {
        system("cls");
        printf("\tL I S T A R  M A S C O T A S");
        printf("\n========================================\n");
        printf("Nombre de la Mascota: %s\n", vec[i].nombre);
        printf("Dirección: %s", vec[i].direcc);
        printf("\nDNI del dueño: %d", vec[i].DNI_DUENIO);
        printf("\nLocalidad: %s", vec[i].localidad);
        printf("FECHA: \nDÍA: %d\nMES: %d\nAÑO: %d", vec[i].Fecha.dia, vec[i].Fecha.mes, vec[i].Fecha.anio);
        printf("\nPeso de la Mascota: %.2f", vec[i].peso);
        printf("\nNumero de teléfono: %s", vec[i].numeroTel);
        printf("\n\n========================================\n");
    }
}