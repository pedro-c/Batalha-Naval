#ifndef __BOMB_H_INCLUDED__
#define __BOMB_H_INCLUDED__
#include "STRUCTS.h"

class Bomb
{
public:
	Bomb(PositionChar targetPosition);
	PositionChar getTargetPosition() const;
	void setValues(char linha, char coluna);
	// OTHER METHODS, if necessary
	// ...
	void show() const; 
private:
	char targetLine, targetColumn;
};
#endif 