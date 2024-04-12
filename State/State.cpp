/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/10 16:04:30 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"

namespace kdo
{
	State::State(stateFlags flags): flags(flags)
	{
	}

	State::State(State const &other): flags(other.flags)
	{
	}

	State::~State(void)
	{
	}

	bool		State::good(void) const
	{
		return (this->flags & goodbit);
	}

	bool		State::eof(void) const
	{
		return (this->flags & eofbit);
	}

	bool		State::fail(void) const
	{
		return (this->flags & failbit);
	}

	bool		State::bad(void) const
	{
		return (this->flags & badbit);
	}

	stateFlags	State::get(void) const
	{
		return (this->flags);
	}

	void		State::set(stateFlags flags)
	{
		this->flags = flags;
	}

	void		State::add(stateFlags flags)
	{
		this->flags = stateFlags(this->flags | flags);
	}

	void		State::del(stateFlags flags)
	{
		this->flags = stateFlags(this->flags & ~flags);
	}

	void		State::clear(void)
	{
		this->flags = clearbit;
	}

	State		State::operator~(void) const
	{
		return (stateFlags(~this->flags));
	}

	bool		State::operator==(stateFlags flags) const
	{
		return (this->flags == flags);
	}

	bool		State::operator!=(stateFlags flags) const
	{
		return (this->flags != flags);
	}

	State		State::operator&(stateFlags flags) const
	{
		return (stateFlags(this->flags & flags));
	}

	State		State::operator|(stateFlags flags) const
	{
		return (stateFlags(this->flags | flags));
	}

	State		State::operator^(stateFlags flags) const
	{
		return (stateFlags(this->flags ^ flags));
	}


	State		&State::operator&=(stateFlags flags)
	{
		this->flags = stateFlags(this->flags & flags);
		return (*this);
	}

	State		&State::operator|=(stateFlags flags)
	{
		this->flags = stateFlags(this->flags | flags);
		return (*this);
	}

	State		&State::operator^=(stateFlags flags)
	{
		this->flags = stateFlags(this->flags ^ flags);
		return (*this);
	}

	State		&State::operator=(stateFlags flags)
	{
		this->flags = flags;
		return (*this);
	}

	bool		State::operator==(State const &other) const
	{
		return (this->flags == other.flags);
	}

	bool		State::operator!=(State const &other) const
	{
		return (this->flags != other.flags);
	}

	State		State::operator&(State const &other) const
	{
		return (stateFlags(this->flags & other.flags));
	}

	State		State::operator|(State const &other) const
	{
		return (stateFlags(this->flags | other.flags));
	}

	State		State::operator^(State const &other) const
	{
		return (stateFlags(this->flags ^ other.flags));
	}

	State		&State::operator&=(State const &other)
	{
		this->flags = stateFlags(this->flags & other.flags);
		return (*this);
	}

	State		&State::operator|=(State const &other)
	{
		this->flags = stateFlags(this->flags | other.flags);
		return (*this);
	}

	State		&State::operator^=(State const &other)
	{
		this->flags = stateFlags(this->flags ^ other.flags);
		return (*this);
	}

	State		&State::operator=(State const &other)
	{
		this->flags = other.flags;
		return (*this);
	}
}
