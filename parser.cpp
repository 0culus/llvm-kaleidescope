//
// Created by Sean Turner on 12/19/15.
//

#include "global.h"

/// This function grabs the next token for us
int parser::GetNextToken(State& state) {
  return state.CurTok = GetTok(state); // modifies state!
}

/// Error handlers
std::unique_ptr<ast::ExprAST> parser::Error(const std::string& errstr) {
  std::cout << "Error: " << errstr << std::endl;

  return nullptr;
}

std::unique_ptr<ast::PrototypeAST> parser::ErrorProto(const std::string& errstr) {
  Error(errstr);

  return nullptr;
}
