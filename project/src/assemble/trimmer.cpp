#include "trimmer.h"

namespace AbcAsm {

  std::string Trimmer::trim(const std::string &line)
  {
    auto comment_pos = line.find('/');

    auto uncommented_line = (comment_pos == std::string::npos) ? line : line.substr(0,comment_pos);

    auto startl = uncommented_line.find_first_not_of(" \t\n\r\f\v");
    if(startl == std::string::npos) return "";
    auto endl = uncommented_line.find_last_not_of(" \t\n\r\f\v");

    auto trimmed_line = uncommented_line.substr(startl,endl -startl +1);

    return trimmed_line;
  }
}
