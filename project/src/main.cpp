//#include "menu.h"
#include "assemble.h"
#include "compiler.h"
#include "lexer.h"

int main() {
  // auto asmblr = AbcAsm::Assembler("./b.asm");
  // asmblr.run();

  auto lex = TSMC::Lexer("int + * 1 2 0 12 012 1abc ");
  lex.tokenize();
  
  return 0;
}
