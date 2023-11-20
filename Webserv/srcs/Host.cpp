/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Host.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/20 16:06:58 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "ClientRequest.hpp"

Host::Host(const Host& src) { *this = src; }

Host::Host(const char* conf) {
	_max_clients = 128;
	_client_max_body_size = 1;
	_client_body_buffer_size = 128;
	_root = "";

	_max_sk = -1;
	ConfigurationParser	parser(_servers, this, conf);
}

Host&	Host::operator=( Host const & src )
{
	(void) src;
	return (*this);
}

Host::~Host()
{
	std::cout << "Host Destructor" << std::endl;
	for (std::vector<Server*>::iterator it = _servers.begin();
		it != _servers.end(); ++it)
		delete (*it);
	for (std::map<int, ClientRequest*>::iterator it = _sk_client_request.begin();
		it != _sk_client_request.end(); ++it)
		delete (it->second);
	std::cout << "End server" << std::endl;
}

void  	Host::add_new_sk_2_master_set(int new_sk, Server* s)
{
	if (new_sk > _max_sk)
		_max_sk = new_sk;
	FD_SET(new_sk, &_master_set);
	_sk_server[new_sk] = s;
}

void	Host::new_client_request_sk(int new_sk, Server* s)
{
	add_new_sk_2_master_set(new_sk, s);
	_sk_client_request[new_sk] = new ClientRequest(new_sk, this);
}

void	Host::start(void)
{
	FD_ZERO(&_master_set);
	FD_ZERO(&_server_set);
	int	listen_sk;
	for (std::vector<Server*>::iterator it = _servers.begin() ; it != _servers.end();)
	{
		(*it)->set_host(this);
		listen_sk = (*it)->server_socket();
		if (listen_sk > 0)
		{
			add_new_sk_2_master_set(listen_sk, *it);
			FD_SET(listen_sk, &_server_set);
			++it;
		}
		else
		{
			delete (*it);
			_servers.erase(it);
		}
	}
	if (!_sk_server.size())
		return ;
	do
	{
		memcpy(&_working_set, &_master_set, sizeof(_master_set));
		if (select_available_sk() == false)
			break;
		for (int i = 0; i <= _max_sk && _sk_ready > 0; ++i)
			if (FD_ISSET(i, &_working_set))
			{
				_sk_ready--;
				if (FD_ISSET(i, &_server_set))
					_sk_server[i]->accept_client_sk();
				else
					_sk_client_request[i]->read_client_request();
			}
	} while (true);
}

void	Host::end(void)
{
}

bool	Host::select_available_sk(void)
{
	std::cout << "Waiting on select() ..." << std::endl;
	_sk_ready = select(_max_sk + 1, &_working_set, NULL, NULL, NULL);// No timeout
	if (_sk_ready < 0)
	{
		if (errno != EINTR)
			perror("working set select() failed");
		return (false);
	}
	return (true);
}

void	Host::close_client_sk(int i)
{
	FD_CLR(i, &_master_set);
	delete (_sk_client_request[i]);
	_sk_client_request.erase(i);
	// If i is max_sk -> find another max_sk
	if (i == _max_sk)
		while (!FD_ISSET(_max_sk, &_master_set))
			_max_sk -= 1;
}

int				Host::get_max_clients(void) const {return (_max_clients);}
std::map<int, Server*>		Host::get_sk_server(void) const {return (_sk_server);}
size_t				Host::get_client_max_body_size(void) const {return (_client_max_body_size);}
size_t				Host::get_client_body_buffer_size(void) const {return (_client_body_buffer_size);}
std::string			Host::get_root(void) const {return (_root);}

void				Host::set_client_max_body_size(size_t n) {_client_max_body_size = n;}
void				Host::set_client_body_buffer_size(size_t n) {_client_body_buffer_size = n;}
void				Host::set_root(std::string r) {_root = r;}
