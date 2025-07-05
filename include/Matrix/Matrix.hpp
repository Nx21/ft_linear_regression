/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasr <nasr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:11:12 by nasr              #+#    #+#             */
/*   Updated: 2025/06/28 15:22:52 by nasr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREDICTION_HPP
#define PREDICTION_HPP
#include <vector>

template <typename T> 
class Matrix
{
private:
    int _nrow, _ncol;
    std::vector<std::vector<T> > mat;
public:
    Matrix(int nrow = 1, int n_col = 1, T def = 0);
    Matrix(Matrix<T> M);
    
    ~Matrix();
};

#endif
