//Oscar Chanax
//Proyecto

//libreria pantalla

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

Servo servo1, servo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

  
#include <SoftwareSerial.h>                                                       //Libreria para Comunicación Serial

SoftwareSerial blut (10, 11); //RX, TX


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



int led = 9;



void setup() {
//Defino pines servomotor

servo1.attach(9);  // attaches the servo on pin 9 to the servo object
servo2.attach(8);  // attaches the servo on pin 9 to the servo object


  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();              //Limpia la pantalla

  pinMode(led, OUTPUT);
  blut.begin(9600);                                                                    //Inicializa comunicación Serial en 300 BPS
  Serial.begin(9600);                                                                 //Inicializa monitor Serial para visualizacion

  display.setTextColor(SSD1306_WHITE);        // Color de texto

}

void loop()
{


  if (blut.available() > 0)                   //>1 para que no se apage el led despues de enviar el dato por el monitor serie
  {
    //Lectura del dato en comunicacion Serial
    String dato = blut.readString();


    Serial.println (dato);  //Aqui imprimo los valores obtinidos de puerto (String)

    //Aqui separo los datos enviados
    double q1, q2, a1, a2, Px, Py;

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
      q1 = dato.substring(0, comma1).toDouble();
      q2 = dato.substring(comma1 + 1, comma2).toDouble();
      a1 = dato.substring(comma2 + 1, comma3).toDouble();
      a2 = dato.substring(comma3 + 1, comma4).toDouble();
      Px = dato.substring(comma4 + 1, comma5).toDouble();
      Py = dato.substring(comma5 + 1).toDouble();
    }



    //IMPRIMO LOS VALORES EN LA PANTALLA OLED

    display.clearDisplay();
    display.setTextSize (2);                     //tamaño de letras
    display.setCursor(0, 0);                     //Poscion del cursor
    display.print ("Q1: ");                //Impresion de hola mundo
    display.setCursor(0, 35);                     //Poscion del cursor
    display.print ("Q2: ");                //Impresion de hola mundo



    display.setTextSize (2);                     //tamaño de letras
    display.setCursor(45, 0);                     //Poscion del cursor
    display.print (q1);
    display.setCursor(35, 35);                     //Poscion del cursor
    display.print (q2);

    display.display();                          //imprime en pantalla



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

  }

  //Movimiento servo
  servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);

}
