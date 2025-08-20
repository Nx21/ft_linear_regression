#include "csv_to_matrix/csv_to_matrix.hpp"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>

void print_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " [csv_file] [--norm] [--learning-rate value]" << std::endl;
    std::cout << "  csv_file: Path to CSV data file (default: data/data.csv)" << std::endl;
    std::cout << "  --norm: Enable feature normalization" << std::endl;
    std::cout << "  --learning-rate: Set learning rate (default: 0.01 without norm, 0.1 with norm)" << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  " << program_name << " data/data.csv" << std::endl;
    std::cout << "  " << program_name << " data/data.csv --norm" << std::endl;
    std::cout << "  " << program_name << " data/data.csv --norm --learning-rate 0.05" << std::endl;
}

int main(int argc, char const *argv[])
{
    try {
        std::string filename = "data/data.csv";
        bool use_normalization = false;
        double learning_rate = -1.0;

        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];

            if (arg == "--help" || arg == "-h") {
                print_usage(argv[0]);
                return 0;
            }
            else if (arg == "--norm") {
                use_normalization = true;
            }
            else if (arg == "--learning-rate") {
                if (i + 1 < argc) {
                    learning_rate = std::stod(argv[i + 1]);
                    i++;
                } else {
                    std::cerr << "Error: --learning-rate requires a value" << std::endl;
                    print_usage(argv[0]);
                    return 1;
                }
            }
            else if (arg.find("--") == 0) {
                std::cerr << "Error: Unknown option " << arg << std::endl;
                print_usage(argv[0]);
                return 1;
            }
            else {

                filename = arg;
            }
        }

        if (learning_rate < 0) {
            learning_rate = use_normalization ? 0.1 : 1e-8;
        }

        std::cout << "Training linear regression model..." << std::endl;
        std::cout << "Reading data from: " << filename << std::endl;
        std::cout << "Normalization: " << (use_normalization ? "ENABLED" : "DISABLED") << std::endl;
        std::cout << "Learning rate: " << learning_rate << std::endl;

        auto csv = csv_to_matrix(filename);

        LR lr;

        if (csv.size() < 2) {
            std::cerr << "Error: CSV file must contain at least header and one data row" << std::endl;
            return 1;
        }

        if (csv[0].size() < 2) {
            std::cerr << "Error: CSV file must contain at least 2 columns (features and target)" << std::endl;
            return 1;
        }

        size_t n_samples = csv.size() - 1;
        size_t n_features = csv[0].size() - 1;
        Matrix<double> X(n_samples, n_features + 1, 1.0);
        MVector<double> y(n_samples);

        std::cout << "Dataset: " << n_samples << " samples" << std::endl;
        std::cout << "Features: " << n_features << " (";
        for (size_t j = 0; j < n_features; j++) {
            std::cout << csv[0][j];
            if (j < n_features - 1) std::cout << ", ";
        }
        std::cout << ")" << std::endl;
        std::cout << "Target: " << csv[0][csv[0].size() - 1] << std::endl;

        std::vector<double> feature_means(n_features, 0.0);
        std::vector<double> feature_stds(n_features, 1.0);

        if (use_normalization) {
            std::cout << "\nCalculating normalization parameters..." << std::endl;

            for (size_t i = 1; i < csv.size(); i++) {
                for (size_t j = 0; j < n_features; j++) {
                    feature_means[j] += std::stod(csv[i][j]);
                }
            }
            for (size_t j = 0; j < n_features; j++) {
                feature_means[j] /= n_samples;
            }

            for (size_t i = 1; i < csv.size(); i++) {
                for (size_t j = 0; j < n_features; j++) {
                    double val = std::stod(csv[i][j]);
                    feature_stds[j] += (val - feature_means[j]) * (val - feature_means[j]);
                }
            }
            for (size_t j = 0; j < n_features; j++) {
                feature_stds[j] = sqrt(feature_stds[j] / n_samples);
            }

            std::cout << "Feature normalization parameters:" << std::endl;
            for (size_t j = 0; j < n_features; j++) {
                std::cout << "  " << csv[0][j] << " - mean: " << feature_means[j]
                          << ", std: " << feature_stds[j] << std::endl;
            }
        }

        for (size_t i = 1; i < csv.size(); i++) {
            if (csv[i].size() != csv[0].size()) {
                std::cerr << "Error: Row " << i << " has different number of columns than header" << std::endl;
                return 1;
            }

            X[i-1][0] = 1.0;

            for (size_t j = 0; j < n_features; j++) {
                double val = std::stod(csv[i][j]);
                if (use_normalization) {
                    X[i-1][j + 1] = (val - feature_means[j]) / feature_stds[j];
                } else {
                    X[i-1][j + 1] = val;
                }
            }

            y[i-1] = std::stod(csv[i][csv[i].size() - 1]);
        }

        std::cout << "\nTraining model..." << std::endl;
        lr.train(X, y, learning_rate, 1000);

        MVector<double> theta = lr.get_theta();
        std::cout << "Training completed!" << std::endl;
        std::cout << "Learned parameters:" << std::endl;
        for (size_t i = 0; i < theta.size(); i++) {
            if (i == 0) {
                std::cout << "θ₀ (intercept): " << theta[i] << std::endl;
            } else {
                std::cout << "θ" << i << " (" << csv[0][i-1] << "): " << theta[i] << std::endl;
            }
        }

        std::ofstream model_file("model.txt");
        if (model_file.is_open()) {

            model_file << n_features << std::endl;

            for (size_t j = 0; j < n_features; j++) {
                model_file << csv[0][j] << std::endl;
            }

            model_file << csv[0][csv[0].size() - 1] << std::endl;

            model_file << (use_normalization ? 1 : 0) << std::endl;

            if (use_normalization) {
                for (size_t j = 0; j < n_features; j++) {
                    model_file << feature_means[j] << std::endl;
                }
                for (size_t j = 0; j < n_features; j++) {
                    model_file << feature_stds[j] << std::endl;
                }
            }

            for (size_t i = 0; i < theta.size(); i++) {
                model_file << theta[i] << std::endl;
            }
            model_file.close();
            std::cout << "Model saved to: model.txt" << std::endl;
        } else {
            std::cerr << "Warning: Could not save model to file" << std::endl;
        }

        std::cout << "Linear model: " << csv[0][csv[0].size() - 1] << " = " << theta[0];
        for (size_t i = 1; i < theta.size(); i++) {
            std::cout << " + " << theta[i] << " * " << csv[0][i-1];
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const char* e) {
        std::cerr << "Error: " << e << std::endl;
        return 1;
    }

    return 0;
}
