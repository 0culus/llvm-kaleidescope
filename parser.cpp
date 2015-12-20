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

std::unique_ptr<ast::ExprAST> ParseDoubleExpr(State& state) {
  auto result = std::make_unique<ast::DoubleExprAST>(state.DoubleVal);
  parser::GetNextToken(state);

  return std::move(result);
}

std::unique_ptr<ast::ExprAST> ParseParenExpr(State& state) {
  parser::GetNextToken(state); // eat the leading paren

  auto V = parser::ParseExpression(state); // TODO: implement

  if (!V) {
    return nullptr;
  }

  if (state.CurTok != ')') {
    return parser::Error(std::string("expected ')'"));
  }

  parser::GetNextToken(state);

  return V;
}