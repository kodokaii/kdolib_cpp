/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFStr.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/08 23:43:14 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../kdolib.hpp"

class BNFParser;
class BNFRep;
class BNFCat;
class BNFAlts;

class BNFStr: public BNFParser
{
	protected:
		std::string	ref;

	public:
					BNFStr(std::string const &name, std::string const &str);
					BNFStr(std::string const &str);
					BNFStr(BNFStr const &other);
					~BNFStr(void);
		BNFParser	*clone(void) const;
		int			parse(std::string &str, size_t start = 0);
		BNFStr		&operator=(BNFStr const &other);
};
