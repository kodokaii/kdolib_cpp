/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFCat.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/19 12:13:45 by nlaerema         ###   ########.fr       */
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
	t_uint	cr;

	for (cr = 0; cr < other.rules.size(); cr++)
		this->rules.push_back(other.rules[cr]->clone());
}

BNFCat::~BNFCat(void)
{
	t_uint	cr;

	for (cr = 0; cr < this->rules.size(); cr++)
		delete this->rules[cr];
}

std::string BNFCat::getFormatName(void) const
{
    return ('(' + this->name + ')');
}

BNFParser	*BNFCat::clone(void) const
{
	return (new BNFCat(*this));
}

ssize_t		BNFCat::parse(std::string const &str, size_t start)
{
	ssize_t	finalLen(0);
	ssize_t	len;
	t_uint	cr;

	for (cr = 0; cr < this->rules.size(); cr++)
	{
		len = this->rules[cr]->parse(str, start + finalLen);
		if (len == BNF_PARSE_ERROR)
			break;
		finalLen += len;	
	}
	if (cr < this->rules.size())
	{
		finalLen += this->rules[cr]->getErrorLen();
		this->value = str.substr(start, finalLen);
		this->errorLen = finalLen;
		this->ruleEnd = cr + 1;
		return (BNF_PARSE_ERROR);
	}
	this->value = str.substr(start, finalLen);
	this->errorLen = BNF_ERROR_LEN_NONE;
	this->ruleEnd = cr;
	return (finalLen);
}

BNFFind     BNFRep::find(std::string const &name, size_t depth) const
{
    BNFFind res;
    t_uint  cr;

    if (depth)
    {
      for (cr = 0; cr < this->ruleEnd; cr++)
          res.merge((*this->rules[cr]).find(name, depth - 1));
      res.pushParent(*this);
      if (this->name == name)
          res.push_back(BNFInher(*this));
    }
    return (res);
}

BNFAlts     BNFCat::operator|(BNFParser const &other) const
{
	return (BNFAlts(2, this, &other));
}

BNFAlts      BNFCat::operator|(std::string const &str) const
{
    BNFStr   tmp(str);

    return (BNFAlts(2, this, &tmp));
}

BNFAlts      BNFCat::operator|(char c) const
{
    BNFChar   tmp(c);

    return (BNFAlts(2, this, &tmp));
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

BNFRep      BNFCat::operator%(size_t n) const
{
    return (BNFRep(*this, n, n));
}

BNFRep      BNFCat::operator!(void) const
{
    return (BNFRep(*this, 0, 1));
}

BNFRep      BNFCat::operator+(size_t max) const
{
	return (BNFRep(*this, 0, max));
}

BNFRep		BNFCat::operator-(size_t min) const
{
	return (BNFRep(*this, min, BNF_INFINI));
}

BNFFind		BNFCat::operator[](std::string const &name) const
{
	return (this->find(name));
}

BNFCat		&BNFCat::operator=(BNFCat const &other)
{
	t_uint	cr;

	for (cr = 0; cr < this->rules.size(); cr++)
		delete this->rules[cr];
	this->rules.clear();
	*static_cast<BNFParser *>(this) = other;
	for (cr = 0; cr < other.rules.size(); cr++)
		this->rules.push_back(other.rules[cr]->clone());
	this->ruleEnd = other.ruleEnd;
	return (*this);
}
