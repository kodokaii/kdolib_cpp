/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_userInput.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/18 17:31:06 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_USERINPUT_H
# define GET_USERINPUT_H

# include "../kdolib.hpp"

namespace kdo
{
	template<typename T>
	void	get_userInput(std::string prompt, T &var)
	{
		std::cout << prompt;	
		std::cin >> var;
	}
}

#endif
