#include <Servo.h>
#include <Adafruit_NeoPixel.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

#define PIN        6 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 16 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels


void setup() {

  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(9600);        // initialize serial

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  //pixels.clear();
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH

    delay(100);                // delay 100 milliseconds

    Serial.println("Motion detected!");

    myservo.write(90);

    for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(i, pixels.Color(0, 255, 255));

      pixels.show();   // Send the updated pixel colors to the hardware.

      delay(50); // Pause before next pass through loop
    }

  }
  else {

    delay(200);             // delay 200 milliseconds


    Serial.println("Motion stopped!");
    // state = LOW;       // update variable state to LOW
    myservo.write(0);

    for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(i, pixels.Color(255, 0, 255));

      pixels.show();   // Send the updated pixel colors to the hardware.

      delay(50); // Pause before next pass through loop
    }
  }


  Serial.println(val);


}
