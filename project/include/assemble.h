#pragma once

#include "source_reader.h"
#include "trimmer.h"

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

namespace ABCASM{
  class Assembler {
  public:
    Assembler(const std::string &path);
    void run();
  private:
    void read();
    void trim_line();
    void do_pass1();
    void do_pass2();
    
    std::string file_path;
    std::vector<std::string> lines;
    std::vector<std::string> fined_lines;
    std::unordered_map<std::string,int> symbol_table;
  };

} // namespace ABCASM
