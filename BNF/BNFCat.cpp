/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFCat.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/14 18:55:14 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFCat.hpp"

BNFCat::BNFCat(std::string const &name, t_uint count, ...):	BNFParser(name),
															ruleEnd(0)		
{
	va_list	argList;

	va_start(argList, count);
	while (count--)
		this->rules.push_back(va_arg(argList, BNFParser *)->clone());
	va_end(argList);
}

BNFCat::BNFCat(t_uint count, ...):	BNFParser(""),
									ruleEnd(0)		
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
			this->name += ' ';
	}
	va_end(argList);
}

BNFCat::BNFCat(BNFCat const &other):	BNFParser(other),
										ruleEnd(0)		
{
	t_uint	i;

	for (i = 0; i < other.rules.size(); ++i)
		this->rules.push_back(other.rules[i]->clone());
}

BNFCat::~BNFCat(void)
{
	t_uint	i;

	for (i = 0; i < this->rules.size(); ++i)
		delete this->rules[i];
}

std::string BNFCat::getFormatName(void) const
{
    return ('(' + this->name + ')');
}

BNFParser	*BNFCat::clone(void) const
{
	return (new BNFCat(*this));
}

int			BNFCat::parse(kdo::string_view const &str, size_t start, size_t len)
{
	t_uint	i;

	this->state.clear();
	this->set(str.data(), str.start() + start, 0);
	for (i = 0; this->size() < len && i < this->rules.size(); ++i)
	{
		if (this->rules[i]->parse(str, start + this->size(), len - this->size()))
			break;
		if (this->rules[i]->getState().eof())
			this->state.add(kdo::eofbit);
		*this += this->rules[i]->size();
	}
	if (i < this->rules.size())
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

BNFFind     BNFCat::find(std::string const &name, size_t depth) const
{
    BNFFind res;
    t_uint  i;

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

BNFCat      BNFCat::operator&(BNFParser const &other) const
{
	BNFCat	res(*this);

	res.name += ' ' + other.getFormatName();
	res.rules.push_back(other.clone());
	return (res);
}

BNFCat      BNFCat::operator&(std::string const &str) const
{
    BNFStr	*tmp(new BNFStr(str));
	BNFCat		res(*this);

	res.name += ' ' + tmp->getFormatName();
	res.rules.push_back(tmp);
	return (res);
}

BNFCat      BNFCat::operator&(char c) const
{
    BNFChar	*tmp(new BNFChar(c));
	BNFCat	res(*this);

	res.name += ' ' + tmp->getFormatName();
	res.rules.push_back(tmp);
	return (res);
}

BNFCat		&BNFCat::operator=(BNFCat const &other)
{
	t_uint	i;

	for (i = 0; i < this->rules.size(); ++i)
		delete this->rules[i];
	this->rules.clear();
	*static_cast<BNFParser *>(this) = other;
	for (i = 0; i < other.rules.size(); ++i)
		this->rules.push_back(other.rules[i]->clone());
	this->ruleEnd = other.ruleEnd;
	return (*this);
}
