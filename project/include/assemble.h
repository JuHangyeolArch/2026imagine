#pragma once

#include "source_reader.h"
#include "vect_writer.h"
#include "trimmer.h"
#include "hextool.h"

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <cstdint>

namespace AbcAsm{
  class Assembler {
  public:
    Assembler(const std::string &path);
    void run();
  private:
    void read();
    void trim_line();
    void first_pass();
    void second_pass();
    int sp_line(const std::string &source, std::string &dest, int &lc);

    std::string remove_label(const std::string &line);
    int handle_pseudo(const std::string &line, int &lc, uint16_t &val, int &is_line);
    int handle_mri(const std::string &line, uint16_t &val);
    int handle_nomri(const std::string &line, uint16_t &val);
    
    std::string file_path;
    std::vector<std::string> lines;
    std::vector<std::string> fined_lines;
    std::unordered_map<std::string,int> symbol_table;
    std::vector<std::string> machine_codes;

    static const std::unordered_map<std::string,int> mri_table;
    static const std::unordered_map<std::string,int> rri_table;
    static const std::unordered_map<std::string,int> io_table;
    
  };

} // namespace ABCASM
