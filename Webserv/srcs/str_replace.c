/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:23:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/27 14:24:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


namespace ft {

while ( pos != std::string::npos ) {
			line.erase(pos, toFind.length());
			line.insert(pos, toReplace);
			pos = line.find(toFind, pos + toReplace.length());
		}

}
