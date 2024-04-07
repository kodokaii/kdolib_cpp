/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strupper.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:45:57 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/07 20:47:00 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kdolib.hpp"

namespace kdo
{
	std::string strupper(std::string str)
	{
		std::string::iterator   i; 

		for (i = str.begin(); i != str.end(); ++i)
			*i = std::toupper(*i);
		return (str);
	}
}
