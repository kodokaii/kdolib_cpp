/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_view.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/07 20:43:48 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_view.hpp"

namespace kdo
{
	string_view::string_view(std::string &str, size_t pos, size_t len):	str(str),
																		pos(pos),
																		len(len)
																				
	{
	}

	string_view::string_view(string_view const &other): str(other.str),
														pos(other.pos),
														len(other.len)
	{
	}

	string_view::~string_view(void)
	{
	}

	string_view::iterator				string_view::begin()
	{
		return (this->str.begin() + this->start());
	}

	string_view::const_iterator			string_view::begin() const
	{
		return (this->str.begin() + this->start());
	}

	string_view::iterator				string_view::end()
	{
		return (this->str.begin() + this->start() + this->size());
	}

	string_view::const_iterator			string_view::end() const
	{
		return (this->str.begin() + this->start() + this->size());
	}

	string_view::reverse_iterator		string_view::rbegin()
	{
		return (this->str.rbegin() + (this->str.size() - this->start()));
	}

	string_view::const_reverse_iterator	string_view::rbegin() const
	{
		return (this->str.rbegin() + (this->str.size() - this->start()));
	}

	string_view::reverse_iterator		string_view::rend()
	{
		return (this->str.rbegin() + (this->str.size() - this->start() - this->size()));
	}

	string_view::const_reverse_iterator	string_view::rend() const
	{
		return (this->str.rbegin() + (this->str.size() - this->start() - this->size()));
	}

	string_view::const_iterator			string_view::cbegin()
	{
		return (this->str.begin() + this->start());
	}

	string_view::const_iterator			string_view::cend()
	{
		return (this->str.begin() + this->start() + this->size());
	}

	string_view::const_reverse_iterator	string_view::crbegin()
	{
		return (this->str.rbegin() + (this->str.size() - this->start()));
	}

	string_view::const_reverse_iterator	string_view::crend()
	{
		return (this->str.rbegin() + (this->str.size() - this->start() - this->size()));
	}

	size_t								string_view::size(void) const
	{
		if (this->str.size() <= this->pos)
			return (0);
		if (this->str.size() <= this->pos + this->len)
			return (this->str.size() - this->pos);
		return (this->len);
	}

	size_t								string_view::length(void) const
	{
		if (this->str.length() <= this->pos)
			return (0);
		if (this->str.length() <= this->pos + this->len)
			return (this->str.length() - this->pos);
		return (this->len);
	}

	size_t								string_view::start(void) const
	{
		if (this->str.size() < this->pos)
			return (this->str.size());
		return (this->pos);
	}

	void								string_view::shr(size_t n)
	{
		this->pos += n;
	}

	void								string_view::shl(size_t n)
	{
		this->pos -= n;
	}

	void								string_view::add(size_t n)
	{
		this->len += n;
	}

	void								string_view::sub(size_t n)
	{
		this->len -= n;
	}

	void								string_view::clear(void)
	{
		this->len = 0;
	}

	char								&string_view::at(size_t pos)
	{
		return (this->str.at(this->pos + pos));
	}

	char const							&string_view::at(size_t pos) const
	{
		return (this->str.at(this->pos + pos));
	}

	char								&string_view::back(void)
	{
		if (!this->len)
			return (*this->str.end());
		return (this->str[this->start() + this->len - 1]);
	}

	char const							&string_view::back(void) const
	{
		if (!this->len)
			return (*this->str.end());
		return (this->str[this->start() + this->len - 1]);
	}

	char								&string_view::front(void)
	{
		return (this->str[this->start()]);
	}

	char const							&string_view::front(void) const
	{
		return (this->str[this->start()]);
	}

	std::string							string_view::string(void) const
	{
		return (this->str.substr(this->start(), this->size()));
	}

	char								&string_view::operator[](size_t pos)
	{
		return (this->str[this->start() + pos]);
	}

	char const							&string_view::operator[](size_t pos) const
	{
		return (this->str[this->start() + pos]);
	}

	string_view 						&string_view::operator+=(size_t n)
	{
		this->len += n;
		return (*this);
	}

	string_view 						&string_view::operator-=(size_t n)
	{
		this->len -= n;
		return (*this);
	}

	string_view 						string_view::operator+(size_t n) const
	{
		return (string_view(this->str, this->pos, this->len + n));
	}

	string_view 						string_view::operator-(size_t n) const
	{
		return (string_view(this->str, this->pos, this->len - n));
	}

	string_view 						&string_view::operator++(void)
	{
		++this->len;
		return (*this);
	}

	string_view 						string_view::operator++(int)
	{
		string_view	tmp(*this);

		++this->len;
		return (tmp);
	}

	string_view 						&string_view::operator--(void)
	{
		--this->len;
		return (*this);
	}

	string_view 						string_view::operator--(int)
	{
		string_view	tmp(*this);

		--this->len;
		return (tmp);
	}

	string_view							&string_view::operator=(string_view const &other)
	{
		this->str = other.str;
		this->pos = other.pos;
		this->len = other.len;
		return (*this);
	}
}
