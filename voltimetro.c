//display      A  B  C  D  E  F  G DP                            
//terminales  B7 B5 B2 B1 B3 B4 B6 B0  B7 B6 B5 B4 B3 B2 B1 B0   PORT_B
//      CERO   1  1  1  1  1  1  0      1  0  1  1  1  1  1  0    0xBE   
//       UNO   0  1  1  0  0  0  0      0  0  1  0  0  1  0  0    0x24   
//       DOS   1  1  0  1  1  0  1      1  1  1  0  1  0  1  0    0xEA 
//      TRES   1  1  1  1  0  0  1      1  1  1  0  0  1  1  0    0xE6 
//    CUATRO   0  1  1  0  0  1  1      0  1  1  1  0  1  0  0    0x74 
//    CINCO    1  0  1  1  0  1  1      1  1  0  1  0  1  1  0    0xD6 
//     SEIS    1  0  1  1  1  1  1      1  1  0  1  1  1  1  0    0xDE 
//    SIETE    1  1  1  0  0  0  0      1  0  1  0  0  1  0  0    0xA4 
//     OCHO    1  1  1  1  1  1  1      1  1  1  1  1  1  1  0    0xFE  
//    NUEVE    1  1  1  1  0  1  1      1  1  1  1  0  1  1  0    0xF6  

#include <16F886.h>
#device ADC=10 
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=20000000)

#use fast_io(A)
#use fast_io(B)
#use fast_io(C)

void number (char numero)
{
   switch (numero){
      case 0:
         output_b (0xBE);
         break;
      case 1:
         output_b (0x24);
         break;
      case 2:
         output_b (0xEA);
         break;
      case 3:
         output_b (0xE6);
         break;
      case 4:
         output_b (0x74);
         break;
      case 5:
         output_b (0xD6);
         break;
      case 6:
         output_b (0xDE);
         break;
      case 7:
         output_b (0xA4);
         break;
      case 8:
         output_b (0xFE);
         break;
      case 9:
         output_b (0xF6);
         break;
   }
   
   delay_us(10);
}

void main ()
{ 
   int32 adc, volt, prom; 

   // DEFINICION DE ENTRADAS Y SALIDAS
   set_tris_a(0x01);
   set_tris_b(0x00);
   set_tris_c(0x00);
   
   // SETEO DE VALORES DE LAS SALIDAS.
   output_a (0x00);
   output_b (0x00);
   output_c (0x00);
   
   //SETEO DEL ADC.
   setup_adc_ports(sAN0);  
   setup_adc(ADC_CLOCK_DIV_32);
   set_adc_channel(0);
    
   while(1)
   {
      for (i=0, i<4; i++){
         //Tomo valor de ADC.
         adc = read_adc();
         delay_us(10);
         volt = (adc*280)/1023;
         //Acumulos los valores de tension para hacer el promedio.
         prom += volt;
      }
      //aca hago el promedio.
      prom /= 5;
      
      //DISPLAY 1
      output_low  (PIN_C2);
      delay_us(10);
      //SETEO VALOR
      number (prom%10);    //unidad.
      //ENCIENDO DISPLAY.
      output_high (PIN_C0);
      delay_ms(5);
   
      //DISPLAY 2
      output_low  (PIN_C0);
      delay_us(10);
      //SETEO VALOR
      number ((prom/10)%10);          //decena.
      output_high (PIN_B0);           //punto.
      delay_us(10);
      //ENCIENDO DISPLAY
      output_high (PIN_C1);
      delay_ms(5);
   
      //DISPLAY 3
      output_low  (PIN_C1);
      delay_us(10);
      //SETEO VALOR
      number (prom/100);   //centena.
      output_low  (PIN_B0);//punto.
      delay_us(10);
      //ENCIENDO DISPLAY
      output_high (PIN_C2);
      delay_ms(10);
   }
}

