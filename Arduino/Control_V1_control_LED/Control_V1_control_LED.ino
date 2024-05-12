//Oscar Chanax
//Proyecto #2 Telecomunicaciones
//Receptor FSK
#include <SoftwareSerial.h>                                                       //Libreria para Comunicación Serial

int RxArduino = 11;                                                               //Configuración Pin Receptor         
int TxArduino = 12;                                                               //Configuracion Pin Transmisor

int led = 9;

int Brillo = 0;

//SoftwareSerial FSK(RxArduino, TxArduino, 1);                                        //configuracion de parámetros comunicacion serial (Pin Recepción, Pin Transmisor, Inversion de nivel)

void setup() {
  pinMode(led, OUTPUT);
  //FSK.begin(300);                                                                    //Inicializa comunicación Serial en 300 BPS                                          
  Serial.begin(9600);                                                                 //Inicializa monitor Serial para visualizacion
                        
}

void loop() 
{   
  
  if (Serial.available() > 0)                   //>1 para que no se apage el led despues de enviar el dato por el monitor serie
  {
   int Dato = Serial.read();                                                           //Lectura del dato en comunicacion Serial 
  
   //analogWrite(led,Dato); // Establece el brillo del LED

   if (Dato == 'E')
    {
      digitalWrite(led, HIGH);
    }
    else if (Dato == 'F')
    {
      digitalWrite(led, LOW);
    }
    Serial.println(Dato);                     //Imprime en el monitor serial lo enviado
  }
   
}
