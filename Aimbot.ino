///////// kalla på biblotek
#include <Servo.h> /servo bibliotek
#include <stdio.h> // matte 
#include <math.h> //matte


#define laserPin 10 //definera att laserpin är  på arduinon


int pos = 0;          // definiera integern pos som 0
int minsta = 10000;   // defeniera integern minsa som 10000
float grad = 0;       //definiera float grad som 0
float lasergrad = 0;  //definiera float lasergrad som 0

//////// definiera in värden

Servo myservo1;       //definiera servon myservo1
Servo myservo2;       //definiera servon myservo2
#define echoPin 6     //deiniera vilken pin Echo från ultrljudsensorn har på arduinon 
#define trigPin 7     //definiera vilken pin trig från ultraljudsensorn har på arduinon

// defines variables
long duration;        // Variabeln för hur länge ljudvågen har åkt
int distance;         // variablen for distansen 


void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);                         // Sätter trigpinen som en OUTPUT
  pinMode(echoPin, INPUT);                          // Sätter echoPin som en INPUT
  Serial.begin(9600);                               // Startar Serial Communication med 9600 bauds hastighet 
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // Skriver ut text i serial monitor
  Serial.println("with Arduino UNO R3");            // skriver ut text i serial monitor


  pinMode(laserPin, OUTPUT);                        //sätter laserpin som en OUTPUT

  ///// outputs och inputs osv
  myservo1.attach(9);                               // definierar vilken pin servo1 är kopplad till
  myservo2.attach(5);                               // definierar vilken pin servo2 är kopplad till


  digitalWrite(laserPin, HIGH);                     // sätter digitalwrite laserpin som HIGH


}

void loop() {
  // Huvudkod som kommer köra om och om igen
  minsta = 10000;
  
  for (pos = 0 ; pos <= 180; pos += 2) {    // för pos = 0 gäller om pos mer än eller lika med 180 och adderar 2 grader till pos varje gång den körs
   
    digitalWrite(trigPin, LOW);             //Trigpin sätts som LOW för att kunna få ett mer exakt värde 
    delayMicroseconds(2);                   // Fördröjer  2 millisekunder
                                           
    digitalWrite(trigPin, HIGH);            // trigPin sätts som HIGH och ett värde i millisekunder

    delayMicroseconds(10);                  // Fördröjer 10 millisekunder
    digitalWrite(trigPin, LOW);             // trigpin sätts som LOW och förbereds för nytt värde

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);      // Duration blir lika med tiden ljudvågorna färdades fram och tillbaka
    // Calculating the distance
    distance = duration * 0.034 / 2;        // Distans blir lika med tiden * 0.034 för att gå från tid till distans som sedan divideras med två för fram och tillbaka
   
    
    if (distance < minsta && distance != 0) { // if statement om distance är mindre än minsta och distans inte är lika med 0 
      minsta = distance;                      // blir minsta=distance
      grad = pos;                             // grad blir lika med pos för att se gradtalet där ett nytt värde hittades

      
      
      grad = grad * 0.0174532925;             // Gör om grad till grad i radian genom att multiplicera med 0.0174532925
      
      
      lasergrad = atan((sin(grad) * minsta) / (cos(grad) * minsta + 4)); // Graden för där servon där lasern sitter på ska bli genom trigonometri


      lasergrad = lasergrad * 57.2957792; // eftersom lasergrad är i radian gör vi om det till grader för att kunna ge myservo2 en posistion att gå till
      grad = grad * 57.2957792;           // grad som koverteras tillbaka till grader från radian
      Serial.print("grad: ");             //skriver ut "grad" i serial monitor
      Serial.println(pos);                //skriver ut värdet för pos alltså graden i serial monitor
      Serial.print("lasergrad: ");        //skriver ut "lasergrad" i serial monitor
      Serial.println(lasergrad);          //skriver ut värder för lasergrad alltså vilken grad myservo2 ska ha för lasern

    }

    myservo2.write(lasergrad);            // Säger åt myservo2 att gå till lasergrad som är ett gradvärde
    delay(100);

    myservo1.write(pos);                  // Säger åt myservo1 att gå till pos gradvärde
    delay(100);


  }
  

}
