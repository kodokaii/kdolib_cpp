/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stricmp.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:45:41 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/13 20:26:43 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../kdolib.hpp"

namespace kdo
{
	template <class S1, class S2>
	int	stricmp(S1 const &s1 , S2 const &s2)
	{
		size_t	i;

		i = 0;
		while (s1[i] && std::tolower(s1[i]) == std::tolower(s2[i]))
			i++;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
}
