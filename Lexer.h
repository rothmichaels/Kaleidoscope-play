/*
  Lexer.h
  Kaleidoscope

  June 9, 2016
*/

#ifndef Lexer_h_include
#define Lexer_h_include

#include <string>

namespace Lexer {
  // Tokens
  enum Token {
    // End of File
    TokenEOF = -1,

    // keywords
    TokenKeyword_def = -2,
    TokenKeyword_extern = -3,

    // primary
    TokenIdentifier = -4,
    TokenNumber = -5,
  };
  
  extern std::string IdentifierStr;
  extern double NumVal;

  int gettok();
}

#endif
