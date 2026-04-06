#include "menu.h"
#include "assemble.h"


int main() {
  auto asmblr = AbcAsm::Assembler("./a.asm");

  asmblr.run();
  
  return 0;
}
