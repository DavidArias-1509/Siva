#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include<thread>
#include<fstream>


using namespace std;
using std::this_thread::sleep_for; //funcion sleep_for();

int gotoxy(USHORT x, USHORT y){
	COORD cp={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cp);
}

fstream Busetas;
fstream contrasena;

struct USER{
	long PASWORD;
	char NAME[50];
}USUARIO;

struct REGISTRO{
	char Ruta[100];
	char Placa[10];
	char Fecha[10];
	int Sec_recorrido;
	int N_bus;
	double Val_Prod;
}Buses[220];

int N_El=0, Exit=0, i=0, t, OPT,idb, sid;

void TITLES();
int Menu();
void CAPTURA_DATOS();
void INFORME();
void CONSULTA();
int security();
int mod();
void busqueda();
void confirm();
void MODIFICAR();
void ELIMINAR();
void Persistir();
int Salir();
int verificar();

main(){
	int M, Z=0;
	while(Z==0){
	TITLES();
	M=Menu();
	switch (M){
		case 1 : CAPTURA_DATOS();
	            break ;
      
	   case 2 : CONSULTA();	   
				break;
				   
	   case 3 :	CAPTURA_DATOS();
	   			break;
				
		case 4: MODIFICAR();
				break;	
					
		case 5: ELIMINAR();
				break;	
					
		case 6: INFORME();
				break; 
				
		case 7: Persistir();
				break;
				
		case 8: Z=Salir();
		}		
	}
}

void TITLES(){
	system("cls"); system("color 02");
	gotoxy(47,2); printf("SIVA");
	gotoxy(35,3); printf("Sistema Integrado de Transporte de Valledupar");
	gotoxy(42,4); printf("Contabilidad y Registro");
}

int Menu(){
		TITLES();
    	int OPT;
		gotoxy(23,8);  cout << "1 - ALMACENAR INFROMACION INICIAL" ;
		gotoxy(23,9);  cout << "2 - CONSULTA ";
		gotoxy(23,10); cout << "3 - AGREGAR INFORMACION";
		gotoxy(23,11); cout << "4 - MODIFICAR DATOS";
		gotoxy(23,12); cout << "5 - ELIMINAR REGISTRO";
		gotoxy(23,13); cout << "6 - GENERAR INFORME";
		gotoxy(23,14); cout << "7- PERSISTIR INFORMACION";
		gotoxy(23,15); cout << "8- SALIR - CERRAR PROGRAMA";   
		do {
		gotoxy(24,18); cout << "Seleccine una alternativa :               ";
		gotoxy(54,18); cin>> OPT;
		} while ((OPT < 1 ) || (OPT > 8));
    
    	return OPT;
	}
	
void mod(int w){
	gotoxy(5,6);cout<<"1- Numero del bus: "<<Buses[w].N_bus;
	gotoxy(5,7);cout<<"2- Placa: "<<Buses[w].Placa;
	gotoxy(5,8);cout<<"3- Ruta: "<<Buses[w].Ruta;
	gotoxy(5,9);cout<<"Secuencia de recorrido: "<<Buses[w].Sec_recorrido;
	gotoxy(5,10);cout<<"4- Fecha: "<<Buses[w].Fecha;
	gotoxy(5,11);cout<<"5- Dinero Producido: "<<Buses[w].Val_Prod;
	gotoxy(5,12);cout<<"6- Cancelar / No modificar";
	do {
		gotoxy(54,16);cout<<"     ";
		gotoxy(24,16);cout<<"Seleccine una alternativa :  ";
		gotoxy(54,16); cin>> OPT;
	} while ((OPT < 1 ) || (OPT > 5));
	gotoxy(24,16);cout<<"                               ";
	
	switch (OPT){
		
		case 1: do{
				gotoxy(25,6);  cout<<"              ";
				gotoxy(25,6); cin>>Buses[i].N_bus;
				}while((Buses[w].N_bus<0)||(Buses[w].N_bus>220));
				break;
				
		case 2:	gotoxy(15,7); cout<<"            ";
				gotoxy(15,7); cin.sync(); gets(Buses[w].Placa);
				break;
									
		case 3:	gotoxy(14,8); cin.sync(); gets(Buses[w].Ruta);
				gotoxy(14,8); cout<<strupr(Buses[w].Ruta);
				break;
		
		case 4: gotoxy(15,10); cin.sync(); gets(Buses[w].Fecha);
				break;
		
		case 5: do{
					gotoxy(26,11);cout<<"                 ";
					gotoxy(26,11);cin>>Buses[w].Val_Prod;
				}while(Buses[w].Val_Prod<0);
				break;

		case 6: gotoxy(24,16);cout<<"Ok... No se registaron cambios";
				t=2;
				break; 
		}
}

