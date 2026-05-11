#include "token.h"

namespace TSMC {

  TokenType Token::getType() { return type; }

  Token::Token(TokenType t, std::string v) : type(t), value(v) {}

  Token::operator std::string() const {return value;}
  
  bool Token::isKeyword() {
    return type == TokenType::INT || type == TokenType::IF ||
      type == TokenType::ELSE || type == TokenType::WHILE ||
      type == TokenType::RETURN;
  }

  bool Token::isNumber() {
    return type == TokenType::NUMBER;
  }
  bool Token::isID() {
    return type == TokenType::ID;
  }
  bool Token::isEOF() {
    return type == TokenType::END_OF;
  }
  bool Token::isOperator() {
    return type == TokenType::PLUS || type == TokenType::MINUS ||
      type == TokenType::STAR || type == TokenType::SLASH ||
      type == TokenType::ASSIGN || type == TokenType::EQUAL ||
      type == TokenType:: AMPER;
  }
  bool Token::isSymbol() {
    return type == TokenType::L_PARENTH || type == TokenType::R_PARENTH ||
      type == TokenType::L_BRACE || type == TokenType::R_BRACE ||
      type == TokenType:: SEMIC || type == TokenType:: COMMA;
  }

}
