/*
  Parser.cpp
  Kaleidescope

  June 9, 2016
*/

#ifndef AST_h_include
#define AST_h_include

#include <string>
#include <vector>

namespace AST {

  /// ExprAST - Base class for all expression nodes.
  class Expr {
  public:
    virtual ~Expr();
  };

  /// NumberExpr - Expression class for numeric literals like "1.0".
  class NumberExpr : public Expr {
  public:
    NumberExpr(double val);
  private:
    double val; // TODO: const?
  };

  /// VariableExpr - Expression class for referencing a variable, like "a".
  class VariableExpr : public Expr {
  public:
    VariableExpr(const std::string& varName);
  private:
    std::string name;
  };

  /// BinaryExpr - Expression class for a binary operator.
  class BinaryExpr : public Expr {
  public:
    BinaryExpr(char op, std::unique_ptr<Expr> lhs,
               std::unique_ptr<Expr> rhs);
  private:
    char op;
    std::unique_ptr<Expr> lhs, rhs;
  };

  /// CallExpr - Expression class for function calls.
  class CallExpr : public Expr {
  public:
    CallExpr(const std::string& fn, std::vector<std::unique_ptr<Expr>> args);
  private:
    std::string fn_identifier;
    std::vector<std::unique_ptr<Expr>> args;
  };

  class Prototype: public Expr {
  public:
    Prototype(const std::string& name, std::vector<std::string> args);
  private:
    std::string fn_name;
    std::vector<std::string> fn_args;
  };

  class Function: public Expr {
  public:
    Function(std::unique_ptr<Prototype> proto, std::unique_ptr<Expr> body);
  private:
    std::unique_ptr<Prototype> fn_prototype;
    std::unique_ptr<Expr> fn_body;
  };

}

#endif
