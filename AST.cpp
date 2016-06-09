/*
  Parser.cpp
  Kaleidescope

  June 9, 2016
*/

#include <string>
#include <vector>

/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  virtual ~ExprAST() {}
};

/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST {
public:
  NumberExprAST(double val) : val{val} {}
private:
  double val; // TODO: const?
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
public:
  VariableExprAST(const std::string &varName) : name{varName} {}
private:
  std::string name;
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
public:
  BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs,
                std::unique_ptr<ExprAST> rhs)
    : op{op}, lhs{std::move(lhs)}, rhs{std::move(rhs)} {}
private:
  char op;
  std::unique_ptr<ExprAST> lhs, rhs;
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
public:
  CallExprAST(const std::string& fn, std::vector<std::unique_ptr<ExprAST>> args)
    : fn_identifier{fn}, args{std::move(args)} {}
private:
  std::string fn_identifier;
  std::vector<std::unique_ptr<ExprAST>> args;
};

class PrototypeAST: public ExprAST {
public:
  PrototypeAST(const std::string& name, std::vector<std::string> args)
    : fn_name{name}, fn_args{args} {}
private:
  std::string fn_name;
  std::vector<std::string> fn_args;
};

class FunctionAST: public ExprAST {
public:
  FunctionAST(std::unique_ptr<PrototypeAST> proto, std::unique_ptr<ExprAST> body)
    : fn_prototype{std::move(proto)}, fn_body{std::move(body)} {}
private:
  std::unique_ptr<PrototypeAST> fn_prototype;
  std::unique_ptr<ExprAST> fn_body;
};
