//Oscar Chanax
//Proyecto

//libreria pantalla

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include <SoftwareSerial.h>                                                       //Libreria para Comunicación Serial

SoftwareSerial blut (10,11); //RX, TX


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int RxArduino = 11;                                                               //Configuración Pin Receptor
int TxArduino = 12;                                                               //Configuracion Pin Transmisor

int led = 9;



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

}

void loop()
{


  if (blut.available() > 0)                   //>1 para que no se apage el led despues de enviar el dato por el monitor serie
  {

     
       //Lectura del dato en comunicacion Serial
   
      String dato = blut.readString();
Serial.println (dato);
      
/*
    String dato1 = " ";
    String dato2 = " ";
    String dato3 = " ";
    String dato4 = " ";
    String dato5 = " ";
    String dato6 = " ";
*/
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

double total = a1+a2;
/*
int index1 = dato.indexOf(','); // Encuentra el índice del primer espacio en la cadena
int index2 = dato.indexOf(',', index1 + 1); // Encuentra el índice del segundo espacio en la cadena
int index3 = dato.indexOf(',', index2 + 1); // Encuentra el índice del tercer espacio en la cadena
int index4 = dato.indexOf(',', index3 + 1); // Encuentra el índice del cuarto espacio en la cadena
int index5 = dato.indexOf(',', index4 + 1); // Encuentra el índice del quinto espacio en la cadena


if (index1 != -1 && index2 != -1 && index3 != -1 && index4 != -1 && index5 != -1) { // Si se encuentran los seis espacios
  dato1 = dato.substring(0, index1); // La primera parte de la cadena hasta el primer espacio es el primer dato
  dato2 = dato.substring(index1 + 1, index2); // La segunda parte de la cadena entre el primer y segundo espacio es el segundo dato
  dato3 = dato.substring(index2 + 1, index3); // La tercera parte de la cadena entre el segundo y tercer espacio es el tercer dato
  dato4 = dato.substring(index3 + 1, index4); // La cuarta parte de la cadena entre el tercer y cuarto espacio es el cuarto dato
  dato5 = dato.substring(index4 + 1, index5); // La quinta parte de la cadena entre el cuarto y quinto espacio es el quinto dato
  dato6 = dato.substring(index5 + 1); // La sexta parte de la cadena después del quinto espacio es el sexto dato
}

  
*/


    /*
    double q1 = atof(dato1.c_str());
    double q2 = atof(dato2.c_str());
    double a1 = atof(dato3.c_str());
    double a2 = atof(dato4.c_str());
    double Px = atof(dato5.c_str());
    double Py = atof(dato6.c_str());

     */
     
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
    Serial.print ("||");
    Serial.print ("Py+Px: ");
    Serial.println (total);
  }

}
