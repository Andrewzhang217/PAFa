#ifndef PAFA_INCLUDE_ANALYSER_H_
#define PAFA_INCLUDE_ANALYSER_H_

#include "biosoup/nucleic_acid.hpp"
#include "../include/alias.h"
#include "../include/data_structure.h"

#include <memory>
#include <string>

namespace PAFa {
class Analyser {
  public:
    Analyser(const std::string &paf_file_path, const std::string &sequence_file_path);
    [[nodiscard]] double FindPrecision() const;
    [[nodiscard]] double FindRecall() const;
    void FindTruePafOverlaps();
    void FindAllTrueOverlaps();
    std::uint32_t num_of_paf_overlaps = 0;
    std::uint32_t num_of_true_paf_overlaps = 0;
    std::uint32_t num_of_false_positives = 0;
    std::uint32_t num_of_false_negatives = 0;
    std::uint32_t num_of_true_overlaps = 0;

  private:
    const std::string &paf_file_path_;
    const std::string &sequence_file_path_;
    std::vector<std::unique_ptr<Sequence>> targets_;
    std::vector<std::unique_ptr<Overlap>> paf_overlaps_;
    SetOverlaps all_true_overlaps_;
    void Initialise();
    std::vector<std::unique_ptr<Sequence>> ConvertToSequence(std::vector<std::unique_ptr<biosoup::NucleicAcid>> &raw_sequences);
    static bool comp(const std::unique_ptr<Sequence> &first, const std::unique_ptr<Sequence> &second);
    bool IsTrueOverlap(std::unique_ptr<Sequence> &lhs, std::unique_ptr<Sequence> &rhs);
    bool IsSameContig(std::string_view lhs_name, std::string_view rhs_name);
    std::pair<std::uint32_t,
              std::uint32_t> FindRange(std::unique_ptr<biosoup::NucleicAcid> &sequence); // Extract the start_ and end_ positions of the simulated read
};

} // namespace PAFa

#endif //PAFA_INCLUDE_ANALYSER_H_
