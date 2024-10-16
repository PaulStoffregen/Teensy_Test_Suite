// Check whether all 4 IntervalTimer instances are able to run simultaneously
//
// Success criteria:
//  1 - prints "successmask = 0xFF"
//  2 - pins 5, 6, 7, 8 toggle at 1 kHz
//  3 - pins 1, 2, 3, 4 to not change

// previously reported bug
// https://forum.pjrc.com/index.php?threads/possible-intervaltimer-bug.23676/

IntervalTimer timer_1;
IntervalTimer timer_2;
IntervalTimer timer_3;
IntervalTimer timer_4;

#define LED 13

elapsedMicros period;
bool firstrun = true;
volatile unsigned char successmask = 0;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void success(uint8_t mask)
{
  noInterrupts();
  successmask |= mask;
  interrupts();
}

void loop()
{
  if (period >= 500) { // try and start all 4 timers every 1500uS
    period -= 500;  // reset time period
    if (!firstrun) {
      Serial.printf("successmask = 0x%02X (should be 0xFF)\n", successmask);
    }
    successmask = 0;
    start_timer1();
    start_timer2();
    start_timer3();
    start_timer4();
    firstrun = false;
  }
}


void start_timer1() {
  if (timer_1.begin(timer_1_output_end, 300)) {
    success(0x01);
  } else {
    digitalWriteFast(1, HIGH);
    delayMicroseconds(100);
    digitalWriteFast(1, LOW);
  }
}

void timer_1_output_end()
{
  digitalToggle(5);
  timer_1.end();               // stop the timer
  success(0x10);
}

void start_timer2()
{
  if (timer_2.begin(timer_2_output_end, 300)) {
    success(0x02);
  } else {
    digitalWriteFast(2, HIGH);
    delayMicroseconds(100);
    digitalWriteFast(2, LOW);
  }
}

void timer_2_output_end()
{
  digitalToggle(6);
  timer_2.end();
  success(0x20);
}

void start_timer3()
{
  if (timer_3.begin(timer_3_output_end, 300)) {
    success(0x04);
  } else {
    digitalWriteFast(3, HIGH);
    delayMicroseconds(100);
    digitalWriteFast(3, LOW);
  }
}

void timer_3_output_end()
{
  digitalToggle(7);
  timer_3.end();
  success(0x40);
}

void start_timer4()
{
  if (timer_4.begin(timer_4_output_end, 300)) {
    success(0x08);
  } else {
    digitalWriteFast(4, HIGH);
    delayMicroseconds(100);
    digitalWriteFast(4, LOW);
  }
}

void timer_4_output_end()
{
  digitalToggle(8);
  timer_4.end();
  success(0x80);
}
