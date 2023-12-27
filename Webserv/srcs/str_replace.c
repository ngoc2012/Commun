/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:23:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/27 14:47:29 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


namespace ft {

std::string str_replace(std::string src, std::string find, std::string rep)
{
    size_t  pos = src.find(find);
    while ( pos != std::string::npos ) {
        src.erase(pos, find.length());
        src.insert(pos, rep);
        pos = src.find(find, pos + rep.length());
    }
}

}
