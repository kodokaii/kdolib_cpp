/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFInher.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/15 10:28:47 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFInher.hpp"

BNFInher::BNFInher(BNFParser const &son):	inherErrorLen(BNF_ERROR_POS_NONE),
											name(son.getName()),
											value(son.getValue()),
											errorLen(son.getErrorLen())
{
}


BNFInher::BNFInher(BNFInher const &other):	inher(other.inher),
											inherErrorLen(other.inherErrorLen),
											name(other.name),
											value(other.value),
											errorLen(other.errorLen)
{
}

BNFInher::~BNFInher(void)
{
}

size_t				BNFInher::pushParent(BNFParser const &parent)
{
	this->inher.push_back(parent.getName());
	this->inherErrorLen = std::max(this->inherErrorLen, parent.getErrorLen());
	return (this->inher.size());
}

bool				BNFInher::isHeir(t_uint count, ...) const
{
	va_list	argList;

	va_start(argList, count);
	return (this->isHeir(count, argList));
}

bool				BNFInher::isHeir(t_uint count, va_list argList) const
{
	char	*parent;
	t_uint	cr;

	cr = 0;
	while (cr < this->inher.size() && count)
	{
		parent = va_arg(argList, char *);
		while (cr < this->inher.size() && this->inher[cr] != parent)
			cr++;
		count--;
	}
	va_end(argList);
	if (cr == this->inher.size())
		return (false);	
	return (true);
}

std::string const	&BNFInher::getName(void) const
{
	return (this->name);
}

std::string const	&BNFInher::getValue(void) const
{
	return (this->value);
}

ssize_t				BNFInher::getErrorLen(void) const
{
	return (this->errorLen);
}

ssize_t				BNFInher::getInherErrorLen(void) const
{
	return (this->inherErrorLen);
}

BNFInher			&BNFInher::operator=(BNFInher const &other)
{
	this->inher = other.inher;
	this->inherErrorLen = other.inherErrorLen;
	this->name = other.name;
	this->value = other.value;
	this->errorLen = other.errorLen;
	return (*this);
}
