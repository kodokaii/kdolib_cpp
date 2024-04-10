/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFVar.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/10 14:47:57 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../kdolib.hpp"

class BNFParser;
class BNFAlts;
class BNFCat;
class BNFRep;

class BNFVar: public BNFParser
{
	protected:
		BNFParser	*rule;

	public:
					BNFVar(std::string const &name);
					BNFVar(std::string const &name, BNFParser const &rule);
					BNFVar(BNFVar const &other);
					~BNFVar(void);
		BNFParser	*clone(void) const;
		int			parse(std::string &str, size_t start = 0);
		int			parse(kdo::string_view const &str, size_t start = 0);
		BNFFind     find(std::string const &name, size_t depth = BNF_INFINI) const;
		BNFVar		&operator=(BNFVar const &other);
		BNFVar		&operator=(BNFParser const &other);
};
