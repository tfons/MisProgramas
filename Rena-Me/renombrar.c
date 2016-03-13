/*
 * renombrar.c
 * Version para Windows 1.0
 * Copyright 2015 Tonys Fonseca <tonys_2105@outlook.com>
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 500
#define MAX_V 1000
#define DELAY 999999999
///definicion de tipos
typedef char cadena[MAX];
typedef char extension[5];
typedef struct
{
	cadena nombre;
	extension ext;
}archivo;
///cabeceras
int menu();
void generarComando(cadena c, cadena r);
void renombrar(archivo *v, int n, int z, cadena ruta, cadena name);
void leerCadena(cadena c);
void llenarVector(FILE *a_lista, archivo *v, int *n);
int tienePunto(cadena cad, int L);
void obtenerExt(cadena x, extension ext);
void logo();
void esperar();
///principal
int main()
{
	FILE *a_lista;
	int z, n, op;
	cadena name, ruta, comando=" ";
	archivo v[MAX_V];
	
	system("color C");
	logo();
	esperar();
	do
	{
		op=menu();
		switch(op)
		{
			case 1:
				system("cls");
				printf("\n\tRena-ME 1.00 \t\tCopyright F.Software 2015");
				printf("\n\t--------------------------------------------------\n");
				printf("\n\tIngrese ruta de los archivos: ");
				leerCadena(ruta);
				generarComando(comando, ruta);//genera el comando que se ejecutara en la terminal
				system(comando);//ejecuta el comando creado
				a_lista=fopen("lista.txt", "r");
				printf("\n\tIngrese nuevo nombre: ");
				leerCadena(name);
				printf("\n\tIngrese identificador: ");
				scanf("%d", &z);
				llenarVector(a_lista, v, &n);//almacena en el vector los datos de lista.txt
				renombrar(v, n, z, ruta, name);//renombra los archivos de lista.txt
				//system("erase lista.txt");
				break;
		}
	}while(op != 0);

	return 0;
}
///subprogramas
/*muestra un menu*/
int menu()
{
	int op;
	
	system("cls");//borra la pantalla
	system("color B");
	printf("\n\tRena-ME 1.00 \t\tCopyright F.Software 2015");
	printf("\n\t--------------------------------------------------\n");
	printf("\n\t1. Renombrar archivos");
	printf("\n\t0. Salir");
	printf("\n\n\t--------------------------------------------------\n");
	printf("\n\n\tIndique su opcion>> ");
	do
	{
		scanf("%d",&op);
	} while (op < 0 || op > 1);
	return (op);
}
//genera un comando para guardar en lista.txt el nombre de los archivos
void generarComando(cadena c, cadena r)
{
	strcat(c, "dir/b ");
	strcat(c, "\"");//1era comilla
	strcat(c, r);
	strcat(c, "\"");//2da comilla
	strcat(c, " >lista.txt");
}
//renombra los archivos de lista.txt
void renombrar(archivo *v, int n, int z, cadena ruta, cadena name)
{
	int i;
	cadena old_name, new_name, identificador, c=" ";
	
	for(i=0; i<=(n-1); i++)
	{
		strcpy(old_name, "\"");//inserta 1era comilla
		strcat(old_name, ruta);//inserta ruta
		strcat(old_name, "\\");//inserta backslash
		strcat(old_name, v[i].nombre);//inserta nombre antiguo
		strcat(old_name, "\"");//inserta 2da comilla
		strcpy(new_name, "\"");///inserta 1era comilla
		strcat(new_name, name);///inserta nombre nuevo
		strcat(new_name, "-");///inserta guion
		sprintf(identificador, "%d", z);///convierte identificador a una cadena
		strcat(new_name, identificador);///inserta identificador
		strcat(new_name, v[i].ext);///inserta extension del archivo
		strcat(new_name, "\"");///inserta 2da comilla
		strcpy(c, "rename ");
		strcat(c, old_name);
		strcat(c, " ");
		strcat(c, new_name);
		system(c);//renombra el archivo
		z++;
	}
	printf("\n\t%d ARCHIVOS RENOMBRADOS!\n", i);
	esperar();
}
//lee una cadena de caracteres
void leerCadena(cadena c)
{
	fflush(stdin);
	scanf("%[^\n]", c);
}
//llena el vector con los nombres de la lista
void llenarVector(FILE *a_lista, archivo *v, int *n)
{
	int i;
	a_lista=fopen("lista.txt", "r");
	
	i=0;
	while(!feof(a_lista))
	{
		fgets(v[i].nombre, 100, a_lista);
		if(v[i].nombre[strlen(v[i].nombre)-1] == '\n')
		{
			v[i].nombre[strlen(v[i].nombre)-1] = 0;
		}
		obtenerExt(v[i].nombre, v[i].ext);
		i++;
	}
	*n=i-1;
	a_lista=fopen("lista.txt", "w");
	fclose(a_lista);
}
//obtiene la extension de 3 digitos de archivo
void obtenerExt(cadena x, extension ext)
{
	int i, j, l, pos;
	
	l=strlen(x);
	pos=strcspn(x, ".");
	j=0;

	for(i=pos; i<=(l-1); i++)
	{
		ext[j]=x[i];
		j++;
	}
}
void logo()
{
	printf("\n\n");
	printf("\n\t\t---------------------------------------------\n");
	printf("\t\t\t   ++++++++++\n");
	printf("\t\t\t  ++++++++++++\n");
	printf("\t\t\t ++++++++++++++\n");
	printf("\t\t\t++++++++++++++++\n");  
	printf("\t\t\t ++++++++++++++  ++++++++++\n");
	printf("\t\t\t  ++++++++++++  ++++++++++++\n");
	printf("\t\t\t   ++++++++++  ++++++++++++++\n");
	printf("\t\t\t              ++++++++++++++++\n");                                
	printf("\t\t\t   ++++++++++  ++++++++++++++\n");
	printf("\t\t\t  ++++++++++++  ++++++++++++\n");
	printf("\t\t\t ++++++++++++++  ++++++++++\n");
	printf("\t\t\t++++++++++++++++\n");  
	printf("\t\t\t ++++++++++++++\n");
	printf("\t\t\t  ++++++++++++\n");
	printf("\t\t\t   ++++++++++\n");
	printf("\n\t\t\tCopyright F.SOFTWARE 2015");
	printf("\n\t\t---------------------------------------------\n");
}
void esperar()
{
	long int i;
	
	for(i=0; i<DELAY; i++);
}
