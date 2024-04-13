/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/13 13:26:56 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include "../kdolib.hpp"

#define BNF_INFINI					SIZE_MAX

class BNFRep;
class BNFCat;
class BNFAlts;
class BNFFind;

class BNFParser: public kdo::string_view
{
	protected:
		std::string			name;
		kdo::State			state;

	public:
							BNFParser(std::string const &name = "<>");
							BNFParser(BNFParser const &other);
		virtual				~BNFParser(void);
		std::string const	&getName(void) const;
		kdo::State const	&getState(void) const;
		virtual std::string	getFormatName(void) const;
		virtual BNFParser	*clone(void) const = 0;
		virtual BNFFind		find(std::string const &name, size_t depth = BNF_INFINI) const;
		virtual int			parse(std::string &str, size_t start = 0, size_t len = std::string::npos);
		virtual int			parse(kdo::string_view const &str, size_t start = 0, size_t len = std::string::npos) = 0;
		virtual BNFAlts		operator|(BNFParser const &other) const;
		virtual BNFAlts		operator|(std::string const &str) const;
		virtual BNFAlts		operator|(char c) const;
		virtual BNFCat		operator&(BNFParser const &other) const;
		virtual BNFCat		operator&(std::string const &str) const;
		virtual BNFCat      operator&(char c) const;
		virtual BNFRep		operator^(size_t n) const;
		virtual BNFRep		operator!(void) const;
		virtual BNFRep		operator~(void) const;
		virtual BNFRep		operator*(void) const;
		virtual BNFFind		operator[](std::string const &name) const;
		BNFParser			&operator=(BNFParser const &other);
};

BNFAlts	operator|(std::string const &str, BNFParser const &parser);
BNFAlts	operator|(char c, BNFParser const &parser);
BNFCat	operator&(std::string const &str, BNFParser const &parser);
BNFCat	operator&(char c, BNFParser const &parser);
