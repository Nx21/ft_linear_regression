# ft_linear_regression

A simple linear regression implementation in C++ to predict car prices based on mileage. This project implements a basic machine learning algorithm that uses gradient descent to find the optimal parameters for a linear function.

## Overview

This project consists of two main programs:
1. `predict` - Predicts the price of a car for a given mileage
2. `train` - Trains the model using gradient descent on the provided dataset

The program uses the following hypothesis for price prediction:
```
estimatePrice(mileage) = θ₀ + (θ₁ * mileage)
```

## Requirements

- C++ compiler (supporting C++11 or later)
- Make

## Project Structure

```
ft_linear_regression/
├── src/
│   ├── predict
│   ├── train
│   └── utils
├── include/
│   └── 
├── data/
│   ├── predict
│   ├── train
│   └── utils
├── Makefile
└── README.md
```

## Building the Project

To build both programs, simply run:
```bash
make all
```

This will create two executables:
- `predict` - for price prediction
- `train` - for training the model

## Usage

### Training the Model

```bash
./train data/data.csv
```

The training program will:
1. Read the dataset from the specified CSV file
2. Perform linear regression using gradient descent
3. Save the computed parameters (θ₀ and θ₁) to a file for later use in prediction

### Predicting Prices

```bash
./predict
```

The prediction program will:
1. Load the trained parameters
2. Prompt you for a mileage value
3. Output the estimated price for the given mileage

## Implementation Details

### Training Algorithm

The training program implements gradient descent using the following formulas:

```
tmpθ₀ = learningRate * (1/m) * Σ(estimatePrice(mileage[i]) - price[i])
tmpθ₁ = learningRate * (1/m) * Σ(estimatePrice(mileage[i]) - price[i]) * mileage[i]
```

Where:
- m is the number of training examples
- learningRate is the step size for gradient descent
- estimatePrice uses the current θ₀ and θ₁ values

### Data Format

The training data should be provided in a CSV file with the following format:
```
mileage,price
240000,3650
139800,3800
150500,4400
...
```

## Visualization

The project includes data visualization capabilities to:
- Plot the training data points
- Display the regression line
- Show the convergence of the gradient descent algorithm

## Error Metrics

The program calculates and displays various error metrics to evaluate the model's performance:
- Mean Squared Error (MSE)
- R-squared (R²) value
- Mean Absolute Error (MAE)

## License

This project is part of the 42 school curriculum.

## Author

EDDINE Nasr

## Acknowledgments

Based on the ft_linear_regression project from 42 school.
https://cdn.intra.42.fr/pdf/pdf/143936/en.subject.pdf