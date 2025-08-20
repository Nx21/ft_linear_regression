#include "Matrix/Matrix.hpp"
#include "csv_to_matrix/csv_to_matrix.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

void normalize_features(Matrix<double>& X, const std::vector<double>& means, const std::vector<double>& stds) {
    size_t m = X.get_nrow();
    size_t n = X.get_ncol();

    for (size_t i = 0; i < m; i++) {
        for (size_t j = 1; j < n; j++) {
            X[i][j] = (X[i][j] - means[j-1]) / stds[j-1];
        }
    }
}

bool load_model(const std::string& filename, std::vector<std::string>& feature_names,
                std::string& target_name, std::vector<double>& theta,
                bool& is_normalized, std::vector<double>& means, std::vector<double>& stds) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open model file: " << filename << std::endl;
        return false;
    }

    std::string line;

    if (!std::getline(file, line)) return false;
    int num_features = std::stoi(line);

    feature_names.resize(num_features);
    for (int i = 0; i < num_features; i++) {
        if (!std::getline(file, feature_names[i])) return false;
    }

    if (!std::getline(file, target_name)) return false;

    if (!std::getline(file, line)) return false;
    is_normalized = (std::stoi(line) == 1);

    if (is_normalized) {
        means.resize(num_features);
        stds.resize(num_features);
        for (int i = 0; i < num_features; i++) {
            if (!std::getline(file, line)) return false;
            means[i] = std::stod(line);
        }
        for (int i = 0; i < num_features; i++) {
            if (!std::getline(file, line)) return false;
            stds[i] = std::stod(line);
        }
    }

    theta.resize(num_features + 1);
    for (int i = 0; i < num_features + 1; i++) {
        if (!std::getline(file, line)) return false;
        theta[i] = std::stod(line);
    }

    file.close();
    return true;
}

std::vector<double> predict(const Matrix<double>& X, const std::vector<double>& theta) {
    size_t m = X.get_nrow();
    std::vector<double> predictions(m);

    for (size_t i = 0; i < m; i++) {
        double pred = 0;
        for (size_t j = 0; j < theta.size(); j++) {
            pred += theta[j] * X[i][j];
        }
        predictions[i] = pred;
    }

    return predictions;
}

void calculate_metrics(const std::vector<double>& y_true, const std::vector<double>& y_pred) {
    size_t m = y_true.size();

    double mse = 0;
    for (size_t i = 0; i < m; i++) {
        double error = y_pred[i] - y_true[i];
        mse += error * error;
    }
    mse /= m;

    double rmse = std::sqrt(mse);

    double mae = 0;
    for (size_t i = 0; i < m; i++) {
        mae += std::abs(y_pred[i] - y_true[i]);
    }
    mae /= m;

    double y_mean = 0;
    for (size_t i = 0; i < m; i++) {
        y_mean += y_true[i];
    }
    y_mean /= m;

    double ss_tot = 0, ss_res = 0;
    for (size_t i = 0; i < m; i++) {
        ss_tot += (y_true[i] - y_mean) * (y_true[i] - y_mean);
        ss_res += (y_true[i] - y_pred[i]) * (y_true[i] - y_pred[i]);
    }

    double r_squared = 1 - (ss_res / ss_tot);

    std::cout << "\n=== MODEL EVALUATION METRICS ===" << std::endl;
    std::cout << "Number of test samples: " << m << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Mean Squared Error (MSE): " << mse << std::endl;
    std::cout << "Root Mean Squared Error (RMSE): " << rmse << std::endl;
    std::cout << "Mean Absolute Error (MAE): " << mae << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "R-squared (R²): " << r_squared << std::endl;

    std::cout << "\n=== INTERPRETATION ===" << std::endl;
    std::cout << "• RMSE: On average, predictions are off by ±" << std::fixed << std::setprecision(0) << rmse << " units" << std::endl;
    std::cout << "• MAE: Average absolute error is " << mae << " units" << std::endl;
    std::cout << "• R²: Model explains " << std::fixed << std::setprecision(1) << (r_squared * 100) << "% of the variance in the data" << std::endl;

    if (r_squared > 0.8) {
        std::cout << "• Model quality: EXCELLENT" << std::endl;
    } else if (r_squared > 0.6) {
        std::cout << "• Model quality: GOOD" << std::endl;
    } else if (r_squared > 0.4) {
        std::cout << "• Model quality: FAIR" << std::endl;
    } else {
        std::cout << "• Model quality: POOR" << std::endl;
    }
}

void print_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " [test_csv_file] [model_file]" << std::endl;
    std::cout << "  test_csv_file: Path to test CSV data file (default: data/data.csv)" << std::endl;
    std::cout << "  model_file: Path to trained model file (default: model.txt)" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  " << program_name << " test_data.csv model.txt" << std::endl;
    std::cout << "  " << program_name << " data/data.csv" << std::endl;
    std::cout << "  " << program_name << std::endl;
}

