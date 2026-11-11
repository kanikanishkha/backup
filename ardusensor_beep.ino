#define PULSE_TIMEOUT   150000L // 150ms

#define RED_PIN         5
#define GREEN_PIN       7
#define BLUE_PIN        6

#define BUZZER_PIN      8
#define TRIGGER_PIN     9
#define ECHO_PIN        10

/**
 * This function takes inputs for RGB values in the form of three
 * integers to light up the LED with color
 */
void setcolor(int R, int G, int B)
{
    analogWrite(RED_PIN, R);
    analogWrite(GREEN_PIN, G);
    analogWrite(BLUE_PIN, B);
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
    int duration = pulseIn(ECHO_PIN, HIGH, PULSE_TIMEOUT);
    delay(25);
    
    // Returns calculated distance
    return duration / 58;
}

/**
 * This is the beep function for green light
 */
void slow_beep()
{
    setcolor(0, 255, 0);
    tone(BUZZER_PIN, 1000);
    delay(100);
    noTone(BUZZER_PIN);
    delay(1000);
}

/**
 * This is the beep function for yellow light
 */
void medium_beep()
{
    setcolor(255, 255, 0);
    tone(BUZZER_PIN, 1000);
    delay(100);
    noTone(BUZZER_PIN);
    delay(100);
}

/**
 * This is the beep function for red light
 */
void fast_beep()
{
    setcolor(255, 0, 0);
    tone(BUZZER_PIN, 1000);
    delay(50);
    noTone(BUZZER_PIN);
    delay(50);
}

/**
 * This function is the entry point for the arduino program and it sets the
 * modes for the pins of external components
 */
void setup()
{
    Serial.begin(19200);

    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void loop()
{
    setcolor(0, 0, 0); // no color
    long dist = distance();

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
