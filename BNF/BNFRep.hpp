/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRep.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/09 14:47:03 by nlaerema         ###   ########.fr       */
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

		static std::string	getFormatName(BNFParser const &rule, size_t min, size_t max);

	public:
					BNFRep(std::string const &name, BNFParser const &rule, size_t min, size_t max = BNF_INFINI);
					BNFRep(BNFParser const &rule, size_t min, size_t max = BNF_INFINI);
					BNFRep(BNFRep const &other);
					~BNFRep(void);
		std::string getFormatName(void) const;
		BNFParser	*clone(void) const;
		int			parse(std::string &str, size_t start = 0);
		BNFFind     find(std::string const &name, size_t depth = BNF_INFINI) const;
		BNFFind		operator[](std::string const &name) const;
		BNFRep		&operator=(BNFRep const &other);
};
