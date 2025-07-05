/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasr <nasr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:11:40 by nasr              #+#    #+#             */
/*   Updated: 2025/07/05 20:52:31 by nasr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix/Matrix.hpp"

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

    if(argc != 2 && argc != 1)
    {
        std::cerr << "Wrong number of aarguments" << std::endl;
        return 1;
    }
    if(argc == 2)
    {
        std::ifstream file;
        file.open(argv[1]);
        if(file.is_open())
        {
            std::cerr << "Prediction: unable to open file: " << argv[1] << std::endl;
            return 0;
        }
        
    }
    // double result = estimatePrice(params[0], params[1], params[2]);
    // std::cout << result << std::endl;
    return 0; 
}
