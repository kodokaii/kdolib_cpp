/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFAlts.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/10 14:37:34 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../kdolib.hpp"

class BNFParser;
class BNFRep;
class BNFCat;
class BNFAlts;

class BNFAlts: public BNFParser
{
	protected:
		std::vector<BNFParser *>	rules;
		t_uint						ruleEnd;

	public:
					BNFAlts(std::string const &name, t_uint count, ...);
					BNFAlts(t_uint count, ...);
					BNFAlts(BNFAlts const &other);
					~BNFAlts(void);
		std::string getFormatName(void) const;
		BNFParser	*clone(void) const;
		int			parse(std::string &str, size_t start = 0);
		int			parse(kdo::string_view const &str, size_t start = 0);
		BNFFind     find(std::string const &name, size_t depth = BNF_INFINI) const;
		BNFAlts     operator|(BNFParser const &other) const;
		BNFAlts     operator|(std::string const &str) const;
		BNFAlts     operator|(char c) const;
		BNFAlts		&operator=(BNFAlts const &other);
};
