#define PULSE_TIMEOUT   150000L // 150ms

#define BUZZER_PIN      8
#define TRIGGER_PIN     9
#define ECHO_PIN        10

#define BEEP_RANGE      33 // in cm

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

void fast_beep()
{
        tone(BUZZER_PIN, 1000);
        delay(50);
        noTone(BUZZER_PIN);
        delay(50);
}

void medium_beep()
{
        tone(BUZZER_PIN, 1000);
        delay(100);
        noTone(BUZZER_PIN);
        delay(100);
}

void slow_beep()
{
        tone(BUZZER_PIN, 1000);
        delay(100);
        noTone(BUZZER_PIN);
        delay(1000);
}

void loop()
{ 
    int dist = distance();

    if (dist <= BEEP_RANGE) {
        if (dist > 18 && dist <= 33) {
          slow_beep();
        }
        else if (dist > 8 && dist <= 18) {
          medium_beep();
        }
        else if (dist <= 8) {
          fast_beep();
        }
    }
}
