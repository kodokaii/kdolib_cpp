/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:29:49 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/17 19:51:53 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.hpp"

namespace kdo
{
	std::string	chex(unsigned char c)
	{
		std::stringstream	ss;

		ss << std::setfill('0') << std::hex << std::setw(2) << (unsigned int)c;
		return (ss.str());
	}

	std::ios_base::iostate	convert(std::string &output, std::string const &input)
	{
		output = input;
		return (std::ios_base::iostate());
	}

	bool    allConverted(std::ios_base::iostate state)
	{
		return (!(state ^ std::ios::eofbit & (std::ios::badbit | std::ios::eofbit)));
	}

}
