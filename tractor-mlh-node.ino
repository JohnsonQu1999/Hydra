// -----------------------------------------
// Publisher Code Demo
/* -----------------------------------------
    Each time a button is pressed, publish
    the total number of button-presses to
    an event. 
------------------------------------------*/

// GPIO Definitions
float locationLat = 50; // Stores the number of times the flash-button is pressed
float locationLon = 60;

// Setup GPIO
void setup() {
    
}

// Poll the button status, increment or reset the counter, publish the count.
void loop() {
    String dataStringLat = String(locationLat);
    String dataStringLon = String(locationLon);
    Particle.publish("Tractor_Lat", dataStringLat, PRIVATE);
    Particle.publish("Tractor_Lon", dataStringLon, PRIVATE);
    delay(5000);
}