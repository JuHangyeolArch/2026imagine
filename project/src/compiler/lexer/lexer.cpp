#include "lexer.h"
#include <cctype>
#include <iostream>

namespace TSMC {

int skipWhiteSpace(const std::string &input, size_t pos) {
  while (pos < input.length() &&
         std::isspace(static_cast<unsigned char>(input[pos]))) {
    pos++;
  }

  return pos;
}

  Lexer::Lexer(const std::string &sourceCode)
    : tokenList({}), sourceString(sourceCode), identifier_table({}) {}

  
  int Lexer::tokenize() {

    size_t pos = 0;
    while ((tokenList.empty())||(tokenList.back().getType() != TokenType::END_OF)) {
      tokenList.push_back(getNextToken(pos));
    }

    for (auto &token : tokenList) {
      std::string s = token;
      std::cout<<s<<" "<<(int)token.getType()<<std::endl;
      
    }
    
    return 0;
  }
  /*

    다음 토큰을 탐색, 테이블과 비교하여 토큰 객체를 반환
    
   */
  Token Lexer::getNextToken(size_t &pos) {
    pos = skipWhiteSpace(sourceString, pos);
    TokenType t;
    size_t len = 0;
    std::string word;
    
    if (checkNum(pos,len)) {
      word = sourceString.substr(pos,len);
      t = TokenType::NUMBER;
    }
    else if (checkKeyword(pos, len, t)) {
      word = sourceString.substr(pos, len);     
      
    }
    else if (checkID(pos,len)) {
      word = sourceString.substr(pos, len);
      identifier_table.insert(word);
      t = TokenType::ID;
      
    }
    else if (checkOperator(pos,len, t)) {
      word = sourceString.substr(pos, len);
      
    }
    else if (checkSymbols(pos, t)) {
      word = sourceString.substr(pos, len);
    }
    else if (pos == sourceString.length()) {
      word = "";
      t = TokenType::END_OF;
    }
    else {
      len =0;
      for (; pos + len <= sourceString.length() &&
             !std::isspace(sourceString[pos + len]);
           len++);
      word = sourceString.substr(pos,len);
      
      t = TokenType::ERR;
    }

    pos +=len;

    return Token(t, word);
  }

  /*

    각 종류의 토큰을 구별한다.
    
   */
  bool Lexer::checkID(size_t pos, size_t &len) {
    /*
      식별자는
      -소문자로 시작해야한다.
      -소문자, 대문자, 숫자, 또는 언더바를 사용할 수 있다.
     */
    len = 0;
    if (std::islower(sourceString[pos])) {
      for (; pos + len <= sourceString.length() &&
	     (std::islower(sourceString[pos + len]) ||
	      std::isupper(sourceString[pos + len]) ||
	      std::isdigit(sourceString[pos + len]) ||
	      (sourceString[pos + len] == '_'));
           ++len);
      return 1;      
    }
    else {
      return 0;
    }
    
  }
  bool Lexer::checkNum(size_t pos, size_t &len) {
    /*
      숫자는 0|[1-9][0-9]* 의 경우를 만족해야함.
      -0이 가장 앞에 오면 1의자리인 0밖에 없음.
      -1~9가 왔다면 뒤에 0이 나올 수 있음.

     */
    len = 0;
    if (sourceString[pos] == '0') {
      ++len;
      if (std::isupper(sourceString[pos + 1]) ||
	  std::islower(sourceString[pos + 1]) ||
          std::isdigit(sourceString[pos + 1])) { return 0;}
      return 1;
    }
    else if (std::isdigit(sourceString[pos])) {
      for (; pos + len <= sourceString.length() &&
             std::isdigit(sourceString[pos + len]);
           ++len);
      if (std::isupper(sourceString[pos + len]) ||
          std::islower(sourceString[pos + len])) {
	return 0;
      }
      else{
        return 1;
      }
    }
    else {
      return 0;
    }
  }

  /*

    전부 소문자인경우 키워드 테이블을 검색한다.

   */
    
  bool Lexer::checkKeyword(size_t pos, size_t &len, TokenType &t) {
    len = 0;
    if (islower(sourceString[pos])) {
      for (; pos + len <= sourceString.length() &&
             std::islower(sourceString[pos + len]); ++len);
      auto it = keyword_table.find(sourceString.substr(pos,len));
      if (it != keyword_table.end()) {
	t = it->second; 
        return 1;
      }
      else {
	return 0;
      }
    }
    else {

      return 0;
    }
  }

  /*

    연산자는 긴 것부터 짧은 것 순으로 찾는다.

   */

  bool Lexer::checkOperator(size_t pos, size_t &len, TokenType &t) {
    for (len = 2; len > 0; --len) {
      if (pos + len <= sourceString.length()) {
	std::string cand = sourceString.substr(pos, len);
        if (operator_table.count(cand)) {
          t = operator_table.at(cand);
	  return 1;
        }	
      }
    }
    return 0;
  }
  /*
    한 글자로 된 구문 기호를 찾는다.

   */
  
  bool Lexer::checkSymbols(size_t pos, TokenType &t) {
    auto it = symbols_table.find(sourceString.substr(pos,1));

    if (it != symbols_table.end()) {
      t = it->second;
      return 1;
    }
    else {
      return 0;
    }
  }   

  /*
   키워드, 연산자, 기호에 대한 테이블
    
   */
  const std::unordered_map<std::string, TokenType> Lexer::keyword_table = {
    {"int", TokenType::INT},{"if", TokenType::IF},
    {"else", TokenType::ELSE},{"while", TokenType::WHILE},
    {"return", TokenType::RETURN}};
  
  const std::unordered_map<std::string, TokenType> Lexer::operator_table = {
    {"+", TokenType::PLUS},   {"-", TokenType::MINUS},
    {"*", TokenType::STAR},   {"/", TokenType::SLASH},
    {"=", TokenType::ASSIGN}, {"==", TokenType::EQUAL},
    {"&", TokenType::AMPER}};
  const std::unordered_map<std::string, TokenType> Lexer::symbols_table = {
      {"(", TokenType::L_PARENTH}, {")", TokenType::R_PARENTH},
      {"{", TokenType::L_BRACE},   {"}", TokenType::R_BRACE},
      {";", TokenType::SEMIC},     {",", TokenType::COMMA},
  };

  
}
