/*
 * @file RTU-Master.ino
 *
 * @author     brainelectronics <git@brainelectronics.de>
 * @date       11 April 2020
 * @version    0.1.0
 *
 * @brief      Read multiple coils from slave device example
 *
 * @required   RTU-slave.ino at version 0.1.0
 *
 * The circuit:
 *    Any Arduino, ESP32 or ESP8266
 *    RS485 board connected to UART port
 *    test script interacts via RS485-USB module
 *
 * Note:
 *    does not work directly via USB as the board restarts
 *
 * Logging:
 *    0   Not set, output everything
 *    10  Debug
 *    20  Info
 *    30  Warning
 *    40  Error
 *    50  Critical
 *    255 Off
 *
 * History/Credits:
 *  Original library
 *  Copyright by André Sarmento Barbosa
 *  http://github.com/andresarmento/modbus-arduino
 *
 *  Forked from
 *  (c)2017 Alexander Emelianov (a.m.emelianov@gmail.com)
 *  https://github.com/emelianov/modbus-esp8266
 *
*/

#include <ModbusRTU.h>

#include "general.h"

// Modbus Registers Offsets
const uint16_t TEST_HREG = 100;
const uint16_t numOfRegs = 1;

// define the slave id on the bus to read from
#define SLAVE_ID         12
#define MODBUS_BAUDRATE  9600 // baudrate used on the RS485 bus

// uncomment the following define to communicate via Serial
// no serial debug communication is possible then
#define USE_SOFTWARE_SERIAL

#ifdef USE_SOFTWARE_SERIAL
  #include <SoftwareSerial.h>
  #define RS485RX          4    // WeMos RX to D2 (GPIO4, Arduino pin 4)
  #define RS485TX          5    // WeMos TX to D1 (GPIO5, Arduino pin 5)

  // SoftwareSerial(int8_t rxPin, int8_t txPin = -1, bool invert = false);
  SoftwareSerial rs485(RS485RX, RS485TX);
#endif

// define array of coils values to be read from slave
// array size must be capable to store the number of registers to read
bool coils[numOfRegs];

// ModbusRTU object
ModbusRTU mb;

bool cbWrite(Modbus::ResultCode event, uint16_t transactionId, void* data)
{
#ifdef ESP8266
  Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
#elif ESP32
  Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
#else
  Serial.printf_P("Request result: 0x%02X\n", event);
#endif

  return true;
}

void setup()
{
  _debugOutputBuffer = (char *) calloc(255, sizeof(char));
  _thisFileName = (char *) calloc(255, sizeof(char));

#ifdef USE_SOFTWARE_SERIAL
  // print debug only if software serial is used for RS485 bus

  DEBUG_BEGIN(DEBUG_BAUD_RATE);

  // IMPORTANT
  // THE FOLLOWING LINES ARE MANDATORY FOR EACH SKETCH

  // get filename without extension from filePath
  _thisFileName = getSketchFileName(__FILE__);

  // display all available informations of this sketch on console
  printSketchInfo((char*)_thisFileName);
  // END OF MANDATORY STUFF
#endif

#ifdef USE_SOFTWARE_SERIAL
  rs485.begin(MODBUS_BAUDRATE);
  // rs485.begin(MODBUS_BAUDRATE, SWSERIAL_8N1);
  mb.begin(&rs485);
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284__)
  // use Serial1 on Arduino Mega
  Serial1.begin(MODBUS_BAUDRATE, SERIAL_8N1);
  mb.begin(&Serial1);
#else
  // use default Serial otherwise
  Serial.begin(MODBUS_BAUDRATE, SERIAL_8N1);
  mb.begin(&Serial);
#endif

  mb.master();
}

void loop()
{
  // Returns slave id for active request or 0 if no request in-progress.
  if (!mb.slave())
  {
    // readCoil(uint8_t slaveId, uint16_t offset, bool* value, uint16_t numregs = 1, cbTransaction cb = nullptr);
    mb.readCoil(SLAVE_ID, TEST_HREG, coils, numOfRegs, cbWrite);
  }

  mb.task();
  yield();
}
