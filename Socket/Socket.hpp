/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/17 23:01:05 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include "../kdolib.hpp"

class Socket
{
	protected:
		int		fd;

	public:
				Socket(void);
				Socket(int fd);
				Socket(int domain, int type, int protocol = 0);
				~Socket(void);
		int		open(int domain, int type, int protocol = 0);
		bool	is_open(void) const;
		void	close(void);
		int		getFd(void) const;
		void	setFd(int fd);
};
