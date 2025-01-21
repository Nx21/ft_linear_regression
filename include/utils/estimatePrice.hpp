/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   estimatePrice.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasr <nasr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:02:41 by nasr              #+#    #+#             */
/*   Updated: 2024/12/03 21:12:57 by nasr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESTIMATEPRICE_HPP
#define ESTIMATEPRICE_HPP

double estimatePrice(double tita0, double tita1, double mileage)
{
    return tita0 + tita1 * mileage;
}


#endif