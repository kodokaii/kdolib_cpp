/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iequals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 21:09:51 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/19 21:10:51 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kdolib.hpp"

namespace kdo
{
	static bool ichar_equals(char a, char b)
	{
		return std::tolower(static_cast<unsigned char>(a)) ==
			   std::tolower(static_cast<unsigned char>(b));
	}

	bool iequals(const std::string &a, const std::string &b)
	{
		return a.size() == b.size()
			&& std::equal(a.begin(), a.end(), b.begin(), ichar_equals);
	}
}
