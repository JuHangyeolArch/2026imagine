#include "vect_writer.h"


namespace AbcAsm
{

  int VectWriter::write(const std::string path, const std::vector<std::string> lines)
  {
    std::ofstream output_file;

    output_file.open(path);

    if (output_file.is_open())
      {
	for(auto &l : lines)
	  {
	    output_file<<l<<std::endl;
	  }

	return 1;
      }
    else
      {
	return 0;
      }

  }

}