void CAPTURA_DATOS(){
	int cont;
	char cn='S', ok;
	while((cn=='S')&&(N_El<219)){
		TITLES();
		gotoxy(15,6); cout<<"Registro #"<<(N_El+1);
		gotoxy(15,7); cout<<"Placa del bus: ";
		gotoxy(15,8); cout<<"Numero del bus: ";
		gotoxy(15,9); cout<<"Ruta: ";
		gotoxy(15,10);cout<<"Fecha: DD/MM/AA";
		gotoxy(15,11);cout<<"Valor Producido: ";
		//Lectura de datos
		
		gotoxy(30,7); cin.sync(); gets(Buses[N_El].Placa);
		
		do{
			gotoxy(31,8);cout<<"        ";
			gotoxy(31,8);cin>>Buses[N_El].N_bus;
		}while((Buses[N_El].N_bus<1)||(Buses[N_El].N_bus>200));

		Buses[N_El].Sec_recorrido<-1;

		if(N_El>0){
			for(i=0; i<N_El; i++){
				if((Buses[i].N_bus)==(Buses[N_El].N_bus)){
					Buses[N_El].Sec_recorrido++;
				}
			}
		}		

		gotoxy(21,9); cin.sync(); gets(Buses[N_El].Ruta);
		gotoxy(21,9); cout<<strupr(Buses[N_El].Ruta);
		gotoxy(22,10);cout<<"               ";
		gotoxy(22,10); cin.sync(); gets(Buses[N_El].Fecha);

		do{
			gotoxy(32,11);cout<<"                 ";
			gotoxy(32,11);cin>>Buses[N_El].Val_Prod;
		}while(Buses[N_El].Val_Prod<0);
		
		do{
			gotoxy(33,15); cout<<"   ";
		  	gotoxy(15,14); cout <<"Los datos estan correctos? Verifique";
		  	gotoxy(15,15); cout <<"SI-> S / NO-> N : "; 
			cin.sync(); ok=getchar();	
	  		ok=toupper(ok);
		}while((ok!='S')&&(ok!='N'));
			gotoxy(15,14); cout <<"                                        ";
		  	gotoxy(15,15); cout <<"                                ";
		
		if(ok=='N'){
			TITLES();
			mod(N_El);
		}
		
		do{
			gotoxy(33,15); cout<<"   ";
		  	gotoxy(15,14); cout <<"DESEA AGREGAR UN ELEMENTO MAS?";
		  	gotoxy(15,15); cout <<"SI-> S / NO-> N : "; 
			cin.sync(); cn=getchar();	
	  		cn=toupper(cn);
		}while((cn!='S')&&(cn!='N'));
		N_El++;
	}
}

void INFORME(){
	int i, R;
	if(N_El==0){
		TITLES();
		gotoxy(15,5);cout<<"Error... No hay registros...";
		gotoxy(15,7);cout<<"Presione Cualquier Tecla Para Volver al Menu Iniacial..."; getch();
	}
	else
	{
		TITLES();
		R=6;
		for(i=0; i<N_El; i++){
			gotoxy(5,R); cout<<"Numero del bus: "<<Buses[i].N_bus;
			gotoxy(5,R+1);cout<<"Placa: "<<Buses[i].Placa;
			gotoxy(5,R+2);cout<<"Ruta: "<<Buses[i].Ruta;
			gotoxy(5,R+3);cout<<"Secuencia de recorrido: "<<Buses[i].Sec_recorrido;
			gotoxy(5,R+4);cout<<"Fecha: "<<Buses[i].Fecha;
			gotoxy(5,R+5);cout<<"Dinero Producido: "<<Buses[i].Val_Prod;
			R=R+7;
		}
		gotoxy(15,R+2);cout<<"Presione Cualquier Tecla Para Volver al Menu Iniacial..."; getch();	
	}
}

