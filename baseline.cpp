// Copyright 2019, Nikita Kazeev, Higher School of Economics
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <vector>
#include <limits>

#include "./parser.h"
#include "ripped_evaluator/evaluator.h"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    const std::string MODEL_FILE = "track_2_model.cbm";
    NCatboostStandalone::TOwningEvaluator evaluator(MODEL_FILE);
    // Skip header
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::setprecision(std::numeric_limits<float>::max_digits10);
    std::cout << "id,prediction\n";
    while (std::cin.good() && std::cin.peek() != EOF) {
	std::vector<float> features(100);
        size_t id;
        ugly_hardcoded_parse(std::cin, &id, &features);
        std::swap(features[53], features[45]);

        for (int i = 0; i < 27; i++) {
            std::swap(features[i + 62], features[i + 46]);
        }


        // for (int i=0; i < 72; i++) {
        //     std::cout<<i << " " << features[i] <<std::endl;
        // } 
        // break;
        const float prediction = \
            evaluator.Apply(features, NCatboostStandalone::EPredictionType::RawValue);
        std::cout << id << DELIMITER << prediction  << '\n';
    }
    return 0;
}
