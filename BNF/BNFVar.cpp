/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFVar.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/09 00:55:39 by nlaerema         ###   ########.fr       */
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

BNFParser	*BNFVar::clone(void) const
{
	return (new BNFVar(*this));
}

int			BNFVar::parse(std::string &str, size_t start)
{
	ssize_t	res;

	res = this->rule->parse(str, start);
	this->copy(*this->rule);
	this->state = this->rule->getState();
	return(this->state.fail());
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

BNFVar	&BNFVar::operator=(BNFVar const &other)
{
	delete this->rule;
	this->copy(*other.rule);
	this->state = other.rule->getState();
	this->rule = other.rule->clone();
	return (*this);
}

BNFVar	&BNFVar::operator=(BNFParser const &other)
{
	delete this->rule;
	this->copy(other);
	this->state = other.getState();
	this->rule = other.clone();
	return (*this);
}
