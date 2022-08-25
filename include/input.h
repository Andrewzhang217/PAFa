#ifndef PAFA_SRC_INPUT_H_
#define PAFA_SRC_INPUT_H_

#include <vector>
#include <memory>

#include "bioparser/parser.hpp"
#include "biosoup/nucleic_acid.hpp"
#include "overlap.h"

namespace PAFa {
class Input {
  public:
    explicit Input(const std::string &path);
    std::vector<std::unique_ptr<Overlap>> ParsePAF();
    std::vector<std::unique_ptr<biosoup::NucleicAcid>> ParseFASTAQ();

  private:
    static bool IsSuffix(const std::string &s, const std::string &suffix);
    const std::string &path_;
};
} // namespace PAFa

#endif //PAFA_SRC_INPUT_H_
