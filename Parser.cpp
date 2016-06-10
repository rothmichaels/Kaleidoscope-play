/*
  Parser.cpp
  Kaleidescope

  June 9, 2016
*/


#include <string>
#include <vector>

#include "Lexer.h"
#include "AST.h"

namespace Parser {
  static int CurrentToken;

  static int getNextToken() {
    return CurrentToken = Lexer::gettok();
  }

  /// LogError* - These are little helper functions for error handling.
  std::unique_ptr<AST::Expr> LogError(const char *str) {
    fprintf(stderr, "LogError: %s\n", str);
    return nullptr;
  }
  std::unique_ptr<AST::Prototype> LogErrorP(const char *str) {
    LogError(str);
    return nullptr;
  }

  static std::unique_ptr<AST::Expr> ParseExpression() {
    return nullptr;
  }

  /// numberexpr ::= number
  static std::unique_ptr<AST::Expr> ParseNumberExpr() {
    auto Result = std::unique_ptr<AST::NumberExpr>{new AST::NumberExpr{Lexer::NumVal}};
    getNextToken(); // consume the number
    return std::move(Result);
  }

  /// parenexpr ::= '(' expression ')'
  static std::unique_ptr<AST::Expr> ParseParenExpr() {
    getNextToken(); // eat (.
    auto V = ParseExpression();
    if (!V)
      return nullptr;

    if (CurrentToken != ')')
      return LogError("expected ')'");
    getNextToken(); // eat ).
    return V;
  }

  /// identifierexpr
  ///   ::= identifier
  ///   ::= identifier '(' expression* ')'
  static std::unique_ptr<AST::Expr> ParseIdentifierExpr() {
    std::string identifierName = Lexer::IdentifierStr;
    getNextToken();
    // not followed by paren, so var not fn
    if (CurrentToken != '(') {
      return std::unique_ptr<AST::VariableExpr>{new AST::VariableExpr{identifierName}};
    }

    // fn call
    getNextToken(); // eat (
    std::vector<std::unique_ptr<AST::Expr>> args;
    if (CurrentToken != ')') {
      while (true) {
        if (auto arg = ParseExpression()) {
          args.push_back(std::move(arg));
        } else {
          return nullptr;
        }
        if (CurrentToken == ')') {
          break;
        }

        if (CurrentToken != ',') {
          return LogError("Expected ')' or ',' in argument list.");
        }

        getNextToken();
      }
    }

    getNextToken(); // eat )

    return std::unique_ptr<AST::CallExpr>{new AST::CallExpr{identifierName,std::move(args)}};
  }

  /// primary
  ///   ::= identifierexpr
  ///   ::= numberexpr
  ///   ::= parenexpr
  static std::unique_ptr<AST::Expr> ParsePrimary() {
    switch (CurrentToken) {
    case Lexer::TokenIdentifier:
      return ParseIdentifierExpr();
    case Lexer::TokenNumber:
      return ParseNumberExpr();
    case '(':
      return ParseParenExpr();
    default:
      return LogError("unkown token when expecting expression");
    }
  }

  
}

