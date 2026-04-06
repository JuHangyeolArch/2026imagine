#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace AbcAsm {

  class SourceReader {    
  public:
    SourceReader();
    int read(const std::string &path);
    operator std::vector<std::string>() const;
    
  private:
    std::vector<std::string> lines;
    static int is_white_space(const std::string str);
  };
}
