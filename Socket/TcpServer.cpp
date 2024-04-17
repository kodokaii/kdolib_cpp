/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TcpServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/17 17:40:02 by nlaerema         ###   ########.fr       */
/*                                                                            */ /* ************************************************************************** */

#include "TcpServer.hpp"

TcpServer::TcpServer(void):	connected(false),
							backlog(TCP_SERVER_INVALID_BACKLOG),
							addrError(0)
{
}

TcpServer::TcpServer(std::string const &port, int backlog):	connected(false),
															backlog(TCP_SERVER_INVALID_BACKLOG),
															addrError(0)
{

	this->connect(port, backlog);
}

TcpServer::~TcpServer(void)
{
	std::map<int, TcpClient *>::iterator	it;

	for (it = this->clients.begin(); it != this->clients.end(); ++it)
		delete it->second;
	this->disconnect();
}

int				TcpServer::getAddrs(struct addrinfo **res, std::string const &service)
{
	struct addrinfo	hints = {};
	int				error;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	error = getaddrinfo(NULL, service.c_str(), &hints, res);
	return (error);
}

int				TcpServer::connect(std::string const &port, int backlog)
{
	struct addrinfo				*addrs;
	struct addrinfo				*cr;
	int							fd;
	int							opt;

	this->addrError = this->getAddrs(&addrs, port);
	if (this->addrError)
		return (this->addrError);
	for (cr = addrs; cr; cr = cr->ai_next)
	{
		fd = ::socket(cr->ai_family, cr->ai_socktype, cr->ai_protocol);
		if (fd == INVALID_FD)
			continue;
		opt = 1;
		if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
			return (EXIT_ERRNO);
		if (!::bind(fd, cr->ai_addr, cr->ai_addrlen) && !listen(fd, backlog))
			break;
		::close(fd);
	}
	freeaddrinfo(addrs);
	if (!cr)
		return (EXIT_ERRNO);
	this->disconnect();
	this->fd = fd;
	this->backlog = backlog;
	this->connected = true;
	return (EXIT_SUCCESS);
}

int				TcpServer::accept(TcpClient const *&client)
{
	struct sockaddr_storage clientAddr;
	socklen_t				addrSize;
	int						clientSocket;

	addrSize = sizeof(clientAddr);
	clientSocket = ::accept(this->fd, (struct sockaddr *)&clientAddr, &addrSize);
	if (clientSocket == INVALID_FD)
		return (EXIT_ERRNO);
	this->clients[clientSocket] = new TcpClient(clientSocket);
	client = this->clients[clientSocket];
	return (EXIT_SUCCESS);
}

int				TcpServer::broadcast(void const *buf, size_t len, int flags)
{
	int											error(0);
	std::map<int, TcpClient *>::iterator	it;

	for (it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if (it->second->send(buf, len, flags) < 0)
			error++;
	}
	return (error);
}

int				TcpServer::broadcast(std::string const &str, int flags)
{	
	int											error(0);
	std::map<int, TcpClient *>::iterator	it;

	for (it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if (it->second->send(str, flags) < 0)
			error++;
	}
	return (error);
}

int				TcpServer::broadcast(kdo::string_view const &str, int flags)
{
	int											error(0);
	std::map<int, TcpClient *>::iterator	it;

	for (it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if (it->second->send(str, flags) < 0)
			error++;
	}
	return (error);
}

void			TcpServer::disconnect(void)
{
	std::map<int, TcpClient *>::iterator	it;

	this->close();
	this->connected = false;
	for (it = this->clients.begin(); it != this->clients.end(); ++it)
		delete it->second;
	this->clients.clear();
}

void			TcpServer::disconnectClient(int clientSocket)
{
	std::map<int, TcpClient *>::iterator  it;

	it = this->clients.find(clientSocket);
	if (it != this->clients.end())
	{
		delete it->second;
		this->clients.erase(it);
	}
}

int				TcpServer::getClient(TcpClient const *&client, int clientSocket)
{
	std::map<int, TcpClient *>::iterator  it;

	it = this->clients.find(clientSocket);
	if (it == this->clients.end())
		return (EXIT_FAILURE);
	client = it->second;
	return (EXIT_SUCCESS);
}

bool			TcpServer::isConnected(void) const
{
	return (this->connected);
}

int				TcpServer::getAddrError(void) const
{
	return (this->addrError);
}

int				TcpServer::getBacklog(void) const
{
	return (this->backlog);
}
