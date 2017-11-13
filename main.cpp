// -----------------------------------------------------------------------------
// main.cpp                                                             main.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the main() function and doxygen's main page.
 * @author     Col. Walter E. Kurtz
 * @version    2017-11-13
 * @copyright  GNU General Public License - Version 3.0
 *
 * @mainpage
 *
 * @section issue What is the issue here?
 *   Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod
 *   tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim
 *   veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid
 *   ex ea commodi consequat. Quis aute iure reprehenderit in voluptate
 *   velit esse cillum dolore eu fugiat nulla pariatur.
 *   Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui
 *   officia deserunt mollit anim id est laborum.
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
// #include <cstdlib>
// #include <climits>
// #include <cfloat>
// #include <cmath>
// #include <ctime>
// #include <list>
// #include <stack>
// #include <vector>
// #include <queue>
// #include <deque>
// #include <set>
// #include <map>
// #include <algorithm>
// #include <string>
// #include <sstream>
// #include <fstream>
#include <iostream>
#include <iomanip>
#include "message.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// ------
// hexify
// ------
/**
 * This function reads each byte from stdin and
 * writes its hexadecimal representation to stdout.
 *
 * @param max  the maximum number of bytes to print per line
 *             - each byte causes two characters of output
 *             - max == 0 never breaks a line
 *
 * @return
 * Value | Meaning
 * ----: | :------
 *  true | cin reached eof
 * false | cin didn't reach eof
 */
bool hexify(int max = 0)
{
  // one byte from the stream
  char c;

  // initialize byte counter
  int out = max;

  // read each byte individually from the stream
  while ( cin.get(c) )
  {
    // convert char to unsigned
    unsigned u = static_cast<unsigned>(c);

    // check if limit is given
    if (max > 0)
    {
      // check if line break is needed
      if (out == 0)
      {
        // start new line (use LF character only)
        cout << static_cast<char>(10);

        // reset counter
        out = max;
      }

      // decrease counter
      out -= 1;
    }

    // use iomanip to create hex numbers
    cout << setfill('0') << hex << uppercase << setw(2) << u;
  }

  // check if all data has been read
  return cin.eof();
}

// --------
// unhexify
// --------
/**
 * This function reads hex numbers from stdin and
 * prints their real byte value to stdout.
 */
bool unhexify()
{
  // first hexadecimal digit
  char c;

  // read each byte individually from the stream
  while ( cin.get(c) )
  {
    // skip line feed characters
    while (c == 10)
    {
      // get next byte from the stream
      if ( !cin.get(c) )
      {
        // check if all data has been read
        return cin.eof();
      }
    }

    // second hexadecimal digit
    char d = 10;

    // skip line feed characters
    while (d == 10)
    {
      // read second hexadecimal digit from the stream
      if ( !cin.get(d) )
      {
        // notify user
        msg::err("unexpected end of stream");

        // signalize trouble
        return false;
      }
    }

    // the real byte value
    unsigned char byte = 0;

    // add higher byte
    switch (c)
    {
      case '1':           byte +=  16; break;
      case '2':           byte +=  32; break;
      case '3':           byte +=  48; break;
      case '4':           byte +=  64; break;
      case '5':           byte +=  80; break;
      case '6':           byte +=  96; break;
      case '7':           byte += 112; break;
      case '8':           byte += 128; break;
      case '9':           byte += 144; break;
      case 'A': case 'a': byte += 160; break;
      case 'B': case 'b': byte += 176; break;
      case 'C': case 'c': byte += 192; break;
      case 'D': case 'd': byte += 208; break;
      case 'E': case 'e': byte += 224; break;
      case 'F': case 'f': byte += 240; break;
    }

    // add lower byte
    switch (d)
    {
      case '1':           byte +=  1; break;
      case '2':           byte +=  2; break;
      case '3':           byte +=  3; break;
      case '4':           byte +=  4; break;
      case '5':           byte +=  5; break;
      case '6':           byte +=  6; break;
      case '7':           byte +=  7; break;
      case '8':           byte +=  8; break;
      case '9':           byte +=  9; break;
      case 'A': case 'a': byte += 10; break;
      case 'B': case 'b': byte += 11; break;
      case 'C': case 'c': byte += 12; break;
      case 'D': case 'd': byte += 13; break;
      case 'E': case 'e': byte += 14; break;
      case 'F': case 'f': byte += 15; break;
    }

    // print native byte
    cout << byte;
  }

  // check if all data has been read
  return cin.eof();
}

// ----
// main
// ----
/**
 * @brief  The program starts in this function.
 *
 * @param argc  holds the number of passed command-line arguments.
 * @param argv  holds the list of passed command-line arguments.
 *
 * @return
 * Value | Meaning
 * ----: | :------
 *     0 | The requested operation finished successfully.
 *     1 | The requested operation failed.
 */
int main(int argc, char** argv)
{
  // hexify(40);
  unhexify();
}

