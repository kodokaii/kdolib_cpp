/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitlist.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:14:18 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 11:20:55 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kdolib.hpp"

namespace kdo
{
	std::vector<std::string>	splitlist(std::string raw)
	{
		std::vector<std::string>	elems;
		std::string::size_type		pos;

		// TODO: use the BNF parser?
		while ((pos = raw.find(',')) != std::string::npos)
		{
			std::string	elem = raw.substr(0, pos);
			elems.push_back(elem);
			raw.erase(0, pos + 1);
		}
		elems.push_back(raw);
		return (elems);
	}
}
