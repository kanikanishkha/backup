#define PULSE_TIMEOUT   150000L // 150ms

#define RED_PIN         5
#define GREEN_PIN       7
#define BLUE_PIN        6

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
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

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

void setcolor(int R, int G, int B)
{
  analogWrite(RED_PIN, R);
  analogWrite(GREEN_PIN, G);
  analogWrite(BLUE_PIN, B);
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
  setcolor(0, 0, 0);
    int dist = distance();

    if (dist <= BEEP_RANGE) {
        if (dist > 18 && dist <= 33) {
          setcolor(0, 255, 0);
          slow_beep(); // green
        }
        else if (dist > 8 && dist <= 18) {
          setcolor(255, 255, 0);
          medium_beep(); // yellow
        }
        else if (dist <= 8) {
          setcolor(255, 0, 0);
          fast_beep(); // red
        }
    }
}
