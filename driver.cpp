//
// Created by Sean Turner on 12/10/15.
//

// this provides an entry point and the main loop

#include "global.h"

static void MainLoop(State& state) {
  while (1) {
    std::cout << "ready> " << std::endl;
    switch (state.CurTok) {
      case static_cast<int>(Token::tok_eof):
        return;
      case ';':
        parser::GetNextToken(state); // ignoring toplevel semicolons
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
  State n;
  State& state = n; // hacky?

  state.BinOpPrecedence['<'] = 10;
  state.BinOpPrecedence['+'] = 20;
  state.BinOpPrecedence['-'] = 20;
  state.BinOpPrecedence['*'] = 40;

  // get first token
  parser::GetNextToken(state);

  // for now we will just call our MainLoop() function
  MainLoop(state);

  return 0;
}