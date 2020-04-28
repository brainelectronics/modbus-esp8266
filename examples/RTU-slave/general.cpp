/***************************************
*    include all libs
***************************************/

// system libs

// contributed libs

// custom libs
#include "general.h"

char* _debugOutputBuffer;               // debug buffer
const char* _thisFileName;              // file name of this sketch

uint8_t _ubEnableLog = bTrue;           // default: output no messages
uint8_t _ubLogThreshold = LEVEL_NOTSET; // default: output nothing

const char* getSketchFileName(const char* theFile)
{
  // return __FILENAME__;
  return ({const char * pStr = strrchr(theFile, '/'); pStr ? pStr + 1 : theFile;});
}

void printDebug(char *message, uint8_t ubDebugLevel)
{
  // if logging to console is enabled in general
  if (_ubEnableLog == bTrue)
  {
    // if the debug level of this message is larger than the system threshold
    if (ubDebugLevel >= _ubLogThreshold)
    {
      // print it out
      // Serial.println(message);
      DEBUG_PRINTLN(message);
    }
  }

  // clear buffer? no as sprintf() is recommended to use
  // clearDebugBuffer();
}

void printSketchInfo(char* filename)
{
  sprintf(_debugOutputBuffer, "\nStarting up %s v%d, compiled %s %s\n", filename, CURRENT_FIRMWARE_VERSION, __DATE__, __TIME__);

  // begin serial with 115k baud independant of Debug interface
  Serial.begin(115200);
  Serial.println(_debugOutputBuffer);
  // Starting up testSketch.ino v123, compiled Aug  5 2019 11:53:05
}