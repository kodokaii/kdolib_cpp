/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRange.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/09 19:48:40 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../kdolib.hpp"

class BNFParser;
class BNFRep;
class BNFCat;
class BNFAlts;

class BNFRange: public BNFParser
{
	protected:
		t_uchar	cMin;
		t_uchar	cMax;

	public:
					BNFRange(std::string const &name, t_uchar cMIn, t_uchar cMax);
					BNFRange(t_uchar cMin, t_uchar cMax);
					BNFRange(BNFRange const &other);
					~BNFRange(void);
		BNFParser	*clone(void) const;
		int			parse(std::string &str, size_t start = 0);
		int			parse(kdo::string_view const &str, size_t start = 0);
		BNFRange	&operator=(BNFRange const &other);
};
