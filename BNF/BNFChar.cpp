/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFChar.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/09 19:50:43 by nlaerema         ###   ########.fr       */
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

int			BNFChar::parse(std::string &str, size_t start)
{
	this->parse(kdo::string_view(str, start));
}

int			BNFChar::parse(kdo::string_view const &str, size_t start)
{
	if (str[start] != this->c)
	{
		this->clear();
		this->state.set(kdo::failbit);
		return (EXIT_FAILURE);
	}
	this->set(str.data(), str.start() + start, 1);
	this->state.set(kdo::goodbit);
	return (EXIT_SUCCESS);
}

BNFChar		&BNFChar::operator=(BNFChar const &other)
{
	*static_cast<BNFParser *>(this) = other;
	this->c = other.c;
	return (*this);
}
