#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

int analogpin = 0;
int buttonOn = LOW;
int buttonOff = LOW;
int val = 0;
int valorMax = -1024;
int valorMin = 1024;
int amplitud;
int puntoMedio;
bool Encendido;
bool positivo = true;
int contadorCruce = 0;
unsigned short int cambios = 0;
int contador;

bool contando;

unsigned short int frecuencia;

unsigned long tiempoInicial = 0;

const unsigned long segundo = 1000;

bool ciclo;

int idx = 0;

unsigned long tiempoTranscurrido;

int* arregloValores = new int[459];

unsigned int determinante = 0;


void setup()
{
  lcd.begin(16, 2);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop()
{
  buttonOn = digitalRead(2);
  buttonOff = digitalRead(3);
  
 
  val = analogRead(analogpin);

  if(buttonOn == HIGH){
  Encendido = true;} //buttonOn
  
  if(buttonOff == HIGH){
    ciclo = true;
    Encendido = false;
  }//buttonOff
  
  
  if(Encendido){  
   
    if(val > valorMax){
    	valorMax = val;
    }
     
    if(val < valorMin){
    	valorMin = val;
    }
    
    amplitud = (valorMax - valorMin)/2;
    
    //puntoMedio = (valorMax + valorMin)/2;    
     
      }//Encendido
  
  
  
  
  
  if(ciclo){
    
    if(val== amplitud && !contando){
      tiempoInicial = millis();
      contando = true;
    }
      if(contando){
     arregloValores[idx] = analogRead(analogpin);
    idx++;
    delay(2);
       if(millis() - tiempoInicial >= segundo){
      Serial.println("Termino la recoleccion de datos...");
      Serial.println(idx);
    delay(8000);      
         Serial.println("Imprimiendo datos tomados en un segundo");
         
         for(int j = 0; j <= idx;j++){
         	Serial.println(arregloValores[j]); 
         }
         delay(8000);
         
         for(int i = 0; i <= idx; i++){
           
           if(i < idx){             
             if(arregloValores[i] == arregloValores[i+1]){
             	determinante++;
             }

    
           if(positivo){

           if(arregloValores[i+1]>0){
           contadorCruce++;
           positivo = false;
           }
             
           }  
           
           if(!positivo){
               
           if(arregloValores[i+1] < 0){
           contadorCruce++;
           positivo = true;
           }
               
           }
             
           
           
           }  
         }
         
         frecuencia = contadorCruce;
         Serial.println("La frecuencia es: ");
         if(frecuencia%2 == 0){
         	Serial.println(frecuencia/2);
         }
         else{
         Serial.println((frecuencia-1)/2);
         }
         Serial.println("La amplitud es: ");
         Serial.println(amplitud);
         
         if(determinante > contadorCruce){
         Serial.println("Onda cuadrada");
         }
         else if(determinante == 0){
         Serial.println("Onda triangular");
         }
         else if(determinante != 0 && determinante <= contadorCruce){
         Serial.println("Onda Sinusoidal");
         }
         else{
         Serial.println("Señal desconocida");
         }
         
         
         
      contando = false;
    	ciclo = false;
    }
      }
    
      

      }//ciclo
           
   
}//loop
