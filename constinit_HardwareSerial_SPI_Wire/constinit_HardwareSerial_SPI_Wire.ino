// Confirm whether classes Wire, SPI and HardwareSerial are constinit.
//
// Many memory addresses are printed, from a startup hook and from setup().
//
// Success criteria:
//  1 - All numbers are non-zero
//  2 - Results are identical between startup hook and setup() runs


#include <Wire.h>
#include <SPI.h>

uintptr_t Teensyduino_Test_constinit_Wire(int instance, int index) {
  if (instance == 0) {
    if (index == -1) return (uintptr_t)("Wire");
    if (index == 0) return 2;
    if (index == 1) return Wire.portAddr;
    if (index == 2) return (uintptr_t)&Wire.hardware;
  }
  if (instance == 1) {
    if (index == -1) return (uintptr_t)("Wire1");
    if (index == 0) return 2;
    if (index == 1) return Wire1.portAddr;
    if (index == 2) return (uintptr_t)&Wire2.hardware;
  }
  if (instance == 2) {
    if (index == -1) return (uintptr_t)("Wire2");
    if (index == 0) return 2;
    if (index == 1) return Wire2.portAddr;
    if (index == 2) return (uintptr_t)&Wire2.hardware;
  }
#if defined(ARDUINO_TEENSY_MICROMOD)
  if (instance == 3) {
    if (index == -1) return (uintptr_t)("Wire3");
    if (index == 0) return 2;
    if (index == 1) return Wire3.portAddr;
    if (index == 2) return (uintptr_t)&Wire3.hardware;
  }
#endif
  return 0;
}


uintptr_t Teensyduino_Test_constinit_SPI(int instance, int index) {
  if (instance == 0) {
    if (index == -1) return (uintptr_t)("SPI");
    if (index == 0) return 2;
    if (index == 1) return SPI.port_addr;
    if (index == 2) return SPI.hardware_addr;
  }
  if (instance == 1) {
    if (index == -1) return (uintptr_t)("SPI1");
    if (index == 0) return 2;
    if (index == 1) return SPI1.port_addr;
    if (index == 2) return SPI1.hardware_addr;
  }
  if (instance == 2) {
    if (index == -1) return (uintptr_t)("SPI2");
    if (index == 0) return 2;
    if (index == 1) return SPI2.port_addr;
    if (index == 2) return SPI2.hardware_addr;
  }
  return 0;
}

uintptr_t Teensyduino_Test_constinit_HardwareSerial(int instance, int index) {
  if (instance == 0) {
    if (index == -1) return (uintptr_t)("Serial");
    if (index == 0) return 2;
    if (index == 1) return Serial1.port_addr;
    if (index == 2) return (uintptr_t)Serial1.hardware;
  }
  if (instance == 1) {
    if (index == -1) return (uintptr_t)("Serial2");
    if (index == 0) return 2;
    if (index == 1) return Serial2.port_addr;
    if (index == 2) return (uintptr_t)Serial2.hardware;
  }
  if (instance == 2) {
    if (index == -1) return (uintptr_t)("Serial3");
    if (index == 0) return 2;
    if (index == 1) return Serial3.port_addr;
    if (index == 2) return (uintptr_t)Serial3.hardware;
  }
  if (instance == 3) {
    if (index == -1) return (uintptr_t)("Serial4");
    if (index == 0) return 2;
    if (index == 1) return Serial4.port_addr;
    if (index == 2) return (uintptr_t)Serial4.hardware;
  }
  if (instance == 4) {
    if (index == -1) return (uintptr_t)("Serial5");
    if (index == 0) return 2;
    if (index == 1) return Serial5.port_addr;
    if (index == 2) return (uintptr_t)Serial5.hardware;
  }
  if (instance == 5) {
    if (index == -1) return (uintptr_t)("Serial6");
    if (index == 0) return 2;
    if (index == 1) return Serial6.port_addr;
    if (index == 2) return (uintptr_t)Serial6.hardware;
  }
  if (instance == 6) {
    if (index == -1) return (uintptr_t)("Serial7");
    if (index == 0) return 2;
    if (index == 1) return Serial7.port_addr;
    if (index == 2) return (uintptr_t)Serial7.hardware;
  }
#if defined(ARDUINO_TEENSY41)
  if (instance == 7) {
    if (index == -1) return (uintptr_t)("Serial8");
    if (index == 0) return 2;
    if (index == 1) return Serial8.port_addr;
    if (index == 2) return (uintptr_t)Serial8.hardware;
  }
#endif
  return 0;
}



void print_info(uintptr_t (*f)(int, int)) {

  int instance = 0;
  while (1) {
    const char *name = (char *)f(instance, -1);
    if (!name) break;
    int count = f(instance, 0);
    for (int i = 1; i <= count; i++) {
      uintptr_t n = f(instance, i);
      Serial.print(name);
      Serial.print(": var #");
      Serial.print(i);
      Serial.print(" = ");
      Serial.println(n, HEX);
    }
    instance++;
  }
}


extern "C" {
  void startup_late_hook() {
    while (!Serial) ; // wait for serial monitor
    delay(15);
    Serial.println("startup_late_hook");
    print_info(Teensyduino_Test_constinit_Wire);
    print_info(Teensyduino_Test_constinit_SPI);
    print_info(Teensyduino_Test_constinit_HardwareSerial);
  }
}

void setup() {
  Serial.println("\nsetup");
  print_info(Teensyduino_Test_constinit_Wire);
  print_info(Teensyduino_Test_constinit_SPI);
  print_info(Teensyduino_Test_constinit_HardwareSerial);
}

void loop() {
  delay(1);
}
