/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFChar.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/09 19:29:05 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../kdolib.hpp"

class BNFParser;
class BNFRep;
class BNFCat;
class BNFAlts;

class BNFChar: public BNFParser
{
	protected:
		char	c;

	public:
					BNFChar(std::string const &name, char c);
					BNFChar(char c);
					BNFChar(BNFChar const &other);
					~BNFChar(void);
		BNFParser	*clone(void) const;
		int			parse(std::string &str, size_t start = 0);
		int			parse(kdo::string_view const &str, size_t start = 0);
		BNFChar		&operator=(BNFChar const &other);
};
