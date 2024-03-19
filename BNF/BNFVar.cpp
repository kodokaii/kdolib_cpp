/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFVar.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/19 18:43:29 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFVar.hpp"

BNFVar::BNFVar(std::string const &name):	BNFParser(name),
											rule(NULL)
{
}

BNFVar::BNFVar(std::string const &name, BNFParser const &rule):	BNFParser(name),
																rule(rule.clone())
{
}

BNFVar::BNFVar(BNFVar const &other):	BNFParser(other),
										rule(other.rule->clone())
{
}

BNFVar::~BNFVar(void)
{
	delete this->rule;
}

std::string BNFVar::getFormatName(void) const
{
    return (this->name);
}

BNFParser	*BNFVar::clone(void) const
{
	return (new BNFVar(*this));
}

ssize_t		BNFVar::parse(std::string const &str, size_t start)
{
	ssize_t	res;

	res = this->rule->parse(str, start);
	this->value = this->rule->getValue();
	this->errorLen = this->rule->getErrorLen();
	return(res);
}

BNFFind     BNFVar::find(std::string const &name, size_t depth) const
{
	BNFFind	res;

	if (depth)
	{
		res.merge(this->rule->find(name, depth - 1));
		res.pushParent(*this);
		if (this->name == name)
			res.push_back(BNFInher(*this));
	}
	return (res);
}

BNFAlts     BNFVar::operator|(BNFParser const &other) const
{
	return (BNFAlts(2, this, &other));
}

BNFAlts      BNFVar::operator|(std::string const &str) const
{
    BNFStr   tmp(str);

    return (BNFAlts(2, this, &tmp));
}

BNFAlts      BNFVar::operator|(char c) const
{
    BNFChar   tmp(c);

    return (BNFAlts(2, this, &tmp));
}

BNFCat      BNFVar::operator&(BNFParser const &other) const
{
	return (BNFCat(2, this, &other));
}

BNFCat      BNFVar::operator&(std::string const &str) const
{
    BNFStr   tmp(str);

    return (BNFCat(2, this, &tmp));
}

BNFCat      BNFVar::operator&(char c) const
{
    BNFChar   tmp(c);

    return (BNFCat(2, this, &tmp));
}

BNFRep      BNFVar::operator%(size_t n) const
{
    return (BNFRep(*this, n, n));
}

BNFRep      BNFVar::operator!(void) const
{
    return (BNFRep(*this, 0, 1));
}

BNFRep      BNFVar::operator+(size_t max) const
{
	return (BNFRep(*this, 0, max));
}

BNFRep		BNFVar::operator-(size_t min) const
{
	return (BNFRep(*this, min, BNF_INFINI));
}

BNFFind		BNFVar::operator[](std::string const &name) const
{
	return (this->find(name));
}

BNFVar	&BNFVar::operator=(BNFVar const &other)
{
	delete this->rule;
	this->value = other.getValue();
	this->errorLen = other.getErrorLen();
	this->rule = other.rule->clone();
	return (*this);
}

BNFVar	&BNFVar::operator=(BNFParser const &other)
{
	delete this->rule;
	this->value = other.getValue();
	this->errorLen = other.getErrorLen();
	this->rule = other.clone();
	return (*this);
}
