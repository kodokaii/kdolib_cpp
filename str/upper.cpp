/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upper.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 01:49:25 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/18 01:54:43 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kdolib.hpp"

namespace kdo
{
	std::string	toUppercase(std::string str)
	{
		std::string::iterator   cr; 

		for (cr = str.begin(); cr != str.end(); cr++)
			*cr = toupper(*cr);
		return (str);
	}
}
