/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFStr.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/08 23:43:39 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFStr.hpp"

BNFStr::BNFStr(std::string const &name, std::string const &str):	BNFParser(name),
																	ref(str)
{
}

BNFStr::BNFStr(std::string const &str):	BNFParser('\"' + str + '\"'),
										ref(str)
{
}

BNFStr::BNFStr(BNFStr const &other):	BNFParser(other),
										ref(other.ref)
{
}

BNFStr::~BNFStr(void)
{
}

BNFParser	*BNFStr::clone(void) const
{
	return (new BNFStr(*this));
}

int			BNFStr::parse(std::string &str, size_t start)
{
	if (str.compare(start, this->ref.length(), this->ref))
	{
		this->clear();
		this->state.set(kdo::failbit);
		return (EXIT_FAILURE);
	}
	this->set(str, start, this->ref.length());
	this->state.set(kdo::goodbit);
	return (EXIT_SUCCESS);
}

BNFStr	&BNFStr::operator=(BNFStr const &other)
{
	*static_cast<BNFParser *>(this) = other;
	this->ref = other.ref;
	return (*this);
}
