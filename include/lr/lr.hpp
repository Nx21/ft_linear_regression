#include "trim.hpp"
#ifndef LR_HPP
#define LR_HPP

#include "Matrix/Matrix.hpp"
#include "ft_stod.hpp"
#include <cstddef>

class LR
       
{
    private:
        MVector<double> _theta;
        bool _use_normalization = false;
        std::vector<double> _feature_means;
        std::vector<double> _feature_stds;
        public:
        friend std::ostream& operator<<(std::ostream& os, const LR& obj);
        LR(){};
        LR(MVector<double> const &theta):_theta(theta){};
        void test_from_test_file(const std::string& test_file_name) {
            std::ifstream test_file(test_file_name);
            if (!test_file.is_open()) {
                std::cerr << "Could not open test file: " << test_file_name << std::endl;
                return;
            }
            size_t expected_features = _theta.size() - 1;
            std::string line;
            size_t line_num = 0;
            size_t total = 0, correct = 0;
            double total_error = 0.0;
            while (std::getline(test_file, line)) {
                line_num++;
                std::vector<double> features;
                std::stringstream ss(line);
                std::string item;
                std::vector<std::string> items;
                while (std::getline(ss, item, ',')) {
                    trim(item, " \t");
                    items.push_back(item);
                }
                if (items.size() != expected_features + 1) {
                    std::cerr << "Line " << line_num << ": Expected " << expected_features << " features plus 1 solution, got " << items.size() << std::endl;
                    continue;
                }
                for (size_t i = 0; i < expected_features; i++) {
                    if (!items[i].empty()) {
                        try {
                            features.push_back(ft_stod(items[i]));
                        } catch (...) {
                            std::cerr << "Line " << line_num << ": Invalid number '" << items[i] << "'" << std::endl;
                            break;
                        }
                    } else {
                        std::cerr << "Line " << line_num << ": Empty feature value" << std::endl;
                        break;
                    }
                }
                if (features.size() != expected_features) {
                    std::cerr << "Line " << line_num << ": Expected " << expected_features << " features, got " << features.size() << std::endl;
                    continue;
                }
                double true_value = 0.0;
                try {
                    true_value = ft_stod(items[expected_features]);
                } catch (...) {
                    std::cerr << "Line " << line_num << ": Invalid true value '" << items[expected_features] << "'" << std::endl;
                    continue;
                }
                MVector<double> x(features);
                double predicted_value = this->prediction(x);
                double error = std::abs(predicted_value - true_value);
                double error_percent = (true_value != 0.0) ? (error / std::abs(true_value)) * 100.0 : 0.0;
                total_error += error_percent;
                total++;
                std::cout << "Line " << line_num << ": Prediction = " << predicted_value << ", True = " << true_value << ", Error = " << error << " (" << error_percent << "%)" << std::endl;
            }
            test_file.close();
            if (total > 0) {
                double avg_error_percent = total_error / total;
                double accuracy = 100.0 - avg_error_percent;
                std::cout << "\nTested " << total << " cases. Average error percentage: " << avg_error_percent << "%\n";
                std::cout << "Accuracy: " << accuracy << "%\n";
            } else {
                std::cout << "No valid test cases found." << std::endl;
            }
        }
        std::vector<double> normalize_features(const std::vector<double>& features) const {
            if (!_use_normalization || _feature_means.size() != features.size() || _feature_stds.size() != features.size())
                return features;
            std::vector<double> normalized(features.size());
            for (size_t i = 0; i < features.size(); i++) {
                normalized[i] = (features[i] - _feature_means[i]) / _feature_stds[i];
            }
            return normalized;
        }
        void predict_from_test_file(const std::string& test_file_name) {
            std::ifstream test_file(test_file_name);
            if (!test_file.is_open()) {
                std::cerr << "Could not open test file: " << test_file_name << std::endl;
                return;
            }
            size_t expected_features = _theta.size() - 1;
            std::string line;
            size_t line_num = 0;
            while (std::getline(test_file, line)) {
                line_num++;
                std::vector<double> features;
                std::stringstream ss(line);
                std::string item;
                while (std::getline(ss, item, ',')) {
                    trim(item, " \t");
                    if (!item.empty()) {
                        try {
                            features.push_back(ft_stod(item));
                        } catch (...) {
                            std::cerr << "Line " << line_num << ": Invalid number '" << item << "'" << std::endl;
                            features.clear();
                            break;
                        }
                    }
                    else {
                        std::cerr << "Line " << line_num << ": Empty feature value" << std::endl;
                        features.clear();
                        break;
                    }
                }
                if (features.size() != expected_features) {
                    std::cerr << "Line " << line_num << ": Expected " << expected_features << " features, got " << features.size() << std::endl;
                    continue;
                }
                MVector<double> x(features);
                double predicted_value = this->prediction(x);
                std::cout << "Line " << line_num << ": Prediction = " << predicted_value << std::endl;
            }
            test_file.close();
        }
        void set_theta(std::vector<double> const &vec)
        {
            _theta = MVector(vec);
        }
        void load_from_model_file(const std::string& model_file_name) {
            std::ifstream model_file(model_file_name);
            if (!model_file.is_open()) {
                throw std::runtime_error("Could not open model file: " + model_file_name);
            }
            size_t n_features;
            model_file >> n_features;
            std::vector<std::string> feature_names(n_features);
            for (size_t i = 0; i < n_features; i++) {
                model_file >> feature_names[i];
            }
            std::string target_name;
            model_file >> target_name;
            int norm_flag;
            model_file >> norm_flag;
            _use_normalization = (norm_flag == 1);
            if (_use_normalization) {
                _feature_means.resize(n_features);
                _feature_stds.resize(n_features);
                for (size_t i = 0; i < n_features; i++) {
                    model_file >> _feature_means[i];
                }
                for (size_t i = 0; i < n_features; i++) {
                    model_file >> _feature_stds[i];
                }
            }
            std::vector<double> theta(n_features + 1);
            for (size_t i = 0; i < theta.size(); i++) {
                model_file >> theta[i];
            }
            model_file.close();
            set_theta(theta);
        }
        void    train(Matrix<double> const &X , MVector<double> const &y, double alpha = 0.01, size_t iterations = 1000)
        {
            size_t n = X.get_ncol(), m = X.get_nrow();
            _theta = MVector<double>(n, 0);

            for (size_t itr = 0; itr < iterations; itr++)
            {

                MVector<double> predictions(m);
                for (size_t i = 0; i < m; i++)
                {
                    predictions[i] = _theta * X[i];
                }

                MVector<double> gradients(n, 0);
                for (size_t j = 0; j < n; j++)
                {
                    double sum = 0;
                    for (size_t i = 0; i < m; i++)
                    {
                        sum += (predictions[i] - y[i]) * X[i][j];
                    }
                    gradients[j] = sum / m;
                }

                for (size_t j = 0; j < n; j++)
                {
                    _theta[j] = _theta[j] - alpha * gradients[j];
                }

                if (itr % 100 == 0)
                {
                    double cost = 0;
                    for (size_t i = 0; i < m; i++)
                    {
                        double error = predictions[i] - y[i];
                        cost += error * error;
                    }
                    cost = cost / (2 * m);
                    std::cout << "Iteration " << itr << ", Cost: " << cost << std::endl;
                }
            }
        }
        double prediction(const MVector<double>& x_raw) {
            MVector<double> features = x_raw;
            puts("pred");
            if (_use_normalization) {
                puts("norm");
                for (size_t i = 0; i < features.size(); ++i) {
                    std::cout << "feature_means " << i << ": " << _feature_means[i] << std::endl;
                    std::cout << "feature_stds " << i << ": " << _feature_stds[i] << std::endl;
                    features[i] = (features[i] - _feature_means[i]) / _feature_stds[i];
                    std::cout << "Normalized feature " << i << ": " << features[i] << std::endl;
                }
            }
            double result = _theta[0];
            for (size_t i = 0; i < features.size(); i++)
            {
                result += features[i] * _theta[i + 1];
            } 
            return result;
        }
        MVector<double> const &get_theta() const {
            return _theta;
        }
        void read_csv(std::vector<std::vector<std::string> > const &csv, std::string const &out)
        {
            puts("read_csv begin");
            if(csv.size() < 1  || find(csv[0].begin(),csv[0].end(),out) == csv[0].end())
            throw "csv error";
            size_t n = csv.size(), m = csv[0].size();
            Matrix<double> x(n -1, m + 1,  1);
            MVector <double> y(n -1);

            puts("read_csv mid");
            for(int i = 1; i < n; i++)
            {
                if(csv[i].size() != m)
                    throw "csv format error";
                size_t k = 1;
                for(int j = 0; j < m; j++)
                {
                    if(csv[0][j] == out)
                    y[i - 1] = std::stod(csv[i][j]);
                    else
                    {
                        x[i - 1][k] = std::stod(csv[i][j]);
                        k++;
                    }
                }
            }
            std::cout << y << std::endl;
        }

        ~LR(){

        };
};

std::ostream& operator<<(std::ostream& os, const LR& obj) {
    os << "=== LOADED TRAINED MODEL ===\n";
    os << "Parameters: " << obj.get_theta().size() - 1 << " features\n";
    os << "Normalization: " << (obj._use_normalization ? "ENABLED" : "DISABLED") << "\n";
    if (obj._use_normalization) {
        os << "Normalization parameters:" << std::endl;
        for (size_t i = 0; i < obj._feature_means.size(); i++) {
            os << "  Feature " << i << " - mean: " << obj._feature_means[i]
               << ", std: " << obj._feature_stds[i] << std::endl;
        }
    }
    os << "Theta (parameters):" << std::endl;
    os << "θ₀ (intercept): " << obj.get_theta()[0] << std::endl;
    for (size_t i = 1; i < obj.get_theta().size(); i++) {
        os << "θ" << i << ": " << obj.get_theta()[i] << std::endl;
    }
    return os;
}

#endif