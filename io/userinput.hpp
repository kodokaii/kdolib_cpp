/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userinput.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/05 23:16:17 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../kdolib.hpp"

namespace kdo
{
	template<typename T>
	int	userinput(const std::string &prompt, T &output)
	{
		std::string			line;
		
		std::cout << prompt;	
		std::getline(std::cin, line);
		return (kdo::convert(line, output).fail);
	}
}
