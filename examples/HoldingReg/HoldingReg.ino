/*
 * @file HoldingReg.ino
 *
 * @author     brainelectronics <git@brainelectronics.de>
 * @date       11 April 2020
 * @version    0.1.0
 *
 * @brief      Configure Holding Register with initial value 0xABCD
 *
 * Holding registers can be set or get.
 *
 * @required   controlHoldingModbusIp.py at version 0.1.0
 *
 * The circuit:
 *    ESP32 or ESP8266
 *
 * Note:
 *  - None
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

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else //ESP32
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>

#include "general.h"
#include "wifiConfig.h"

// Modbus Registers Offsets
const uint16_t TEST_HREG = 100;
uint16_t registerValue = 0xABCD;
uint16_t lastRegisterValue = registerValue;

// ModbusIP object
ModbusIP mb;

void setup()
{
  _debugOutputBuffer = (char *) calloc(255, sizeof(char));
  _thisFileName = (char *) calloc(255, sizeof(char));

  DEBUG_BEGIN(DEBUG_BAUD_RATE);

  // IMPORTANT
  // THE FOLLOWING LINES ARE MANDATORY FOR EACH SKETCH

  // get filename without extension from filePath
  _thisFileName = getSketchFileName(__FILE__);

  // display all available informations of this sketch on console
  printSketchInfo((char*)_thisFileName);
  // END OF MANDATORY STUFF

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    DEBUG_PRINT(".");
  }

  DEBUG_PRINTLN("");

  sprintf(_debugOutputBuffer, "Connected with IP %s to %s", WiFi.localIP().toString().c_str(), WiFi.SSID().c_str());
  printDebug(_debugOutputBuffer, LEVEL_INFO);

  mb.slave();

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
    sprintf(_debugOutputBuffer, "%d Hreg content changed from %d to %d", millis(), lastRegisterValue, registerValue);
    printDebug(_debugOutputBuffer, LEVEL_INFO);

    lastRegisterValue = registerValue;
  }

  delay(10);
}
