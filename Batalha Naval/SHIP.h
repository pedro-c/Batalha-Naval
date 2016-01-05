#ifndef _SHIP
#define _SHIP

#include <string>
#include "STRUCTS.h"

using namespace std;

class Ship
{
public:
	Ship(char sym, PositionChar pos, char ori, unsigned int s, unsigned int cor);
	bool move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax); // moves the boat (SEE NOTES)
	bool moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax, vector<vector<int>> &board); // moves the ship randomly
	bool attack(size_t partNumber); //partNumber = {0,1,…, size-1}
	bool isDestroyed() const; // checks whether the ship is destroyed
	void show() const; // shows the attributes of the ship (for debugging)
	//Objetos novos
	char getShipSymbol() const;
	unsigned int getShipPositionCol() const;
	unsigned int getShipPositionLin() const;
	char getShipOrientation() const;
	unsigned int getShipSize() const; 
	unsigned int getShipColor() const; 
	string getShipStatus() const;
	PositionInt getShipPosition() const;
	void setDefaultStatus();
private:
	char symbol; // 'P' = "porta-aviões"; 'F' = "fragata"; … (portuguese names)
	PositionInt position; // coordinates of the upper left corner of the ship
	char orientation; // 'H' = horizontal; 'V' = vertical
	unsigned int size; // number os cells occupied by the ship, on the board
	unsigned int color; // color code: o=BLACK, 1=BLUE, … (see annex of 1st proj.)
	string status; // status[i]: uppercase = good; lowercase = damaged
	// ex: "FFFF" means that the "fragata" is intact;
	// ex: "FFfF" means that the 'partNumber' 2 was hit by a bomb
	// OTHER ATTRIBUTES OR METHODS, if necessary
	// ...
};
#endif