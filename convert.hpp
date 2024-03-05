/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/05 22:26:06 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "kdolib.hpp"

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