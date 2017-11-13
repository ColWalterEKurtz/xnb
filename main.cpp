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
// #include <iostream>
// #include <iomanip>
#include "message.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
// using namespace std;


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
  // check number of arguments
  if (argc < 2)
  {
    // warning
    msg::wrn( msg::insq("no arguments passed (~ passed by default)", argv[0]) );
  }

  else
  {
    // info: number of user-passed arguments
    msg::nfo( msg::ins("you passed ~ argument(s)", msg::str(argc - 1)) );

    // show all user-passed arguments
    for(int i = 1; i < argc; i++)
    {
      // info: user-passed argument
      msg::nfo( msg::catq("you passed: ", argv[i]) );
    }
  }

  // signalize success
  return 0;
}
