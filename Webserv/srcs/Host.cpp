/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Host.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/18 13:56:44 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include "Configuration.hpp"

Host::Host(const Host& src) { *this = src; }

Host::Host(const char* conf) {
	_max_clients = 128;
	_client_max_body_size = 1;
	_client_body_buffer_size = 128;
	_parser_error = false;

	_max_sk = -1;
	Configuration	parser(_servers, this, conf);
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
	for (std::map<int, Request*>::iterator it = _sk_request.begin();
		it != _sk_request.end(); ++it)
		delete (it->second);
	std::cout << "End server" << std::endl;
}

void	Host::start(void)
{
	if (_parser_error || !check_servers_conf())
		return ;
	FD_ZERO(&_master_read_set);
	FD_ZERO(&_master_write_set);
	FD_ZERO(&_server_set);
	start_server();
	if (!_sk_server.size())
		return ;
	do
	{
		memcpy(&_read_set, &_master_read_set, sizeof(_master_read_set));
		memcpy(&_write_set, &_master_write_set, sizeof(_master_write_set));
		if (select_available_sk() == false)
			break;
		check_sk_ready();
	} while (true);
}

bool	Host::check_servers_conf(void)
{
	for (std::vector<Server*>::iterator it = _servers.begin(); it != _servers.end(); ++it)
		if ((*it)->get_root() == "")
		{
			std::cerr << "Error: root null" << std::endl;
			return (false);
		}
	return (true);
}

void	Host::start_server(void)
{
	int	listen_sk;
	for (std::vector<Server*>::iterator it = _servers.begin(); it != _servers.end();)
	{
		(*it)->set_host(this);
		listen_sk = (*it)->server_socket();
		if (listen_sk > 0)
		{
			add_sk_2_master_read_set(listen_sk, *it);
			FD_SET(listen_sk, &_server_set);
			++it;
		}
		else
		{
			delete (*it);
			_servers.erase(it);
		}
	}
}

bool	Host::select_available_sk(void)
{
	std::cout << "Waiting on select() ..." << std::endl;
	_sk_ready = select(_max_sk + 1, &_read_set, &_write_set, NULL, NULL);// No timeout
	//std::cout << "_sk_ready = " << _sk_ready << std::endl;
	if (_sk_ready < 0)
	{
		perror("select() failed");
		return (false);
	}
	return (true);
}

void	Host::check_sk_ready(void)
{
    Response*    response;

	for (int i = 0; i <= _max_sk && _sk_ready > 0; ++i)
	{
		if (FD_ISSET(i, &_read_set))
		{
			//std::cout << "Read set sk = " << i << std::endl;
			_sk_ready--;
			if (FD_ISSET(i, &_server_set))
				_sk_server[i]->accept_client_sk();
            else
				_sk_request[i]->read_header();
		}
		if (FD_ISSET(i, &_write_set))
		{
			//std::cout << "Write set sk = " << i << std::endl;
            response = _sk_request[i]->get_response();
			_sk_ready--;
			response->send();
		}
	}
}

void  	Host::add_sk_2_master_read_set(int new_sk, Server* s)
{
	if (new_sk > _max_sk)
		_max_sk = new_sk;
	FD_SET(new_sk, &_master_read_set);
	_sk_server[new_sk] = s;
}

void	Host::new_request_sk(int new_sk, Server* s)
{
	add_sk_2_master_read_set(new_sk, s);
	_sk_request[new_sk] = new Request(new_sk, this, s);
}

void	Host::new_response_sk(int new_sk)
{
	FD_SET(new_sk, &_master_write_set);
}

void	Host::close_client_sk(int i)
{
	FD_CLR(i, &_master_write_set);
	FD_CLR(i, &_master_read_set);
	delete (_sk_request[i]);
	_sk_request.erase(i);
	// If i is max_sk -> find another max_sk
	if (i == _max_sk)
		while (!FD_ISSET(_max_sk, &_master_read_set))
			_max_sk -= 1;
}

int			Host::get_max_clients(void) const {return (_max_clients);}
std::map<int, Server*>	Host::get_sk_server(void) const {return (_sk_server);}
std::map<int, Request*>	Host::get_sk_request(void) const {return (_sk_request);}
//std::map<int, Response*>	Host::get_sk_response(void) const {return (_sk_response);}
size_t			Host::get_client_max_body_size(void) const {return (_client_max_body_size);}
size_t			Host::get_client_body_buffer_size(void) const {return (_client_body_buffer_size);}

void			Host::set_client_max_body_size(size_t n) {_client_max_body_size = n;}
void			Host::set_client_body_buffer_size(size_t n) {_client_body_buffer_size = n;}
void			Host::set_parser_error(bool e) {_parser_error = e;}
