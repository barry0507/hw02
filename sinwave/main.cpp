#include "mbed.h"
#include "math.h"
Serial pc( USBTX, USBRX );
AnalogOut Aout(DAC0_OUT);
AnalogIn Ain(A0);

//7segs
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);

//SW,LED
DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);


char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int i;
float ADC_data[1010];

int main(){
 // int A[5] = {3,5,1,6,7};
  int count = 0;
  
  for( i=0;i<500;i++){
    ADC_data[i] = Ain;
    wait(0.002); 
  }
  for( i=0;i<500;i++){ 
    if(ADC_data[i]> ADC_data[i+1] && ADC_data[i]> ADC_data[i-1]) {count=count+1;}
    //pc.printf("%1.3f\r\n",ADC_data[i]);
    else {count = count;}
  }
  pc.printf("%d\r\n",count);
  int A[3]={count/100,(count-100)/10,count-100};
  while(1){ 
    for(float i=0; i<2000; i++ ){
        Aout = (sin(3.1415926*count*i/1000))/2+0.5;
        wait(1/2000);
    }    
    
    if(Switch == 0 ){  
     // if(Switch==1){break;} 
      greenLED = 0;
      redLED = 1;
      for( i=0;i<=2;i++){
        if(i == 2)
          display = table[A[i]]+0x80;
        else
          display = table[A[i]];
        wait(0.5);
      }
      
    }

    else{
      redLED = 0;
      greenLED = 1;
    }
  }
}

