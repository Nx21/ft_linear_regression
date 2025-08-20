#include "Matrix/Matrix.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

double ft_stod(const std::string &s)
{

    if (s.find_first_not_of("0123456789.-+") != s.npos ||
        std::count(s.begin(), s.end(), '.') > 1) {
        std::cerr << "Error: Invalid number format '" << s << "'" << std::endl;
        exit(1);
    }

    try {
        return std::stod(s);
    } catch (const std::exception& e) {
        std::cerr << "Error: Cannot convert '" << s << "' to number" << std::endl;
        exit(1);
    }
}

double estimatePrice(const std::vector<double>& theta, const std::vector<double>& features)
{
    if (theta.size() != features.size() + 1) {
        std::cerr << "Error: Dimension mismatch between theta and features" << std::endl;
        exit(1);
    }

    double result = theta[0];
    for (size_t i = 0; i < features.size(); i++) {
        result += theta[i + 1] * features[i];
    }
    return result;
}

std::vector<double> parseFeatureInput(const std::string& input, size_t expected_features)
{
    std::vector<double> features;
    std::stringstream ss(input);
    std::string item;

    while (std::getline(ss, item, ',')) {

        item.erase(0, item.find_first_not_of(" \t"));
        item.erase(item.find_last_not_of(" \t") + 1);

        if (!item.empty()) {
            features.push_back(ft_stod(item));
        }
    }

    if (features.size() != expected_features) {
        std::cerr << "Error: Expected " << expected_features << " features, got " << features.size() << std::endl;
        exit(1);
    }

    return features;
}

std::vector<double> normalizeFeatures(const std::vector<double>& features,
                                     const std::vector<double>& means,
                                     const std::vector<double>& stds)
{
    std::vector<double> normalized(features.size());
    for (size_t i = 0; i < features.size(); i++) {
        normalized[i] = (features[i] - means[i]) / stds[i];
    }
    return normalized;
}

