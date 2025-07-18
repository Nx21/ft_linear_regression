/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csv_to_matrix.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasreddinehanafi <nasreddinehanafi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:28:34 by nasreddineh       #+#    #+#             */
/*   Updated: 2025/07/14 11:41:53 by nasreddineh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSV_TO_MATRIX_HPP
#define CSV_TO_MATRIX_HPP

#include "lr/lr.hpp"

std::vector<std::vector<std::string>> csv_to_matrix(std::string const &filename)
{
    puts("csv_to_matrix");
    std::ifstream input{filename};
    puts("csv_to_matrix read file ");
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
};

#endif