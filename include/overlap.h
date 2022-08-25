#ifndef PAFA_INCLUDE_OVERLAP_H_
#define PAFA_INCLUDE_OVERLAP_H_

#include <memory>

namespace PAFa {
class Overlap {
  public:
    Overlap(const char *q_name,
            std::uint32_t q_name_len,
            std::uint32_t q_len,
            std::uint32_t q_begin,
            std::uint32_t q_end,
            char orientation,
            const char *t_name,
            std::uint32_t t_name_len,
            std::uint32_t t_len,
            std::uint32_t t_begin,
            std::uint32_t t_end,
            std::uint32_t num_matches,
            std::uint32_t overlap_len,
            std::uint32_t quality
    );
  private:
    const char *q_name_;
    std::uint32_t q_name_len_;
    std::uint32_t q_len_;
    std::uint32_t q_begin_;
    std::uint32_t q_end_;
    const char *t_name_;
    std::uint32_t t_name_len_;
    std::uint32_t t_len_;
    std::uint32_t t_begin_;
    std::uint32_t t_end_;
    std::uint32_t num_matches_;
    std::uint32_t overlap_len_;
    std::uint32_t quality_;
    char orientation_;
};

} // namespace PAFa
#endif //PAFA_INCLUDE_OVERLAP_H_
