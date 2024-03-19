/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRep.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/19 11:58:34 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../kdolib.hpp"

class BNFParser;
class BNFRep;
class BNFCat;
class BNFAlts;

class BNFRep: public BNFParser
{
	protected:
		BNFParser					*rule;
		std::vector<BNFParser *>	rules;
		size_t						ruleEnd;
		size_t						min;
		size_t						max;

		static std::string getFormatName(BNFParser const &rule, size_t min, size_t max);

	public:
					BNFRep(std::string const &name, BNFParser const &rule, size_t min, size_t max);
					BNFRep(BNFParser const &rule, size_t min, size_t max);
					BNFRep(BNFRep const &other);
					~BNFRep(void);
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
		BNFRep		&operator=(BNFRep const &other);
};