int main(int argc, char** argv) {
    std::string test_file = "data/data.csv";
    std::string model_file = "model.txt";

    if (argc > 3) {
        print_usage(argv[0]);
        return 1;
    }

    if (argc >= 2) {
        if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
            print_usage(argv[0]);
            return 0;
        }
        test_file = argv[1];
    }

    if (argc == 3) {
        model_file = argv[2];
    }

    std::cout << "=== MODEL TESTING PROGRAM ===" << std::endl;
    std::cout << "Test data file: " << test_file << std::endl;
    std::cout << "Model file: " << model_file << std::endl;

    std::vector<std::string> feature_names;
    std::string target_name;
    std::vector<double> theta;
    bool is_normalized;
    std::vector<double> means, stds;

    if (!load_model(model_file, feature_names, target_name, theta, is_normalized, means, stds)) {
        std::cerr << "Failed to load model from " << model_file << std::endl;
        return 1;
    }

    std::cout << "\n=== LOADED MODEL INFO ===" << std::endl;
    std::cout << "Features: ";
    for (size_t i = 0; i < feature_names.size(); i++) {
        std::cout << "'" << feature_names[i] << "'";
        if (i < feature_names.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    std::cout << "Target: '" << target_name << "'" << std::endl;
    std::cout << "Normalization: " << (is_normalized ? "ENABLED" : "DISABLED") << std::endl;

    if (is_normalized) {
        std::cout << "Normalization parameters:" << std::endl;
        for (size_t i = 0; i < feature_names.size(); i++) {
            std::cout << "  " << feature_names[i] << " - mean: " << means[i] << ", std: " << stds[i] << std::endl;
        }
    }

    std::cout << "Model parameters:" << std::endl;
    std::cout << "  θ₀ (intercept): " << theta[0] << std::endl;
    for (size_t i = 0; i < feature_names.size(); i++) {
        std::cout << "  θ" << (i+1) << " (" << feature_names[i] << "): " << theta[i+1] << std::endl;
    }

    std::cout << "\n=== LOADING TEST DATA ===" << std::endl;
    Matrix<double> X;
    MVector<double> y;
    std::vector<std::string> loaded_features;

    try {
        auto csv = csv_to_matrix(test_file);
        if (csv.size() < 2) {
            throw "CSV file must have at least a header and one data row";
        }

        std::vector<std::string> header = csv[0];
        size_t target_col = header.size() - 1;

        loaded_features.clear();
        for (size_t i = 0; i < header.size() - 1; i++) {
            loaded_features.push_back(header[i]);
        }

        std::cout << "Test dataset loaded successfully:" << std::endl;
        std::cout << "Number of samples: " << (csv.size() - 1) << std::endl;
        std::cout << "Number of features: " << loaded_features.size() << std::endl;

        bool features_match = true;
        if (loaded_features.size() != feature_names.size()) {
            features_match = false;
        } else {
            for (size_t i = 0; i < feature_names.size(); i++) {
                if (loaded_features[i] != feature_names[i]) {
                    features_match = false;
                    break;
                }
            }
        }

        if (!features_match) {
            std::cerr << "Error: Test data features don't match model features!" << std::endl;
            std::cerr << "Model expects: ";
            for (size_t i = 0; i < feature_names.size(); i++) {
                std::cerr << feature_names[i];
                if (i < feature_names.size() - 1) std::cerr << ", ";
            }
            std::cerr << std::endl;
            std::cerr << "Test data has: ";
            for (size_t i = 0; i < loaded_features.size(); i++) {
                std::cerr << loaded_features[i];
                if (i < loaded_features.size() - 1) std::cerr << ", ";
            }
            std::cerr << std::endl;
            return 1;
        }

        size_t m = csv.size() - 1;
        size_t n = feature_names.size() + 1;

        X = Matrix<double>(m, n, 1.0);
        y = MVector<double>(m);

        for (size_t i = 1; i < csv.size(); i++) {
            if (csv[i].size() != header.size()) {
                throw "Inconsistent number of columns in CSV";
            }

            y[i-1] = std::stod(csv[i][target_col]);

            for (size_t j = 0; j < feature_names.size(); j++) {
                X[i-1][j+1] = std::stod(csv[i][j]);
            }
        }

    } catch (const char* error) {
        std::cerr << "Error loading test data: " << error << std::endl;
        return 1;
    }

    if (is_normalized) {
        std::cout << "Applying feature normalization..." << std::endl;
        normalize_features(X, means, stds);
    }

    std::cout << "\n=== MAKING PREDICTIONS ===" << std::endl;
    std::vector<double> predictions = predict(X, theta);

    std::vector<double> y_true(y.size());
    for (size_t i = 0; i < y.size(); i++) {
        y_true[i] = y[i];
    }

    calculate_metrics(y_true, predictions);

    std::cout << "\n=== SAMPLE PREDICTIONS ===" << std::endl;
    std::cout << std::left << std::setw(8) << "Sample" << std::setw(12) << "Actual"
              << std::setw(12) << "Predicted" << std::setw(12) << "Error" << std::setw(12) << "Error%" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    size_t samples_to_show = std::min((size_t)10, y_true.size());
    for (size_t i = 0; i < samples_to_show; i++) {
        double error = predictions[i] - y_true[i];
        double error_percent = std::abs(error / y_true[i]) * 100;

        std::cout << std::left << std::setw(8) << (i+1)
                  << std::setw(12) << std::fixed << std::setprecision(0) << y_true[i]
                  << std::setw(12) << std::fixed << std::setprecision(0) << predictions[i]
                  << std::setw(12) << std::fixed << std::setprecision(0) << error
                  << std::setw(12) << std::fixed << std::setprecision(1) << error_percent << "%"
                  << std::endl;
    }

    if (y_true.size() > samples_to_show) {
        std::cout << "... and " << (y_true.size() - samples_to_show) << " more samples" << std::endl;
    }

    std::cout << "\n=== TESTING COMPLETED ===" << std::endl;
    return 0;
}
