

uint8_t LED_Pin = D0;       // declare LED pin on NodeMCU Dev Kit
uint8_t LED_Pin_1=D4;       // Declare LED pin on 
void setup() {
Serial.begin(9600);
pinMode(LED_Pin, OUTPUT);   // Initialize the LED pin as an output
pinMode(LED_Pin_1, OUTPUT);
}

void loop() {
digitalWrite(LED_Pin, LOW);
digitalWrite(LED_Pin_1,HIGH);// Turn the LED on
Serial.println("the D0 low and D4 high");
delay(800);                // Wait for a second
digitalWrite(LED_Pin, HIGH);// Turn the LED off
digitalWrite(LED_Pin_1,LOW);
Serial.println("the D0 high and D4 low");
delay(500);                // Wait for a second
}
