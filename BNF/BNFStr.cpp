/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFStr.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/19 11:57:57 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFStr.hpp"

BNFStr::BNFStr(std::string const &name, std::string const &str):	BNFParser(name),
																		str(str)
{
}

BNFStr::BNFStr(std::string const &str):	BNFParser('\"' + str + '\"'),
												str(str)
{
}

BNFStr::BNFStr(BNFStr const &other):	BNFParser(other),
												str(other.str)
{
}

BNFStr::~BNFStr(void)
{
}

std::string BNFStr::getFormatName(void) const
{
	return (this->name);
}

BNFParser	*BNFStr::clone(void) const
{
	return (new BNFStr(*this));
}

ssize_t		BNFStr::parse(std::string const &str, size_t start)
{
	if (str.length() < start + this->str.length()
		|| str.compare(start, this->str.length(), this->str))
	{
		this->value.clear();
		this->errorLen = 0;
		return (BNF_PARSE_ERROR);
	}
	this->value = str.substr(start, this->str.length());
	this->errorLen = BNF_ERROR_LEN_NONE;
	return (this->str.length());
}

BNFFind     BNFStr::find(std::string const &name, size_t depth) const
{ 
    BNFFind res;
  
    if (depth && this->name == name)
        res.push_back(BNFInher(*this));
    return (res);
}

BNFAlts		BNFStr::operator|(BNFParser const &other) const
{
	return (BNFAlts(2, this, &other));
}

BNFAlts      BNFStr::operator|(std::string const &str) const
{
    BNFStr   tmp(str);

    return (BNFAlts(2, this, &tmp));
}

BNFAlts      BNFStr::operator|(char c) const
{
    BNFChar   tmp(c);

    return (BNFAlts(2, this, &tmp));
}

BNFCat		BNFStr::operator&(BNFParser const &other) const
{
	return (BNFCat(2, this, &other));
}

BNFCat      BNFStr::operator&(std::string const &str) const
{
    BNFStr   tmp(str);

    return (BNFCat(2, this, &tmp));
}

BNFCat      BNFStr::operator&(char c) const
{
    BNFChar   tmp(c);

    return (BNFCat(2, this, &tmp));
}

BNFRep      BNFStr::operator%(size_t n) const
{
    return (BNFRep(*this, n, n));
}

BNFRep      BNFStr::operator!(void) const
{
    return (BNFRep(*this, 0, 1));
}

BNFRep		BNFStr::operator+(size_t max) const
{
	return (BNFRep(*this, 0, max));
}

BNFRep		BNFStr::operator-(size_t min) const
{
	return (BNFRep(*this, min, BNF_INFINI));
}

BNFFind		BNFStr::operator[](std::string const &name) const
{
	return (this->find(name));
}

BNFStr	&BNFStr::operator=(BNFStr const &other)
{
	*static_cast<BNFParser *>(this) = other;
	this->str = other.str;
	return (*this);
}
