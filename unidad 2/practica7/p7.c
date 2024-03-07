//Practica 7

//Usuarios

//Encargado: Jos� Eduardo C�rdenas Ruiz
//Francisco Javier L�pez V�zquez 
//David V�zquez Reyes
//Adalberto Ram�rez Guti�rrez
//C�sar Eduardo Mart�nez Campa

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <16F877a.h>
// Esta l�nea incluye el archivo de cabecera espec�fico del microcontrolador PIC 16F877a.

#DEVICE ADC=10
// Esta l�nea establece la resoluci�n del convertidor anal�gico a digital (ADC) en 10 bits.

#USE delay(crystal=20Mhz)
// Esta l�nea configura una funci�n de demora utilizando un cristal de 20MHz como base de tiempo.

#fuses HS,NOWDT,NOPROTECT,PUT,NOLVP,NOBROWNOUT
// Esta l�nea configura los fusibles del microcontrolador seg�n las especificaciones dadas.

#use RS232(BAUD=9600, BITS=8, PARITY=N, XMIT=PIN_C6, RCV=PIN_C7)
// Esta l�nea configura la comunicaci�n serie RS232 con una velocidad de baudios de 9600, 8 bits de datos, sin paridad, y define los pines de transmisi�n (XMIT) y recepci�n (RCV).

#include <stdio.h>
// Esta l�nea incluye la librer�a est�ndar de E/S para el manejo de entradas y salidas.

#USE STANDARD_IO(B)
#USE STANDARD_IO(C)
#USE STANDARD_IO(D)
// Estas l�neas definen el uso de los puertos B, C y D como puertos de E/S est�ndar.

#DEFINE M1 PIN_E0
// Esta l�nea define el pin M1 como el pin E0.

#define LCD_DATA_PORT   0X07
#define LCD_ENABLE_PIN  PIN_C5
#define LCD_RS_PIN      PIN_C3
#define LCD_RW_PIN      PIN_C4
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7
// Estas l�neas definen los pines y el puerto para la conexi�n del LCD.

#include <lcd.c>
// Esta l�nea incluye el archivo de la librer�a para el control del LCD.

short High = 0;
// Esta l�nea declara una variable corta llamada High e inicializa su valor en 0.

int16 T_HIGH;
int16 T_LOW;
// Estas l�neas declaran variables de 16 bits llamadas T_HIGH y T_LOW.

char dato_rx;
// Esta l�nea declara una variable de tipo char llamada dato_rx.

int16 contador=0;
double porcentaje;
float RPM=0;
int dientes=32;
// Estas l�neas declaran variables de 16 bits (contador), double (porcentaje), float (RPM) e int (dientes) e inicializan sus valores.

#INT_EXT
void ext_isr(){
   contador++;
}
// Esta l�nea declara una rutina de servicio de interrupci�n externa que incrementa el contador cada vez que se produce una interrupci�n externa.

#INT_TIMER0
void ext_isr2(){
      if(porcentaje >= 100){
         set_timer0(T_HIGH);
         output_high(M1);
      return;
      }
      if(porcentaje == 0){
         set_timer0(T_HIGH);
         output_low(M1);
      return;
      }
      if(High){
       set_timer0(T_HIGH); 
       output_high(M1);
     }else{
       set_timer0(T_LOW);
       output_low(M1);
     }
   High++;
}
// Esta l�nea declara una rutina de servicio de interrupci�n para el temporizador 0 que controla la salida del motor.

#INT_RDA
void interrupcion_RDA(){
 
   dato_rx = getc();
   
   if(dato_rx=='j')
   {
        porcentaje = getc();
   }
}
// Esta l�nea declara una rutina de servicio de interrupci�n para la recepci�n de datos serie RS232.

void main(){
   input(PIN_B0);
// Esta l�nea configura el pin B0 como entrada.

   lcd_init();
// Esta l�nea inicializa el LCD.

   output_low(PIN_E0);
   output_low(PIN_E1);
// Estas l�neas establecen el estado bajo en los pines E0 y E1.

   enable_interrupts(INT_EXT);
   enable_interrupts(INT_RDA);
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
   ext_int_edge(H_TO_L);
   enable_interrupts(INT_TIMER0);
// Estas l�neas habilitan las interrupciones externas, las interrupciones para la recepci�n de datos serie RS232 y el temporizador 0.

   enable_interrupts(GLOBAL);
   set_timer0(255);
// Estas l�neas habilitan todas las interrupciones y establecen el valor inicial del temporizador 0.

   printf(lcd_putc,"AC MOTOR CONTROL \nMax RPM:3500");
   delay_ms(2500);
// Esta l�nea imprime un mensaje en el LCD y espera 2500 ms.

   while(1){
   lcd_gotoxy(1,1);
   printf(lcd_putc,"\fDuty Cicle: %lf \nRPM: %f",porcentaje, RPM);
   delay_ms(1000);
// Este bucle imprime el ciclo de trabajo y las RPM en el LCD cada segundo.

   RPM = ((float)contador*60) / (dientes);
// Esta l�nea calcula las RPM.

   lcd_gotoxy(1,1);
   printf(lcd_putc,"\fDC: %lf \nRPM: %f1.1",porcentaje, RPM);
// Esta l�nea imprime un mensaje en el LCD.
   
   contador=0;
// Reseteamos el contador.
 
   T_LOW= (int16)(((float)porcentaje*255.0)/100);
   T_HIGH =255-T_LOW;
// Esta l�nea define el tiempo en alto y el tiempo en bajo del PWM dependiendo del porcentaje.
  }
}
// End of Line
