#include "BOARD.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "STRUCTS.h"
#include "COLORS.h"

using namespace std;

Board::Board(const string &filename)
{
	int x, y;
	char simbolo, orientacao;
	PositionChar posicao;
	unsigned int tamanho, cor;
	ifstream fichJogo(filename);
	if (fichJogo.is_open()) // Se o ficheiro existir (abrir)
	{
		stringstream ss;
		char lixo;
		string sfich;
		string coordenadas;
		getline(fichJogo, sfich); // passar a primeira linha do ficheiro para a string sfich
		ss << sfich;
		ss >> x;
		ss >> lixo;
		ss >> y;
		numLines = y;
		numColumns = x;
		board.resize(y);
		for (size_t i = 0; i < y; i++)
		{
			for (size_t j = 0; j < x; j++)
			{
				board[i].push_back(-1);
			}
		}
		while (getline(fichJogo, sfich))
		{
			ss.clear();
			ss << sfich;
			ss >> simbolo;
			ss >> tamanho;
			ss >> posicao.lin;
			ss >> posicao.col;
			ss >> orientacao;
			ss >> cor;
			ships.push_back(Ship(simbolo, posicao, orientacao, tamanho, cor)); // Introduz no vetor ships o navio
		}
		fichJogo.close();
		for (size_t i = 0; i < ships.size(); i++) // Ciclo para colocar os navios que estao descritos no tabuleiro
		{
			putShip(ships[i]);
		}
	}
	else
		cout << "Erro ao abrir ficheiro!" << endl;
}

