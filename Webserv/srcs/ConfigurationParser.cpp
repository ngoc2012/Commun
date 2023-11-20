/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/20 17:53:06 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigurationParser.hpp"

ConfigurationParser::ConfigurationParser() {}
ConfigurationParser::ConfigurationParser(const ConfigurationParser& src) { *this = src; }
ConfigurationParser&	ConfigurationParser::operator=( ConfigurationParser const & src )
{
	(void) src;
	return (*this);
}
ConfigurationParser::~ConfigurationParser() {}
std::string	ConfigurationParser::remove_comments(std::string& s)
{
	size_t	hash_pos = s.find("#");
	if (hash_pos == std::string::npos)
		return (s);
	return (s.substr(0, hash_pos));
}
std::string	ConfigurationParser::remove_spaces_end(std::string& s)
{
	size_t	n = s.length();
	while (n > 0 && (s[n - 1] == ' ' || s[n - 1] == '	'))
		n--;
	return (s.substr(0, n));
}

bool	ConfigurationParser::host_parser(std::string cmd, Host& host, std::vector<std::string>&, int i)
{
	int	n;

	if (cmd[0] != '	')
		return (false);
	if (words[0] == "client_max_body_size")
	{
		n = std::atoi(words[1].c_str());
		if (!is_digit(words[1]) || n < 0 || n > 100)
			return (false);
		host.set_client_max_body_size(n);
	}
	else if (words[0] == "client_body_buffer_size")
	{
		n = std::atoi(words[1].c_str());
		if (!is_digit(words[1]) || n < 0 || n > 1024)
			return (false);
		host.set_client_max_body_size(n);
	}
	else if (words[0] == "root")
	{
		struct stat	info;
		if (!(stat(folderPath, &info) == 0 && S_ISDIR(info.st_mode)))
			return (false);
		host.set_root(words[1]);
	}
	else
		return (false);
	return (true);
}

bool	ConfigurationParser::server_parser(std::string cmd, Server& server, std::vector<std::string>&, int i)
{
	if (cmd[0] != '	')
		return (false);
	else if (words[0] == "listen")
		if (!listen(server, words))
			return (false);
	else if (words[0] == "root")
	{
		struct stat	info;
		if (!(stat(folderPath, &info) == 0 && S_ISDIR(info.st_mode)))
			return (false);
		host.set_root(words[1]);
	}
	else
		return (false);
}

ConfigurationParser::ConfigurationParser(std::vector<Server*>& servers, Host& host, const char* conf)
{
	//const char*	keys_server[] = {"listen", "server_name", "location"};
	//const char*	keys_location[] = {"methods", "client_max_body_size", "client_body_buffer_size", "fastcgi_pass", "fastcgi_param", "include"};
	err = 0;
	std::ifstream	conf_file(conf);
	if (!conf_file.is_open()) {
		std::cerr << "Error opening the file." << std::endl;
		return ;
	}
	enum e_part {HOST, SERVER, P_NONE};
	e_part	part = P_NONE;
	Server		*new_server = 0;
	int		i = 0;
	std::string	line;
	bool	err = false;
	while (std::getline(conf_file, line))
	{
		std::string		s = remove_comments(line);
		s = remove_spaces_end(s);
		//std::cout << "|" << s << "|" << std::endl;
		std::vector<std::string>	words = split_string(s, std::string(" 	"));
		i++;
		if (words.size() == 0)
			;
		else if (s == "host")
			part = HOST;
		else if (s == "server")
		{
			part = SERVER;
			new_server = new Server();
			servers.push_back(new_server);
		}
		else
			switch (part):
			{
				case P_NONE:
					err = true;
					break ;
				case SERVER:
					err = !server_parser(s, new_server, words, i);
					break;
				case HOST:
					err = !host_parser(s, host, words, i);
					break;
			}
		if (err)
		{
			conf_file_error(cmd, i);
			break ;
		}
	}
	conf_file.close();
}

bool	ConfigurationParser::listen(Server* s, std::vector<std::string> words)
{
	if (words.size() != 2)
		return (false);
	std::vector<std::string>	address = split_string(words[1], std::string(":"));
	if (address.size() != 2)
		return (false);
	std::vector<std::string>	ip = split_string(address[0], std::string("."));
	if (ip.size() != 4)
		return (false);
	int	n;
	for (int j = 0; j < 4; j++)
	{
		n = std::atoi(ip[j].c_str());
		if (!is_digit(ip[j]) || n < 0 || n > 255)
			return (false);
	}
	n = std::atoi(address[1].c_str());
	if (!is_digit(address[1]) || n < 0 || n > 65535)
		return (false);
	s->set_ip_address(address[0]);
	s->set_port(std::atoi(address[1].c_str()));
	//std::cout << s->get_ip_address() << ":" << s->get_port() << std::endl;
	return (true);
}

void	ConfigurationParser::conf_file_error(std::string line, int i)
{
	std::cerr << "Configuration file error at line "
		<< i << " :" << line << " (code err " << err << ")" << std::endl;
}
