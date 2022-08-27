#include "../include/input.h"

#include "bioparser/fasta_parser.hpp"
#include "bioparser/fastq_parser.hpp"
#include "bioparser/parser.hpp"
#include "bioparser/paf_parser.hpp"

#include <iostream>
#include <memory>

std::atomic<std::uint32_t> biosoup::NucleicAcid::num_objects{0};

namespace PAFa{
Input::Input(const std::string &path) :
        path_(path) {}
bool Input::IsSuffix(const std::string &s, const std::string &suffix) {
    return s.size() >= suffix.size() && s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}
std::vector<std::unique_ptr<Overlap>> Input::ParsePAF() {
    if (IsSuffix(path_, ".paf")) {
        try {
            auto parser = bioparser::Parser<Overlap>::Create<bioparser::PafParser>(path_);
            auto overlaps = parser->Parse(-1);
            return overlaps;
        } catch (const std::invalid_argument &exception) {
            std::cerr << exception.what() << std::endl;
        }
    }

    throw std::invalid_argument("Error: Invalid file format.");
}
std::vector<std::unique_ptr<biosoup::NucleicAcid>> Input::ParseFASTAQ() {
    if (IsSuffix(path_, ".fasta") || IsSuffix(path_, ".fasta.gz") ||
            IsSuffix(path_, ".fna") || IsSuffix(path_, ".fna.gz") ||
            IsSuffix(path_, ".fa") || IsSuffix(path_, ".fa.gz")) {
        try {
            auto parser = bioparser::Parser<biosoup::NucleicAcid>::Create<bioparser::FastaParser>(path_);
            auto sequences = parser->Parse(-1);
            return sequences;
        } catch (const std::invalid_argument &exception) {
            std::cerr << exception.what() << std::endl;
        }
    }
    if (IsSuffix(path_, ".fastq") || IsSuffix(path_, ".fastq.gz") ||
            IsSuffix(path_, ".fq") || IsSuffix(path_, ".fq.gz")) {
        try {
            auto parser = bioparser::Parser<biosoup::NucleicAcid>::Create<bioparser::FastqParser>(path_);
            auto sequences = parser->Parse(-1);
            return sequences;
        } catch (const std::invalid_argument &exception) {
            std::cerr << exception.what() << std::endl;
        }
    }
    throw std::invalid_argument("Error: Invalid sequences file format.");
}
} // namespace PAFa
