#pragma once

#include "token.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace TSMC {



  class Lexer {
  public:
    Lexer(const std::string &sourceCode);
    int tokenize();

  private:
    Token getNextToken(size_t &pos);
    bool checkID(size_t pos, size_t &len);
    bool checkNum(size_t pos, size_t &len);
    bool checkKeyword(size_t pos, size_t &len, TokenType &t);
    bool checkOperator(size_t pos,size_t &len, TokenType &t);
    bool checkSymbols(size_t pos, TokenType &t);

    std::string sourceString;
    std::vector<Token> tokenList;
    static const std::unordered_map<std::string, TokenType> keyword_table;
    static const std::unordered_map<std::string, TokenType> operator_table;
    static const std::unordered_map<std::string, TokenType> symbols_table;
    std::unordered_set<std::string> identifier_table;

  };

  
}
