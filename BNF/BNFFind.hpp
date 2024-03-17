/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFFind.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/17 22:43:14 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../kdolib.hpp"

class BNFParser;
class BNFInher;

class BNFFind: public std::vector<BNFInher>
{
	public:
					BNFFind(void);
					BNFFind(BNFFind const &other);
					~BNFFind(void);
		void		merge(BNFFind const &other);
		void		pushParent(BNFParser const &parent);
		BNFFind		isHeir(t_uint count, ...) const;
		BNFFind		isFail(void) const;
		BNFFind		isSuccess(void) const;
		BNFFind		&operator=(BNFFind const &other);
};
