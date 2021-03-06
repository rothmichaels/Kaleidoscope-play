/*
  Lexer.cpp
  Kaleidescope

  June 9, 2016
*/

#include "Lexer.h"

#include <cstdlib>

namespace Lexer {
  
  std::string IdentifierStr;
  double NumVal;

  /**
     Get token from standard input
  */
  int gettok() {
    static int lastChar = ' ';
    // skip whitespace
    while (isspace(lastChar)) {
      lastChar = getchar();
    }
    // collect keywords and other identifiers
    if (isalpha(lastChar)) {
      IdentifierStr = lastChar;
      while (isalnum((lastChar = getchar()))) {
        IdentifierStr += lastChar;
      }

      if (IdentifierStr == "def") {
        return TokenKeyword_def;
      }
      if (IdentifierStr == "extern") {
        return TokenKeyword_extern;
      }
      return TokenIdentifier;
    }

    // lex numbers
    if (isdigit(lastChar) || lastChar == '.') {
      std::string numString;
      bool decimal = (lastChar == '.');
      do {
        numString += lastChar;
        lastChar = getchar();
      } while (isdigit(lastChar) || (!decimal && lastChar == '.'));
      NumVal = strtod(numString.c_str(), 0);
      return TokenNumber;
    }

    // Check EOF
    if (lastChar == EOF) {
      return TokenEOF;
    }

    // Raw char token
    int rawChar = lastChar;
    lastChar = getchar();
    return rawChar;
  }
}
