/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/17 22:59:15 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kdolib.hpp"
#include "BNFParser.hpp"

BNFParser::BNFParser(std::string const &name):	name(name),
												errorLen(BNF_ERROR_POS_UNINITIALIZED)
{
}

BNFParser::BNFParser(BNFParser const &other):	name(other.name),
												value(other.value),
												errorLen(other.errorLen)
{
}

BNFParser::~BNFParser(void)
{
}

std::string const	&BNFParser::getName(void) const
{
	return (this->name);
}

std::string const	&BNFParser::getValue(void) const
{
	return (this->value);
}

ssize_t				BNFParser::getErrorLen(void) const
{
	return (this->errorLen);
}

BNFParser			&BNFParser::operator=(BNFParser const &other)
{
	this->name = other.name;
	this->value = other.value;
	this->errorLen = other.errorLen;
	return (*this);
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
