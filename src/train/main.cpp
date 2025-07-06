/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasr <nasr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:03:22 by nasr              #+#    #+#             */
/*   Updated: 2024/11/28 22:10:03 by nasr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lr/lr.hpp"

std::vector<std::vector<std::string>> &csv_to_matrix(std::string const &str)
{
    std::string filename{"csv_file.txt"};
    std::ifstream input{filename};
    std::vector<std::vector<std::string>> csvRows;


    if (!input.is_open()) {
        throw "Couldn't read file: " + filename + "\n"; 
    }
    for (std::string line; std::getline(input, line);)
    {
        std::istringstream ss(std::move(line));
        std::vector<std::string> row;
        if (!csvRows.empty()){
            row.reserve(csvRows.front().size());
        }
        for (std::string value; std::getline(ss, value, ',');) {
            row.push_back(std::move(value));
        }
        csvRows.push_back(std::move(row));
    }
    return csvRows;
}

int main(int argc, char const *argv[])
{
    LR lr;
    if (argc < 2)
    {
        lr.set_theta(std::vector<double> (2, 0));
        std::cout << lr << std::endl;
        return 0;
    }

    return 0;   
}
