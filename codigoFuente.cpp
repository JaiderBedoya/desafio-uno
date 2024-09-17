#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

int analogpin = 0;

int buttonOn = LOW;

int buttonOff = LOW;

int val;

int valorMax = -1024;

int valorMin = 1024;

unsigned int amplitud;

bool Encendido;

bool positivo = true;

int contadorCruce = 0;

bool contando;

unsigned short int* frecuencia = new unsigned short int(0);

unsigned long* tiempoInicial = new unsigned long(0);

const unsigned long segundo = 1000;

bool ciclo;

int idx = 0;

unsigned long tiempoTranscurrido;

int* arregloValores = new int[459];

unsigned int determinante = 0;

void imprimirDatos(unsigned short int* frecuencia, int amp, int* promedio, unsigned int determinante, int contadorCruce, int idx){
	
  
  		 lcd.setCursor(1,0);
         lcd.print("Frecuencia: ");
         lcd.setCursor(1,1);
         lcd.print(*frecuencia);
      	 delay(1500);
         
         lcd.setCursor(1,0);
         lcd.print("Amplitud: ");
         lcd.setCursor(1,1);
         lcd.print(amp);
      	 delay(1500);
         lcd.clear();
         lcd.setCursor(1,0);
         lcd.print("Tipo de onda: ");
         lcd.setCursor(1,1);
            
         
         if (*promedio < -2 || *promedio > 2){
         lcd.print("Desconocida");
         }
         else if(determinante >= 400 && *promedio == 0){
         lcd.print("Cuadrada");
         }
         else if(determinante <= 2*(contadorCruce/2) && *promedio > -1 && *promedio < 1){
         lcd.print("Triangular");
         }
         else if(determinante > 3*(contadorCruce/2) && determinante < idx-contadorCruce && *promedio > -1 && *promedio < 1){
         lcd.print("Sinusoidal");
         }


}



void setup()
{
  lcd.begin(16, 2);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
}

void loop()
{
  buttonOn = digitalRead(2);
  buttonOff = digitalRead(3);
  
 
  val = analogRead(analogpin);
  
  if(buttonOn == HIGH){
  Encendido = true;
  } //buttonOn
  
  if(buttonOff == HIGH){
    ciclo = true;
    Encendido = false;
  }//buttonOff
  
  
  
  
  
  if(Encendido){
    Serial.println(val);
   
    if(val > valorMax){
    	valorMax = val;
    }
     
    if(val < valorMin){
    	valorMin = val;
    }
    
    amplitud = (valorMax - valorMin)/2;
    
      }//Encendido
  
  
  
  
  
  
  
  
  if(ciclo){
    
    if(val== amplitud && !contando){
      *tiempoInicial = millis();
      contando = true;
    }
      if(contando){
        
        
     arregloValores[idx] = analogRead(analogpin);
    idx++;
    delay(2);
        
        
       if(millis() - *tiempoInicial >= segundo){ 
         
         Serial.println("Imprimiendo valores guardados");
         delay(2000);
         
         for(int j = 0; j < idx; j++){
         Serial.println(arregloValores[j]);
         }
         
         
         int* media = new int(0);
         
         
         for(int i = 0; i <= idx; i++){
           
           media += arregloValores[i];    
           
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
           *media /= idx-1;
         }
         *frecuencia = contadorCruce;
         if(*frecuencia%2 == 0){
         	*frecuencia /= 2;
         }
         else{
         *frecuencia = (*frecuencia-1)/2;
         }
         
         imprimirDatos(frecuencia, amplitud, media, determinante, contadorCruce, idx);
         
         
         delay(2000);
         lcd.clear();
            Encendido = false;   
      		contando = false;
    		ciclo = false;
         	positivo = true;
         	amplitud = -1024;
            frecuencia = 0;
         	contadorCruce = 0;
         	delete media;
        	determinante = 0;
         	delete [] arregloValores;
         	delete tiempoInicial;
         	valorMax = -1024;
         	valorMin = 1024;
    }
      }
    
      

      }//ciclo
           
   
}//loop
