/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strupper.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:45:57 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/08 12:09:21 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kdolib.hpp"

namespace kdo
{
	std::string strupper(std::string str)
	{
		std::string::iterator   it;

		for (it = str.begin(); it != str.end(); ++it)
			*it = std::toupper(*it);
		return (str);
	}
}
