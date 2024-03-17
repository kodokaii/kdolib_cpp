/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFChar.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/17 22:43:13 by nlaerema         ###   ########.fr       */
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
		std::string	getFormatName(void) const;
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFAlts		operator|(BNFParser const &other) const;
		BNFAlts     operator|(std::string const &str) const;
		BNFAlts     operator|(char c) const;
		BNFCat		operator&(BNFParser const &other) const;
		BNFCat      operator&(std::string const &str) const;
		BNFCat      operator&(char c) const;
		BNFRep		operator%(size_t n) const;
		BNFRep		operator!(void) const;
		BNFRep		operator+(size_t max) const;
		BNFRep		operator-(size_t min) const;
		BNFFind		operator[](std::string const &name) const;
		BNFChar		&operator=(BNFChar const &other);
};
