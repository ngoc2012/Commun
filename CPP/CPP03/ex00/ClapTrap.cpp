/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/30 21:51:53 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

void	welcome(ClapTrap &c) { std::cout << name << " join the game\n"; }

ClapTrap::ClapTrap()
{
	name = std::string("RANDOM");
	welcome(&this); 
}

ClapTrap::ClapTrap(std::string name)
:
	name(name),
	hit_points(10),
	energy_points(10),
	attack_damage(0)
{ welcome(&this); }

ClapTrap::ClapTrap(const ClapTrap& src)
:
	name(src.name),
	hit_points(src.hit_points),
	energy_points(src.energy_points),
	attack_damage(src.attack_damage)
{ welcome(&this); }

/*
** @brief Destructor:
** Called when the object "ClapTrap" is delete
*/
ClapTrap::~ClapTrap()
{
	std::cout << name << " quit game." << std::endl;
}

ClapTrap & ClapTrap::srcerator=(const ClapTrap& src)
{
	if (this == &src)
		return (*this);
	this->_hit_points = src._hit_points;
	this->_max_hit_points = src._max_hit_points;
	this->_energy_points = src._energy_points;
	this->_max_energy_points = src._max_energy_points;
	this->_level = src._level;
	this->_name = src._name;
	this->_melee_attack_damage = src._melee_attack_damage;
	this->_ranged_attack_damage = src._ranged_attack_damage;
	this->_armor_damage_reduction = src._armor_damage_reduction;
	return (*this);
}

/*
** @brief Ranged attack of the ClapTrap.
*/
void		ClapTrap::rangedAttack(std::string const & target)
{
	_print_suffix(this->_name, this->_hit_points);
	std::cout << "J'urine des arcs-en-ciel sur toi \033[1;34m" << target << "\033[0m, \033[1;33m" << this->_ranged_attack_damage << "\033[0m de ta décadante vie en moins dans ta face !" << std::endl;
}

/*
** @brief Melee attack of the ClapTrap.
*/
void		ClapTrap::meleeAttack(std::string const & target)
{
	_print_suffix(this->_name, this->_hit_points);
	std::cout << "Ah Ya ! \033[1;34m" << target <<"\033[0m prend donc \033[1;33m" << this->_melee_attack_damage << "\033[0m dégats de mon... épée cubique en bois!" << std::endl;
}

/*
** @brief Used to remove hit points to the ClapTrap
*/
void		ClapTrap::takeDamage(unsigned int amount)
{
	amount -= this->_armor_damage_reduction;
	_print_suffix(this->_name, ((int)this->_hit_points - (int)amount >= 0) ? this->_hit_points - amount : 0);
	std::cout << "Ah sa maman l'.. Hyménoptère ! J'ai pris \033[1;33m" << amount + this->_armor_damage_reduction << "\033[0m dans les roulantes ! Non ... \033[1;33m" << amount << "\033[0m j'avais oublié ma coque ... héhé." << std::endl;
	if (amount > this->_hit_points)
		amount = this->_hit_points;
	this->_hit_points -= amount;
}

/*
** @brief Used to repare the ClapTrap
*/
void		ClapTrap::beRepaired(unsigned int amount)
{
	if (amount + this->_hit_points > this->_max_hit_points)
		amount = this->_max_hit_points - this->_hit_points;
	_print_suffix(this->_name, this->_hit_points + amount);
	std::cout << "HUUUUUUMMM ! \033[1;33m" << amount << "\033[0m de santé ... Attend, le rouge c'est quel goût déja?" << std::endl;
	this->_hit_points += amount;
}

/*
** @brief Select randomly and attack.
** Remove 25 energy points.
*/
void		ClapTrap::vaulthunter_dot_exe(std::string const & target)
{
	attacks cmd[] = {
		&ClapTrap::mathAttack,
		&ClapTrap::questionAttack,
		&ClapTrap::danseAttack,
		&ClapTrap::lostAttack,
		&ClapTrap::monologueAttack
	};
	
	if (this->_energy_points < 25)
	{
		_print_suffix(this->_name, this->_hit_points);
		std::cout << "Oh ! Comment ça j'ai pas énergie illimité ? Je vais te chopper se constructeur moi tu vas voir ! Enfin.. Quand je me serais reposé..." << std::endl;
		return;
	}
	(this->*cmd[rand() % 5])(target);
	this->_energy_points -= 25;
}

/*
** @brief Math Attack of the FlagTrap for
** vaulthunter_dot_exe.
*/
void		ClapTrap::mathAttack(std::string const & target)
{
	_print_suffix(this->_name, this->_hit_points);
	std::cout << "Comment ça marche les maths ? Est-ce que j'ai l'air gros comme ça ? Si un car et une girafe se reproduisaient, ça ferait quoi ? Une carafe ? Ah ! Ca doit encore plus dur pour \033[1;34m" << target;
	std::cout << "\033[0m qui prend \033[1;33m666\033[0m de dégats ! " << std::endl;
}

/*
** @brief Question Attack of the FlagTrap for
** vaulthunter_dot_exe.
*/
void		ClapTrap::questionAttack(std::string const & target)
{
	_print_suffix(this->_name, this->_hit_points);
	std::cout << "Dans ces moments là il m'arrive de me poser des questions sur le sens de ma vie et quelque chose me distrait… et et c'est quoi ça… \033[1;34m" << target;
	std::cout << "\033[0m qui prend \033[1;33m999\033[0m dégats... cool !" << std::endl;
}

/*
** @brief Dance Attack of the FlagTrap for
** vaulthunter_dot_exe.
*/
void		ClapTrap::danseAttack(std::string const & target)
{
	_print_suffix(this->_name, this->_hit_points);
	std::cout << "Est-ce que ça veut dire que je peux danser ? Steuplaiiiiiit ! Yes, merci ! ... Merde, ma danse été si bonne que ça a brulé les capteurs de \033[1;34m" << target; 
	std::cout << "\033[0m qui prend \033[1;33m12345\033[0m dégats... Déso pas déso !" << std::endl;
}

/*
** @brief Lost Attack of the FlagTrap for
** vaulthunter_dot_exe.
*/
void		ClapTrap::lostAttack(std::string const & target)
{
	_print_suffix(this->_name, this->_hit_points);
	std::cout << "Je peux tirer sur quelque chose, monter des escaliers, shooter \033[1;34m" << target << "\033[0m ? Inutile de répondre ... je viens déja de lui mettre \033[1;33m42\033[0m de dégats... Cheh !" << std::endl;
}

/*
** @brief Monologue Attack of the FlagTrap for
** vaulthunter_dot_exe.
*/
void		ClapTrap::monologueAttack(std::string const & target)
{
	_print_suffix(this->_name, this->_hit_points);
	std::cout << "Avant j'avais pas le droit de jouer avec des flingues et puis ce bon vieux Jacky est arrivé et il était très en colère, « Il me faut un robot, qu'il a dit, un robot qui fera tout ce que je veux » ";
	std::cout << "et puis il m'a vu dans un coin et ça lui a donné une idée, il m'a bidouillé en peu pour que je puisse utiliser des armes et puis il m'a lâché dans la nature en me disant « Amuse-toi bien »…";
	std::cout << "Et me voilà, mercenaire de la mort et du chaos prêt à répondre aux ordres pour… oh mince comment je vais me dépêtrer de cette phrase, j'aurais jamais du m'embarquer là-dedans.";
	std::cout << "Comment t'a réussi à te prendre \033[1;33m11111111\033[0m dégats juste en m'écoutant ? Dit le si je t'ennuis \033[1;34m" << target << "\033[0m ?!" << std::endl;
}
