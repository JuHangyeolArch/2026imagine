#include "source_reader.h"
#include <iostream>

namespace AbcAsm {

  SourceReader::SourceReader()
  {

  }

  int SourceReader::read(const std::string &path)
  {
    std::ifstream input_file;
    std::string temp;
    
    input_file.open(path);

    if (input_file.is_open())
    {
      while (std::getline(input_file,temp))
      {
        if (!this->is_white_space(temp))
	{
          this->lines.push_back(temp);
        }
      }

      input_file.close();

      return 1;
    }
    else
    {      
      return 0;
    }
  }

  int SourceReader::is_white_space(const std::string str)
  {
    if(!str.empty())
    {
      for (auto &c : str)
      {
        if (!std::isspace(c))
	{
	  return 0;
	}
      }
    }

    return 1;
  }

  SourceReader::operator std::vector<std::string>() const
  {
    return this->lines;
  }
}
