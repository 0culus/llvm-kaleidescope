//
// Created by Sean Turner on 12/10/15.
//

#pragma once

#include "global.h"

namespace parser {

  /// ExprAST is the base class for all expression nodes
  class ExprAST {
  public:
    virtual ~ExprAST();
  };

  /// DoubleExprAST is the expression class for numeric double literals
  class DoubleExprAST : public ExprAST {
    double Val;

  public:
    DoubleExprAST(double val) : Val(val) { }
  };

  /// VariableExprAST is the expression class for referencing a variable
  class VariableExprAST : public ExprAST {
    std::string Name;

  public:
    VariableExprAST(const std::string &name) : Name(name) { }
  };

  /// BinaryExprAST is the expression class for a binary operator
  class BinaryExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

  public:
    BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs,
                  std::unique_ptr<ExprAST> rhs)
      : Op(op), LHS(std::move(lhs)), RHS(std::move(rhs)) { }
  };


}