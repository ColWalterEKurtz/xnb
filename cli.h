// -----------------------------------------------------------------------------
// cli.h                                                                   cli.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref cli class.
 * @author     Col. Walter E. Kurtz
 * @version    2017-07-18
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef CLI_H_INCLUDE_NO1
#define CLI_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <vector>
#include <string>


// ---
// cli
// ---
/**
 * @brief  This class defines the command-line interface.
 */
class cli
{

public:

  // ---------------------------------------------------------------------------
  // Settings                                                           Settings
  // ---------------------------------------------------------------------------

  // operations that are mutually exclusive
  enum
  {
    SHOW_HELP,
    SHOW_VERSION,
    SHOW_DEFAULT_VALUES,
    CREATE_COMMON_FILES,
    SHOW_LIST_OF_COORDINATES,
    CREATE_DERIVED_FILES
  }
  operation;

  /// the list of positional parameters
  std::vector< std::string > pparams;

  /// the name of the pbm file to parse
  std::string file_pbm;

  /// the name of the list file
  std::string file_coordinates;

  /// the name of the settings file
  std::string file_settings;


  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // ---
  // cli
  // ---
  /**
   * @brief  The standard-constructor.
   */
  cli();


  // ---------------------------------------------------------------------------
  // Handling                                                           Handling
  // ---------------------------------------------------------------------------

  // -----
  // parse
  // -----
  /**
   * @brief  This method uses getopt() to parse the given arguments.
   */
  bool parse(int argc, char** argv);

  // --------
  // getXName
  // --------
  /**
   * @brief  returns argv[0]
   */
  std::string getXName(bool brief = true) const;


protected:

  // ---------------------------------------------------------------------------
  // Internal methods                                           Internal methods
  // ---------------------------------------------------------------------------

  // -----
  // reset
  // -----
  /**
   * @brief  This method restores the initial state.
   */
  void reset();

  // --------
  // int2char
  // --------
  /**
   *
   */
  std::string int2char(int ascii) const;


private:

  // ---------------------------------------------------------------------------
  // Attributes                                                       Attributes
  // ---------------------------------------------------------------------------

  /// the executable's name
  std::string m_argv0;

};

#endif  /* #ifndef CLI_H_INCLUDE_NO1 */