void CONSULTA(){
	int id, i, t, R;
	if(N_El==0){
		TITLES();
		gotoxy(15,5);cout<<"Error... No hay registros...";
		gotoxy(15,7);cout<<"Presione Cualquier Tecla Para Volver al Menu Iniacial..."; getch();
	}
	else
	{
		TITLES();
		gotoxy(15,5);cout<<"Ingrese el Numero del Bus: ";
		do{
			gotoxy(42,5); cout<<"              ";
			gotoxy(42,5); cin>>id;
			gotoxy(20,7);cout<<"Error...";
		}while((id<0)||(id>2100000000));
		gotoxy(20,7);cout<<"          ";
		t=0; R=6;
		TITLES();
		for(i=0; i<N_El; i++){
			if(Buses[i].N_bus==id){
			t=1;
			gotoxy(5,R); cout<<"Numero del bus: "<<Buses[i].N_bus;
			gotoxy(5,R+1);cout<<"Placa: "<<Buses[i].Placa;
			gotoxy(5,R+2);cout<<"Ruta: "<<Buses[i].Ruta;
			gotoxy(5,R+3);cout<<"Secuancia de recorrido: "<<Buses[i].Sec_recorrido;
			gotoxy(5,R+4);cout<<"Fecha: "<<Buses[i].Fecha;
			gotoxy(5,R+5);cout<<"Dinero Producido: "<<Buses[i].Val_Prod;
			R=R+7;
			}
		}
		if(t==0){
			TITLES();
			gotoxy(20,5); cout<<"NO HAY COINCIDENCIAS EN LOS REGISTROS";
		}			
		gotoxy(15,12);cout<<"Presione Cualquier Tecla Para Volver al Menu Iniacial..."; getch();
	}
}

int verificar(long X){
	int r=0;
	contrasena.open("C:\\Siva\\CONTRASEÑA.dat", ios::in);
	if(contrasena.fail()){
		r=1;
	}
	else{
		while(! contrasena.eof()){
			contrasena.read((char*)&USUARIO, sizeof(USER));
			if( contrasena.eof() )
			break;
			if(USUARIO.PASWORD==X){
			r=1;	
			}
		}
	}
	contrasena.close();
	return r;
}

int security(){
	long ingreso;
	int X=0;
	TITLES();
	gotoxy(10,8);cout<<"PARA REALIZAR ESTA ACCION DEBE INGRESAR LA CLAVE DE SEGURIDAD";
	gotoxy(15,10);cout<<"Contraseña: ";
	
	do{//Verificar contraseña
		gotoxy(27,10);cout<<"             ";
		gotoxy(27,10);cin>>ingreso;
		gotoxy(10,12);cout<<"Se han realizado "<<X<<" intentos";
		X++;
	}while(ingreso<0);

	 X=verificar(ingreso);

	return X;
}

void busqueda(){
	TITLES();
			gotoxy(15,5);cout<<"Ingrese el Numero del Bus: ";
			do{//validar numero del bus
				gotoxy(42,5); cout<<"              ";
				gotoxy(42,5); cin>>idb;
				gotoxy(20,7);cout<<"Error... valor fuera de rango";
			}while((idb<0)||(idb>220));
			gotoxy(20,7);cout<<"                            ";
			
			gotoxy(15,6);cout<<"Ingrese el Numero de la secuencia: ";
			do{//validar secuencia de recorrido
				gotoxy(44,6); cout<<"              ";
				gotoxy(44,6); cin>>sid;
				gotoxy(20,7);cout<<"Error... valor fuera de rango";
			}while((sid<0)||(sid>20));
			gotoxy(20,7);cout<<"                            ";
}

void confirm(){
	if(t==0){
				TITLES();
				gotoxy(20,5); cout<<"NO HAY COINCIDENCIAS EN LOS REGISTROS";
				gotoxy(15,7);cout<<"Presione Cualquier Tecla Para Volver al Menu Iniacial..."; getch();
			}else{	
				if(t==2){
					gotoxy(20,15); cout<<"No se registraron cambios el registro";
					gotoxy(15,16);cout<<"Presione Cualquier Tecla Para Volver al Menu Iniacial..."; getch();
				}else{
					gotoxy(20,15); cout<<"Se realizacon los cambios al registro";
					gotoxy(15,16);cout<<"Presione Cualquier Tecla Para Volver al Menu Iniacial..."; getch();	
				}
			}
}

