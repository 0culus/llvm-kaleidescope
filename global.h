//
// Created by Sean Turner on 12/10/15.
//

#pragma once

#include <cctype>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

/// LLVM uses their own make_unique in the tutorial. We'll reproduce it here,
/// but may not use it! The helper namespace might be useful anyway
namespace helper {
  template <class T, class... Args>
  static
    typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
    make_unique(Args &&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
};
}

/// encapsulate the global state in one struct to keep things clean...
/// ...well as clean as passing state around can be anyway.
struct State {
  // manage precedence for binary operators
  std::map<char, int> BinOpPrecedence;

  // lexer things
  std::string IdentifierStr; // filled if tok_identifier
  double DoubleVal; // filled if tok_double

  // parser state
  int CurTok;
};

/**
 * Here we define all the tokens we need; add to this to add more!
 */
enum class Token {
  tok_eof = -1,

  tok_def = -2,
  tok_extern = -3,

  tok_identifier = -4,
  tok_double = -5
};

/// Our Lexer
// for now, we place these things in their own namespaces
// to at the very least, avoid global namespace pollution
namespace lexer {
  int GetTok(State& state);
}

/// Our Abstract Syntax Tree (AST)
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
  /// implicitly deals with the argcount.
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

/// Our Parser
namespace parser {
  using namespace lexer;

  int GetNextToken(State& state);

  /// Error handlers
  std::unique_ptr<ast::ExprAST> Error(const std::string& errstr);

  std::unique_ptr<ast::PrototypeAST> ErrorProto(const std::string& errstr);
}


