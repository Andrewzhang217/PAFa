#ifndef PAFA_SRC_INPUT_H_
#define PAFA_SRC_INPUT_H_

#include <vector>
#include <memory>

#include "overlap.h"

namespace PAFa {
class Input {
  public:

    explicit Input(const std::string &path);
    std::vector<std::unique_ptr<Overlap>> Sequences();

  private:

    static bool IsSuffix(const std::string &s, const std::string &suff);
    void ParseFile();
    const std::string &path_;
    std::vector<std::unique_ptr<Overlap>> overlaps_;
};
} // namespace PAFa

#endif //PAFA_SRC_INPUT_H_
