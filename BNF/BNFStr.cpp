/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFStr.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ /*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */ /*   Updated: 2024/04/09 19:53:52 by nlaerema         ###   ########.fr       */
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

int			BNFStr::parse(kdo::string_view const &str, size_t start, size_t len)
{
	if (this->ref.size() < len || str.size() < start + this->ref.size() || str.compare(start, this->ref.length(), this->ref))
	{
		this->clear();
		this->state.set(kdo::failbit);
		if (str.size() < start + this->ref.length())
			this->state.add(kdo::eofbit);
		return (EXIT_FAILURE);
	}
	this->set(str.data(), str.start() + start, this->ref.length());
	this->state.set(kdo::goodbit);
	if (str.size() == start + this->ref.length())
		this->state.add(kdo::eofbit);
	return (EXIT_SUCCESS);
}

BNFStr	&BNFStr::operator=(BNFStr const &other)
{
	*static_cast<BNFParser *>(this) = other;
	this->ref = other.ref;
	return (*this);
}
