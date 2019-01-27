// -----------------------------------------
// Subscriber Code Demo
/* -----------------------------------------
    Subscribe to an event and assume all 
    data that comes in is numeric.
    Convert the string data to an integer
    and flash an LED that number of times.
------------------------------------------*/
#include <math.h>
#include <cmath>
#define earthRadiusKm 6371.0

int pinA = D1;
int pinB = D3;
// int pinC = D3;
int tStart = millis();
int tEnd = millis();


volatile bool TractorLatTrigger = 0;
volatile bool TractorLonTrigger = 0;
volatile bool TrailerLatTrigger = 0;
volatile bool TrailerLonTrigger = 0;
volatile int TractorLat;
volatile int TractorLon;
volatile int TrailerLat;
volatile int TrailerLon;

void setup() {
    
  // Setup GPIO
  pinMode(pinA,OUTPUT);
  pinMode(pinB,OUTPUT);
//   pinMode(pinC,OUTPUT);
  
  digitalWrite(pinA,LOW);
  digitalWrite(pinB,LOW);
//   digitalWrite(pinC,LOW);
  
  // Subscribe to an event published by our second Raspberry Pi (or other device!)
  Particle.subscribe("Tractor_Lat", myHandlerTractorLat, MY_DEVICES);
  Particle.subscribe("Tractor_Lon", myHandlerTractorLon, MY_DEVICES);
  Particle.subscribe("Trailer_Lat", myHandlerTrailerLat, MY_DEVICES);
  Particle.subscribe("Trailer_Lon", myHandlerTrailerLon, MY_DEVICES);
  // The MY_DEVICES argument means that only events published by devices registered to this Particle Cloud account will be accepted.
}

void loop() {
    // Subscribe to an event published by our second Raspberry Pi (or other device!)
    // Particle.subscribe("Tractor_Info", myHandler, MY_DEVICES);
    // if (trigger) { // trigger is set TRUE in the event handler
    //     digitalWrite(pinA,HIGH);
    // }
    delay(1000);
    
    if (TractorLatTrigger && TractorLonTrigger && TrailerLatTrigger && TrailerLonTrigger){
        // Particle.publish("Data_Received","Got Data!",PRIVATE);

        
        // Particle.publish("test",String(distanceM(TractorLat, TractorLon, TrailerLat, TrailerLon)),PRIVATE);
        // float temp = distanceM(TractorLat, TractorLon, TrailerLat, TrailerLon);
        // float compare = abs(30.0);
        // int comparasion=(int)(0.0<(temp-30));
        // bool temp2 = (temp-compare)>0;
        //Particle.publish("temp",String(temp),PRIVATE);
        //Particle.publish("compare",String(compare),PRIVATE);
        // Particle.publish("tempCompare",String(temp2),PRIVATE);
        
        
        
        int newTemp = fakeCheck(TractorLat, TractorLon, TrailerLat, TrailerLon);
        // constrain(newTemp, 30, 99);
        // Particle.publish("fakeCheck",String(newTemp),PRIVATE);
        
        if(newTemp > 30) {
            tooFar();
        }
        else{
            normal();
        }
        
        TractorLatTrigger = 0;
        TractorLonTrigger = 0;
        TrailerLatTrigger = 0;
        TrailerLonTrigger = 0;
        
        tStart = millis();
        tEnd = millis();
    }
    
    if(abs(tEnd-tStart) > 15000){
        disconnected();
    }
    
    tEnd = millis();
        
        
    // normal();
    // delay(5000);
    // high();
    // delay(5000);
    // low();
    // delay(5000);
    // disconnected();
    // delay(5000);
}

float toRad(float degrees) {
    return (degrees*3.1415926/180);
}

double fakeCheck(double Lat1, double Lon1, double Lat2, double Lon2){
    double dLat = toRad(Lat1-Lat2);
    double dLon = toRad(Lon1-Lon2);
    double earthR = 6371000;
    double dist = sqrt((dLat*earthR)*(dLat*earthR) + (dLon*earthR)*(dLon*earthR));
    return dist;
}

// float distanceM(float Lat1, float Lon1, float Lat2, float Lon2) {
//     float lat1r, lon1r, lat2r, lon2r, u, v;
//     lat1r = toRad(Lat1);
//     lon1r = toRad(Lon1);
//     lat2r = toRad(Lat2);
//     lon2r = toRad(Lon2);
    
