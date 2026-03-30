#include "assemble.h"

namespace ABCASM{

  Assembler::Assembler(const std::string &path)
  {
    this->file_path = path;
  }

  void Assembler::run()
  {
    this->read();
    this->trim_line();
    

  }

  void Assembler::read()
  {
    auto sr = SourceReader();
    sr.read(this->file_path);
    this->lines = sr;
    
  }

  void Assembler::trim_line()
  {
    for (const auto &line : this->lines)
    {
      this->fined_lines.push_back((Trimmer::trim(line)));
    }
  }

  void Assembler::do_pass1()
  {
    auto lc = 0;
    for (const auto &line : this->fined_lines)
    {
      std::stringstream ss(line);
      std::string token;
      if(!(ss>>token)) continue;

      if (token.back() == ',')
      {
	std::string label = token.substr(0, token.size() -1);
        this->symbol_table.insert({label,lc});
	++lc;
	continue;

      }
      else if (token == "ORG")
      {
	ss>>std::hex>>lc;
	continue;
      }

      else if (token == "END")
      {
	break;
      }
    }
  }

  void Assembler::do_pass2()
  {


  }
  
}
