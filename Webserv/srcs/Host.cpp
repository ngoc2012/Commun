/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Host.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/16 19:59:17 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "ClientRequest.hpp"

Host::Host(const Host& src) { *this = src; }

Host::Host(const char* conf) {
	_max_sk = -1;
	_max_clients = 128;
	_servers = c;
	_end_host = false;
	ConfigurationParser	parser(servers, conf);
}

Host&	Host::operator=( Host const & src )
{
	(void) src;
	return (*this);
}

Host::~Host() {}

void  	Host::add_new_sk_2_master_set(int new_sk, Server* s)
{
	if (new_sk > _max_sk)
		_max_sk = new_sk;
	FD_SET(new_sk, &_master_set);
	_sk_server[new_sk] = s;
}

void	Host::new_client_request_sk(int new_sk, Server* s)
{
	add_new_sk_2_master_set(int new_sk, Server* s);
	_client_requests[new_sk] = new ClientRequest(new_sk, this);
}

void	Host::start(void)
{
	FD_ZERO(&_master_set);
	FD_ZERO(&_server_set);
	int	listen_sk;
	for (std::vector<Server*>::iterator it = _servers.begin() ; it != _servers.end(); ++it)
	{
		(*it)->set_host(this);
		listen_sk = (*it)->server_socket();
		if (listen_sk > 0)
		{
			add_new_sk_2_master_set(listen_sk, *it);
			FD_SET(listen_sk, &_server_set);
		}
	}
	do
	{
		memcpy(&_working_set, &_master_set, sizeof(_master_set));
		if (select_available_sk() == false)
			break;
		for (int i = 0; i <= _max_sk && _sk_ready > 0; ++i)
			if (FD_ISSET(i, &_working_set))
			{
				_sk_ready--;
				if (FD_ISSET(im &_server_set))
					_servers[i]->accept_client_sk();
				else
					_client_requests[i]->read_client_request();
			}
	} while (true);
	end();
}

void	Host::end(void)
{
	for (std::vector<Server*>::iterator it = _servers->begin();
		it != _servers->end(); ++it)
		delete (it);
	for (std::vector<ClientRequest*>::iterator it = _client_requests->begin();
		it != _client_requests->end(); ++it)
		delete (it);
	std::cout << "End server" << std::endl;
}

bool	Host::select_available_sk(void)
{
	std::cout << "Waiting on select() ..." << std::endl;
	_sk_ready = select(_max_sk + 1, &_working_set, NULL, NULL, NULL);// No timeout
	if (_sk_ready < 0)
	{
		perror("working set select() failed");
		return (false);
	}
	return (true);
}

void	Host::close_client_sk(int i)
{
	FD_CLR(i, &_master_set);
	delete (_client_requests[i]);
	_client_requests.erase(i);
	// If i is max_sk -> find another max_sk
	if (i == _max_sk)
		while (!FD_ISSET(_max_sk, &_master_set))
			_max_sk -= 1;
}

int	Host::get_max_clients(void) const {return (_max_clients);}

void	Host::set_end_host(bool e) {_end_host = e;}
