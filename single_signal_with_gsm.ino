    
    //arduino pin numbers from which yellow, red and green LEDs are getting power
    int yellowLedPin=12;
    int redLedPin=13;
    int greenLedPin=11;
    
    
    //transmit and receive arduino pin numbers, connected to receive and transmit pins of gsm module, respectively
    int transmitPin=3;//8
    int receivePin=2;//5
    
    //the number of times red LED loop runs, approx 10 seconds
    long startTime=0;
    long finishTime=100000;
    long finishTimeYellow=25000;
    
    //storing live message(message received when gsm module is connected to network) received by gsm module
    char msg;

    #include <SoftwareSerial.h>
    SoftwareSerial mySerial(receivePin, transmitPin);

    void setup() {

     Serial.begin(9600);                           // Setting the baud rate of Serial Monitor (Arduino)
     mySerial.begin(9600);                         // Setting the baud rate of GSM Module 
      
     mySerial.println("AT+CNMI=2,2,0,0,0\r");        // AT Command for GSM module to recieve a live SMS
     delay(200);                                   // putting delay for the serial to become available
     while (mySerial.available()>0)
     {
     msg=mySerial.read();
     Serial.print(msg);                            //printing AT command
     }
     
     pinMode(yellowLedPin,OUTPUT);
     pinMode(redLedPin,OUTPUT);
     pinMode(greenLedPin,OUTPUT);

    }

    void loop() {

     digitalWrite(redLedPin,HIGH);
     while(startTime<finishTime){
     if(startTime==75000){
     digitalWrite(yellowLedPin,HIGH);
     }
     if(mySerial.available()>0){
     interrupt();
     digitalWrite(redLedPin,HIGH);
     startTime=0;
     }
     
     
     startTime++;
     }

     /////////////////
     startTime=0;
     
     digitalWrite(redLedPin,LOW);
     
     while(startTime<finishTimeYellow){
     
     if(mySerial.available()>0){
     interrupt();
     break;
     }
     startTime++;
     }

     ///////////////////
     startTime=0;
     digitalWrite(yellowLedPin,LOW);
    

     digitalWrite(greenLedPin,HIGH);
     while(startTime<finishTime){
     
     if(mySerial.available()>0){
     interrupt();
     break;
     }
     startTime++;
     }
     ///////////////
     startTime=0;
     digitalWrite(greenLedPin,LOW);
 
   }

    void interrupt(){
 
     msg=mySerial.read();
     if(msg!=' '){
   
     digitalWrite(redLedPin,LOW);
     digitalWrite(yellowLedPin,LOW);
     digitalWrite(greenLedPin,HIGH);
    
     delay(5000);
     digitalWrite(greenLedPin,LOW);
    
     while(mySerial.available()>0){
      char t=mySerial.read();
      Serial.print(t); 
      
     }
     msg=' ';
    
   }

}

