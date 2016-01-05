#include <iostream>
#include "BOMB.h"
#include "STRUCTS.h"
#include "BOARD.h"

using namespace std;

Bomb::Bomb(PositionChar targetPosition)
{
	int var = rand() % 5; //Se 0 nao altera,se 1 aumenta a ESTE, se 2 aumenta a SUL,se 3 aumenta a OESTE , se 4 aumenta a NORTE
	if (var == 1)
		targetPosition.col++;
	else if (var == 2)
		targetPosition.lin++;
	else if (var == 3)
		targetPosition.col--;
	else if (var == 4)
		targetPosition.lin--;
	targetLine = targetPosition.lin; //Depois de alterar ou nao as coordenadas indicadas pelo utilizador ele passa as para os elementos privados da class Bomb
	targetColumn = targetPosition.col;
}

PositionChar Bomb::getTargetPosition() const //Para obter as coordenadas da bomba
{
	PositionChar coordf;
	coordf.lin = targetLine;
	coordf.col = targetColumn;
	return coordf;
}

void Bomb::show() const
{
	cout << "targetLine= " << targetLine << endl << "targetColumn= " << targetColumn;
}

void Bomb::setValues(char linha, char coluna)
{
	targetLine = linha;
	targetColumn = coluna;
}