int main(int argc, char const *argv[])
{
    size_t n_features = 0;
    std::vector<std::string> feature_names;
    std::string target_name;
    std::vector<double> theta;
    bool use_normalization = false;
    std::vector<double> feature_means;
    std::vector<double> feature_stds;

    try {

        std::ifstream model_file("model.txt");
        if (model_file.is_open()) {
            model_file >> n_features;

            feature_names.resize(n_features);
            for (size_t i = 0; i < n_features; i++) {
                model_file >> feature_names[i];
            }

            model_file >> target_name;

            int norm_flag;
            model_file >> norm_flag;
            use_normalization = (norm_flag == 1);

            if (use_normalization) {
                feature_means.resize(n_features);
                feature_stds.resize(n_features);

                for (size_t i = 0; i < n_features; i++) {
                    model_file >> feature_means[i];
                }
                for (size_t i = 0; i < n_features; i++) {
                    model_file >> feature_stds[i];
                }
            }

            theta.resize(n_features + 1);
            for (size_t i = 0; i < theta.size(); i++) {
                model_file >> theta[i];
            }

            model_file.close();

            std::cout << "=== LOADED TRAINED MODEL ===" << std::endl;
            std::cout << "Number of features: " << n_features << std::endl;
            std::cout << "Features: ";
            for (size_t i = 0; i < n_features; i++) {
                std::cout << "'" << feature_names[i] << "'";
                if (i < n_features - 1) std::cout << ", ";
            }
            std::cout << std::endl;
            std::cout << "Target variable: '" << target_name << "'" << std::endl;
            std::cout << "Normalization: " << (use_normalization ? "ENABLED" : "DISABLED") << std::endl;

            if (use_normalization) {
                std::cout << "\nNormalization parameters:" << std::endl;
                for (size_t i = 0; i < n_features; i++) {
                    std::cout << "  " << feature_names[i] << " - mean: " << feature_means[i]
                              << ", std: " << feature_stds[i] << std::endl;
                }
            }

            std::cout << "Parameters:" << std::endl;
            std::cout << "θ₀ (intercept): " << theta[0] << std::endl;
            for (size_t i = 1; i < theta.size(); i++) {
                std::cout << "θ" << i << " (" << feature_names[i-1] << "): " << theta[i] << std::endl;
            }

            std::cout << "Model equation: " << target_name << " = " << theta[0];
            for (size_t i = 1; i < theta.size(); i++) {
                std::cout << " + " << theta[i] << " * " << feature_names[i-1];
            }
            std::cout << std::endl << std::endl;

        } else {
            std::cout << "No trained model found (model.txt). Using default parameters." << std::endl;
            std::cout << "Run the training program first to get better predictions." << std::endl;
            std::cout << "Assuming single feature (default behavior)..." << std::endl;
            n_features = 1;
            feature_names = {"feature"};
            target_name = "target";
            theta = {0.0, 0.0};
            std::cout << std::endl;
        }

        if (argc == 2) {

            std::vector<double> raw_features = parseFeatureInput(argv[1], n_features);
            std::vector<double> features = raw_features;

            if (use_normalization) {
                features = normalizeFeatures(raw_features, feature_means, feature_stds);
            }

            double predicted_value = estimatePrice(theta, features);

            std::cout << "Input features:" << std::endl;
            for (size_t i = 0; i < raw_features.size(); i++) {
                std::cout << "  " << feature_names[i] << ": " << raw_features[i];
                if (use_normalization) {
                    std::cout << " (normalized: " << features[i] << ")";
                }
                std::cout << std::endl;
            }
            std::cout << "Estimated " << target_name << ": " << predicted_value << std::endl;

        } else if (argc == 1) {

            std::cout << "=== " << target_name << " Prediction ===" << std::endl;
            std::cout << "Enter values for the features to get " << target_name << " estimation:" << std::endl;
            std::cout << "Format: ";
            for (size_t i = 0; i < n_features; i++) {
                std::cout << feature_names[i];
                if (i < n_features - 1) std::cout << ",";
            }
            std::cout << std::endl << std::endl;

            while (true) {
                std::cout << "Enter values (";
                for (size_t i = 0; i < n_features; i++) {
                    std::cout << feature_names[i];
                    if (i < n_features - 1) std::cout << ",";
                }
                std::cout << "): ";

                std::string input;
                std::getline(std::cin, input);

                if (input == "exit" || input == "quit" || input == "q") {
                    std::cout << "Goodbye!" << std::endl;
                    break;
                }

                if (input.empty()) {
                    std::cout << "Please enter valid feature values or 'exit' to quit." << std::endl;
                    continue;
                }

                try {
                    std::vector<double> raw_features = parseFeatureInput(input, n_features);
                    std::vector<double> features = raw_features;

                    if (use_normalization) {
                        features = normalizeFeatures(raw_features, feature_means, feature_stds);
                    }

                    double predicted_value = estimatePrice(theta, features);

                    std::cout << "Input features:" << std::endl;
                    for (size_t i = 0; i < raw_features.size(); i++) {
                        std::cout << "  " << feature_names[i] << ": " << raw_features[i];
                        if (use_normalization) {
                            std::cout << " (normalized: " << features[i] << ")";
                        }
                        std::cout << std::endl;
                    }
                    std::cout << "Estimated " << target_name << ": " << predicted_value << std::endl;
                    std::cout << std::endl;

                } catch (...) {
                    std::cout << "Invalid input. Please enter valid numbers separated by commas." << std::endl;
                }
            }

        } else {
            std::cerr << "Usage: " << argv[0] << " [feature_values]" << std::endl;
            std::cerr << "  - No arguments: Interactive mode" << std::endl;
            std::cerr << "  - One argument: Predict " << target_name << " for given feature values" << std::endl;
            std::cerr << "  - Feature format: ";
            for (size_t i = 0; i < n_features; i++) {
                std::cout << feature_names[i];
                if (i < n_features - 1) std::cout << ",";
            }
            std::cerr << std::endl;
            return 1;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