void MODIFICAR(){
	int  cont=0;
	cont=security();
	if(cont==1){
		if(N_El==0){
			TITLES();
			gotoxy(15,5);cout<<"Error... No hay registros...";
			gotoxy(15,7);cout<<"Presione Cualquier Tecla Para Volver al Menu Iniacial..."; getch();
		}
		else
		{
			busqueda();
			t=0;
			for(i=0; i<N_El && t==0; i++){
				if((Buses[i].N_bus==idb)&&(Buses[i].Sec_recorrido==sid)){
					t=1;
					TITLES();
					mod(i);				
					}
			}
			confirm();
		}
	}
}
 
void ELIMINAR(){
		int  m, cont=0;
		char cn;
	cont=security();
	if(cont==1){
		if(N_El==0){
			TITLES();
			gotoxy(15,5);cout<<"Error... No hay registros...";
			gotoxy(15,7);cout<<"Presione Cualquier Tecla Para Volver al Menu Iniacial..."; getch();
		}
		else
		{
			busqueda();
			t=0; 
			for(i=0; i<N_El && t==0; i++){
				if((Buses[i].N_bus==idb)&&(Buses[i].Sec_recorrido==sid)){
					t=1;
					TITLES();
					gotoxy(5,6);  cout<<"Numero del bus: "<<Buses[i].N_bus;
					gotoxy(5,7);cout<<"Placa: "<<Buses[i].Placa;
					gotoxy(5,8);cout<<"Ruta: "<<Buses[i].Ruta;
					gotoxy(5,9);cout<<"Secuencia de recorrido: "<<Buses[i].Sec_recorrido;
					gotoxy(5,10);cout<<"Fecha: "<<Buses[i].Fecha;
					gotoxy(5,11);cout<<"Dinero Producido: "<<Buses[i].Val_Prod;			
					do{
					gotoxy(33,12); cout<<"   ";
					gotoxy(15,13); cout <<"DESEA ELIMINAR EL REGISTRO?";
					gotoxy(15,12); cout <<"SI-> S / NO-> N : "; 
					cin.sync(); cn=getchar();	
					cn=toupper(cn);
					}while((cn!='S')&&(cn!='N'));
					
					if(cn=='S'){
						for(m=i; m<N_El; m++){
							Buses[m].N_bus = Buses[m + 1].N_bus;	
							strcpy( Buses[m].Ruta , Buses[m+1].Ruta);
							strcpy(Buses[m].Placa, Buses[m+1].Placa);
							strcpy(Buses[m].Fecha, Buses[m + 1].Fecha);
							Buses[m].Sec_recorrido = Buses[m + 1].Sec_recorrido;
							Buses[m].Val_Prod = Buses[m + 1].Val_Prod;
						}
					N_El=N_El-1;
					}
					if(cn=='N'){
						t=2;
					}	
				}
			}
			confirm();
		}
	}
}

int Salir(){
	char cn;
	int x=1;
	if(Exit==0){
		TITLES();
		gotoxy(15,5);cout<<"Advertencia! Usted no ha guardado los registros en la base de datos";
		do{
			gotoxy(33,15); cout<<"   ";
		  	gotoxy(15,7); cout <<"Desea Salir Sin registar cambios?";
		  	gotoxy(15,8); cout <<"SI-> S / NO-> N : "; 
			cin.sync(); cn=getchar();	
	  		cn=toupper(cn);
		}while((cn!='S')&&(cn!='N'));
		if(cn=='S'){
			gotoxy(15,7);cout<<"Cerrando Programa";
			for(i<0; i<5; i++){
				sleep_for(0.30ms); cout<<".";
			}
		}
		if(cn=='N'){
			gotoxy(15,7);cout<<"Por favor espere";
			for(i<0; i<5; i++){
				sleep_for(0.30ms); cout<<".";
			}
			Persistir();
		}
	}
	return x;
}

void Persistir(){
	Exit=1;
	TITLES();
	gotoxy(15,7); cout<<"Registrando cambios";
	for(i=0; i<10; i++){
		sleep_for(50ms);cout<<".";
	}
	Busetas.open("C:\\Siva\\cuentas.dat", ios::app);
	for(i=0; i<N_El; i++){
		Busetas.write((char*)&Buses[i], sizeof(REGISTRO));
	}
	Busetas.close();
	gotoxy(10,9);cout<<"Se han registrado los cambios con exito";
	gotoxy(10,10);cout<<"Presione Cualquier Tecla Para Volver al Menu Iniacial..."; getch();
}

