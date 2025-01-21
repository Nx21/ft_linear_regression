/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasr <nasr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:38:28 by nasr              #+#    #+#             */
/*   Updated: 2025/01/21 23:00:44 by nasr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREDICTION_HPP
#define PREDICTION_HPP


class prediction
{
private:
    std::vector <double> _teta;
public:
    prediction();
    prediction(const std::vector <double> teta);
    double predict(const std::vector <double>  keys) const;
    void  update_params(const std::vector <double> teta);
    ~prediction();
};

prediction::prediction():_teta(std::vector(2, double(0)))
{
}

prediction::prediction(const std::vector <double> teta)
{
    if(teta.size() < 2)
        throw "invalid teta size";
    this->_teta = teta;
}

void prediction::update_params(const std::vector <double> teta)
{
    if(teta.size() < 2)
        throw "invalid teta size";
    this->_teta = teta;
}

double prediction::predict(const std::vector <double>  keys) const
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



prediction::~prediction()
{
}

#endif