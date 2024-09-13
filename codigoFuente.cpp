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





bool ciclo;
int idx = 0;
float tiempoInicial;
unsigned long tiempoTranscurrido;


int contadorCiclo = 0;

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
  }//buttonOff
  
  
  if(Encendido){  
    
   
    if(val > valorMax){
    	valorMax = val;
    }
     
    if(val < valorMin){
    	valorMin = val;
    }
    
    amplitud = (valorMax - valorMin)/2;
    
    puntoMedio = (valorMax + valorMin)/2;
    
     
    if(ciclo){
    int* arregloValores = new int[amplitud*2];
      
      for(int idx = 0; idx < (amplitud*2); idx++){
        arregloValores[idx] = analogRead(analogpin);
        delay(10);
      }      
      Serial.println("Termino la recoleccion de datos...");
    delay(8000);
      for(int i = 0; i < amplitud*2; i++){
        Serial.print("Indice: ");
        Serial.println(i);
        Serial.println(arregloValores[i]);
      }
        ciclo = false;
      
    }//ciclo
    
    
    
      
        } 
    
    
    
    
   
  
  
}//loop
