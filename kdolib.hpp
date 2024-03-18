/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdolib.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/18 12:14:57 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <cerrno>
#include <cstdio>
#include <string>
#include <vector>
#include <csignal>
#include <cstdlib>
#include <cstdarg>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <stdint.h>
#include <limits.h>

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
	std::string toUppercase(std::string str);
}

#include "io/convert.hpp"
#include "io/userinput.hpp"

#include "BNF/BNFInher.hpp"
#include "BNF/BNFFind.hpp"
#include "BNF/BNFParser.hpp"
#include "BNF/BNFChar.hpp"
#include "BNF/BNFStr.hpp"
#include "BNF/BNFRange.hpp"
#include "BNF/BNFRep.hpp"
#include "BNF/BNFCat.hpp"
#include "BNF/BNFAlts.hpp"
#include "BNF/BNFVar.hpp"

#include "Socket/Socket.hpp"
#include "Socket/SocketTcpClient.hpp"
#include "Socket/SocketTcpServer.hpp"
