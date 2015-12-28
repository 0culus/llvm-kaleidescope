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

std::unique_ptr<ast::ExprAST> ParseIdentifierExpr(State& state) {
  std::string IdName = state.IdentifierStr;

  parser::GetNextToken(state); // eat id

  if (state.CurTok != '(') {
    return std::make_unique<ast::VariableExprAST>(std::move(IdName));
  }

  parser::GetNextToken(state); // eat the '('

  std::vector<std::unique_ptr<ast::ExprAST>> Args;

  if (state.CurTok != ')') {
    while (1) {
      if (const auto& Arg = parser::ParseExpression(state)) {
        Args.push_back(std::move(Arg));
      } else {
        return nullptr;
      }

      if (state.CurTok == ')') {
        break;
      }

      if (state.CurTok != ',') {
        return parser::Error(std::string("Expected ')' or ',' in argument list"));
      }
      parser::GetNextToken(state);
    }
  }

  parser::GetNextToken(state); // eat the ')'

  return std::make_unique<ast::CallExprAST>(IdName, std::move(Args));
}