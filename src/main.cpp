#include "iostream"
#include <string>
#include <getopt.h>

#include "../include/analyser.h"

int main(int argc, char **argv) {

    std::string sequence_file_path = argv[1];
    std::string paf_file_path = argv[2];
    PAFa::Analyser analyser{paf_file_path, sequence_file_path};
    std::cout << "Number of true positives: " << analyser.num_of_true_paf_overlaps << "\n";
    std::cout << "Number of false positives: " << analyser.num_of_false_positives << "\n";
    std::cout << "Number of false negatives: " << analyser.num_of_false_negatives << "\n";
    std::cout << "Precision: " << analyser.FindPrecision() << std::endl;
    std::cout << "Recall: " << analyser.FindRecall() << std::endl;
    return 0;
}
