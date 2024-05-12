//Oscar Chanax
//Proyecto

//libreria pantalla

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include <SoftwareSerial.h>                                                       //Libreria para Comunicación Serial

SoftwareSerial blut (11,10); RX, TX


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int RxArduino = 11;                                                               //Configuración Pin Receptor
int TxArduino = 12;                                                               //Configuracion Pin Transmisor

int led = 9;

int Brillo = 0;


void setup() {

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();              //Limpia la pantalla

  pinMode(led, OUTPUT);
  blut.begin(9600);                                                                    //Inicializa comunicación Serial en 300 BPS
  Serial.begin(9600);                                                                 //Inicializa monitor Serial para visualizacion

  display.setTextColor(SSD1306_WHITE);        // Color de texto
  display.setTextSize (2);                     //tamaño de letras

}

void loop()
{


  if (Serial.available() > 0)                   //>1 para que no se apage el led despues de enviar el dato por el monitor serie
  {
    display.clearDisplay();
    display.setCursor(0, 0);                     //Poscion del cursor
    display.print ("Q1: ");                //Impresion de hola mundo
    display.setCursor(0, 30);                     //Poscion del cursor
    display.print ("Q2: ");                //Impresion de hola mundo

    //Lectura del dato en comunicacion Serial
   
      String dato = Serial.readString();

    String dato1;
    String dato2;

    //Aqui separo los datos enviados

    int index = dato.indexOf(' '); // Encuentra el índice del primer espacio en la cadena

    if (index != -1) { // Si se encuentra el espacio
      dato1 = dato.substring(0, index); // La primera parte de la cadena hasta el espacio es el primer dato
      dato2 = dato.substring(index + 1); // La segunda parte de la cadena después del espacio es el segundo dato
    }


    //Conversion de datos a double
    double valor1 = atof(dato1.c_str());
    double valor2 = atof(dato2.c_str());
    



    display.setCursor(35, 0);                     //Poscion del cursor
    display.print (String(valor1));
    display.setCursor(35, 30);                     //Poscion del cursor
    display.print (String(valor2));

    display.display();                          //imprime en pantalla
  
  }

}
