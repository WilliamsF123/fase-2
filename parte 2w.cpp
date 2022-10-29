#include <iostream>
#include <cstdlib>
using namespace std;


void leer();
void Crear();
void Actualizar();
void Borrar();
int main() {
	
	int opciones;
	bool repetir = true;
	char palabra[50];
	char traduccion[50];
	
	do{
		cout<<" 1# Leer"<<endl;
		cout<<" 2# Crear"<<endl;
		cout<<" 3# Actualizar"<<endl;
		cout<<" 4# Borrar"<<endl;
		cout<<" 5# Fin del Programa"<<endl;
		cin>>opciones;
		switch (opciones){
			case 1 : leer ();
					
			break;			
			case 2 : Crear ();
			break;
			case 3 : Actualizar ();
			break;
			case 4 : Borrar ();
			break;
			case 5 : cout<<"Fin del Programa"<<endl;
			break;
		
		
		}
	}while (opciones=!5);
	return 0;
  	
	system("pause");
}
const char *nombre_archivo = "archivo.dat";
struct Traductor{
	char palabra[50];
	char traduccion[50];
	
};

void leer(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo,"rb");
	if (!archivo){
		archivo = fopen(nombre_archivo,"w+b");
	}
	Traductor traductor;
	int id=0; // indice o pocision del registro(fila) dentro del archivo
	fread(&traductor,sizeof(Traductor),1,archivo);
	cout<<"___________________________________________________"<<endl;
	do{
		cout<<"ID: "<<id<<endl;
		cout<<"Palabra: "<<traductor.palabra<<endl;
		cout<<"Traduccion: "<<traductor.traduccion<<endl;
		
		fread(&traductor,sizeof(Traductor),1,archivo);
		id+=1;
	}while(feof(archivo)==0);
	fclose(archivo);
}
void Crear(){
	
	FILE* archivo = fopen(nombre_archivo,"a+b");
	char res;
	Traductor traductor;
	do{
		fflush(stdin);
		cout<<"Ingrese Palabra:";
		cin>>traductor.palabra,50;
		cin.ignore();
		
		cout<<"Ingrese Traduccion:";
		cin.getline(traductor.traduccion,50);
		
			
		fwrite(&traductor,sizeof(Traductor),1,archivo);
		cout<<"Desea ingresar otro Palabra(s/n):";
		cin>>res;
	}while(res=='s' || res=='S');
	fclose(archivo);
	leer();
}
void Actualizar(){
	
	FILE* archivo = fopen(nombre_archivo,"r+b"); 
	Traductor traductor;
	int id=0;
	cout<<"Ingrese el ID que desea Modificar:";
	cin>>id;
	fseek(archivo,id * sizeof(Traductor),SEEK_SET);
		cout<<"Ingrese Palabra:";
		cin>>traductor.palabra,50;
		cin.ignore();
		
		cout<<"Ingrese Traduccion:";
		cin.getline(traductor.traduccion,50);
		
		fwrite(&traductor,sizeof(Traductor),1,archivo);
	
	
	fclose(archivo);
	leer();
}
void Borrar(){
	const char *nombre_archivo_temp = "archivo_temp.dat";
	FILE* archivo_temp = fopen(nombre_archivo_temp,"w+b");
	FILE* archivo = fopen(nombre_archivo,"rb");
	Traductor traductor;
	int id=0,id_n=0;
	cout<<"Ingrese el ID a eliminar:";
	cin>>id;
	while(fread(&traductor,sizeof(Traductor),1,archivo)){
		if (id_n !=id ){
			fwrite(&traductor,sizeof(Traductor),1,archivo_temp);
		}
		id_n++;
	}
	fclose(archivo);
	fclose(archivo_temp);
	
	archivo_temp = fopen(nombre_archivo_temp,"rb");
	archivo = fopen(nombre_archivo,"wb");
	while(fread(&traductor,sizeof(Traductor),1,archivo_temp)){
		fwrite(&traductor,sizeof(Traductor),1,archivo);
		
	}
		fclose(archivo);
	fclose(archivo_temp);
	leer();
}	
