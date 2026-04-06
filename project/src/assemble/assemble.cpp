#include "assemble.h"
#include <iostream>

namespace AbcAsm{

  Assembler::Assembler(const std::string &path)
  {
    this->file_path = path;
  }

  void Assembler::run()
  {
    this->read();
    this->trim_line();

    std::cout<<"###first pass###"<<std::endl;
    this->first_pass();
    std::cout<<"\n\n"<<"###second pass###"<<std::endl;
    this->second_pass();

    VectWriter::write("hello.txt",this->machine_codes);
    
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
      std::cout<<this->fined_lines.back()<<std::endl;
    }
  }

  void Assembler::first_pass()
  {
    auto lc = 0;
    for (const auto &line : this->fined_lines)
    {
      std::stringstream ss(line);
      std::string token;
      if(!(ss>>token)) continue;

      if (token.back() == ',')
      {
	auto label = token.substr(0, token.size() -1);
        this->symbol_table.insert({label,lc});
	std::cout<<label<<":"<<std::hex<<symbol_table[label]<<std::endl;
	++lc;

      }
      else if (token == "ORG")
      {
	ss>>std::hex>>lc;
      }

      else if (token == "END")
      {
	break;
      }
      else
      {
	  ++lc;
      }
    }
  }

  void Assembler::second_pass()
  {
    auto lc = 0;

    for (const auto &line : this->fined_lines)
    {
      std::string machine_line = "";

      if (this->sp_line(line, machine_line, lc)) {
        this->machine_codes.push_back(machine_line);
	std::cout<<machine_line;
	++lc;
      }
      std::cout<<std::endl;
    }
  }

  int  Assembler::sp_line(const std::string &line, std::string &dest,int &lc)
  {
      std::stringstream ss;
      auto unlab_line = remove_label(line);
      auto is_line = 0;
      uint16_t  val = 0;

      std::cout<<unlab_line<<" ->   ";

      if (this->handle_pseudo(unlab_line, lc, val, is_line))
      {
	
      }
      else if (handle_mri(unlab_line,val))
      {
	is_line = 1;
      }
      else if (handle_nomri(unlab_line, val))
      {
	is_line = 1;
      }
      else if (HexTool::ishexstr(unlab_line))
      {
	is_line = 1;
      }
      else
      {
	std::cerr<<unlab_line<<std::endl<<"not valid memory address"<<std::endl;
      }

      ss<<"@"<<std::hex<<std::setfill('0')<<std::setw(3)<<std::uppercase<<lc;
      ss<<" "<<std::hex<<std::setfill('0')<<std::setw(4)<<std::uppercase<<val;
      
      dest = ss.str();

      return is_line;
  }

  std::string Assembler::remove_label(const std::string &line)
  {
    std::stringstream ss(line);
    std::string temp;

    ss>>temp;

    if (temp.back() == ',')
    {
      std::cout<<line.substr(0,ss.tellg())<<"   ";
      return Trimmer::trim(line.substr(ss.tellg()));
    }

    return line;
  }

  int Assembler::handle_pseudo(const std::string &line, int &lc, uint16_t &val,int &is_line)
  {
    std::stringstream ss(line);
    std::string token;
    ss>>token;

    if (token == "ORG")
    {
      ss>>std::hex>>lc;
      is_line = 0;
    }
	
    else if (token == "END")
    {
      is_line = 0;
      
    }
	
    else if (token == "HEX")
    {
      ss>>std::hex>>val;
      is_line = 1;
    }

    else if (token == "DEC")
    {
      ss>>val;
      is_line = 1;
    }
    else
    {
      return 0;
    }

    return 1;
  }
  
  int Assembler::handle_mri(const std::string &line, uint16_t &val)
  {
    std::stringstream ss(line);
    std::string token;
    
    ss>>token;

    auto it = this->mri_table.find(token);

    if (it != this->mri_table.end())
    {
	val += it->second;

	ss>>token;

	it =this->symbol_table.find(token);

        if (HexTool::ishexstr(token))
	{

        }
	else if (it != this->symbol_table.end())
	{
	  val += it->second;
        }
	else
	{
	  std::cerr<<"fuck you\n";
        }

	ss>>token;

	if(token=="I") val+= 0x8000;

        return 1;
    }
    else
    {
      return 0;
    }
  }
  int Assembler::handle_nomri(const std::string &line, uint16_t &val)
  {
    std::stringstream ss(line);
    std::string token;
    
    ss>>token;

    auto it = this->rri_table.find(token);

    if (it != this->rri_table.end())
    {
      val = it->second;
    }

    else
    {
      it = this->io_table.find(token);

      if (it != this->io_table.end())
      {
	val = it->second;
      }
      else
      {
	return 0;
      }
    }

    return 1;
  }

  const std::unordered_map<std::string, int> Assembler::mri_table = {{"AND",0x0000}, {"ADD",0x1000}, {"LDA",0x2000},
                                                                     {"STA", 0x3000}, {"BUN", 0x4000}, {"BSA",0x5000},
                                                                     {"ISZ",0x6000}};

  const std::unordered_map<std::string, int> Assembler::rri_table = {
    {"CLA",0x7800}, {"CLE",0x7400}, {"CMA",0x7200}, {"CME",0x7100}, {"CIR",0x7080}, {"CIL",0x7040}, {"INC",0x7020},
    {"SPA",0x7010}, {"SNA",0x7008}, {"SZA",0x7004}, {"SZE",0x7002}, {"HLT",0x7001}};

  const std::unordered_map<std::string, int> Assembler::io_table = {
    {"INP",0xF800}, {"OUT",0xF400}, {"SKI",0xF200}, {"SKO",0xF100},
    {"ION",0xF080}, {"IOF",0xF040}};
}
