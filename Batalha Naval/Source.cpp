#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <string>
#include <vector>
#include "bomb.h"
#include "Ship.h"
#include "Board.h"
#include "Player.h"
#include "Structs.h"

string PedirFicheiro()
{
	bool flag = true;
	cout << "Qual e o ficheiro de configuracao? ";
	ifstream input;
	string File_name;
	while (flag)
	{
		cin >> File_name;
		input.open(File_name.c_str());
		if (input.fail())
		{
			File_name.append(".txt");
			input.open(File_name.c_str());
			if (input.fail())
			{
				flag = true;
				cout << "Erro de leitura. Indique o nome do ficheiro: ";
				
			}
			else { flag = false; }
		}
		else { flag = false; }
	}
	
	
	return File_name;

}

void clrscr(void)
{
	COORD coordScreen = { 0, 0 }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}

void Score(int score)
{
	int posição = 0;
	char answer;
	ifstream fichscore("score.txt");
	stringstream s;
	string sscore;
	vector<string>vscore;
	while (getline(fichscore, sscore))
	{
		s >> sscore;
		

		vscore.push_back(sscore);
	}
	
	for (int i = 9; i > 0; i--)
	{
		if (score>atoi((vscore[0]).c_str()))
		{
			vscore[0] = to_string(score);
			cout << "Conquistou o primeiro lugar!" << endl;
			cout << "Deseja ver a tabela de scores?(Y/N) ";
			cin >> answer;
			if (answer == 'Y' || answer == 'y')
			{
				for (int i = 0; i < 10; i++)
				{
					cout << (i + 1) << " - " << vscore[i] << endl;
				}
			}
			else {
				cout << "FIM DO JOGO";
			}

			break;
		}
		else if (score > atoi(vscore[i].c_str()))
		{
			if (score < atoi(vscore[i - 1].c_str()))
			{
				vscore[i] = to_string(score);
				cout << "Conquistou o " << (i+1) << " lugar!" << endl;
				cout << "Deseja ver a tabela de scores?(Y/N) ";
				cin >> answer;
				if (answer == 'Y' || answer == 'y')
				{
					for (int i = 0; i < 10; i++)
					{
						cout << (i + 1) << " - " << vscore[i] << endl;
					}
				}
				else {
					cout << "FIM DO JOGO";
				}

				
				break;
			}
		}
		
	}
	fichscore.close();

	ofstream myfile("score.txt"); //guarda no ficheiro as novas pontuações

		
	for (int i = 0; i < 10; i++)
	{
		int x = atoi(vscore[i].c_str());
		myfile << x;
		myfile << '\n';
	}
	myfile.close();
	
}

int main()
{
	int t1 = 0;
	int t2 = 0;
	cout << "Bem-vindo a Batalha Naval !" << endl;
	srand((unsigned int)time(NULL));
	cout << "Jogardo 1 - ";
	Player jogador1 = Player("Player1", PedirFicheiro());
	jogador1.showBoard();
	cout << "Jogardo 2 - ";
	Player jogador2 = Player("Player2", PedirFicheiro());
	jogador2.showBoard();
	
	fflush(stdin);
		cout << "Pronto (Press Enter)?";
	if (cin.get() == '\n')
		cout << " ";
	clrscr();
	

	int var2 = rand() % 2; //escolhe de forma random quem começa primeiro
	if (var2)
	{
		bool flag = true;
		cout << "Player 1 joga primeiro!" << endl;
		while (flag)
		{
			cout << endl;
			cout << "Vez do Player 1" << endl; //Joga o Player 1
			
			fflush(stdin);
			cout << "Pronto (Press Enter)?";
			if (cin.get() == '\n')
				cout << " ";
			const clock_t begin_time1 = clock(); //começa a contar o tempo de jogo do player1
			clrscr();

			jogador2.showBoard();
			jogador2.attackBoard(jogador1.getBomb());
			if (jogador2.playerLost()) //Jogador 2 perdeu
			{
				cout << "Player 1 Ganhou, Parabéns!";
				cout << "Score = ";
				cout << (t1*(jogador2.FleetArea())/(jogador2.BoardArea()));
				int x = (t1*(jogador2.FleetArea()) / (jogador2.BoardArea()));
				Score(x); //coloca o score na tabela dos 10 melhores caso seja possivel
				flag = false;
			}
			jogador2.showBoard();
			t1 = t1 + float(clock() - begin_time1) / CLOCKS_PER_SEC;

			cout << endl;
			cout << "Vez do Player 2" << endl; //Joga o Player 2

			fflush(stdin);
			cout << "Pronto (Press Enter)?";
			if (cin.get() == '\n')
				cout << " ";
			const clock_t begin_time2 = clock(); //começa a contar o tempo de jogo do player2
			clrscr();


			jogador1.showBoard();
			jogador1.attackBoard(jogador1.getBomb());
			if (jogador1.playerLost()) //Jogador 1 perdeu
			{
				cout << "Player 2 Ganhou, Parabéns!";
				cout << "Score = ";
				cout << (t2*(jogador1.FleetArea()) / (jogador1.BoardArea()));
				int x = (t2*(jogador1.FleetArea()) / (jogador1.BoardArea()));
				Score(x);
				flag = false;
			}
			jogador1.showBoard();
			t2 = t2 + float(clock() - begin_time2) / CLOCKS_PER_SEC;
			
		}
		
	}
	else {
		bool flag = true;
		cout << "Player 2 joga primeiro!" << endl;
		while (flag)
		{
			cout << endl;
			cout << "Vez do Player 2" << endl; //Joga o Player 2

			fflush(stdin);
			cout << "Pronto (Press Enter)?";
			if (cin.get() == '\n')
				cout << " ";
			const clock_t begin_time2 = clock(); //começa a contar o tempo de jogo do player2
			clrscr();

			jogador1.showBoard();
			jogador1.attackBoard(jogador1.getBomb());
			if (jogador1.playerLost()) //Jogador 1 perdeu
			{
				cout << "Player 2 Ganhou, Parabéns!";
				cout << "Score = ";
				cout << (t2*(jogador1.FleetArea()) / (jogador1.BoardArea()));
				int x = (t2*(jogador1.FleetArea()) / (jogador1.BoardArea()));
				Score(x);
				flag = false;
			}
			jogador1.showBoard();
			t2 = t2 + float(clock() - begin_time2) / CLOCKS_PER_SEC;

			cout << endl;
			cout << "Vez do Player 1" << endl; //Joga o Player 1

			fflush(stdin);
			cout << "Pronto (Press Enter)?";
			if (cin.get() == '\n')
				cout << " ";
			const clock_t begin_time1 = clock(); //começa a contar o tempo de jogo do player1
			clrscr();

			jogador2.showBoard();
			jogador2.attackBoard(jogador1.getBomb());
			if (jogador2.playerLost()) //Jogador 2 perdeu
			{
				cout << "Player 1 Ganhou, Parabéns!";
				cout << "Score = ";
				cout << (t1*(jogador2.FleetArea()) / (jogador2.BoardArea()));
				int x = (t1*(jogador2.FleetArea()) / (jogador2.BoardArea()));
				Score(x); 
				flag = false;
			}
			jogador2.showBoard();
			t1 = t1 + float(clock() - begin_time1) / CLOCKS_PER_SEC;
		}

	}
	

	return 0;
}