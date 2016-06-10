/*
  Parser.cpp
  Kaleidescope

  June 9, 2016
*/

#include "AST.h"

namespace AST {
  Expr::~Expr() {}
  /// NumberExpr - Expression class for numeric literals like "1.0".
  NumberExpr::NumberExpr(double val) : val{val} {}

  /// VariableExpr - Expression class for referencing a variable, like "a".
  VariableExpr::VariableExpr(const std::string &varName) : name{varName} {}


  /// BinaryExpr - Expression class for a binary operator.
  BinaryExpr::BinaryExpr(char op, std::unique_ptr<Expr> lhs,
                         std::unique_ptr<Expr> rhs)
    : op{op}, lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

  /// CallExpr - Expression class for function calls.
  CallExpr::CallExpr(const std::string& fn, std::vector<std::unique_ptr<Expr>> args)
    : fn_identifier{fn}, args{std::move(args)} {}

  Prototype::Prototype(const std::string& name, std::vector<std::string> args)
    : fn_name{name}, fn_args{args} {}

  Function::Function(std::unique_ptr<Prototype> proto, std::unique_ptr<Expr> body)
    : fn_prototype{std::move(proto)}, fn_body{std::move(body)} {}
}
