/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasreddinehanafi <nasreddinehanafi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:03:22 by nasr              #+#    #+#             */
/*   Updated: 2025/07/14 11:46:47 by nasreddineh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csv_to_matrix/csv_to_matrix.hpp"

int main(int argc, char const *argv[])
{
    LR lr;
    if (argc < 2)
    {
        std::cout << "no arg" << std::endl;
        lr.set_theta(std::vector<double> (2));
        std::cout << "print data" << std::endl;
        std::cout << lr << std::endl;
        return 0;
    }
    std::string file = std::string(argv[1]);
    puts("test");
    puts(argv[1]);
    auto csv = csv_to_matrix(file);
    lr.read_csv(csv, "km");
    return 0;   
}
