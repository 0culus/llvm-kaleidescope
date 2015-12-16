//
// Created by Sean Turner on 12/10/15.
//

#pragma once

#include "global.h"

// this is our Abstract Syntax Tree (AST)

namespace ast {

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

  /// CallExprAST is the expression class for function calls
  class CallExprAST : public ExprAST {
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;

  public:
    CallExprAST(const std::string& callee,
                std::vector<std::unique_ptr<ExprAST>> args)
      : Callee(callee), Args(std::move(args)) { }
  };

  /// PrototypeAST captures the function prototype; name, names of arguments. This
  /// implicity deals with the argcount.
  class PrototypeAST {
    std::string Name;
    std::vector<std::string> Args;

  public:
    PrototypeAST(const std::string& name, std::vector<std::string> args)
      : Name(name), Args(args) { }
  };

  // FunctionAST represents a function definition itself
  class FunctionAST {
    std::unique_ptr<PrototypeAST> Prototype;
    std::unique_ptr<ExprAST> Body;

  public:
    FunctionAST(std::unique_ptr<PrototypeAST> proto,
                std::unique_ptr<ExprAST> body)
      : Prototype(std::move(proto)), Body(std::move(body)) { }
  };
}