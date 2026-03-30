#include "trimmer.h"

namespace ABCASM {

  std::string Trimmer::trim(const std::string &line)
  {
    auto comment_pos = line.find('/');

    auto trimmed_line = (comment_pos == std::string::npos) ? line : line.substr(0,comment_pos);

    return trimmed_line;
  }
}
