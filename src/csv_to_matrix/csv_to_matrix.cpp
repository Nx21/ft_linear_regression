/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csv_to_matrix.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasreddinehanafi <nasreddinehanafi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:33:25 by nasreddineh       #+#    #+#             */
/*   Updated: 2025/07/14 11:41:13 by nasreddineh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csv_to_matrix/csv_to_matrix.hpp"

std::vector<std::vector<std::string>> csv_to_matrix(std::string  &filename)
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
}
