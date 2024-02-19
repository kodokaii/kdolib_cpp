/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userinput.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/19 22:16:08 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_USERINPUT_H
# define GET_USERINPUT_H

# include "../kdolib.hpp"
# include "../str/strconvert.hpp"

namespace kdo
{
	template<typename T>
	int	userinput(const std::string &prompt, T &output)
	{
		std::string			line;
		
		std::cout << prompt;	
		std::getline(std::cin, line);
		return (kdo::strconvert(line, output));
	}
}

#endif
