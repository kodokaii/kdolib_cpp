/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFFind.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/18 13:13:41 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFFind.hpp"

BNFFind::BNFFind(void)
{
}

BNFFind::BNFFind(BNFFind const &other): std::vector<BNFInher>(other)
{
}

BNFFind::~BNFFind(void)
{
}

void		BNFFind::merge(BNFFind const &other)
{
	t_uint	i;

	for (i = 0; i < other.size(); ++i)
		this->push_back(other[i]);
}

BNFFind		BNFFind::heir(t_uint count, ...) const
{
	va_list	argListCopy;
	va_list	argList;
	BNFFind	res;
	t_uint	i;

	va_start(argList, count);
	for (i = 0; i < this->size(); ++i)
	{
		__builtin_va_copy(argListCopy, argList);
		if ((*this)[i].isHeir(count, argListCopy))
			res.push_back((*this)[i]);
	}
	va_end(argList);
	return (res);
}

BNFFind		BNFFind::fail(void) const
{
	BNFFind	res;
	t_uint	i;

	for (i = 0; i < this->size(); ++i)
	{
		if ((*this)[i].getState().fail())
			res.push_back((*this)[i]);
	}
	return (res);
}

BNFFind		BNFFind::good(void) const
{
	BNFFind	res;
	t_uint	i;

	for (i = 0; i < this->size(); ++i)
	{
		if ((*this)[i].getState().good())
			res.push_back((*this)[i]);
	}
	return (res);
}

BNFFind		BNFFind::inherFail(void) const
{
	BNFFind	res;
	t_uint	i;

	for (i = 0; i < this->size(); ++i)
	{
		if ((*this)[i].getInherState().fail())
			res.push_back((*this)[i]);
	}
	return (res);
}

BNFFind		BNFFind::inherGood(void) const
{
	BNFFind	res;
	t_uint	i;

	for (i = 0; i < this->size(); ++i)
	{
		if ((*this)[i].getInherState().good())
			res.push_back((*this)[i]);
	}
	return (res);
}


void		BNFFind::pushParent(BNFParser const &parent)
{
	t_uint	i;

	for (i = 0; i < this->size(); ++i)
		(*this)[i].pushParent(parent);
}

BNFFind		&BNFFind::operator=(BNFFind const &other)
{
	*static_cast<std::vector<BNFInher> *>(this) = other;
	return (*this);
}
