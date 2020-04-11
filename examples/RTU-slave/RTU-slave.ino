/*
 * @file RTU-slave.ino
 *
 * @author     brainelectronics <git@brainelectronics.de>
 * @date       11 April 2020
 * @version    0.1.0
 *
 * @brief      Configure Holding Register with initial value 0xABCD
 *
 * Holding registers can be set or get.
 *
 * @required   controlHoldingModbusRtu.py at version 0.1.0
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
uint16_t registerValue = 0xABCD;
uint16_t lastRegisterValue = registerValue;

// define a unique slave id on the bus for this device
#define SLAVE_ID         12
#define MODBUS_BAUDRATE  9600 // baudrate used on the RS485 bus

#define USE_SOFTWARE_SERIAL

#ifdef USE_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
#define RS485RX          4    // WeMos RX to D2 (GPIO4, Arduino pin 4)
#define RS485TX          5    // WeMos TX to D1 (GPIO5, Arduino pin 5)
#endif

// ModbusRTU object
ModbusRTU mb;
SoftwareSerial rs485(RS485RX, RS485TX); // WeMos (receive pin, transmit pin)

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
  mb.begin(&rs485);
#else
  Serial.begin(MODBUS_BAUDRATE, SERIAL_8N1)
  mb.begin(&Serial);
#endif

  mb.slave(SLAVE_ID);

  mb.addHreg(TEST_HREG, registerValue);
}

void loop()
{
  // call once inside loop() - all magic here
  mb.task();

  // get latest value of this Hreg
  registerValue = mb.Hreg(TEST_HREG);

  // if the Hreg value has changed
  if (registerValue != lastRegisterValue)
  {
#ifdef USE_SOFTWARE_SERIAL
    // print debug only if software serial is used for RS485 bus
    sprintf(_debugOutputBuffer, "%d Hreg content changed from %d to %d", millis(), lastRegisterValue, registerValue);
    printDebug(_debugOutputBuffer, LEVEL_INFO);
#endif

    lastRegisterValue = registerValue;
  }

  yield();
}
