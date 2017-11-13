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
#include <string>
#include <iostream>
#include <iomanip>
#include "message.h"
#include "cli.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// --------
// showHelp
// --------
/**
 *
 */
void showHelp()
{
  cout << endl;
  cout << "NAME" << endl;
  cout << "  xnb - hex and back" << endl;
  cout << endl;
  cout << "SYNOPSIS" << endl;
  cout << "  xnb {-h|-v}             show help resp. version and exit" << endl;
  cout << "  xnb -x [-n <max>] [-t]  convert bytes to hexadecimal numbers" << endl;
  cout << "  xnb -b                  convert hexadecimal numbers back to bytes" << endl;
  cout << endl;
  cout << "DESCRIPTION" << endl;
  cout << "  xnb is a filter that can do exactly two things:" << endl;
  cout << "  1. convert each byte from a stream to a hexadecimal number with two digits" << endl;
  cout << "  2. convert each hexadecimal number from a stream back to its native byte value" << endl;
  cout << endl;
  cout << "OPTIONS" << endl;
  cout << "  -b        convert hexadecimal numbers back to bytes" << endl;
  cout << "  -h        show help and exit" << endl;
  cout << "  -n <max>  don't print more than <max> bytes per line" << endl;
  cout << "  -t        append a trailing LF character" << endl;
  cout << "  -v        show version and exit" << endl;
  cout << "  -x        convert bytes to hexadecimal numbers" << endl;
  cout << endl;
  cout << "EXAMPLES" << endl;
  cout << "  echo \"hello world\" | xnb -x | xnb -b" << endl;
  cout << endl;
  cout << "  echo \"hello world\"                    # print \"hello world\"" << endl;
  cout << "                     | xnb -x           # convert to hex" << endl;
  cout << "                              | xnb -b  # back to \"hello world\"" << endl;
  cout << endl;
}

// -----------
// showVersion
// -----------
/**
 *
 */
void showVersion()
{
  cout << "2017-11-13 21:45:57 UTC" << endl;
}

// -----
// ishex
// -----
/**
 * @brief  This function checks whether the passed character
 *         is a valid hexadecimal digit or not.
 *
 * @param c  the character to check
 *
 * @return
 * Value | Meaning
 * ----: | :------
 *  true | the passed character is a valid hexadecimal digit
 * false | the passed character is no valid hexadecimal digit
 */
bool ishex(char c)
{
  // valid hexadecimal digits
  switch (c)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case 'A': case 'a':
    case 'B': case 'b':
    case 'C': case 'c':
    case 'D': case 'd':
    case 'E': case 'e':
    case 'F': case 'f': return true;
  }

  // invalid character found
  return false;
}

// -------
// hex2dec
// -------
/**
 * @brief  This function converts a hexadecimal number with two digits
 *         to a base 10 number.
 *
 * @param hi  this is the 'hi' part from: hi * 16 + lo
 * @param lo  this is the 'lo' part from: hi * 16 + lo
 *
 * @return hi * 16 + lo
 */
unsigned char hex2dec(char hi, char lo)
{
  // the base 10 number
  unsigned char byte = 0;

  // add higher byte
  switch (hi)
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
  switch (lo)
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

  // return decimal value
  return byte;
}

// ------
// hexify
// ------
/**
 * @brief  This function reads each byte from stdin and
 *         writes its hexadecimal representation to stdout.
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
 * @brief  This function reads hex numbers from stdin and
 *         prints their real byte value to stdout.
 *
 * @return
 * Value | Meaning
 * ----: | :------
 *  true | cin reached eof
 * false | cin didn't reach eof
 */
bool unhexify()
{
  // first hexadecimal digit
  char d1;

  // read each byte individually from the stream
  while ( cin.get(d1) )
  {
    // skip line feed characters
    while (d1 == 10)
    {
      // get next byte from the stream
      if ( !cin.get(d1) )
      {
        // check if all data has been read
        return cin.eof();
      }
    }

    // check extracted character
    if ( !ishex(d1) )
    {
      // notify user
      msg::err("invalid character found");

      // signalize trouble
      return false;
    }

    // second hexadecimal digit
    char d2 = 10;

    // skip line feed characters
    while (d2 == 10)
    {
      // read second hexadecimal digit from the stream
      if ( !cin.get(d2) )
      {
        // notify user
        msg::err("unexpected end of stream");

        // signalize trouble
        return false;
      }
    }

    // check extracted character
    if ( !ishex(d2) )
    {
      // notify user
      msg::err("invalid character found");

      // signalize trouble
      return false;
    }

    // print native byte
    cout << hex2dec(d1, d2);
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
  cli cmdl;

  // parse command line
  if ( cmdl.parse(argc, argv) )
  {
    // check positional parameters
    if ( !cmdl.pparams.empty() )
    {
      // notify user
      msg::err("no positional parameters allowed");

      // signalize trouble
      return 1;
    }

    // SHOW_HELP
    if (cmdl.operation == cli::SHOW_HELP)
    {
      showHelp();
    }

    // SHOW_VERSION
    else if (cmdl.operation == cli::SHOW_VERSION)
    {
      showVersion();
    }

    // HEXIFY
    else if (cmdl.operation == cli::HEXIFY)
    {
      // check limit
      if (cmdl.maxBytes < 0) 
      {
        // notify user
        msg::err("maximum number of bytes per line must not be negative");

        // signalize trouble
        return 1;
      }

      // create hex numbers
      if ( !hexify(cmdl.maxBytes) )
      {
        // signalize trouble
        return 1;
      }

      // print trailing LF character
      if (cmdl.appendLF)
      {
        cout << static_cast<char>(10);
      }
    }

    // UNHEXIFY
    else if (cmdl.operation == cli::UNHEXIFY)
    {
      // restore native bytes
      if ( !unhexify() )
      {
        // signalize trouble
        return 1;
      }
    }

    // wtf
    else
    {
      // notify user
      msg::err("oops...");

      // signalize trouble
      return 1;
    }
  }

  // invalid command line
  else
  {
    // signalize trouble
    return 1;
  }

  // signalize success
  return 0;
}

