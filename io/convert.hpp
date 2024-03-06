/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/06 18:42:04 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sstream>
#include <iostream>

namespace kdo
{
	template<typename To, typename From>
	std::ios_base::iostate	convert(To &output, From const &input)
	{
		std::stringstream	ss;

		ss << input;
		ss >> output;
		return (ss.rdstate());
	}

	template<> inline
	std::ios_base::iostate	convert(std::string &output, std::string const &input)
	{
		output = input;
		return (std::ios_base::iostate());
	}
}
