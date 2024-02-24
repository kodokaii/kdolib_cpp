/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strconvert.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/24 13:28:03 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRCONVERT_H
# define STRCONVERT_H

# include "../kdolib.hpp"

namespace kdo
{
	template<typename T>
	int	strconvert(const std::string &str, T &output)
	{
		std::stringstream	ss(str);

		ss >> output;
		return (!ss || ss.peek() != EOF);
	}

	template<> inline
	int	strconvert(const std::string &str, std::string &output)
	{
		output = str;
		return (0);
	}
}

#endif
