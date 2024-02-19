/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/19 12:45:21 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kdolib.hpp"

namespace kdo
{
	std::string	strtrim(std::string &str, std::string set)
	{
		std::string	dst;
		size_t		start;
		size_t		len;

		start = str.find_first_not_of(set);
		if (start != std::string::npos)
		{
			len = str.find_last_not_of(set) - start + 1;
			dst = str.substr(start, len);
		}
		return (dst);
	}
}
