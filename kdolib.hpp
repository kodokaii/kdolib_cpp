/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdolib.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/06 16:56:32 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <cstdio>
# include <string>
# include <sstream>
# include <iostream>
# include "io/convert.hpp"
# include "io/userinput.hpp"

#define EXIT_ERRNO -1

typedef unsigned int t_uint;

namespace kdo
{
	std::string	strtrim(const std::string &str, const std::string set);
}
