//PRACTICA 14
//USUARIOS
//INSTRUMENTACION 
//TECNM COLIMA ENE-JUN 2024

#include <16F877a.h> //Libreria de controladores del PIC a utilizar
#device ADC=10 //Utilizar ADC
#use delay(crystal=20Mhz) //Utilizar cristal de 20 MegaHertz
#FUSES NOWDT, NOBROWNOUT, NOLVP
#include <math.h> //Libreria para realizar operaciones matematicas 

#include <lcd_c.c> //Libreria de LCD en el puerto    

void main (){

   //Definimos variables

   int16 raw_input=0; //ADC
   float voltage_conv, max_val=0; //Conversion de voltage & voltage rms
   
   setup_adc(ADC_CLOCK_INTERNAL); //Inicializamos el reloj interno del ADC
   setup_adc_ports(AN0_AN1_AN3); //Declaramos la entrada A0 del PIC para la lectura del ADC
   
   lcd_init();//Inicializamos el lcd
   
   printf(lcd_putc,"\fDC VOLTMETER \nVer.2.0"); // Imprimimos un pequeno mensaje por 1 segundo
   delay_ms(1000);
   
   //Peque�a impresion de LCD
   
   while(true){
   max_val=0; //reseteamos ambos valores
   raw_input=0;
   for (int16 i=0; i<300; i++){ //300 iteraciones de lectura
        set_adc_channel(1); //Inicializamos el puerto A0
        raw_input = read_adc(); //leemos el adc y lo guardamos en la variable
        voltage_conv = (4.91 * (float)raw_input/1023.0)*5.0; //hacemos la conversion a voltaje real
        delay_us(20); 
        max_val=voltage_conv*voltage_conv+max_val;// con esos valores de voltaje obtenemos el voltaje promedio o rms 
       }
   if(raw_input>1021){ //limitar el valor del adc a 24.5 v que es el valor que mas da
      printf(lcd_putc,"\fADC = above reading capacity"); //Mostrar en lcd que se pas� de el voltaje recomendado
      setup_adc(ADC_OFF);//apagar adc por proteccion
      }
      if(raw_input<=1021){ //si el adc es menor al limite, imprimir
      printf(lcd_putc,"\fVoltage: %2.1f V",sqrt(max_val/300)); //imprimimos el rms
      printf(lcd_putc,"\nADC = %4lu",raw_input); //observamos los valores recibidos del adc mostrandolos en el lcd tambien
      }
      setup_adc(ADC_CLOCK_INTERNAL);//volver a prender adc
    }
   }
   //En nuestro while(true) hacemos una iteracion de 300 conteos donde leemos el valor del ADC,
   //basados en el divisor de voltage y la resolucion del ADC obtenemos el valor de conversion del ADC y lo convertimos a voltaje
   //con esto obtenemos el valor RMS que es como un promedio de los diferentes voltajes obtenidos
   //imprimimos en pantalla y reiniciamos conteo.

   



