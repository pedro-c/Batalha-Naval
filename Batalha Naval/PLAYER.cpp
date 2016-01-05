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
	cout << "Indique as coordenadas da bomba(LINHA|coluna) ?" << endl;
	while (flag)
	{
		cin >> x >> y;
		if (cin.fail())
		{
			cout << "Coordenadas invalidas!";
			flag = true;

		}
		else{ flag = false; }
		
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

bool Player::playerLost()
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
	return BoardArea();
}