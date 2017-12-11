//arduino pin numbers from which the LEDs are getting power
int yellowLedPin = 9;
int redLedPin = 8;
int greenLedPin = 10;
int redLedPin2 = A2;
int yellowLedPin2 = A4;   
int greenLedPin2 = A0;
int yellowLedPin3 = A1;
int redLedPin3 = A3;
int greenLedPin3 = A5;
int redLedPin4 = 12;
int yellowLedPin4 = 11;
int greenLedPin4 = 13;

//transmit and receive arduino pin numbers, connected to receive and transmit pins of gsm module, respectively
int transmitPin = 5; //8
int receivePin = 3; //5

long startTime = millis();

boolean restart_seq=false;
long finishTime = 12000;


boolean isMsgRcvdPrv=false;

char msg; 

char gsmoutput;


    #include <SoftwareSerial.h>
    SoftwareSerial mySerial(receivePin, transmitPin);

  
void setup() {

   Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
   mySerial.begin(9600); // Setting the baud rate of GSM Module 

   mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command for GSM module to recieve a live SMS
   delay(200); // putting delay for the serial to become available
   
   while (mySerial.available() > 0) {
      gsmoutput = mySerial.read();
      Serial.print(gsmoutput); //printing AT command
   }

   pinMode(yellowLedPin, OUTPUT);
   pinMode(redLedPin, OUTPUT);
   pinMode(greenLedPin, OUTPUT);
   pinMode(redLedPin2, OUTPUT);
   pinMode(yellowLedPin2, OUTPUT);
   pinMode(greenLedPin2, OUTPUT);

   pinMode(redLedPin3, OUTPUT);
   pinMode(yellowLedPin3, OUTPUT);
   pinMode(greenLedPin3, OUTPUT);
   pinMode(redLedPin4, OUTPUT);
   pinMode(yellowLedPin4, OUTPUT);
   pinMode(greenLedPin4, OUTPUT);


   digitalWrite(redLedPin2, HIGH);
   digitalWrite(redLedPin3, HIGH);
   digitalWrite(redLedPin4, HIGH);
}


