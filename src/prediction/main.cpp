
#include "lr/lr.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main(int argc, char const *argv[])
{
    std::string model_file_name = "model.txt";
    std::string test_file_name = "";
    std::string eval_file_name = "";
    std::vector<std::string> feature_args;
    bool interactive = true;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--model" && i + 1 < argc) {
            model_file_name = argv[++i];
        } else if (arg == "--test" && i + 1 < argc) {
            test_file_name = argv[++i];
            interactive = false;
        } else if (arg == "--eval" && i + 1 < argc) {
            eval_file_name = argv[++i];
            interactive = false;
        } else {
            feature_args.push_back(arg);
            interactive = false;
        }
    }

    LR lr;
    try {
        lr.load_from_model_file(model_file_name);
        std::cout << lr << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading model: " << e.what() << std::endl;
        return 1;
    }

    if (!test_file_name.empty()) {
        lr.predict_from_test_file(test_file_name);
        return 0;
    }

    if (!eval_file_name.empty()) {
        lr.test_from_test_file(eval_file_name);
        return 0;
    }

    if (!feature_args.empty()) {
        // Single prediction from command line args
        std::vector<double> features;
        for (const auto& item : feature_args) {
            features.push_back(ft_stod(item));
        }
        if (features.size() != lr.get_theta().size() - 1) {
            std::cerr << "Error: Expected " << (lr.get_theta().size() - 1) << " features, got " << features.size() << std::endl;
            return 1;
        }
        std::vector<double> norm_features = lr.normalize_features(features);
        MVector<double> x(norm_features);
        double predicted_value = lr.prediction(x);
        std::cout << "Prediction: " << predicted_value << std::endl;
        return 0;
    }

    // Interactive mode
    size_t n_features = lr.get_theta().size() - 1;
    std::cout << "=== Interactive Prediction Mode ===" << std::endl;
    std::cout << "Enter " << n_features << " feature values separated by commas, or 'exit' to quit." << std::endl;
    std::string input;
    std::cout << lr << std::endl;
    while (true) {
        std::cout << "Features: ";
        if (!std::getline(std::cin, input)) return 0;
        trim(input, " \t\n");
        if (input == "exit" || input == "quit" || input == "q") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        if (input.empty()) {
            std::cout << "Please enter valid feature values or 'exit' to quit." << std::endl;
            continue;
        }
        std::vector<double> features;
        std::stringstream ss(input);
        std::string item;
        std::cout << "input: '" << input << "'" << std::endl;
        while (std::getline(ss, item, ',')) {
            trim(item, " \t");
            std::cout << "Item: '" << item << "'" << std::endl;
            if (!item.empty()) {
                features.push_back(ft_stod(item));
            }
        }
        
        if (features.size() != n_features) {
            std::cout << "Error: Expected " << n_features << " features, got " << features.size() << std::endl;
            continue;
        }
        MVector<double> x(features);
        double predicted_value = lr.prediction(x);
        puts("reading end");
        std::cout << "Prediction: " << predicted_value << std::endl;
    }
    return 0;
}
