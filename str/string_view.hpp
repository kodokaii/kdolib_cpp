/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_view.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/10 14:28:43 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../kdolib.hpp"

namespace kdo
{
	class string_view
	{
		protected:
			std::string *str;
			size_t		pos;
			size_t		len;

		public:
			typedef std::string::iterator				iterator;
			typedef std::string::const_iterator			const_iterator;
			typedef std::string::reverse_iterator		reverse_iterator;
			typedef std::string::const_reverse_iterator	const_reverse_iterator;

									string_view(void);
									string_view(std::string &str, size_t pos = 0, size_t len = std::string::npos);
									string_view(string_view const &other);
									~string_view(void);
			iterator				begin();	
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();	
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();	
			const_reverse_iterator	rend() const;
			const_iterator			cbegin();	
			const_iterator			cend();
			const_reverse_iterator	crbegin();	
			const_reverse_iterator	crend();	
			std::string				&data(void) const;
			size_t					size(void) const;
			size_t					length(void) const;
			size_t					start(void) const;
			void					clear(void);
			void					shr(size_t n);
			void					shl(size_t n);
			void					add(size_t n);
			void					sub(size_t n);
			char					&at(size_t pos);
			char const				&at(size_t pos) const;
			char					&back(void);
			char const				&back(void) const;
			char					&front(void);
			char const				&front(void) const;
			void					setStr(std::string &str);
			void					setPos(size_t pos);
			void					setLen(size_t len);
			void					set(std::string &str, size_t pos = 0, size_t len = std::string::npos);
			void					copy(string_view const &other);
			std::string				string(void) const;
			std::ostream			&put(std::ostream &stream = std::cout) const;
			int						compare(std::string const &str) const;
			int						compare(size_t pos, size_t len, std::string const &str) const;
			int						compare (size_t pos, size_t len, std::string const &str, size_t subpos, size_t sublen) const;
			int						compare(kdo::string_view const &str) const;
			int						compare(size_t pos, size_t len, kdo::string_view const &str) const;
			int						compare(size_t pos, size_t len, kdo::string_view const &str, size_t subpos, size_t sublen) const;
			char					&operator[](size_t pos);
			char const				&operator[](size_t pos) const;
			string_view 			&operator+=(size_t n);
			string_view 			&operator-=(size_t n);
			string_view 			operator+(size_t n) const;
			string_view 			operator-(size_t n) const;
			string_view 			&operator++(void);
			string_view 			operator++(int);
			string_view 			&operator--(void);
			string_view 			operator--(int);
			string_view				&operator=(string_view const &other);
	};

	std::ostream					&operator<<(std::ostream &stream, string_view const &string_view);
}
