/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRange.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/17 10:44:45 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFRange.hpp"

BNFRange::BNFRange(std::string const &name, t_uchar cMin, t_uchar cMax):	BNFParser(name),
																			cMin(cMin),
																			cMax(cMax)	
{
}

BNFRange::BNFRange(t_uchar cMin, t_uchar cMax):	BNFParser("%x" + kdo::itoa(cMin, 16) + '-' + kdo::itoa(cMax, 16)),
												cMin(cMin),
												cMax(cMax)	
{
}

BNFRange::BNFRange(BNFRange const &other):	BNFParser(other),
											cMin(other.cMin),
											cMax(other.cMax)
{
}

BNFRange::~BNFRange(void)
{
}

std::string BNFRange::getFormatName(void) const
{
	return (this->name);
}

BNFParser	*BNFRange::clone(void) const
{
	return (new BNFRange(*this));
}

ssize_t		BNFRange::parse(std::string const &str, size_t start)
{
	this->value.clear();
	if (str.length() < start || str[start] < this->cMin || this->cMax < str[start])
	{
		this->errorPos = start;
		return (BNF_PARSE_ERROR);
	}
	this->value = str.substr(start, 1);
	this->errorPos = BNF_ERROR_POS_NONE;
	return (1);
}

BNFAlts		BNFRange::operator|(BNFParser const &other) const
{
	return (BNFAlts(2, this, &other));
}

BNFAlts      BNFRange::operator|(std::string const &str) const
{
    BNFStr   tmp(str);

    return (BNFAlts(2, this, &tmp));
}

BNFAlts      BNFRange::operator|(char c) const
{
    BNFChar   tmp(c);

    return (BNFAlts(2, this, &tmp));
}

BNFCat      BNFRange::operator&(BNFParser const &other) const
{
	return (BNFCat(2, this, &other));
}

BNFCat      BNFRange::operator&(std::string const &str) const
{
    BNFStr   tmp(str);

    return (BNFCat(2, this, &tmp));
}

BNFCat      BNFRange::operator&(char c) const
{
    BNFChar   tmp(c);

    return (BNFCat(2, this, &tmp));
}

BNFRep      BNFRange::operator%(size_t n) const
{   
    return (BNFRep(*this, n, n));
}

BNFRep      BNFRange::operator!(void) const
{   
    return (BNFRep(*this, 0, 1));
}

BNFRep      BNFRange::operator+(size_t max) const
{
	return (BNFRep(*this, 0, max));
}

BNFRep      BNFRange::operator-(size_t min) const
{
	return (BNFRep(*this, min, BNF_INFINI));
}

BNFFind		BNFRange::operator[](std::string const &name) const
{
	BNFFind	res;

	if (this->name == name)
		res.push_back(BNFInher(*this));
	return (res);
}

BNFRange	&BNFRange::operator=(BNFRange const &other)
{
	*static_cast<BNFParser *>(this) = other;
	this->cMin = other.cMin;
	this->cMax = other.cMax;
	return (*this);
}
