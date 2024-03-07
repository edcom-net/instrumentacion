#include "EmonLib.h"  // Biblioteca para la familia de sensores SCT-013 
#include "LiquidCrystal_I2C.h" // Libreria para LCD

EnergyMonitor emon1;  // Creamos una instancia del sensor

// Conexión: SDA pin al A4 y SCL pin al A5.
// Conectamos el LCD via I2C, la dirección predeterminada es 0x27 
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // 

/* Voltaje de nuestra red eléctrica */
//float voltajeRed = 127.0;  /* 115V-127V Comúnmente en México */
void setup() {

// Inicializamos el LCD:
  lcd.init();
  lcd.clear();         
  lcd.backlight();

Serial.begin(9600);
 emon1.current(1, 30); //corriente (pin de entrada, constante de calibración)
/* constante de calibración: Es el valor que se desea leer cuando hay 1V a la salida del sensor */
}


void loop() {
/* Obtenemos el valor de la corriente eficaz pasando un número de muestras que se van a tomar para promediar */
float Irms = emon1.calcIrms(1480); // Calculate Irms only

/* Mostramos la información por el monitor serie y lcd*/
if(Irms<1){
Serial.print(" Irms = ");
Serial.println(Irms*1000);
lcd.setCursor(0, 0); // Set the cursor on the third column and first row.
lcd.print("Corriente AC:"); // Print the string "Hello World!
lcd.setCursor(0, 1); // Set the cursor on the third column and first row.
lcd.print(Irms*1000); // Print the string "Hello World!
lcd.setCursor(4, 1); // Set the cursor on the third column and first row.
lcd.print(" mA"); // Print the string "Hello World!
}else{
Serial.print(" Irms = ");
Serial.println(Irms);
lcd.setCursor(0, 0); // Set the cursor on the third column and first row.
lcd.print("Corriente AC:"); // Print the string "Hello World!
lcd.setCursor(0, 1); // Set the cursor on the third column and first row.
lcd.print(Irms); // Print the string "Hello World!
lcd.setCursor(4, 1); // Set the cursor on the third column and first row.
lcd.print(" A"); // Print the string "Hello World!
}

}