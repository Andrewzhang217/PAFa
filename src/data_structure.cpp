#include "../include/data_structure.h"

namespace PAFa {
Overlap::Overlap(const char *q_name,
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
                 std::uint32_t quality) : q_name_(q_name),
                                          q_name_len_(q_name_len),
                                          q_len_(q_len),
                                          q_begin_(q_begin),
                                          q_end_(q_end),
                                          orientation_(orientation),
                                          t_name_(t_name),
                                          t_name_len_(t_name_len),
                                          t_len_(t_len),
                                          t_begin_(t_begin),
                                          t_end_(t_end),
                                          num_matches_(num_matches),
                                          overlap_len_(overlap_len),
                                          quality_(quality) {};

Sequence::Sequence(const std::string &name, uint32_t start, uint32_t anEnd, std::uint32_t id)
        : name_(name), start_(start), end_(anEnd), id_(id) {}
}
