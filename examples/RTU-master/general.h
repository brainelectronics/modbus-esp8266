#ifndef general_h
#define general_h

// required for String
#include <Arduino.h>

#define CURRENT_FIRMWARE_VERSION     1586521678
#define DEBUGGING

// removed for MH ET Live Mini DevKit
#ifndef LED_BUILTIN
#define LED_BUILTIN               2
#endif

#define bTrue                     1  // true
#define bFalse                    0  // false

enum {
  LEVEL_NOTSET = 0,                  //< not set, output everything
  LEVEL_FREE_HEAP = 5,               //< print free heap info
  LEVEL_DEBUG = 10,                  //< debug level
  LEVEL_INFO = 20,                   //< info level
  LEVEL_WARNING = 30,                //< warning level
  LEVEL_ERROR = 40,                  //< error level
  LEVEL_CRITICAL = 50,               //< critical level
  LEVEL_OFF = 255                    //< no output
};

#ifdef DEBUGGING
  #define DEBUG_BAUD_RATE       115200 // baudrate of debug output
  #define DEBUG_BEGIN(x)        Serial.begin(x)
  #define DEBUG_PRINT(...)      Serial.print(__VA_ARGS__)
  #define DEBUG_PRINTV(x, v)    Serial.print(x); Serial.println(v)
  #define DEBUG_PRINTLN(...)    Serial.println(__VA_ARGS__)
  #define DEBUG_PRINT_BUFFER()  Serial.println(_debugOutputBuffer);
#else
  #define DEBUG_BEGIN(...)
  #define DEBUG_PRINT(...)
  #define DEBUG_PRINTV(x, v)
  #define DEBUG_PRINTLN(...)
  #define DEBUG_PRINT_BUFFER()
#endif

extern char* _debugOutputBuffer;     // debug buffer
extern const char* _thisFileName;    // file name of this sketch

/**
 * @brief      print debug message
 *
 * @param      message     The message
 * @param[in]  ubDebugLevel  The debug level
 */
extern void printDebug(char *message, uint8_t ubDebugLevel);

/**
 * @brief      Prints the sketch informations.
 */
extern void printSketchInfo(char* filename);

/**
 * @brief      Gets the sketch file name.
 *
 * @return     The sketch file name.
 * @example    getSketchFileName(__FILE__)
 */
const char* getSketchFileName(const char* theFile);

#endif
