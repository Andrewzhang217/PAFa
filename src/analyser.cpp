#include "../include/analyser.h"
#include "../include/input.h"

#include <algorithm>    // std::sort
#include <cassert>
#include <memory>

namespace PAFa {
Analyser::Analyser(const std::string &paf_file_path, const std::string &sequence_file_path) : paf_file_path_(
        paf_file_path), sequence_file_path_(sequence_file_path) {
    Initialise();
}
void Analyser::Initialise() {
    Input paf{paf_file_path_};
    Input fastaq{sequence_file_path_};
    auto paf_overlaps_raw = paf.ParsePAF();
    for (auto &paf_overlap : paf_overlaps_raw) {
        paf_overlaps_.emplace(paf_overlap->q_name_, paf_overlap->t_name_);
    }
    num_of_paf_overlaps = paf_overlaps_.size();
    auto nucleic_acid = fastaq.ParseFASTAQ();
    targets_ = ConvertToSequence(nucleic_acid);
    FindAllTrueOverlaps();
    FindTruePafOverlaps();
}
std::vector<std::unique_ptr<Sequence>> Analyser::ConvertToSequence(std::vector<std::unique_ptr<biosoup::NucleicAcid>> &raw_sequences) {
    std::vector<std::unique_ptr<Sequence>> dst;
    for (auto &ptr : raw_sequences) {
        auto range = FindRange(ptr);
        dst.emplace_back(std::make_unique<Sequence>(ptr->name, range.first, range.second, ptr->id));
    }
    return dst;
}
bool Analyser::comp(const std::unique_ptr<Sequence> &first, const std::unique_ptr<Sequence> &second) {
    return first->start_ < second->start_;
}
void Analyser::FindAllTrueOverlaps() {
    SetOverlaps set;
    std::sort(targets_.begin(), targets_.end(), comp);
    for (auto lhs = targets_.begin(); lhs != targets_.end(); ++lhs) {
        for (auto rhs = lhs + 1; rhs != targets_.end(); ++rhs) {
            if (rhs->get()->start_ > lhs->get()->end_) break;
            if (IsTrueOverlap(*lhs, *rhs))
                set.emplace(lhs->get()->name_, rhs->get()->name_);
        }
    }
    num_of_true_overlaps = set.size();
    all_true_overlaps_ = std::move(set);
}
bool Analyser::IsTrueOverlap(std::unique_ptr<Sequence> &lhs, std::unique_ptr<Sequence> &rhs) {
    if (!IsSameContig(lhs->name_, rhs->name_)) return false;
    return (lhs->end_ >= rhs->start_ && rhs->end_ >= lhs->start_);
}
bool Analyser::IsSameContig(std::string_view lhs_name, std::string_view rhs_name) {
    auto curr_lhs = std::find_if(lhs_name.begin(), lhs_name.end(), [](auto c) { return c == '_'; });
    auto curr_rhs = std::find_if(rhs_name.begin(), rhs_name.end(), [](auto c) { return c == '_'; });
    return lhs_name.substr(0, curr_lhs - lhs_name.begin()) == rhs_name.substr(0, curr_rhs - rhs_name.begin());
}
std::pair<std::uint32_t, std::uint32_t> Analyser::FindRange(std::unique_ptr<biosoup::NucleicAcid> &sequence) {
    std::string name = sequence->name;
    std::uint32_t start = 0;
    std::uint32_t len = 0;
    auto curr = std::find_if(name.begin(), name.end(), [](auto c) { return c == '_'; });
    curr++;
    for (; std::isdigit(*curr); ++curr) {
        start *= 10;
        start += *curr - '0';
    }
    int underscore_count = 1;
    for (; underscore_count < 6; ++curr) {
        if (*curr == '_') underscore_count++;
    }
    for (; std::isdigit(*curr); ++curr) {
        len *= 10;
        len += *curr - '0';
    }
    return {start, start + len};
}
void Analyser::FindTruePafOverlaps() {
    assert(!paf_overlaps_.empty());
    if (all_true_overlaps_.empty()) return;
    int true_positive = 0;
    for (const auto &overlap : paf_overlaps_) {
        if (all_true_overlaps_.find(overlap) != all_true_overlaps_.end()) {
            ++true_positive;
        }
    }
    num_of_true_paf_overlaps = true_positive;
    num_of_false_positives = num_of_paf_overlaps - true_positive;
    num_of_false_negatives = num_of_true_overlaps - true_positive;
}
double Analyser::FindPrecision() const {
    assert(!paf_overlaps_.empty());
    return static_cast<double> (num_of_true_paf_overlaps) / static_cast<double>(num_of_paf_overlaps);
}
double Analyser::FindRecall() const {
    // tp / (tp + fn)
    // fn is the number of overlaps in true but not found by RAM
    if (num_of_true_overlaps == 0) return 0;
    return static_cast<double> (num_of_true_paf_overlaps) / static_cast<double> (num_of_true_overlaps);
}
} // namespace PAFa
