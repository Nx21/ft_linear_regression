/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasreddinehanafi <nasreddinehanafi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:33:44 by nasreddineh       #+#    #+#             */
/*   Updated: 2025/07/14 11:46:04 by nasreddineh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LR_HPP
#define LR_HPP


#include "Matrix/Matrix.hpp"
#include <cstddef>

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
            puts("read_csv mid");
        }
        
        ~LR(){
            
        };
};
std::ostream& operator<<(std::ostream& os, const LR& obj) {
    
    os << obj.get_theta();
    
    return os;
}

#endif