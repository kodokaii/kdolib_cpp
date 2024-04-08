/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFInher.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/09 01:33:12 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFInher.hpp"

BNFInher::BNFInher(BNFParser const &son):	kdo::string_view(son),	
											name(son.getName()),
											state(son.getState())
{
}


BNFInher::BNFInher(BNFInher const &other):	kdo::string_view(other),
											inher(other.inher),
											inherState(other.inherState),
											name(other.name),
											state(other.state)
{
}

BNFInher::~BNFInher(void)
{
}

size_t				BNFInher::pushParent(BNFParser const &parent)
{
	this->inher.push_back(&parent.getName());
	this->inherState |= parent.getState();
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
	t_uint	i;

	i = 0;
	while (i < this->inher.size() && count)
	{
		parent = va_arg(argList, char *);
		while (i < this->inher.size() && *this->inher[i] != parent)
			++i;
		count--;
	}
	va_end(argList);
	return (i != this->inher.size());
}

std::string const	&BNFInher::getName(void) const
{
	return (this->name);
}

kdo::State const	&BNFInher::getState(void) const
{
	return (this->state);
}

kdo::State const	&BNFInher::getInherState(void) const
{
	return (this->inherState);
}

BNFInher			&BNFInher::operator=(BNFInher const &other)
{
	*static_cast<kdo::string_view *>(this) = other;
	this->inher = other.inher;
	this->inherState = other.inherState;
	const_cast<std::string &>(this->name) = other.name;
	this->state = other.state;
	return (*this);
}
