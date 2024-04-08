/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFInher.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/09 01:32:02 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../kdolib.hpp"

class BNFParser;

class BNFInher: public kdo::string_view
{
	protected:
		std::vector<std::string const *>	inher;
		kdo::State							inherState;
		std::string const					&name;
		kdo::State							state;

	public:
							BNFInher(BNFParser const &son);
							BNFInher(BNFInher const &other);
							~BNFInher(void);
		size_t				pushParent(BNFParser const &parent);
		bool				isHeir(t_uint count, ...) const;
		bool				isHeir(t_uint count, va_list argList) const;
		std::string const	&getName(void) const;
		kdo::State const	&getState(void) const;
		kdo::State const	&getInherState(void) const;
		BNFInher			&operator=(BNFInher const &other);
};
