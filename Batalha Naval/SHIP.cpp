#include <iostream>
#include <string>
#include <vector>
#include "SHIP.h"
using namespace std;

Ship::Ship(char sym, PositionChar pos, char ori, unsigned int s, unsigned int cor)
{
	symbol = sym;
	position.lin = (int)pos.lin - 65;
	position.col = (int)pos.col - 97;
	orientation = ori;
	size = s;
	color = cor;
	string stat = string(s,sym);
	status = stat;
}

bool Ship::move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax)
{
	bool flag = true;
	int line = position.lin;
	int column = position.col;  
	char orientation2 = orientation;


	switch (direction)
	{
	case 'N':
		line--;
	case 'n':
		line--;
	case 'E':
		column++;
	case 'e':
		column++;
	case 'S':
		line++;
	case 's':
		line++;
	case 'O':
		column--;
	case 'o':
		column--;
	}


	if (rotate == true) //se for verdade verifica se esta na vertical ou na horizontal e altero a sua posicao
	{
		if (orientation2 == 'V')
		{
			orientation2 = 'H';
		}
		else { orientation2 = 'V'; }
	}

	if (orientation2 == 'V')
	{
		if (((column + getShipSize()) <= columnMax) && line >= 0 && column >= 0 && line <= lineMax)
		{
			flag = true;
		}
		else { flag = false; }

	}
	else if (orientation2 == 'H')
	{
		if (((line + getShipSize()) <= lineMax) && line >= 0 && column >= 0 && column <= columnMax)
		{
			flag = true;
		}
		else { flag = false; }
	}

	if (flag) //caso a flag seja verdadeira significa que pode mover o navio e entao vai mover o navio
	{
		switch (direction)
		{
		case 'N':
			position.lin--;
		case 'n':
			position.lin--;
		case 'E':
			position.col++;
		case 'e':
			position.col++;
		case 'S':
			position.lin++;
		case 's':
			position.lin++;
		case 'O':
			position.col--;
		case 'o':
			position.col--;
		}

		if (rotate == true) //se for verdade verifica se esta na vertical ou na horizontal e altero a sua posicao
		{
			if (orientation == 'V')
			{
				orientation = 'H';
			}
			else { orientation = 'V'; }
		}

	}

	return flag;
}

bool Ship::moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax, vector<vector<int>> &board)
{
	bool flag = false;
	int shipIndex = board[position.lin][position.col];
	char orientationteste = orientation;
	int colteste = position.col;
	int linteste = position.lin;

	//Move o navio de forma random
	int var = rand() % 5; //Se 0 nao altera,se 1 move para ESTE, se 2 move para SUL,se 3 move para OESTE , se 4 move para NORTE
	switch (var)
	{
	case 1:
		colteste++;
	case 2:
		linteste++;
	case 3:
		colteste--;
	case 4:
		linteste--;
	}

	//Escolhe de forma random se roda o navio
	int var2 = rand() % 2;

	if (var2)
	{
		orientationteste = 'V';
	}
	else { orientationteste = 'H'; }

	//testa se o barco está dentro do tabuleiro
	if (orientationteste == 'V')
	{
		if ((colteste <(columnMax)) && linteste >= 0 && colteste >= 0 && (linteste + getShipSize()) < (lineMax))
		{
			flag = true;
		}
		else
		{
			flag = false;
			return false;
		}


	}
	else if (orientationteste == 'H')
	{
		if ((linteste < (lineMax)) && linteste >= 0 && colteste >= 0 && (colteste + getShipSize()) <(columnMax))
		{
			flag = true;
		}
		else
		{
			flag = false;
			return false;
		}
	}

	//testa se o barco interseta outros barcos
	if (flag == true && orientationteste == 'V')
	{
		for (int z = 0; z < getShipSize(); z++)
		{
			if (board[linteste + z][colteste] == -1)
			{
				flag = true;
			}
			else if (board[linteste + z][colteste] == shipIndex)
			{
				flag = true;
			}
			else
			{
				flag = false;
				return false;
			}
		}
	}
	else if (flag == true && orientationteste == 'H')
	{
		for (int z = 0; z < getShipSize(); z++)
		{
			if (board[linteste][colteste + z] == -1)
			{
				flag = true;
			}
			else if (board[linteste][colteste + z] == shipIndex)
			{
				flag = true;
			}
			else
			{
				flag = false;
				return false;
			}
		}
	}


	//caso seja possivel mover o barco limpa a antiga posição do barco e define uma nova
	if (flag == true)
	{
		//Coloca o barco na nova posição
		switch (var)
		{
		case 1:
			position.col++;
		case 2:
			position.lin++;
		case 3:
			position.col--;
		case 4:
			position.lin--;
		}
		orientation = orientationteste;
	}
	return flag;
}

bool Ship::attack(size_t partNumber) 
{
	if (partNumber > (size - 1))
	{
		return false;
	}
	else if (partNumber <= (size - 1))
	{
		if (isupper(status[partNumber]))
		{
			status[partNumber]=tolower(status[partNumber]);
			return true;
		}
	}
}

bool Ship::isDestroyed() const // Verifica se o navio foi destruido
{
	int i = 0;
	bool verDestroyed = false;
	for (int j = 0; j < status.size(); j++)
	{
		if (islower(status[j])) // Caso seja uma letra pequena conta no i
			i++;
	}
		if (i>=(size / 2))
			verDestroyed = true;
	return verDestroyed;
}

void Ship::show() const
{
	cout << "Tamanho do navio: " << size << endl;
	cout << "Cor: " << color << endl;
	cout << "Simbolo: " << symbol << endl;
	cout << "Estado: " << status << endl;
	cout << "Posicao(linha e coluna): " << position.lin << "," << position.col << endl;
}

char Ship::getShipSymbol() const // Devolve o simbolo do navio
{
	return symbol;
}
unsigned int Ship::getShipPositionCol() const // Devolve a coluna do navio
{
	return position.col;
}
unsigned int Ship::getShipPositionLin() const // Devolve a linha do navio
{
	return position.lin;
}
char  Ship::getShipOrientation() const // Devolve a orientacao do navio
{
	return orientation;
}
unsigned int  Ship::getShipSize() const // Devolve o tamanho do navio
{
	return size;
}
unsigned int  Ship::getShipColor() const // Devolve a cor
{
	return color;
}
string Ship::getShipStatus() const //Devolve o estado do barco
{
	return status;
}
void Ship::setDefaultStatus() //Cria uma string do tipo FFFF
{
	string a;
	a.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		a[i] = symbol;
	}
	status = a;

}
