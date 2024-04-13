/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRep.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/13 11:37:32 by nlaerema         ###   ########.fr       */
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
	t_uint	i;

	for (i = 0; i < other.rules.size(); ++i)
		this->rules.push_back(other.rules[i]->clone());
}

BNFRep::~BNFRep(void)
{
	t_uint	i;

	delete this->rule;
	for (i = 0; i < this->rules.size(); ++i)
		delete this->rules[i];
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

int			BNFRep::parse(kdo::string_view const &str, size_t start, size_t len)
{
	size_t	i;

	this->state.clear();
	this->set(str.data(), str.start() + start, 0);
	for (i = 0; this->size() < len && i < this->max; ++i)
	{
		if (this->rules.size() <= i)
			this->rules.push_back(this->rule->clone());
		if (this->rules[i]->parse(str, start + this->size(), len - this->size())
			|| this->rules[i]->getState().eof())
			break;
		*this += this->rules[i]->size();
	}
	if (i < this->max && this->rules[i]->getState().eof())
		this->state.add(kdo::eofbit);
	if (i < this->min)
	{
		*this += this->rules[i]->size();
		this->state.add(kdo::failbit);
		this->ruleEnd = i + 1;
		return (EXIT_FAILURE);
	}
	this->state.add(kdo::goodbit);
	this->ruleEnd = i;
	return (EXIT_SUCCESS);
}

BNFFind     BNFRep::find(std::string const &name, size_t depth) const
{
	BNFFind	res;
	t_uint	i;

	if (depth)
	{
		for (i = 0; i < this->ruleEnd; ++i)
			res.merge((*this->rules[i]).find(name, depth - 1));
		res.pushParent(*this);
		if (this->name == name)
			res.push_back(BNFInher(*this));
	}
	return (res);
}

BNFFind		BNFRep::operator[](std::string const &name) const
{
	return (this->find(name));
}

BNFRep	&BNFRep::operator=(BNFRep const &other)
{
	t_uint	i;

	delete this->rule;
	for (i = 0; i < this->rules.size(); ++i)
		delete this->rules[i];
	this->rules.clear();
	*static_cast<BNFParser *>(this) = other;
	this->rule = other.rule->clone();	
	for (i = 0; i < other.rules.size(); ++i)
		this->rules.push_back(other.rules[i]->clone());
	this->ruleEnd = other.ruleEnd;
	this->min = other.min;
	this->max = other.max;
	return (*this);
}
