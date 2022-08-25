#include "../include/input.h"

#include "bioparser/parser.hpp"
#include "bioparser/paf_parser.hpp"

#include <iostream>
#include <memory>

namespace PAFa{
Input::Input(const std::string &path) :
        path_(path) {
    ParseFile();
}

void Input::ParseFile() {
    if (IsSuffix(path_, ".paf")) {
        try {
            auto parser = bioparser::Parser<Overlap>::Create<bioparser::PafParser>(path_);
            overlaps_ = parser->Parse(-1);
            return;
        } catch (const std::invalid_argument &exception) {
            std::cerr << exception.what() << std::endl;
            return;
        }
    }

    throw std::invalid_argument("Error: Invalid PAF file format.");
}

bool Input::IsSuffix(const std::string &s, const std::string &suffix) {
    return s.size() >= suffix.size() && s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}
std::vector<std::unique_ptr<Overlap>> Input::Sequences() {
    return std::move(overlaps_);
}
} // namespace PAFa
