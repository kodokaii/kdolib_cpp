/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TcpClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/18 13:02:39 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <netdb.h>
#include "../kdolib.hpp"

#define	TCP_CLIENT_BUF_SIZE 512

class TcpServer;

class TcpClient: protected Socket
{
	protected:
		bool			connected;
		int				addrError;

		int				getAddrs(struct addrinfo **res,
							std::string const &node, std::string const &service) const;

	public:
						TcpClient(void);
						TcpClient(int socketConnected);
						TcpClient(std::string const &addr, std::string const port);
						~TcpClient(void);
		ssize_t			send(void const *buf, size_t len, int flags = 0) const;
		ssize_t			send(char const *str, int flags) const;
		ssize_t			send(std::string const &str, int flags = 0) const;
		ssize_t			send(kdo::string_view const &str, int flags = 0) const;
		ssize_t			recv(void *buf, size_t len, int flags = 0) const;
		ssize_t			recv(std::string &str, int flags = 0) const;
		int				connect(int socketConnected);
		int				connect(std::string const &addr, std::string const &port);
		void			disconnect(void);
		bool			isConnected(void) const;;
		int				getAddrError(void) const;
		using			Socket::getFd;
		TcpClient const	&operator<<(char const *str) const;
		TcpClient const	&operator<<(kdo::string_view const &str) const;
		TcpClient const	&operator<<(std::string const &str) const;
		std::string		&operator>>(std::string &str) const;
};
