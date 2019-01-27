// -----------------------------------------
// Publisher Code Demo
/* -----------------------------------------
    Each time a button is pressed, publish
    the total number of button-presses to
    an event. 
------------------------------------------*/

// GPIO Definitions
float locationLatGood = 50; // Stores the number of times the flash-button is pressed
float locationLonGood = 60;
float locationLatBad = 60;
float locationLonBad = 70;

int badDataButton = D4;

// Setup GPIO
void setup() {
    pinMode(badDataButton, INPUT);
    
}

// Poll the button status, increment or reset the counter, publish the count.
void loop() {
    
    if (digitalRead(badDataButton) == HIGH) {
        String dataStringLat = String(locationLatBad);
        String dataStringLon = String(locationLonBad);
        Particle.publish("Trailer_Lat",dataStringLat,PRIVATE);
        Particle.publish("Trailer_Lon",dataStringLon,PRIVATE);
    } else {
        String dataStringLat = String(locationLatGood);
        String dataStringLon = String(locationLonGood);
        Particle.publish("Trailer_Lat",dataStringLat,PRIVATE);
        Particle.publish("Trailer_Lon",dataStringLon,PRIVATE);
    }
    
    delay(5000);
    
    // String dataStringLatBad = String(locationLatBad);
    // String dataStringLonBad = String(locationLatBad);
    // Particle.publish("Trailer_Lat",dataStringLatBad,PRIVATE);
    // Particle.publish("Trailer_Lon",dataStringLonBad,PRIVATE);
    
    // delay(5000);
}