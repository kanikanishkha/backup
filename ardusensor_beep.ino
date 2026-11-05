#define PULSE_TIMEOUT   150000L // 150ms

#define BUZZER_PIN      8
#define TRIGGER_PIN     9
#define ECHO_PIN        10

#define BEEP_RANGE      0       // in cm

int duration;

/**
 * This function is the entry point for the arduino program and it sets the
 * modes for the pins of external components
 */
void setup()
{
    Serial.begin(19200);   
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

/**
 * This function sends an ultrasonic wave and returns distance once
 * the reflected signal is returned
 */
long distance()
{
    // Prepares the trigger pin
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);

    // Sends an ultrasonic sound wave for 10 microseconds
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    
    // Receives the reflected signal
    duration = pulseIn(ECHO_PIN, HIGH, PULSE_TIMEOUT);
    delay(25);
    
    // Returns calculated distance
    return duration / 58;
}

void loop()
{   
    if (distance() <= BEEP_RANGE) {
        // Make the buzzer beep for 1s at 1000Hz
        tone(BUZZER_PIN, 1000);
        delay(1000);
        noTone(BUZZER_PIN);
        delay(1000);
    }
}
