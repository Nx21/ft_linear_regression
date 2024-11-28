/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasr <nasr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:11:40 by nasr              #+#    #+#             */
/*   Updated: 2024/11/28 22:02:53 by nasr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prediction/prediction.hpp"

double ft_stoi(const std::string &s)
{
    size_t pos = s.find_last_of("+-");
    
    if(s.find_first_not_of("0123456789.-+") != s.npos ||\
        std::count(s.begin(), s.end(), '.') > 1
        )
    {
        std::cerr << "Wrong arguments '" << s  << "'" << std::endl;
        exit(1);
    }
    try
    {
        return stod(s);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Wrong arguments '" << s  << "'" << std::endl;
        exit(1);
    }
    
}


int main(int argc, char const *argv[])
{
    if(argc != 4)
        std::cerr << "Wrong number of aarguments" << std::endl;
    std::vector<double> params(3);
    for (size_t i = 1; i < argc; i++)
    {
        std::string s = argv[i];
        params[i - 1] = ft_stoi(s);
    }
    double result = params[0] + params[1] * params[2];
    std::cout << result << std::endl;
    return 0; 
}
