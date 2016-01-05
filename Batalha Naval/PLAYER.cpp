#include <iostream>
#include "PLAYER.h"
#include "BOMB.h"
#include "STRUCTS.h"
#include "BOARD.h"

using namespace std;

Player::Player(string playerName, string boardFilename) :board(Board(boardFilename))
{
	name = playerName;
}

void Player::showBoard() const
{
	board.display();
}
 
 

Bomb Player::getBomb() const
{
	bool flag = true;
	char x;
	char y;

	PositionChar coordenadas;
	cout << "Indique as coordenadas da bomba(A..." << (char)(64+board.getNumLines()) << "|a..." << (char)(96+board.getNumColumns()) << ") ?" << endl;
	while (flag)
	{
		fflush(stdin);
		cin >> x >> y;
		if (x>=65 && x<=90 && y>=97 && y<=122)
			flag = false;
		else
		{
			cout << "Coordenadas invalidas! Indique novamente: ";
		}
		
	}
	coordenadas.lin = x;
	coordenadas.col = y;
	Bomb bomba(coordenadas);
	return bomba;
}

void Player::attackBoard(const Bomb &b)
{
	board.moveShips();
	board.attack(b);
	
}

bool Player::playerLost() // Verifica se o jogador perdeu
{
	bool flag = false;
	if (board.verifyFleet() == true)
	{
		flag = true;
	}

	return flag;
}

int Player::FleetArea()
{
	return (board.FleetArea());
}

int Player::BoardArea()
{
	return (board.BoardArea());
}
