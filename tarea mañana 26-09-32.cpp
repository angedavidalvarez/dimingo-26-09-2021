#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<stdio.h>
using namespace std;
const char *nombre_archivo = "archivo.dat";
const char *temporal = "temporal.dat";
struct Estudiante{
	int codigo;
	char nombres[50];
	char apellidos[50];
	int telefono;
};
void crear();
void leer();
void actualizar();
void eliminar();
main(){
	int op;
	cout<<"Selecciones una opcion"<<endl;
	cout<<"1. Mostrar datos"<<endl;
	cout<<"2. Agregar datos"<<endl;
	cout<<"3. Modificar datos"<<endl;
	cout<<"4. Eliminar datos"<<endl;
	cout<<"5. Salir"<<endl;
	cout<<"Opcion: "<<endl;
	cin>>op;
	switch(op){
		case 1:
			leer();
			break;
		case 2:
			crear();
			break;
		case 3:
			actualizar();
			break;
		case 4:
			eliminar();
			break;
		case 5:
			return 0;
			break;
	}
	
	

	
}
void leer(){
		system("cls");
		FILE* archivo = fopen(nombre_archivo,"rb");	
		if (!archivo){
			archivo = fopen(nombre_archivo,"w+b");	
		}
		Estudiante estudiante;
		int id=0;	
		fread(&estudiante,sizeof(Estudiante),1,archivo);
		cout<<"____________________________________________"<<endl;
		cout<<"id"<<"|"<<"Codigo"<<"|"<<"Nombres"<<"|"<<"Apellidos"<<"|"<<"Telefono"<<endl;
		do{
		cout<<"____________________________________________"<<endl;
		cout<<id<<"|"<<estudiante.codigo<<"|"<<estudiante.nombres<<"|"<<estudiante.apellidos<<"|"<<estudiante.telefono<<endl;	
		fread(&estudiante,sizeof(Estudiante),1,archivo);
		id+=1;	
		}while(feof(archivo)==0);
		fclose(archivo);
		cout<<endl;
}
void actualizar(){
	FILE* archivo = fopen(nombre_archivo,"r+b");
	int id;
	Estudiante estudiante;
	string nombre,apellido;
	cout<<"Ingres el ID que desa Modificar:";
	cin>>id;
	fseek(archivo,id * sizeof(Estudiante),SEEK_SET);
	cout<<"Ingrese el Codigo:";
		cin>>estudiante.codigo;
		cin.ignore();
		cout<<"Ingrese los Nombres:";
		getline(cin,nombre);
		strcpy(estudiante.nombres,nombre.c_str());
		cout<<"Ingrese los Apellidos:";
		getline(cin,apellido);
		strcpy(estudiante.apellidos,apellido.c_str());
		cout<<"Ingrese el Telefono:";
		cin>>estudiante.telefono;
		cin.ignore();
	
	fwrite(&estudiante,sizeof(Estudiante),1,archivo);
	fclose(archivo);
	leer();
}
void crear(){
	char continuar;
	FILE* archivo = fopen(nombre_archivo,"ab");
	Estudiante estudiante;
	string nombre,apellido;
	do{
		fflush(stdin);
		cout<<"Ingrese el Codigo:";
		cin>>estudiante.codigo;
		cin.ignore();
		cout<<"Ingrese los Nombres:";
		getline(cin,nombre);
		strcpy(estudiante.nombres,nombre.c_str());
		cout<<"Ingrese los Apellidos:";
		getline(cin,apellido);
		strcpy(estudiante.apellidos,apellido.c_str());
		cout<<"Ingrese el Telefono:";
		cin>>estudiante.telefono;
		cin.ignore();
		fwrite(&estudiante,sizeof(Estudiante),1,archivo);
		cout<<"Dese Agregar otro Estudiante (s/n):";
		cin>>continuar;
	} while ( (continuar=='s') || (continuar=='S') );
	fclose(archivo);
	leer();
}
void eliminar(){
    FILE* archivo = fopen(nombre_archivo,"r");
    FILE* archivo2 = fopen(temporal,"r+b");
	ifstream salida;
	Estudiante estudiante;
	int id;
	int i;
	cout<<"Ingres el id que desa Eliminar:";
	cin>>id;
	
	if( fseek(archivo,id * sizeof(Estudiante),SEEK_SET) ==id )
	{
			cout<<"Usuario eliminado"<<endl;
		}
	else{
		fwrite(&estudiante,sizeof(Estudiante),1,archivo2);	
}
	remove("archivo.dat");
	rename("temporal.dat", "archivo.dat");
}