void loop() {

   if(restart_seq){
   digitalWrite(yellowLedPin, HIGH);
   delay(2000);
   digitalWrite(yellowLedPin, LOW);
   digitalWrite(redLedPin, LOW);
   }
   restart_seq=false;
   
   if(!restart_seq)
   turnOnLED(greenLedPin,redLedPin4,redLedPin,finishTime);
   if(!restart_seq)
   turnOnYellowLED(yellowLedPin,yellowLedPin2,redLedPin3);
   if(!restart_seq)
   turnOnLED(greenLedPin3,redLedPin,redLedPin3,finishTime);
   if(!restart_seq)
   turnOnYellowLED(yellowLedPin3,yellowLedPin2,redLedPin2);
   if(!restart_seq)
   turnOnLED(greenLedPin2,redLedPin3,redLedPin2,finishTime);
   if(!restart_seq)
   turnOnYellowLED(yellowLedPin3,yellowLedPin4,redLedPin4);
   if(!restart_seq)
   turnOnLED(greenLedPin4,redLedPin2,redLedPin4,finishTime);
   if(!restart_seq)
   turnOnYellowLED(yellowLedPin4,yellowLedPin,redLedPin);
   



}
 
  

  
   void turnOnLED(int gpin, int rpin, int grpin, int finish) {
  
   int msgpin;
   int msgpiny;
   int msgpinr;
  
   digitalWrite(gpin, HIGH);
   digitalWrite(rpin, HIGH);
   
   
   long elasped = millis() - startTime;
   while (millis() - elasped < finish) { 
   // long passed=millis() - elasped;
    if (mySerial.available() > 0&&!isMsgRcvdPrv){
        // Serial.println("eceived");
         delay(100);
         
       
        while (mySerial.available() > 0)
        {
        gsmoutput = mySerial.read();
        if(gsmoutput==('A')||gsmoutput==('B')||gsmoutput==('X')||gsmoutput==('D'))
        {
        msg=gsmoutput;
        }
        }
    
        

        isMsgRcvdPrv=true;
        
          
        
       
        
        
        if((msg=='A' && gpin==greenLedPin)||(msg=='B' && gpin==greenLedPin2)||(msg=='X' && gpin==greenLedPin3)||(msg=='D' && gpin==greenLedPin4)){

         startTime = 0;
         elasped = millis() - startTime;

         if(msg=='A'){
        msgpin=greenLedPin;
        msgpiny=redLedPin;
        msgpinr=yellowLedPin;
         }
         else if(msg=='B'){
        msgpin=greenLedPin3;
        msgpiny=redLedPin3;
        msgpinr=yellowLedPin2;
         }
         else if(msg=='X'){
        msgpin=greenLedPin2;
        msgpinr=redLedPin2;
        msgpiny=yellowLedPin3;
         }
         else if(msg=='D'){
        msgpin=greenLedPin4;
        msgpinr=redLedPin4;
        msgpiny=yellowLedPin4;
         }
        }
        
        else if(msg=='A')
         {
        testme();
        digitalWrite(gpin, LOW);
        digitalWrite(grpin, HIGH);
        digitalWrite(redLedPin, LOW);
        digitalWrite(greenLedPin, HIGH);
        startTime = 0;
        elasped = millis() - startTime;
        msgpin=greenLedPin;
        msgpiny=redLedPin;
        msgpinr=yellowLedPin;
         }
       
        else  if(msg=='B')
       {
        testme();
        digitalWrite(gpin, LOW);
        digitalWrite(grpin, HIGH);
        digitalWrite(redLedPin3, LOW);
        digitalWrite(greenLedPin3, HIGH);// reset timer
        msgpin=greenLedPin3;
        startTime = 0;
        elasped = millis() - startTime;
        msgpin=greenLedPin3;
        msgpiny=redLedPin3;
        msgpinr=yellowLedPin2;
       }
   
    else if(msg=='X')
      {
        Serial.println(msg);
        testme();
        digitalWrite(gpin, LOW);
        digitalWrite(grpin, HIGH);
        digitalWrite(redLedPin2, LOW);
        digitalWrite(greenLedPin2, HIGH);// reset timer
        msgpin=greenLedPin2;
        startTime = 0;
        elasped = millis() - startTime;
        msgpin=greenLedPin2;
        msgpinr=redLedPin2;
        msgpiny=yellowLedPin3;
      }
      
    else if(msg=='D')
      {
        testme();
        digitalWrite(gpin, LOW);
        digitalWrite(grpin, HIGH);
        digitalWrite(redLedPin4, LOW);
        digitalWrite(greenLedPin4, HIGH);// reset timer
        msgpin=greenLedPin4;
        startTime = 0;
        elasped = millis() - startTime;
        msgpin=greenLedPin4;
        msgpinr=redLedPin4;
        msgpiny=yellowLedPin4;
      }
     
      
    }
     
    
   }
  
   if((isMsgRcvdPrv)){
      Serial.println("isMsgeceiveds");
      isMsgRcvdPrv=false;
      digitalWrite(msgpin, LOW);
      digitalWrite(msgpiny, HIGH);
      delay(2000);
      digitalWrite(msgpiny, LOW);
      digitalWrite(redLedPin, HIGH);
      digitalWrite(redLedPin2, HIGH);
      digitalWrite(redLedPin3, HIGH);
      digitalWrite(redLedPin4, HIGH);
      restart_seq=true;
      
    }
   

   digitalWrite(gpin, LOW);
   
  

   
}

void turnOnYellowLED(int pin, int pin2, int pin3) {

  
   digitalWrite(pin, HIGH);
   digitalWrite(pin2, HIGH);
   
   
   delay(2000);


   digitalWrite(pin, LOW);
   digitalWrite(pin2, LOW);
   digitalWrite(pin3, LOW);
}

void testme(){
    for(int i=0;i<3;i++){
              digitalWrite(yellowLedPin, HIGH);
              digitalWrite(yellowLedPin2, HIGH);
              digitalWrite(yellowLedPin3, HIGH);
              digitalWrite(yellowLedPin4, HIGH);
              delay(500);
              digitalWrite(yellowLedPin, LOW);
              digitalWrite(yellowLedPin2, LOW);
              digitalWrite(yellowLedPin3, LOW);
              digitalWrite(yellowLedPin4, LOW);
              delay(500);
            }
}