//     u = sin((lat2r - lat1r)/2);
//     v = sin((lon2r - lon1r)/2);
//     float result =  2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
//     Particle.publish("Distance",String(result),PRIVATE);
//     return result;
    
    
    // float earthR = 6371000; //in metres
    // float dLat = Lat2-Lat1;
    // float dLon = Lon2-Lon1;
    // float a = (sin(dLat/2)*sin(dLat/2) + cos(Lat1)*cos(Lat2)*sin(dLon/2)*sin(dLon/2));
    // float c = 2*atan2(sqrt(a), sqrt(abs(1-a)));
    // return earthR*c;
    
    // float EarthRad=6371;
    // float dLat=toRad(Lat2-Lat1);
    // float dLon=toRad(Lon2-Lon1);
    
    // Lat1=toRad(Lat1);
    // Lat2=toRad(Lat2);
    
    // float a = sin(dLat/2)*sin(dLat/2)+sin(dLon/2)*sin(dLon/2)*cos(Lat1)*cos(Lat2);
    // float c = 2*atan2(sqrt(a),sqrt(1-a));
    // return EarthRad*c;
// }


void normal(){
  digitalWrite(pinA,HIGH);
  digitalWrite(pinB,LOW);
//   Particle.publish("normal","normal",PRIVATE);
//   digitalWrite(pinC,LOW);
}

void tooFar(){
  digitalWrite(pinA,LOW);
  digitalWrite(pinB,HIGH);
//   Particle.publish("too far","too far",PRIVATE);
//   digitalWrite(pinC,LOW);
}

// void low(){
//   digitalWrite(pinA,LOW);
//   digitalWrite(pinB,LOW);
//   digitalWrite(pinC,HIGH);    
// }

void disconnected(){
  digitalWrite(pinA,LOW);
  digitalWrite(pinB,LOW);
//   digitalWrite(pinC,LOW);
}

void myHandlerTractorLat(const char *event, const char *data)
{
    String temp = data;
    temp.trim();
    TractorLat = temp.toInt();
    TractorLatTrigger = 1;
    // Particle.publish("myHandlerTractorLat",String(TractorLat),PRIVATE);
    //int yes = dataVar.toInt();// Load data, which is a constant into a string variable
    // if (yes == 50) {
    //     Tractortrigger = 1;
    //     String dataString = "yes";
    //   // Particle.publish("Recieved_Data",dataString,PRIVATE);
    // } else {
    //     Tractortrigger = 0;
    // }
}

void myHandlerTractorLon(const char *event, const char *data)
{
    String temp = data;
    temp.trim();
    TractorLon = temp.toInt();
    TractorLonTrigger = 1;
    // Particle.publish("myHandlerTractorLon",String(TractorLon),PRIVATE);
//     //int yes = dataVar.toInt();// Load data, which is a constant into a string variable
//     // if (yes == 50) {
//     //     TractorLonTrigger = 1;
//     //     String dataString = "yes";
//     //   // Particle.publish("Recieved_Data",dataString,PRIVATE);
//     // } else {
//     //     Tractortrigger = 0;
//     // }
}

void myHandlerTrailerLat(const char *event, const char *data)
{
    String temp = data;
    temp.trim();
    TrailerLat = temp.toInt();
    TrailerLatTrigger = 1;
    // Particle.publish("myHandlerTrailerLat",String(TrailerLat),PRIVATE);
//     //int yes = dataVar.toInt();// Load data, which is a constant into a string variable
//     // if (yes == 50) {
//     //     TrailerTrigger = 1;
//     //     String dataString = "yes";
//     //     //Particle.publish("Recieved_Data",dataString,PRIVATE);
//     // } else {
//     //     Trailertrigger = 0;
//     // }
}

void myHandlerTrailerLon(const char *event, const char *data)
{
    String temp = data;
    temp.trim();
    TrailerLon = temp.toInt();
    TrailerLonTrigger = 1;
    // Particle.publish("myHandlerTrailerLon",String(TrailerLon),PRIVATE);
//     //int yes = dataVar.toInt();// Load data, which is a constant into a string variable
//     // if (yes == 50) {
//     //     Trailertrigger = 1;
//     //     String dataString = "yes";
//     //     //Particle.publish("Recieved_Data",dataString,PRIVATE);
//     // } else {
//     //     Trailertrigger = 0;
//     // }
}