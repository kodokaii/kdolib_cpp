/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_view.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/13 18:47:30 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kdolib.hpp"
#include "string_view.hpp"

namespace kdo
{

	string_view::string_view(void): str(NULL),
									pos(0),
									len(0)
	{
	}

	string_view::string_view(std::string &str, size_t pos, size_t len):	str(&str),
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
		return (this->str->begin() + this->start());
	}

	string_view::const_iterator			string_view::begin() const
	{
		return (this->str->begin() + this->start());
	}

	string_view::iterator				string_view::end()
	{
		return (this->str->begin() + this->start() + this->size());
	}

	string_view::const_iterator			string_view::end() const
	{
		return (this->str->begin() + this->start() + this->size());
	}

	string_view::reverse_iterator		string_view::rbegin()
	{
		return (this->str->rbegin() + (this->str->size() - this->start()));
	}

	string_view::const_reverse_iterator	string_view::rbegin() const
	{
		return (this->str->rbegin() + (this->str->size() - this->start()));
	}

	string_view::reverse_iterator		string_view::rend()
	{
		return (this->str->rbegin() + (this->str->size() - this->start() - this->size()));
	}

	string_view::const_reverse_iterator	string_view::rend() const
	{
		return (this->str->rbegin() + (this->str->size() - this->start() - this->size()));
	}

	string_view::const_iterator			string_view::cbegin()
	{
		return (this->str->begin() + this->start());
	}

	string_view::const_iterator			string_view::cend()
	{
		return (this->str->begin() + this->start() + this->size());
	}

	string_view::const_reverse_iterator	string_view::crbegin()
	{
		return (this->str->rbegin() + (this->str->size() - this->start()));
	}

	string_view::const_reverse_iterator	string_view::crend()
	{
		return (this->str->rbegin() + (this->str->size() - this->start() - this->size()));
	}

	std::string							&string_view::data(void) const
	{
		return (*this->str);
	}

	size_t								string_view::size(void) const
	{
		if (this->str->size() <= this->pos)
			return (0);
		if (this->str->size() <= this->pos + this->len)
			return (this->str->size() - this->pos);
		return (this->len);
	}

	size_t								string_view::length(void) const
	{
		if (this->str->length() <= this->pos)
			return (0);
		if (this->str->length() <= this->pos + this->len)
			return (this->str->length() - this->pos);
		return (this->len);
	}

	size_t								string_view::start(void) const
	{
		if (this->str->size() < this->pos)
			return (this->str->size());
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
		return (this->str->at(this->pos + pos));
	}

	char const							&string_view::at(size_t pos) const
	{
		return (this->str->at(this->pos + pos));
	}

	char								&string_view::back(void)
	{
		if (!this->len)
			return (*this->str->end());
		return ((*this->str)[this->start() + this->len - 1]);
	}

	char const							&string_view::back(void) const
	{
		if (!this->len)
			return (*this->str->end());
		return ((*this->str)[this->start() + this->len - 1]);
	}

	char								&string_view::front(void)
	{
		return ((*this->str)[this->start()]);
	}

	char const							&string_view::front(void) const
	{
		return ((*this->str)[this->start()]);
	}

	void								string_view::setStr(std::string &str)
	{
		this->str = &str;
	}

	void								string_view::setPos(size_t pos)
	{
		this->pos = pos;
	}

	void								string_view::setLen(size_t len)
	{
		this->len = len;
	}

	void								string_view::set(std::string &str, size_t pos, size_t len)
	{
		this->str = &str;
		this->pos = pos;
		this->len = len;
	}

	void								string_view::copy(string_view const &other)
	{
		this->str = other.str;
		this->pos = other.pos;
		this->len = other.len;
	}

	char const							*string_view::c_str(void) const
	{
		return (this->str->c_str() + this->start());
	}

	std::string							string_view::string(void) const
	{
		return (this->str->substr(this->start(), this->size()));
	}

	std::ostream						&string_view::put(std::ostream &stream, size_t pos, size_t len) const
	{
		return (stream << std::setw(std::min(this->size(), len)) << (this->str->c_str() + this->start() + pos));
	}

	kdo::string_view					string_view::substr(size_t pos, size_t len) const
	{
		kdo::string_view	sub(*this);

		sub.pos += std::min(sub.size(), pos);
		sub.len = std::min(sub.size(), len);
		return (sub);
	}

	int									string_view::compare(std::string const &str) const
	{
		return (this->str->compare(this->start(), this->size(), str));
	}

	int									string_view::compare(size_t pos, size_t len, std::string const &str) const
	{
		return (this->str->compare(this->start() + pos, std::min(len, this->size()), str));
	}

	int									string_view::compare (size_t pos, size_t len, std::string const &str, size_t subpos, size_t sublen) const
	{
		return (this->str->compare(this->start() + pos, std::min(len, this->size()), str, subpos, sublen));
	}

	int									string_view::compare(kdo::string_view const &str) const
	{
		return (this->str->compare(this->start(), this->size(), str.data(), str.start(), str.size()));
	}

	int									string_view::compare(size_t pos, size_t len, kdo::string_view const &str) const
	{
		return (this->str->compare(this->start() + pos, std::min(len, this->size()), str.data(), str.start(), str.size()));
	}

	int									string_view::compare(size_t pos, size_t len, kdo::string_view const &str, size_t subpos, size_t sublen) const
	{
		return (this->str->compare(this->start() + pos, std::min(len, this->size()), str.data(), str.start() + subpos, std::min(sublen, str.size())));
	}

	size_t								string_view::find(std::string const &str, size_t pos) const
	{
		size_t	i;
		size_t	j;

		i = pos;
		if (!str.size())
			return (std::string::npos);
		while (i < this->size())
		{
			j = 0;
			while ((*this->str)[i + j] == str[j])
			{
				if (j == str.size())
					return (i);
				j++;
			}
			i++;
		}
		return (std::string::npos);
	}

	size_t								string_view::find(char c, size_t pos) const
	{
		size_t	i;

		i = pos;
		while (i < this->size())
		{
			if ((*this->str)[i] == c)
				return (i);
		}
		return (std::string::npos);

	}

	size_t								string_view::find (char const *s, size_t pos) const
	{
		size_t	i;
		size_t	j;

		i = pos;
		if (!s[0])
			return (std::string::npos);
		while (i < this->size())
		{
			j = 0;
			while ((*this->str)[i + j] == s[j])
			{
				j++;
				if (!s[0])
					return (i);
			}
			i++;
		}
		return (std::string::npos);
	}

	size_t								string_view::find (char const *s, size_t pos, size_t n) const
	{
		size_t	i;
		size_t	j;

		i = pos;
		if (!s[0] || !n)
			return (std::string::npos);
		while (i < this->size())
		{
			j = 0;
			while ((*this->str)[i + j] == s[j])
			{
				j++;
				if (!s[0] || j == n)
					return (i);
			}
			i++;
		}
		return (std::string::npos);
	}

	size_t								string_view::find(kdo::string_view const &str, size_t pos) const
	{
		size_t	i;
		size_t	j;

		i = pos;
		if (!str.size())
			return (std::string::npos);
		while (i < this->size())
		{
			j = 0;
			while ((*this->str)[i + j] == str[j])
			{
				j++;
				if (j == str.size())
					return (i);
			}
			i++;
		}
		return (std::string::npos);
	}

	bool								string_view::operator<(std::string const &str) const
	{
		return (this->compare(str) < 0);
	}

	bool								string_view::operator<=(std::string const &str) const
	{
		return (this->compare(str) <= 0);
	}

	bool								string_view::operator>(std::string const &str) const
	{
		return (0 < this->compare(str));
	}

	bool								string_view::operator>=(std::string const &str) const
	{
		return (0 <= this->compare(str));
	}

	bool								string_view::operator==(std::string const &str) const
	{
		return (!this->compare(str));
	}

	bool								string_view::operator!=(std::string const &str) const
	{
		return (this->compare(str));
	}

	std::string							string_view::operator+(std::string const &str) const
	{
		return (this->string() + str);
	}

	bool								string_view::operator<(kdo::string_view const &str) const
	{
		return (this->compare(str) < 0);
	}

	bool								string_view::operator<=(kdo::string_view const &str) const
	{
		return (this->compare(str) <= 0);
	}

	bool								string_view::operator>(kdo::string_view const &str) const
	{
		return (0 < this->compare(str));
	}

	bool								string_view::operator>=(kdo::string_view const &str) const
	{
		return (0 <= this->compare(str));
	}

	bool								string_view::operator==(kdo::string_view const &str) const
	{
		return (!this->compare(str));
	}

	bool								string_view::operator!=(kdo::string_view const &str) const
	{
		return (this->compare(str));
	}

	std::string							string_view::operator+(kdo::string_view const &str) const
	{
		return (this->string() + str.string());
	}

	char								&string_view::operator[](size_t pos)
	{
		return ((*this->str)[this->start() + pos]);
	}

	char const							&string_view::operator[](size_t pos) const
	{
		return ((*this->str)[this->start() + pos]);
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
		return (string_view(*this->str, this->pos, this->len + n));
	}

	string_view 						string_view::operator-(size_t n) const
	{
		return (string_view(*this->str, this->pos, this->len - n));
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

	std::ostream					&operator<<(std::ostream &stream, string_view const &strView)
	{
		return (strView.put(stream));
	}

	bool							operator<(std::string const &str, string_view const &strView)
	{
		return (0 < strView.compare(str));
	}

	bool							operator<=(std::string const &str, string_view const &strView)
	{
		return (0 <= strView.compare(str));
	}

	bool							operator>(std::string const &str, string_view const &strView)
	{
		return (strView.compare(str) < 0);
	}

	bool							operator>=(std::string const &str, string_view const &strView)
	{
		return (strView.compare(str) <= 0);
	}

	bool							operator==(std::string const &str, string_view const &strView)
	{
		return (!strView.compare(str));
	}

	bool							operator!=(std::string const &str, string_view const &strView)
	{
		return (strView.compare(str));
	}

	std::string						operator+(std::string const &str, kdo::string_view const strView)
	{
		return (str + strView.string());
	}

	std::string						operator+=(std::string &str, kdo::string_view const strView)
	{
		return (str += strView.string());
	}

}
