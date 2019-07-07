// -----------------------------------------------------------------------------
// main.cpp                                                             main.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the main() function and doxygen's main page.
 * @author     Col. Walter E. Kurtz
 * @version    2019-07-07
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
#include <iostream>
#include <iomanip>
#include "message.h"
#include "cli.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Magical numbers                                               Magical numbers
// -----------------------------------------------------------------------------

/// returned by hexify() and unhexify() if stdin has no data
const int EMPTY = -1;

/// returned by hexify() and unhexify() if stdin got stuck
const int BUGGY = -2;


// -----------------------------------------------------------------------------
// Functions                                                           Functions
// -----------------------------------------------------------------------------

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
  cout << "  xnb {-h|-v}              show help resp. version and exit" << endl;
  cout << "  xnb -x [-n <max>] [-lt]  convert bytes to hexadecimal numbers" << endl;
  cout << "  xnb -b                   convert hexadecimal numbers back to bytes" << endl;
  cout << endl;
  cout << "DESCRIPTION" << endl;
  cout << "  xnb is a filter that can do exactly two things:" << endl;
  cout << "  1. convert each byte from a stream to a hexadecimal number with two digits" << endl;
  cout << "  2. convert each hexadecimal number from a stream back to its native byte value" << endl;
  cout << endl;
  cout << "OPTIONS" << endl;
  cout << "  -b        convert hexadecimal numbers back to bytes" << endl;
  cout << "  -h        show help and exit" << endl;
  cout << "  -l        print a real LF character each time a 0A byte has been encoded" << endl;
  cout << "  -n <max>  don't print more than <max> bytes per line" << endl;
  cout << "  -s        separate all hexadecimal numbers with SPACE" << endl;
  cout << "  -t        append a trailing LF character" << endl;
  cout << "  -v        show version and exit" << endl;
  cout << "  -x        convert bytes to hexadecimal numbers" << endl;
  cout << endl;
  cout << "EXAMPLES" << endl;
  cout << "  echo \"hello world\" | xnb -x | xnb -b" << endl;
  cout << endl;
  cout << "  echo \"hello world\"                    # print \"hello world\"" << endl;
  cout << "                     | xnb -x           # convert to hex numbers" << endl;
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
  cout << "2019-06-07" << endl;
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
 *             - only LF characters are used to break lines
 *
 * @param separate  insert a SPACE character to separate
 *                  encoded bytes
 *
 * @param breakLF  print a real LF each time a 0A byte
 *                 has been encoded
 *
 * @return
 * Value | Meaning
 * ----: | :------
 * BUGGY | error
 * EMPTY | no data
 *  >= 0 | the value of the last byte pushed to stdout
 */
int hexify(int max, bool separate, bool breakLF)
{
  // one byte from the stream
  char c;

  // initialize byte counter
  int out = max;

  // the number to print
  int byte = EMPTY;

  // insert SPACE character
  bool space = false;

  // read each byte individually from the stream
  while ( cin.get(c) )
  {
    // convert char to unsigned char (then implicitly to int)
    byte = static_cast<unsigned char>(c);

    // check if limit is given
    if (max > 0)
    {
      // check if line break is needed
      if (out == 0)
      {
        // start new line (use LF character only)
        cout << static_cast<char>(10);

        // don't start next line with SPACE character
        space = false;

        // reset counter
        out = max;
      }

      // decrease counter
      out -= 1;
    }

    // add SPACE separator
    if (separate && space) cout << ' ';

    // use iomanip to create hex numbers
    cout << setfill('0') << hex << uppercase << setw(2) << byte;

    // separate next hex number
    space = true;

    // check if line breaking is enabled
    if (breakLF)
    {
      // check if a LF character has been read
      if (byte == 10)
      {
        // start new line (use LF character only)
        cout << static_cast<char>(10);

        // don't start next line with SPACE character
        space = false;

        // reset counter
        out = max;
      }
    }
  }

  // check eof state
  if ( !cin.eof() )
  {
    // signalize trouble
    return BUGGY;
  }

  // return last byte written to stdout
  return byte;
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
 * BUGGY | error
 * EMPTY | no data
 *  >= 0 | the value of the last byte pushed to stdout
 */
int unhexify()
{
  // the byte to print
  int byte = EMPTY;

  // read entire stream
  while (true)
  {
    // two hexadecimal digits
    char hi = 32;
    char lo = 32;

    // one byte from stdin
    char ex = 0;

    // read most significant digit first
    while ( cin.get(ex) )
    {
      // skip whitespace characters
      if (ex ==  9) continue;
      if (ex == 10) continue;
      if (ex == 13) continue;
      if (ex == 32) continue;

      hi = ex;
      break;
    }

    // no more characters from stdin
    if (hi == 32)
    {
      // return last byte written to stdout
      return byte;
    }

    // check extracted character
    if ( !ishex(hi) )
    {
      // notify user
      msg::err("invalid character found");

      // signalize trouble
      return BUGGY;
    }

    // read least significant thereafter
    while ( cin.get(ex) )
    {
      // skip whitespace characters
      if (ex ==  9) continue;
      if (ex == 10) continue;
      if (ex == 13) continue;
      if (ex == 32) continue;

      lo = ex;
      break;
    }

    // no more characters from stdin
    if (hi == 32)
    {
      // notify user
      msg::err("unexpected end of stream");

      // signalize trouble
      return BUGGY;
    }

    // check extracted character
    if ( !ishex(lo) )
    {
      // notify user
      msg::err("invalid character found");

      // signalize trouble
      return BUGGY;
    }

    // convert number to native byte
    byte = hex2dec(hi, lo);

    // print native byte
    cout << static_cast<unsigned char>(byte);
  }

  // check eof state
  if ( !cin.eof() )
  {
    // signalize trouble
    return BUGGY;
  }

  // return last byte written to stdout
  return byte;
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

      // try to create readable hex numbers
      int last = hexify(cmdl.maxBytes, cmdl.separate, cmdl.syncLF);

      // check last byte
      if (last == BUGGY)
      {
        // signalize trouble
        return 1;
      }

      // print trailing LF character
      if (cmdl.appendLF)
      {
        if ( !(cmdl.syncLF && (last == 10)) )
        {
          cout << static_cast<char>(10);
        }
      }
    }

    // UNHEXIFY
    else if (cmdl.operation == cli::UNHEXIFY)
    {
      // try to restore native byte values
      if (unhexify() == BUGGY)
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

