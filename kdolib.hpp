/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdolib.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/24 13:27:13 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KDOLIB_H
# define KDOLIB_H

# include <cstdio>
# include <string>
# include <sstream>
# include <iostream>
# include "io/userinput.hpp"
# include "str/strconvert.hpp"

typedef unsigned int t_uint;

namespace kdo
{
	std::string	strtrim(const std::string &str, const std::string set);
}

#endif
