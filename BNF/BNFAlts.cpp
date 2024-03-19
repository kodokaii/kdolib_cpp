/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFAlts.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/19 12:17:43 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFAlts.hpp"

BNFAlts::BNFAlts(std::string const &name, t_uint count, ...): BNFParser(name) 
{
	va_list	argList;

	va_start(argList, count);
	while (count--)
		this->rules.push_back(va_arg(argList, BNFParser *)->clone());
	va_end(argList);
}

BNFAlts::BNFAlts(t_uint count, ...): BNFParser("")
{
	va_list		argList;
	BNFParser	*cr;

	va_start(argList, count);
	while (count--)
	{
		cr = va_arg(argList, BNFParser *)->clone();
		this->rules.push_back(cr);
		this->name += cr->getFormatName();
		if (count)
			this->name += '|';
	}
	va_end(argList);
}

BNFAlts::BNFAlts(BNFAlts const &other):	BNFParser(other)
{
	t_uint	cr;

	for (cr = 0; cr < other.rules.size(); cr++)
		this->rules.push_back(other.rules[cr]->clone());
}

BNFAlts::~BNFAlts(void)
{
	t_uint	cr;

	for (cr = 0; cr < this->rules.size(); cr++)
		delete this->rules[cr];
}

std::string BNFAlts::getFormatName(void) const
{
    return ('(' + this->name + ')');
}

BNFParser	*BNFAlts::clone(void) const
{
	return (new BNFAlts(*this));
}

ssize_t		BNFAlts::parse(std::string const &str, size_t start)
{
	ssize_t	finalLen(BNF_PARSE_ERROR);
	ssize_t	len;
	t_uint	cr;

	this->ruleEnd = 0;
	for (cr = 0; cr < this->rules.size(); cr++)
	{
		len = this->rules[cr]->parse(str, start);
		if (finalLen < len)
		{
			finalLen = len;
			this->ruleEnd = cr;
		}
		else if (finalLen == BNF_PARSE_ERROR
				&& this->rules[cr]->getErrorLen() < this->rules[this->ruleEnd]->getErrorLen())
			this->ruleEnd = cr;
	}
	this->value = this->rules[this->ruleEnd]->getValue();
	this->errorLen = this->rules[this->ruleEnd]->getErrorLen();
	return (finalLen);
}

BNFFind     BNFAlts::find(std::string const &name, size_t depth) const
{
	BNFFind	res;

	if (depth)
	{
		res.merge((*this->rules[this->ruleEnd]).find(name, depth - 1));
		res.pushParent(*this);
		if (this->name == name)
			res.push_back(BNFInher(*this));
	}
	return (res);
}

BNFAlts     BNFAlts::operator|(BNFParser const &other) const
{
	BNFAlts	res(*this);

	res.name += '|' + other.getFormatName();
	res.rules.push_back(other.clone());
	return (res);
}

BNFAlts      BNFAlts::operator|(std::string const &str) const
{
    BNFStr   *tmp(new BNFStr(str));
	BNFAlts		res(*this);

	res.name += '|' + tmp->getFormatName();
	res.rules.push_back(tmp);
	return (res);
}

BNFAlts      BNFAlts::operator|(char c) const
{
    BNFChar	*tmp(new BNFChar(c));
	BNFAlts	res(*this);

	res.name += '|' + tmp->getFormatName();
	res.rules.push_back(tmp);
	return (res);
}

BNFCat		BNFAlts::operator&(BNFParser const &other) const
{
	return (BNFCat(2, this, &other));
}

BNFCat      BNFAlts::operator&(std::string const &str) const
{
    BNFStr   tmp(str);

    return (BNFCat(2, this, &tmp));
}

BNFCat      BNFAlts::operator&(char c) const
{
    BNFChar   tmp(c);

    return (BNFCat(2, this, &tmp));
}

BNFRep      BNFAlts::operator%(size_t n) const
{
    return (BNFRep(*this, n, n));
}

BNFRep      BNFAlts::operator!(void) const
{
    return (BNFRep(*this, 0, 1));
}

BNFRep      BNFAlts::operator+(size_t max) const
{
	return (BNFRep(*this, 0, max));
}

BNFRep      BNFAlts::operator-(size_t min) const
{
	return (BNFRep(*this, min, BNF_INFINI));
}

BNFFind		BNFAlts::operator[](std::string const &name) const
{
	return (this->find(name));
}

BNFAlts	&BNFAlts::operator=(BNFAlts const &other)
{
	t_uint	cr;

	for (cr = 0; cr < this->rules.size(); cr++)
		delete this->rules[cr];
	this->rules.clear();
	*static_cast<BNFParser *>(this) = other;
	for (cr = 0; cr < other.rules.size(); cr++)
		this->rules.push_back((other.rules[cr])->clone());
	this->ruleEnd = other.ruleEnd;
	return (*this);
}
