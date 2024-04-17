/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TcpServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/17 17:37:53 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <netdb.h>
#include "../kdolib.hpp"

#define TCP_SERVER_INVALID_BACKLOG -1
#define TCP_SERVER_DEFAULT_BACKLOG 128

class TcpClient;

class TcpServer: protected Socket
{
	protected:
		bool								connected;
		int									backlog;
		int									addrError;
		std::map<int, TcpClient *>			clients;

		int				getAddrs(struct addrinfo **res, std::string const &port);

	public:
						TcpServer(void);
						TcpServer(std::string const &port, int backlog = TCP_SERVER_DEFAULT_BACKLOG);
						~TcpServer(void);
		int				connect(std::string const &port, int backlog = TCP_SERVER_DEFAULT_BACKLOG);
		int				accept(TcpClient const *&client);
		int				broadcast(void const *buf, size_t len, int flags = 0);
		int				broadcast(std::string const &str, int flags = 0);
		int				broadcast(kdo::string_view const &str, int flags = 0);
		void			disconnect(void);
		void			disconnectClient(int clientSocket);
		int				getClient(TcpClient const *&client, int clientSocket);
		bool			isConnected(void) const;
		int				getAddrError(void) const;
		int				getBacklog(void) const;
		using			Socket::getFd;
};
