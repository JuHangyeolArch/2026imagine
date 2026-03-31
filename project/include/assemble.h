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
    void first_pass();
    void second_pass();
    
    std::string file_path;
    std::vector<std::string> lines;
    std::vector<std::string> fined_lines;
    std::unordered_map<std::string,int> symbol_table;
  };

} // namespace ABCASM
