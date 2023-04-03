/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blackjack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:03:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/03 16:06:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main(int argc, char *argv[]) {
	int total = 0;
	int num_aces = 0;
	char *cards = argv[1];

	while (*cards != '\0') {
		char c = *cards;

		if (c >= '2' && c <= '9') {
			total += c - '0';
		} else if (c == 'T' || c == 'J' || c == 'Q' || c == 'K') {
			total += 10;
		} else if (c == 'A') {
			num_aces++;
			total += 11;
		}

		cards++;
	}

	while (total > 21 && num_aces > 0) {
		total -= 10;
		num_aces--;
	}

	if (total == 21)
	{
		printf("Blackjack!\n");
	}
	else
	{
		printf("%d\n", total);
	}
	return total;
}
