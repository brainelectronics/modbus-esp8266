/*
 * @file Led.ino
 *
 * @author     brainelectronics <git@brainelectronics.de>
 * @date       11 April 2020
 * @version    0.1.0
 *
 * @brief      Control LED_BUILTIN using Write Single Coil Modbus Function
 *
 * @required   controlLedModbusIp.py at version 0.1.0
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
const uint16_t LED_COIL = 100;
const uint8_t ledPin = LED_BUILTIN;
uint8_t ledState = 0;
uint8_t lastLedState = 0;

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

  // LED is used in inverted mode, LOW is active, HIGH is off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  mb.addCoil(LED_COIL);
}

void loop()
{
  //Call once inside loop() - all magic here
  mb.task();

  ledState = mb.Coil(LED_COIL);

  // if the led state has changed
  if (ledState != lastLedState)
  {
    sprintf(_debugOutputBuffer, "%d LED changed from %d to %d", millis(), lastLedState, ledState);
    printDebug(_debugOutputBuffer, LEVEL_INFO);

    lastLedState = ledState;

    // change ledPin to LED_COIL register value
    // LED is used in inverted mode, LOW is active, HIGH is off
    digitalWrite(ledPin, !ledState);
  }

  delay(10);
}
