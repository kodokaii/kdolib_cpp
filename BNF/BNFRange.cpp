/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFRange.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/13 11:02:15 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFRange.hpp"

BNFRange::BNFRange(std::string const &name, t_uchar cMin, t_uchar cMax):	BNFParser(name),
																			cMin(cMin),
																			cMax(cMax)	
{
}

BNFRange::BNFRange(t_uchar cMin, t_uchar cMax):	BNFParser("%x" + kdo::itoa(cMin, 16) + '-' + kdo::itoa(cMax, 16)),
												cMin(cMin),
												cMax(cMax)	
{
}

BNFRange::BNFRange(BNFRange const &other):	BNFParser(other),
											cMin(other.cMin),
											cMax(other.cMax)
{
}

BNFRange::~BNFRange(void)
{
}

BNFParser	*BNFRange::clone(void) const
{
	return (new BNFRange(*this));
}

int			BNFRange::parse(kdo::string_view const &str, size_t start, size_t len)
{
	if (!len || str.size() < start || str[start] < this->cMin || this->cMax < str[start])
	{
		this->clear();
		this->state.set(kdo::failbit);
		if (str.size() < start)
			this->state.add(kdo::eofbit);
		return (EXIT_FAILURE);
	}
	this->set(str.data(), str.start() + start, 1);
	this->state.set(kdo::goodbit);
	if (str.size() == start)
		this->state.add(kdo::eofbit);
	return (EXIT_SUCCESS);
}

BNFRange	&BNFRange::operator=(BNFRange const &other)
{
	*static_cast<BNFParser *>(this) = other;
	this->cMin = other.cMin;
	this->cMax = other.cMax;
	return (*this);
}
