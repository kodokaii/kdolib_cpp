/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRep.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/19 11:16:19 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <stdlib.h>
#include "BNFRep.hpp"

BNFRep::BNFRep(std::string const &name, BNFParser const &rule, size_t min, size_t max):	BNFParser(name),
																						rule(rule.clone()),
																						ruleEnd(0),
																						min(min),
																						max(max)
{
}

BNFRep::BNFRep(BNFParser const &rule, size_t min, size_t max):	BNFParser(BNFRep::getFormatName(rule, min, max)),
																rule(rule.clone()),
																ruleEnd(0),
																min(min),
																max(max)
{
}

BNFRep::BNFRep(BNFRep const &other):	BNFParser(other),
										rule(other.rule->clone()),
										ruleEnd(0),
										min(other.min),
										max(other.max)
{
	t_uint	cr;

	for (cr = 0; cr < other.rules.size(); cr++)
		this->rules.push_back(other.rules[cr]->clone());
}

BNFRep::~BNFRep(void)
{
	t_uint	cr;

	delete this->rule;
	for (cr = 0; cr < this->rules.size(); cr++)
		delete this->rules[cr];
}

std::string BNFRep::getFormatName(BNFParser const &rule, size_t min, size_t max)
{
	if (min == max)
		return (kdo::itoa(min) + rule.getFormatName());
	if (!min && max == 1)
		return ('[' + rule.getName() + ']');
	if (!min && max == BNF_INFINI)
		return ('*' + rule.getFormatName());
	if (!min)
		return ('*' + kdo::itoa(max) + rule.getFormatName());
	if (max == BNF_INFINI)
		return (kdo::itoa(min) + '*' + rule.getFormatName());
	return (kdo::itoa(min) + '*' + kdo::itoa(max) + rule.getFormatName());
}

std::string	BNFRep::getFormatName(void) const
{
    return (this->name);
}

BNFParser	*BNFRep::clone(void) const
{
	return (new BNFRep(*this));
}

ssize_t		BNFRep::parse(std::string const &str, size_t start)
{
	size_t	finalLen(0);
	ssize_t	len;
	size_t	cr;

	for (cr = 0; cr < this->max; cr++)
	{
		if (this->rules.size() <= cr)
			this->rules.push_back(this->rule->clone());
		len = this->rules[cr]->parse(str, start + finalLen);
		if (len == BNF_PARSE_ERROR)
			break;
		finalLen += len;	
	}
	if (cr < this->min)
	{
		finalLen += this->rules[cr]->getErrorLen();
		this->value = str.substr(start, finalLen);
		this->errorLen = finalLen;
		this->ruleEnd = cr + 1;
		return (BNF_PARSE_ERROR);
	}
	this->value = str.substr(start, finalLen);
	this->errorLen = BNF_ERROR_POS_NONE;
	this->ruleEnd = cr;
	return (finalLen);
}

BNFAlts		BNFRep::operator|(BNFParser const &other) const
{
	return (BNFAlts(2, this, &other));
}

BNFAlts      BNFRep::operator|(std::string const &str) const
{
    BNFStr   tmp(str);

    return (BNFAlts(2, this, &tmp));
}

BNFAlts      BNFRep::operator|(char c) const
{
    BNFChar   tmp(c);

    return (BNFAlts(2, this, &tmp));
}

BNFCat		BNFRep::operator&(BNFParser const &other) const
{
	return (BNFCat(2, this, &other));
}

BNFCat      BNFRep::operator&(std::string const &str) const
{
    BNFStr   tmp(str);

    return (BNFCat(2, this, &tmp));
}

BNFCat      BNFRep::operator&(char c) const
{
    BNFChar   tmp(c);

    return (BNFCat(2, this, &tmp));
}

BNFRep      BNFRep::operator%(size_t n) const
{
	return (BNFRep(*this->rule, n, n));
}

BNFRep      BNFRep::operator!(void) const
{
	return (BNFRep(*this->rule, 0, 1));
}

BNFRep		BNFRep::operator+(size_t max) const
{
	return (BNFRep(*this->rule, this->min, max));
}

BNFRep		BNFRep::operator-(size_t min) const
{
	return (BNFRep(*this->rule, min, this->max));
}

BNFFind		BNFRep::operator[](std::string const &name) const
{
	BNFFind	res;
	t_uint	cr;

	for (cr = 0; cr < this->ruleEnd; cr++)
		res.merge((*this->rules[cr])[name]);
	res.pushParent(*this);
	if (this->name == name)
		res.push_back(BNFInher(*this));
	return (res);
}

BNFRep	&BNFRep::operator=(BNFRep const &other)
{
	t_uint	cr;

	delete this->rule;
	for (cr = 0; cr < this->rules.size(); cr++)
		delete this->rules[cr];
	this->rules.clear();
	*static_cast<BNFParser *>(this) = other;
	this->rule = other.rule->clone();	
	for (cr = 0; cr < other.rules.size(); cr++)
		this->rules.push_back(other.rules[cr]->clone());
	this->ruleEnd = other.ruleEnd;
	this->min = other.min;
	this->max = other.max;
	return (*this);
}
