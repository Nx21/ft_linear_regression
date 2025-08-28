# Linear Regression Project

A comprehensive implementation of linear regression using gradient descent in C++, featuring normalization, command-line interface, and model evaluation tools.

## Features
- Train a linear regression model on CSV data
- Save and load model parameters
- Predict values for new data
- Evaluate model accuracy on test datasets
- Supports feature normalization
- Command-line interface for training, prediction, and evaluation

## Directory Structure
```
ft_linear_regression/
├── data/                # Example CSV data files
├── include/             # Header files
├── obj/                 # Object files (generated)
├── scripts/             # Utility scripts
├── src/                 # Source code
│   ├── train/           # Training program
│   ├── prediction/      # Prediction program
│   └── ...
├── Makefile             # Build instructions
├── model.txt            # Saved model parameters
├── README.md            # Project documentation
```

## Build Instructions

1. Clone the repository and navigate to the project directory.
2. Run:
	```sh
	make
	```
	This will build the training and prediction executables.

## Usage

### Training
Train a model using your CSV data:
```sh
./train data/data.csv
```
This will create `model.txt` with the trained parameters.

### Prediction
Predict values for new data:
```sh
./prediction feature1 feature2 ...
```
Or use a test file:
```sh
./prediction --test data/test.csv
```

### Evaluation
Evaluate model accuracy on a test set (last column must be the true value):
```sh
./prediction --eval data/test.csv
```

### Model Options
You can specify a custom model file:
```sh
./prediction --model mymodel.txt feature1 feature2 ...
```

## Model File Format
The model file (`model.txt`) contains:
- Number of features
- Feature names
- Target name
- Normalization flag
- Feature means and stds (if normalized)
- Model parameters (theta)

## License
MIT

## Author
Nx21

- **Training Program**: Train linear regression models with optional feature normalization
- **Prediction Program**: Interactive prediction interface with automatic model detection
- **Test Program**: Comprehensive model evaluation with multiple error metrics
- **Command-Line Interface**: Flexible argument parsing for all programs
- **Feature Normalization**: Z-score normalization for stable convergence
- **Model Persistence**: Save and load trained models
- **Cross-Platform**: C++ implementation with Python alternatives

## 📁 Project Structure

```
ft_linear_regression/
├── src/
│   ├── train/main.cpp      # Training program
│   ├── prediction/main.cpp # Prediction program
│   └── test/main.cpp       # Model evaluation program
├── include/
│   ├── lr/lr.hpp           # Linear regression class
│   ├── Matrix/Matrix.hpp   # Matrix operations
│   ├── MVector/MVector.hpp # Vector operations
│   └── csv_to_matrix/      # CSV parsing utilities
├── data/
│   └── data.csv           # Training dataset
├── Makefile               # Build configuration
└── scripts/               # Development utilities (git ignored)
```

## 🔧 Building

```bash
make clean && make
```

This creates three executables:
- `train` - Training program
- `prediction` - Prediction program  
- `test` - Model evaluation program

## 📖 Usage

### Training
```bash
# Basic training
./train data/data.csv

# With normalization (recommended)
./train data/data.csv --norm

# Custom learning rate
./train data/data.csv --norm --learning-rate 0.05

# Help
./train --help
```

### Prediction
```bash
./prediction
# Interactive mode - enter feature values to get predictions
```

### Model Evaluation
```bash
# Test on training data
./test

# Test on separate dataset
./test data/test_data.csv

# Custom model file
./test data/test_data.csv my_model.txt
```

## � Model Performance

| Method | R² Score | RMSE | MAE | Quality |
|--------|----------|------|-----|---------|
| With Normalization | 0.733 | 668 | 558 | GOOD |
| Without Normalization | -8.21 | 3920 | 3516 | POOR |

## 🧮 Algorithm Details

### Gradient Descent Formula
```
θⱼ := θⱼ - α × (1/m) × Σ(hθ(x⁽ⁱ⁾) - y⁽ⁱ⁾) × xⱼ⁽ⁱ⁾
```

### Feature Normalization
```
x_norm = (x - μ) / σ
```
Where μ is the mean and σ is the standard deviation.

## 🔍 Key Components

### Linear Regression Class (`lr.hpp`)
- Gradient descent implementation
- Training with configurable learning rate and iterations
- Cost function monitoring
- Parameter optimization

### Matrix Operations (`Matrix.hpp`, `MVector.hpp`)
- Custom matrix and vector classes
- Mathematical operations for linear algebra
- Memory management

### CSV Processing (`csv_to_matrix.hpp`)
- Automatic CSV parsing
- Flexible format support (last column as target)
- Data validation

## 📈 Error Metrics

The test program provides comprehensive evaluation:
- **MSE**: Mean Squared Error
- **RMSE**: Root Mean Squared Error  
- **MAE**: Mean Absolute Error
- **R²**: Coefficient of determination

## 🎯 Best Practices

1. **Always use normalization** for features with different scales
2. **Start with learning rate 0.1** for normalized data
3. **Use very small learning rates** (1e-12) for non-normalized data
4. **Monitor cost function** convergence during training
5. **Evaluate on separate test data** for realistic performance assessment

## 🔧 Development Tools

See `scripts/README.md` for additional development utilities including:
- Python implementations
- Comment removal tools
- Project summary scripts

## � License

This project is part of the 42 curriculum for learning machine learning fundamentals.

1. **Initialize weights** (usually to 0 or small random values).
2. **Compute predictions** using the current weights.
3. **Calculate the cost function** (typically MSE).
4. **Compute gradients** of the cost with respect to each weight.
5. **Update weights** using the gradient descent update rule.
6. **Repeat** steps 2–5 until convergence or the maximum number of iterations is reached.

---

## ✅ When to Use Gradient Descent

- Large datasets or high-dimensional feature spaces.
- Online or mini-batch learning scenarios.
- Preference for iterative optimization methods.

---

## 📌 Conclusion

Gradient Descent is a powerful and flexible method for optimizing linear regression models. It provides control over training dynamics and is widely used in practice due to its efficiency with large datasets.