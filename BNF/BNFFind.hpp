/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFFind.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/09 01:35:18 by nlaerema         ###   ########.fr       */
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
		BNFFind		heir(t_uint count, ...) const;
		BNFFind		fail(void) const;
		BNFFind		good(void) const;
		BNFFind     inherFail(void) const;
		BNFFind     inherGood(void) const;
		BNFFind		&operator=(BNFFind const &other);
};
