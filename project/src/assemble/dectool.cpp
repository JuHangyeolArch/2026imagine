#include "dectool.h"

namespace AbcAsm
{

  int DecTool::isdecstr(const std::string &str)
  {
    
    for (char c : str)
    {
      if(!std::isdigit(c))
	return false;
    }
    return true;
  }
  



}
