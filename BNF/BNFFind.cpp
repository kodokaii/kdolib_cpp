/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFFind.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/15 10:24:43 by nlaerema         ###   ########.fr       */
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
	t_uint	cr;

	for (cr = 0; cr < other.size(); cr++)
		this->push_back(other[cr]);
}

BNFFind		BNFFind::isHeir(t_uint count, ...) const
{
	va_list	argListCopy;
	va_list	argList;
	BNFFind	res;
	t_uint	cr;

	va_start(argList, count);
	for (cr = 0; cr < this->size(); cr++)
	{
		__builtin_va_copy(argListCopy, argList);
		if ((*this)[cr].isHeir(count, argListCopy))
			res.push_back((*this)[cr]);
	}
	va_end(argList);
	return (res);
}

BNFFind		BNFFind::isFail(void) const
{
	BNFFind	res;
	t_uint	cr;

	for (cr = 0; cr < this->size(); cr++)
	{
		if ((*this)[cr].getInherErrorLen() != BNF_ERROR_POS_NONE)
			res.push_back((*this)[cr]);
	}
	return (res);
}

BNFFind		BNFFind::isSuccess(void) const
{
	BNFFind	res;
	t_uint	cr;

	for (cr = 0; cr < this->size(); cr++)
	{
		if ((*this)[cr].getInherErrorLen() == BNF_ERROR_POS_NONE)
			res.push_back((*this)[cr]);
	}
	return (res);
}

void		BNFFind::pushParent(BNFParser const &parent)
{
	t_uint	cr;

	for (cr = 0; cr < this->size(); cr++)
		(*this)[cr].pushParent(parent);
}

BNFFind		&BNFFind::operator=(BNFFind const &other)
{
	*static_cast<std::vector<BNFInher> *>(this) = other;
	return (*this);
}
