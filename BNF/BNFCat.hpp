/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFCat.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/19 12:13:01 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../kdolib.hpp"

class BNFParser;
class BNFRep;
class BNFCat;
class BNFAlts;

class BNFCat: public BNFParser
{
	protected:
		std::vector<BNFParser *>	rules;
		t_uint						ruleEnd;

	public:
					BNFCat(std::string const &name, t_uint count, ...);
					BNFCat(t_uint count, ...);
					BNFCat(BNFCat const &other);
					~BNFCat(void);
		std::string getFormatName(void) const;
		BNFParser	*clone(void) const;
		ssize_t		parse(std::string const &str, size_t start = 0);
		BNFFind     find(std::string const &name, size_t depth = BNF_INFINI) const;
		BNFAlts     operator|(BNFParser const &other) const;
		BNFAlts     operator|(std::string const &str) const;
		BNFAlts     operator|(char c) const;
        BNFCat      operator&(BNFParser const &other) const;
		BNFCat      operator&(std::string const &str) const;
		BNFCat      operator&(char c) const;
		BNFRep      operator%(size_t n) const;
		BNFRep      operator!(void) const;
        BNFRep      operator+(size_t max) const;
        BNFRep      operator-(size_t min) const;
		BNFFind		operator[](std::string const &name) const;
		BNFCat		&operator=(BNFCat const &other);
};
