 /**********************************************************************************************************************
 // FileName:        main.cpp
 // Program version: Dev-C++ 5.11
 // Company:         TECNM - ITCH
 // Description:     Lab_3 POO conf ADC
 // Authors:         Luis Octavio Mendez Valles
 // Professor:       Alfredo Chacon
 // Subject:         Arquitectura de Prog. Para Hardware
 // Updated:         15/12/2022
 ************************************************************************************************************************/
 
#include <iostream>
#include <stdlib.h>

using namespace std;

//Variables globales para el funcionamiento del programa
bool select;
float fr;
int can;

//Clase
class ADC{
	
	//Atributos
	private:
		static int res1;
		float frec;
		int canal;
		float volts;
		double res2;
	
	public:
		ADC(){}; //Constructor
		//Metodos
		void canales();
		void leerVolts();
		void muestraDatos();
		static void capturaDatos();
		virtual void frecP(float); //Método para el polimorfismo
		float capturaf();
		
};

//Inicializa las variables estaticas
int ADC::res1=0;

//Clase hija para la frecuencia directa
class ADC_FrecM : public ADC{
	
	public:
		void frecP(float);
		
};

//Clase hija para el calculo de la frecuencia
class ADC_Fs : public ADC{
	
	public:
		void frecP(float);
		
};

//Método para la frecuencia directa
void ADC_FrecM::frecP(float fs){
	
	ADC::frecP(fs);
	
}

//Método para el calculo de la frecuencia
void ADC_Fs::frecP(float ack){
	
	float fs;
	fs = 8000000/ack;
	ADC::frecP(fs);
	
}

void ADC::frecP(float fs){
	frec = fs;
}

float ADC::capturaf(){
	return frec;
}

void ADC::canales(){ //Definicion del metodo canales

	//Lee los canales
	do{
    	cout<<"\nIntroducir canal AN a usar (1-32): ";
    	cin>>canal;
    	if(canal<1 || canal>32){ //Verifica el canal
    		cout<<"Entrada invalida"<<endl;
    	}
	}while(canal<1 || canal>32); //Repite si la entrada es incorrecta

}

void ADC::leerVolts(){ //Definicion del metodo leerVolts

	//Lee el voltaje
	do{
    	cout<<"\nIntroducir voltaje (0-3.3v) del canal "<<canal<<": ";
    	cin>>volts;
    	if(volts<0 || volts>3.3){ //Verifica el voltaje
    		cout<<"Entrada invalida"<<endl;
    	}
	}while(volts<0 || volts>3.3); //Repite si la entrada es incorrecta

	//Conversion a 8 bits
	if(res1 == 8){
		res2 = (volts*255)/3.3;
	}
	
	//Conversion a 10 bits
	if(res1 == 10){
		res2 = (volts*1023)/3.3;
	}
	
	//Conversion a 12 bits
	if(res1 == 12){
		res2= (volts*4095)/3.3;
	}

}

void ADC::muestraDatos(){ //Definicion del metodo muestraDatos

	cout<<"\nCanal AN"<<canal<<"\nConversion: "<<res2<<"\nFrecuencia de muestreo: "<<capturaf()<<endl;

}

void ADC::capturaDatos(){ //Definicion del metodo capturaDatos
	
	cout<<"\nIntroducir la cantidad de canales a leer: ";
    cin>>can;
	
	//Lee la resolucion
	do{
		cout<<"\nIntroducir resolucion de bits (8, 10, 12): ";
		cin>>res1;
		if(res1!=8 && res1!=10 && res1!=12){ //Verifica la resolucion
			cout<<"Entrada invalida"<<endl;
		}
	}while(res1!=8 && res1!=10 && res1!=12); //Repite si la entrada es incorrecta
	
	if(!select){
		//Lee el factor ack
		cout<<"\nIntroducir factor ack (2, 4, 8, 16, 32, 64): ";
		do{
			cin>>fr;
			if(fr!=2 && fr!=4 && fr!=8 && fr!=16 && fr!=32 && fr!=64)
				cout<<"Factor x no valido"<<endl;
		}while (fr!=2 && fr!=4 && fr!=8 && fr!=16 && fr!=32 && fr!=64);
	}
	else{
		//Lee la frecuencia
		cout<<"\nIntroducir frecuencia de muestreo (Hz): ";
		cin>>fr;
	}

}

void portada(); //Prototipo de funcion 

//main
int main(){
	
	portada(); //Llama a portada
	cout<<"\nSeleccione una forma de obtener la frecuencia de muestreo\n0.- Calculada (ack)\n1.- Directa"<<endl;
	cin>>select;
	ADC::capturaDatos(); //Llama al metodo capturaDatos
    
    if(select){
    	ADC_FrecM canalM[can];
	    //Ciclos para los metodos
		for(int i=0;i<can;i++){
			canalM[i].canales();
		}
		for(int i=0;i<can;i++){
			canalM[i].frecP(fr);
			canalM[i].leerVolts();
		}
		for(int i=0;i<can;i++){
			canalM[i].muestraDatos();
		}
	}
	else{
		ADC_Fs canals[can];	
	    //Ciclos para los metodos
		for(int i=0;i<can;i++){
			canals[i].canales();
		}
		for(int i=0;i<can;i++){
			canals[i].frecP(fr);
			canals[i].leerVolts();
		}
		for(int i=0;i<can;i++){
			canals[i].muestraDatos();
		}	
	}

	return 0;
}

//Se imprime la portada
void portada() {
	
	printf("---------------------------------------------------------\n");
	printf("|| Instituto Tecnologico de Chihuahua                  ||\n");
	printf("|| Autor: Luis Octavio Mendez Valles 19060757          ||\n");
	printf("|| Programa: Lab_3 Configuracion ADC                   ||\n");
	printf("|| Catedratico: Alfredo Chacon                         ||\n");
	printf("|| Materia: Arquitectura de Prog. para Hardware        ||\n");
	printf("---------------------------------------------------------\n\n");
	printf("-------------------------------------------------------------\n");
	printf("|| Instrucciones de uso: Introduzca la resolucion de bits  ||\n");
	printf("|| deseada, asi como la frecuencia de muestreo, cantidad y ||\n");
    printf("|| canales a leer.                                         ||\n");
    printf("-------------------------------------------------------------\n\n");
    
}
