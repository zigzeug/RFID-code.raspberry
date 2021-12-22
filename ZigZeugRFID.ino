//Bismillah
//AET A.Mbaye14018
//les librairie à utiliser
#include <Adafruit_Fingerprint.h>
#include <SPI.h>
#include <RFID.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>



// la connexion à Ethernet
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 218);

//les constantes
const char DOUT_LED_ROUGE = 4;
const char DOUT_LED_VERTE = 5;
//var
int buzzer = 6;

SoftwareSerial mySerial(2, 3);
RFID monModuleRFID(10,9);

int UID[5]={};
int MASTERKEY[5]={147,51,100,2,198,};



Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


void setup()
{
  //initilalisations 
  Serial.begin(9600);
  SPI.begin();
  finger.begin(57600);
  monModuleRFID.init();
  
  //connexion à Ethernet
  Ethernet.begin(mac, ip);
  EthernetServer server(80);

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
    

  //les pins de sortie 
  pinMode(DOUT_LED_ROUGE, OUTPUT);
  pinMode(DOUT_LED_VERTE, OUTPUT);
  digitalWrite(DOUT_LED_ROUGE, LOW);
  digitalWrite(DOUT_LED_VERTE, LOW);

}



uint8_t p = finger.fingerSearch();


void loop()
{
    if (monModuleRFID.isCard()) {  
          if (monModuleRFID.readCardSerial() && p == FINGERPRINT_OK) {        
            Serial.print("L'UID est: ");
            for(int i=0;i<=4;i++)
            {
              UID[i]=monModuleRFID.serNum[i];
              Serial.print(UID[i],DEC);
              Serial.print(".");
            }
            Serial.println("");
          }
          
          if (UID[0] == MASTERKEY[0]
           && UID[1] == MASTERKEY[1]
           && UID[2] == MASTERKEY[2]
           && UID[3] == MASTERKEY[3]
           && UID[4] == MASTERKEY[4])
          {
              digitalWrite(DOUT_LED_VERTE, HIGH);
              tone(buzzer, 50);
              delay(200);
              digitalWrite(DOUT_LED_VERTE, LOW);
              noTone(buzzer);
          }
          else
          {
              digitalWrite(DOUT_LED_ROUGE, HIGH);
              tone(buzzer, 50);
              delay(200);
              digitalWrite(DOUT_LED_ROUGE, LOW);
              noTone(buzzer);
          }          
          monModuleRFID.halt();
    }
    delay(1);    
}


                                                    //Alhamdoulilah
                                                    //ZigZeug 1er du nom
                                                    //Jobs Jr
