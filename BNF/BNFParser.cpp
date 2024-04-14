/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/14 11:46:34 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kdolib.hpp"
#include "BNFParser.hpp"

BNFParser::BNFParser(std::string const &name):	name(name)
{
}

BNFParser::BNFParser(BNFParser const &other):	kdo::string_view(other),
												name(other.name)
{
}

BNFParser::~BNFParser(void)
{
}

std::string const	&BNFParser::getName(void) const
{
	return (this->name);
}

kdo::State const	&BNFParser::getState(void) const
{
	return (this->state);
}

std::string			BNFParser::getFormatName(void) const
{
	return (this->name);
}

int					BNFParser::parse(std::string &str, size_t start, size_t len)
{
	return (this->parse(kdo::string_view(str), start, len));
}

BNFFind				BNFParser::find(std::string const &name, size_t depth) const
{
	BNFFind res;

	if (depth && this->name == name)
		res.push_back(BNFInher(*this));
	return (res);
}

BNFAlts				BNFParser::operator|(BNFParser const &other) const
{
	return (BNFAlts(2, this, &other));
}

BNFAlts				BNFParser::operator|(std::string const &str) const
{
	BNFStr   tmp(str);

	return (BNFAlts(2, this, &tmp));
}

BNFAlts				BNFParser::operator|(char c) const
{
	BNFChar   tmp(c);

	return (BNFAlts(2, this, &tmp));
}

BNFCat				BNFParser::operator&(BNFParser const &other) const
{
	return (BNFCat(2, this, &other));
}

BNFCat				BNFParser::operator&(std::string const &str) const
{
	BNFStr	tmp(str);

	return (BNFCat(2, this, &tmp));
}

BNFCat				BNFParser::operator&(char c) const
{
	BNFChar   tmp(c);

	return (BNFCat(2, this, &tmp));
}

BNFRep				BNFParser::operator^(size_t n) const
{
	return (BNFRep(*this, n, n));
}

BNFRep				BNFParser::operator!(void) const
{
	return (BNFRep(*this, 0, 1));
}

BNFRep				BNFParser::operator~(void) const
{
	return (BNFRep(*this, 1, BNF_INFINI));
}

BNFRep				BNFParser::operator*(void) const
{
	return (BNFRep(*this, 0, BNF_INFINI));
}

BNFFind				BNFParser::operator[](std::string const &name) const
{
	return (this->find(name));
}

BNFAlts	operator|(std::string const &str, BNFParser const &parser)
{
	BNFStr	tmp(str);

	return (BNFAlts(2, &tmp, &parser));
}

BNFAlts	operator|(char c, BNFParser const &parser)
{
	BNFChar	tmp(c);

	return (BNFAlts(2, &tmp, &parser));
}

BNFCat	operator&(std::string const &str, BNFParser const &parser)
{
	BNFStr	tmp(str);

	return (BNFCat(2, &tmp, &parser));
}

BNFCat	operator&(char c, BNFParser const &parser)
{
	BNFChar	tmp(c);

	return (BNFCat(2, &tmp, &parser));
}

BNFParser			&BNFParser::operator=(BNFParser const &other)
{
	*static_cast<kdo::string_view *>(this) = other;
	this->name = other.name;
	this->state = other.state;
	return (*this);
}
