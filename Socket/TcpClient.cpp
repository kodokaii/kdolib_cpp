/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TcpClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/17 15:20:18 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TcpClient.hpp"

TcpClient::TcpClient(void):	connected(false),
							addrError(0)
{
}

TcpClient::TcpClient(int fd):	connected(false),
								addrError(0)
{
	this->connect(fd);
}

TcpClient::TcpClient(std::string const &addr, std::string const port):	connected(false),
																		addrError(0)
{
	this->connect(addr, port);
}

TcpClient::~TcpClient(void)
{
	this->disconnect();
}

int				TcpClient::getAddrs(struct addrinfo **res,
				std::string const &node, std::string const &service) const
{
	struct addrinfo	hints = {};
	int				error;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	error = getaddrinfo(node.c_str(), service.c_str(), &hints, res);
	return (error);
}

ssize_t			TcpClient::send(void const *buf, size_t len, int flags) const
{
	return (::send(this->fd, buf, len, flags));
}

ssize_t			TcpClient::send(char const *str, int flags) const
{
	return (::send(this->fd, str, strlen(str), flags));
}

ssize_t			TcpClient::send(std::string const &str, int flags) const
{
	return (::send(this->fd, str.c_str(), str.size(), flags));
}

ssize_t			TcpClient::send(kdo::string_view const &str, int flags) const
{
	return (::send(this->fd, str.c_str(), str.size(), flags));
}

ssize_t			TcpClient::recv(void *buf, size_t len, int flags) const
{
	return (::recv(this->fd, buf, len, flags));
}

ssize_t			TcpClient::recv(std::string &str, int flags) const
{
	static char	buf[TCP_CLIENT_BUF_SIZE];
	ssize_t		bytes_recv(TCP_CLIENT_BUF_SIZE);
	ssize_t		all_bytes_recv(0);

	str.clear();
	while (bytes_recv == TCP_CLIENT_BUF_SIZE)
	{
		bytes_recv = ::recv(this->fd, buf, TCP_CLIENT_BUF_SIZE, flags);
		if (0 < bytes_recv)
		{
			all_bytes_recv += bytes_recv;
			str.append(buf, bytes_recv);
		}
		if (bytes_recv < 0 && all_bytes_recv == 0)
			return (-1);
	}
	return (all_bytes_recv);
}

int				TcpClient::connect(int socketConnected)
{
	int			socketType;
	socklen_t	typeSize;

	typeSize = sizeof(socketType);
	if (getsockopt(socketConnected, SOL_SOCKET, SO_TYPE, &socketType, &typeSize))
		return (EXIT_ERRNO);
	if (socketType != SOCK_STREAM)
		return (EXIT_FAILURE);
	this->setFd(socketConnected);
	return (EXIT_SUCCESS);
}

int				TcpClient::connect(std::string const &addr, std::string const &port)
{
	struct addrinfo				*addrs;
	struct addrinfo				*cr;
	int							fd;

	this->addrError = this->getAddrs(&addrs, addr, port);
	if (this->addrError)
		return (this->addrError);
	for (cr = addrs; cr; cr = cr->ai_next)
	{
		fd = ::socket(cr->ai_family, cr->ai_socktype, cr->ai_protocol);
		if (fd == INVALID_FD)
			continue;
		if (!::connect(fd, cr->ai_addr, cr->ai_addrlen))
			break;
		::close(fd);
	}
	freeaddrinfo(addrs);
	if (!cr)
		return (EXIT_ERRNO);
	this->disconnect();
	this->fd = fd;
	this->connected = true;
	return (EXIT_SUCCESS);
}

void			TcpClient::disconnect(void)
{
	if (this->isConnected())
	{
		this->close();
		this->connected = false;
	}
}

bool			TcpClient::isConnected(void) const
{
	return (this->connected);
}

int				TcpClient::getAddrError(void) const
{
	return (this->addrError);
}

TcpClient const	&TcpClient::operator<<(char const *str) const
{
	this->send(str);
	return (*this);
}

TcpClient const	&TcpClient::operator<<(kdo::string_view const &str) const
{
	this->send(str);
	return (*this);
}

TcpClient const	&TcpClient::operator<<(std::string const &str) const
{
	this->send(str);
	return (*this);
}

std::string		&TcpClient::operator>>(std::string &str) const
{
	this->recv(str);
	return (str);
}
