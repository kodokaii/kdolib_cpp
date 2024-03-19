/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:29:49 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/19 17:22:52 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.hpp"

namespace kdo
{
	bool    allConverted(std::ios_base::iostate state)
	{
		return (!(state ^ std::ios::eofbit & (std::ios::badbit | std::ios::eofbit)));
	}
}
