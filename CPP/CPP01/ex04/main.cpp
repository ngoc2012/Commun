/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:45:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/01 17:15:25 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

int	main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Error: Number arguments must be 3\n";
		return (1);
	}
	std::string	fin(argv[1]);
	std::ifstream   in(argv[1]);
	if (in.fail())
	{
		std::cerr << "Error: Unable to open the file: " << argv[1] << std::endl;
		return (1);
	}
	std::string	fout = fin + std::string(".replace");
	std::ofstream   out(fout.c_str());
	if (out.fail())
	{
		in.close();
		std::cerr << "Error: Unable to write to file: " << fout << std::endl;
		return (1);
	}
	std::string line;
	std::string	toFind(argv[2]);
	std::string	toReplace(argv[3]);
	while (std::getline(in, line))
	{
		int	pos = line.find(toFind);
		while ( pos != -1 ) {
			line.erase(pos, toFind.length());
			line.insert(pos, toReplace);
			pos = line.find(toFind[pos + toReplace.length()]);
		}
		out << line << "\n";
	}
	out.close();
	in.close();
	return (0);
}
