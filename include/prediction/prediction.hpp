/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasr <nasr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:38:28 by nasr              #+#    #+#             */
/*   Updated: 2025/01/25 10:36:31 by nasr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREDICTION_HPP
#define PREDICTION_HPP
#include "utils/estimatePrice.hpp"

class Prediction
{
private:
    std::vector <double> _teta;
public:
    Prediction();
    Prediction(const std::vector <double> teta);
    double predict(const std::vector <double>  keys) const;
    void  update_params(const std::vector <double> teta);
    ~Prediction();
};

Prediction::Prediction():_teta(std::vector(2, double(0)))
{
}

Prediction::Prediction(const std::vector <double> teta)
{
    if(teta.size() < 2)
        throw "invalid teta size";
    this->_teta = teta;
}

void Prediction::update_params(const std::vector <double> teta)
{
    if(teta.size() < 2)
        throw "invalid teta size";
    this->_teta = teta;
}

double Prediction::predict(const std::vector <double>  keys) const
{
    if(keys.size() + 1 != this->_teta.size())
        throw "invalid keys size";
    double res = this->_teta[0];
    for (size_t i = 0; i < keys.size(); i++)
    {
        res += keys[i] * this->_teta[i + 1];
    }
    return res;
}



Prediction::~Prediction()
{
}

#endif