bool Board::putShip(const Ship &s)
{
	size_t x = s.getShipPositionCol(); // Passar para x o valor da coluna
	size_t y = s.getShipPositionLin(); // Passar para y o valor da linha
	char pos = s.getShipOrientation(); // pos e a orientacao(vertical ou horizontal)
	bool validPos = true;
	unsigned int k;
	for (size_t i = 0; i < ships.size(); i++) // Ciclo para verificar o indice do navio no vector ships
	{
		if (s.getShipPositionLin() == ships[i].getShipPositionLin() && s.getShipPositionCol() == ships[i].getShipPositionCol()
			&& s.getShipSymbol()==ships[i].getShipSymbol())
		{
			k = i;
		}
	}
	size_t xi = x;
	size_t yi = y;
	size_t i = x;
	size_t j = y;
	if (pos == 'H' || pos == 'h')
	{
		if ((xi + s.getShipSize()) <= board[0].size()) //Se couber no tabuleiro
		{
			for (i; i < (xi + s.getShipSize()); i++) //Verificar se nao interseta nenhum navio
			{
				if (board[j][i] != -1)
					validPos = false;
			}
			if (validPos) //Se nao intersetar nenhum navio
			{
				for (x; x < (xi + s.getShipSize()); x++) //Coloca o indice do navio (no vetor ships) no tabuleiro
				{
					board[y][x] = k;
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if (pos == 'V' || pos == 'v')
	{
		if ((j + s.getShipSize()) <= board.size()) //Se couber no tabuleiro
		{
			for (j; j < (yi + s.getShipSize()); j++) //Verificar se nao interseta nenhum navio
			{
				if (board[j][i] != -1)
					validPos = false;
			}
			if (validPos)
			{
				for (y; y < (yi + s.getShipSize()); y++) //Coloca o indice do navio (no vector ships) no tabuleiro
				{
					board[y][x] = k;
				}
				return true;
			}
			else
			{
				return false; // Se intersetar navios
			}
		}
		else
		{
			return false; // Se ultrapassar o tab
		}
	}
	else
		return false;
}

void Board::moveShips()
{
	for (int i = 0; i < ships.size(); i++)
	{
		bool flag = false;
		while (!flag)
		{
			if (ships[i].isDestroyed() == true)  //se o barco estiver destroido nao é movido
			{

			}
			else {
				flag = ships[i].moveRand(0, 0, board.size(), board[0].size(), board);
				if (flag)
				{
					putShip(ships[i]);
				}
				else
				{
					flag = false;
				}
			}
			
		}
	}
}

int Board::getShipStatus(int ind,int linha,int coluna) // Para verificar que posicao do navio foi atingida
{
	int Navi = 0;// Valor que vai ser returnado com a posiçao do navio atingido
	int Navic = 0;
	for (int i = 0; i < numLines; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			if (i == linha && j == coluna)
				Navi = Navic;
			else if (board[i][j] == ind)
					Navic++;
		}
	}
	return Navi;
}

bool Board::attack(const Bomb &b)
{
	int linha = b.getTargetPosition().lin-65;
	int coluna = b.getTargetPosition().col-97;
	if (coluna < getNumColumns() && linha < getNumLines() && coluna >= 0 && linha >=0)
	{
		if (board[linha][coluna] == -1)
		{
			cout << "Falhou!" << endl;
			return false;
		}
		else
		{
			cout << "Acertou!" << endl;
			int i = board[linha][coluna];
			int partNum=getShipStatus(i,linha,coluna);
			ships[i].attack(partNum);
			return true;
		}
	}
	else
		cout << "Falhou!" << endl;
}

void Board::display() const
{
	size_t linhas = board.size();
	size_t colunas = board[0].size();
	cout << " ";
	for (size_t i = 0; i < board[0].size(); i++)
		cout << setw(3) << (char)(97 + i);
	cout << endl;
	for (size_t i = 0; i < linhas; i++)
	{
		{
			cout << (char)(65 + i);
			for (size_t j = 0; j < colunas; j++)
			{
				if (board[i][j] == -1) // Se a percela tiver valor -1 mostra .
				{
					setcolor(1, 7);
					cout << setw(3) << '.';
				}
				else if (ships[board[i][j]].getShipOrientation() == 'H') // Verifica se o barco correspondente ao indice esta na horizontal
				{
					if (i == ships[board[i][j]].getShipPositionLin() && j == ships[board[i][j]].getShipPositionCol()) // Verifica se corresponde a primeira posição dese navio
					{                                                                                                 // Se corresponder escreve se nao nao faz nada
						for (size_t k = 0; k < ships[board[i][j]].getShipSize(); k++)
						{
							setcolor(ships[board[i][j]].getShipColor(), 7);
							cout << setw(3) << ships[board[i][j + k]].getShipStatus()[k];
						}
					}
				}
				else if (ships[board[i][j]].getShipOrientation() == 'V') // Verifica se o barco esta na vertical
				{
					int deltalin = i - ships[board[i][j]].getShipPositionLin(); // Calcula o indice correspondente a status
					setcolor(ships[board[i][j]].getShipColor(), 7);
					cout << setw(3) << ships[board[i][j]].getShipStatus()[deltalin];
				}
			}
			cout << "  " << "\n";
		}
		setcolor(15, 0);
	}
}

void Board::show() const // Devolve o tabuleiro com os valores
{
	for (int i = 0; i < numLines; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			cout << setw(3) << board[i][j];
		}
		cout << '\n';
	}
}

int Board::getNumLines() const
{
	return numLines;
}

int Board::getNumColumns() const
{
	return numColumns;
}

bool Board::verifyFleet()
{
	bool flag = false;
	int acc = 0;
	for (int i = 0; i < ships.size(); i++)
	{
		if (ships[i].isDestroyed() == true)
		{
			acc++;
		}
	}
	if ((acc) == ships.size())
	{
		flag = true;
	}
	return flag;
}

int Board::FleetArea()
{
	int acc = 0;
	for (int i = 0; i < ships.size(); i++)
	{
		acc = acc + ships[i].getShipSize();
	}
	return acc;
}

int Board::BoardArea()
{
	return (board.size()*board[0].size());
}