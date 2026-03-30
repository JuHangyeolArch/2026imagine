#include "source_reader.h"

namespace ABCASM {

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
	this->lines.push_back(temp);
      }

      return 0;
    }
    else
    {      
      return 1;
    }
  }

  SourceReader::operator std::vector<std::string>() const
  {
    return this->lines;
  }
}
