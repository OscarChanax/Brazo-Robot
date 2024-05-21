#include <SPI.h>
#include <Wire.h>
#include <Servo.h>
#include <SoftwareSerial.h>                                                       //Libreria para Comunicación Serial

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

SoftwareSerial blut (10, 11); //RX, TX
Servo l1, l2, pinza;

int  t = 10, pos = 0;

void setup() {
  //Defino pines servomotor

  l1.attach(5);
  l2.attach(6);
  pinza.attach(7);
  blut.begin(9600);                                                                    //Inicializa comunicación Serial en 300 BPS
  Serial.begin(9600);                                                                 //Inicializa monitor Serial para visualizacion

  l2.write(0);
  l1.write(180);
  pinza.write(40);
  delay(1000);
}

void loop()
{
  if (blut.available() > 0)                   //>1 para que no se apage el led despues de enviar el dato por el monitor serie
  {
    //Lectura del dato en comunicacion Serial
    String dato = blut.readString();


    Serial.println (dato);  //Aqui imprimo los valores obtinidos de puerto (String)

    //Aqui separo los datos enviados
    double a1, a2;
    int q1, q2, Px, Py;

    //NOTA IMPORTANTE LOS DATOS OBTENIDOS DEBEN TENER AL PUNTO COMO SEPARADOR DECIMAL PARA UNA CORRECTA CONVERSION A "DOUBLE"
    // Separar los datos recibidos por comas
    // Encontrar las posiciones de las comas
    int comma1 = dato.indexOf(',');
    int comma2 = dato.indexOf(',', comma1 + 1);
    int comma3 = dato.indexOf(',', comma2 + 1);
    int comma4 = dato.indexOf(',', comma3 + 1);
    int comma5 = dato.indexOf(',', comma4 + 1);

    // Extraer subcadenas y convertirlas a double
    if (comma1 != -1 && comma2 != -1 && comma3 != -1 && comma4 != -1 && comma5 != -1) {
      q1 = dato.substring(0, comma1).toInt();
      q2 = dato.substring(comma1 + 1, comma2).toInt();
      a1 = dato.substring(comma2 + 1, comma3).toDouble();
      a2 = dato.substring(comma3 + 1, comma4).toDouble();
      Px = dato.substring(comma4 + 1, comma5).toInt();
      Py = dato.substring(comma5 + 1).toInt();
    }



    //IMPRIMO LOS VALORES EN EL MONITOS SERIAL
    Serial.print ("Q1: ");
    Serial.print (q1);
    Serial.print ("||");
    Serial.print ("Q2: ");
    Serial.print (q2);
    Serial.print ("||");
    Serial.print ("a1: ");
    Serial.print (a1);
    Serial.print ("||");
    Serial.print ("a2: ");
    Serial.print (a2);
    Serial.print ("||");
    Serial.print ("Px: ");
    Serial.print (Px);
    Serial.print ("||");
    Serial.print ("Py: ");
    Serial.println (Py);

    if (Py == 100) {
      pinza.write(Px);
      delay(800);
      l1.write(q1);
      delay(800);
      l2.write(q2);
      delay(800);
    }
    else {
      l2.write(q2);
      delay(800);
      l1.write(q1);
      delay(800);
      pinza.write(Px);
      delay(800);
    }
  }
}
