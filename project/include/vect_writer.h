#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace AbcAsm
{
  class VectWriter
  {
  public:
    static int write(const std::string path, const std::vector<std::string> lines);

  private:
    
  };

}
