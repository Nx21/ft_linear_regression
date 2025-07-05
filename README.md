# Linear Regression Using Gradient Descent

This project demonstrates how to perform **Linear Regression** using **Gradient Descent**, an optimization algorithm used to minimize the cost function and find the best-fit line for a given dataset.

---

## 📘 Overview

Linear regression is a fundamental algorithm in machine learning for modeling the relationship between a dependent variable and one or more independent variables.

While the **Normal Equation** offers an analytical solution, **Gradient Descent** provides a scalable alternative—especially useful when:
- The number of features is large.
- The feature matrix is non-invertible.
- You want iterative control over learning and convergence.

---

## ⚙️ How Gradient Descent Works

Gradient Descent minimizes the **Mean Squared Error (MSE)** by updating the model's weights (θ) iteratively using the following update rule:

\[
\theta_j := \theta_j - \alpha \cdot \frac{1}{m} \sum_{i=1}^{m} \left(h_\theta(x^{(i)}) - y^{(i)}\right) x_j^{(i)}
\]

### 🔍 Explanation of Terms

| Symbol | Description |
|--------|-------------|
| \( \alpha \) | Learning rate — controls the step size during each iteration. |
| \( m \) | Number of training examples. |
| \( h_\theta(x^{(i)}) \) | Hypothesis (predicted value) for the \(i^{th}\) input. |
| \( x^{(i)} \) | Feature vector of the \(i^{th}\) training example. |
| \( y^{(i)} \) | Actual target value for the \(i^{th}\) example. |
| \( x_j^{(i)} \) | Value of the \(j^{th}\) feature for the \(i^{th}\) example. |

---

## 🧠 Key Points

- **Learning Rate (α)**:
  - Too small → slow convergence.
  - Too large → risk of overshooting or divergence.
- **Number of Iterations**:
  - Must be chosen carefully to ensure convergence.
  - Can be set manually or determined using convergence criteria.

---

## 🛠️ Practical Implementation Steps

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