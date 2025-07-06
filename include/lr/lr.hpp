
#ifndef LR_HPP
#define LR_HPP


#include "Matrix/Matrix.hpp"

class LR
{
    private:
        MVector<double> _theta;
    public:
        LR(){};
        LR(MVector<double> const &theta):_theta(theta){};
        void    set_theta(std::vector<double> const &vec)
        {
            _theta = MVector(vec);
        }
        void    train(Matrix<double> const &X , MVector<double> const &y,double alpha = 1, size_t iterations = 100)
        {
            size_t n = X.get_ncol(), m = X.get_nrow();
            double cst = alpha/m;
            MVector<double> h(m);
            _theta = MVector<double>(n, 1);
            for (size_t itr = 0; itr < iterations; itr++)
            {
                for (size_t i = 0; i < m; i++)
                {
                    h[i] = _theta * X[i] - y[i];
                }
                for (size_t j = 0; j < n; j++)
                {
                    double sum = 0;
                    for (size_t i = 0; i < m; i++)
                    {
                        sum += h[i] * X[i][j];
                    }
                    _theta[j] -= cst * sum;
                }
            }
        }
        double  predection(MVector<double> const &x)
        {
            return x * _theta;
        }
        MVector<double> get_theta() const {
            return _theta;
        }
        
        ~LR();
};
std::ostream& operator<<(std::ostream& os, const LR& obj) {
    os << obj.get_theta();
    return os;
}

LR::LR()
{
}

LR::~LR()
{
}

#endif