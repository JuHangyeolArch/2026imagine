#include "menu.h"
#include "assemble.h"


int main() {
  auto asmblr = AbcAsm::Assembler("./b.asm");

  asmblr.run();
  
  return 0;
}
