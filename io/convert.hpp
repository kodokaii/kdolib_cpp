/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/17 16:54:55 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iomanip>
#include <sstream>
#include <iostream>

namespace kdo
{
	template<class To, class From>
	std::ios_base::iostate	convert(To &output, From const &input)
	{
		std::stringstream	ss;

		ss << input;
		ss >> output;
		return (ss.rdstate());
	}

	template<>
	std::ios_base::iostate	convert<std::string>(std::string &output, std::string const &input)
	{
		output = input;
		return (std::ios_base::iostate());
	}

	template<class integer>
	std::string	itoa(integer n, int base = 10)
	{
		std::stringstream	ss;
		
		if (1 < sizeof(integer))
			ss << std::setbase(base) << n;
		else
			ss << std::setbase(base) << (int)n;
		return (ss.str());
	}

	std::string	chex(unsigned char c);
	bool		allConverted(std::ios_base::iostate state);
}
