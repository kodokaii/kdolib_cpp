/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFChar.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/14 18:36:26 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFChar.hpp"

BNFChar::BNFChar(std::string const &name, char c):	BNFParser(name),
													c(c)
{
}

BNFChar::BNFChar(char c):	BNFParser((char[4]){'\'', c, '\''}),
							c(c)
{
}

BNFChar::BNFChar(BNFChar const &other): BNFParser(other),
										c(other.c)
{
}

BNFChar::~BNFChar(void)
{
}

BNFParser	*BNFChar::clone(void) const
{
	return (new BNFChar(*this));
}

int			BNFChar::parse(kdo::string_view const &str, size_t start, size_t len)
{
	if (!len || str.size() <= start || str[start] != this->c)
	{
		this->set(str.data(), str.start() + start, 0);
		this->state.set(kdo::failbit);
		if (!len || str.size() <= start)
			this->state.add(kdo::eofbit);
		return (EXIT_FAILURE);
	}
	this->set(str.data(), str.start() + start, 1);
	this->state.set(kdo::goodbit);
	if (str.size() == start + 1)
		this->state.add(kdo::eofbit);
	return (EXIT_SUCCESS);
}

BNFChar		&BNFChar::operator=(BNFChar const &other)
{
	*static_cast<BNFParser *>(this) = other;
	this->c = other.c;
	return (*this);
}
