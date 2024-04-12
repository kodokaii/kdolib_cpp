/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFAlts.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/10 16:10:15 by nlaerema         ###   ########.fr       */
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
	t_uint	i;

	for (i = 0; i < other.rules.size(); ++i)
		this->rules.push_back(other.rules[i]->clone());
}

BNFAlts::~BNFAlts(void)
{
	t_uint	i;

	for (i = 0; i < this->rules.size(); ++i)
		delete this->rules[i];
}

std::string BNFAlts::getFormatName(void) const
{
    return ('(' + this->name + ')');
}

BNFParser	*BNFAlts::clone(void) const
{
	return (new BNFAlts(*this));
}

int			BNFAlts::parse(std::string &str, size_t start)
{
	return (this->parse(kdo::string_view(str, start)));
}

int			BNFAlts::parse(kdo::string_view const &str, size_t start)
{
	t_uint	i;

	this->ruleEnd = 0;
	for (i = 0; i < this->rules.size(); ++i)
	{
		this->rules[i]->parse(str, start);
		if ((this->rules[this->ruleEnd]->getState() == this->rules[i]->getState()
				&& this->rules[this->ruleEnd]->size() < this->rules[i]->size())
			|| (this->rules[this->ruleEnd]->getState().fail() && this->rules[i]->getState().good()))
			this->ruleEnd = i;
	}
	this->copy(*this->rules[this->ruleEnd]);
	this->state = this->rules[this->ruleEnd]->getState();
	return (this->state.fail());
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

BNFAlts	&BNFAlts::operator=(BNFAlts const &other)
{
	t_uint	i;

	for (i = 0; i < this->rules.size(); ++i)
		delete this->rules[i];
	this->rules.clear();
	*static_cast<BNFParser *>(this) = other;
	for (i = 0; i < other.rules.size(); ++i)
		this->rules.push_back((other.rules[i])->clone());
	this->ruleEnd = other.ruleEnd;
	return (*this);
}
