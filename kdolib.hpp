/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdolib.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/14 00:50:09 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cerrno>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstdarg>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <stdint.h>
#include <limits.h>
#include "io/convert.hpp"
#include "io/userinput.hpp"

#define EXIT_ERRNO -1

# define TERM_CLEAR     "\e[H\e[2J\e[3J"
# define COLOR_RESET    "\x1B[0m"
# define COLOR_RED      "\x1B[31m"
# define COLOR_GREEN    "\x1B[32m"
# define COLOR_YELLOW   "\x1B[33m"
# define COLOR_BLUE     "\x1B[34m"
# define COLOR_MAGENTA  "\x1B[35m"
# define COLOR_CYAN     "\x1B[36m"
# define COLOR_WHITE    "\x1B[37m"

#define INVALID_FD		-1
#define INVALID_SIZE	-1

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;

namespace kdo
{
	std::string	strtrim(const std::string &str, const std::string set);
}
