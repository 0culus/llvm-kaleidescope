//
// Created by Sean Turner on 12/10/15.
//

// this provides an entry point and the main loop

#include "global.h"

static void MainLoop() {
  while (1) {
    std::cout << "ready> " << std::endl;
    switch (CurTok) {
      case static_cast<int>(Token::tok_eof):
        return;
      case ';':
        GetNextToken(); // ignoring toplevel semicolons
        break;
      case static_cast<int>(Token::tok_def):
        //HandleDefinition();
        break;
      case static_cast<int>(Token::tok_extern):
        //HandleExtern();
        break;
      default:
        //HandleTopLevelExpr();
        break;
    }
  }
}

int main() {
  BinOpPrecedence['<'] = 10;
  BinOpPrecedence['+'] = 20;
  BinOpPrecedence['-'] = 20;
  BinOpPrecedence['*'] = 40;

  // get first token
  //getNextToken()

  // for now we will just call our MainLoop() function
  MainLoop();

  return 0;
}