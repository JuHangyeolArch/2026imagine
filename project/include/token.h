#pragma once

#include <string>

namespace TSMC {


  enum class TokenType {
    
    // EOF
    END_OF,
      
    // Identifiers
    ID,
    
    // Numbers
    NUMBER,
    
    // Keywords
    INT,
    IF,
    ELSE,
    WHILE,
    RETURN,
    
    // Operator
    PLUS,
    MINUS,
    STAR,
    SLASH,
    ASSIGN,
    EQUAL,
    AMPER,
    
    // Symbols
    L_PARENTH,
    R_PARENTH,
    L_BRACE,
    R_BRACE,
    SEMIC,
    COMMA,
    
    
    //ERROR
    ERR
    };
  
  class Token {
  public:    
    Token(TokenType t, std::string v);

    operator std::string() const;
    TokenType getType();
    bool isEOF();
    bool isNumber();
    bool isID();
    bool isKeyword();
    bool isOperator();
    bool isSymbol();

  private:
    std::string value;
    TokenType type;
  };


  
}
