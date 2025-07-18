/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasreddinehanafi <nasreddinehanafi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:53:13 by nasr              #+#    #+#             */
/*   Updated: 2025/07/14 11:45:00 by nasreddineh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
#define MATRIX_HPP
#include "MVector/MVector.hpp"
template <typename T>
class Matrix{
    private:
        size_t _n, _m;
        MVector<T> *_mat;
    public:
        Matrix(size_t n = 0,size_t m = 0, T def = 0)
        {
            this->_n = n;
            this->_m = m;
            this->_mat = new MVector<T>[this->_n];
            for (size_t i = 0; i < this->_n; i++)
            {
                this->_mat[i] = MVector(this->_m, def);
            }
            
        }
        Matrix(Matrix<T> const &inp)
        {
            this->_n = inp.get_nrow();
            this->_m = inp.get_ncol();
            this->_mat = new MVector<T>[this->_n];
            for (size_t i = 0; i < this->_n; i++)
            {
                this->_mat[i] = inp[i];
            }
        }
        MVector<T> &operator[](size_t  index){
            if ( index >= this->_n)
            {
                std::cout << index << std::endl;
                throw std::out_of_range("Index out of range");
            }
            return _mat[index];
        };
        MVector<T> const &operator[](size_t  index) const{
            if ( index >= this->_n)
            {
                
                std::cout << index << std::endl;
                throw std::out_of_range("Index out of range");
            }
            return _mat[index];
        };
        size_t get_nrow() const{return _n;};
        size_t get_ncol() const{return _m;};
};
#endif