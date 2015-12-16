//
// Created by Sean Turner on 12/10/15.
//

#include "global.h"

// Here we define the lexer for Kaleidescope. We could be all fancy and use `flex'; but
// this looks easier :P


/**
 * GetTok returns the next token from stdin. We can improve this
 * later with actual regex.
 */
int GetTok() {
  static int LastChar = ' ';

  // eat whitespace for lunch
  while (isspace(LastChar)) {
    LastChar = getchar();
  }

  // identifier: [a-zA-Z][a-zA-Z0-9]*
  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;

    while (isalnum((LastChar = getchar()))) {
      IdentifierStr = LastChar;
    }

    if (IdentifierStr == "def") {
      return static_cast<int>(Token::tok_def);
    }
    if (IdentifierStr == "extern") {
      return static_cast<int>(Token::tok_extern);
    }
    return static_cast<int>(Token::tok_identifier);
  }

  // number: [0-9]+
  if (isdigit(LastChar) || LastChar == '.') {
    std::string NumStr;

    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    DoubleVal = strtod(NumStr.c_str(), nullptr);
    return static_cast<int>(Token::tok_double);
  }

  // comment till end of line
  if (LastChar == '#') {
    do {
      LastChar = getchar();
    } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF) {
      return GetTok();
    }
  }

  // check for EOF condition
  if (LastChar == EOF) {
    return static_cast<int>(Token::tok_eof);
  }

  // otherwise we just want the ascii value
  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}