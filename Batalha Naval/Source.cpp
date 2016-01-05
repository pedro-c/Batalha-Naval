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
			else 
			{ 
				flag = false;
			}
		}
		else
		{ 
			flag = false;
		}
	}
	
	
	return File_name;

}

string PedirNomeJogador()
{
	string NomeJ; 
	cout << "Indique o seu nickname: " << endl;
	cin >> NomeJ; 
	fflush(stdin);
	return NomeJ;
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

void Score(float score, string player, int fleet, int board)
{
	int posição = 0;
	char answer;
	ifstream fichscore("score.txt");
	stringstream s;
	string sscore;
	string name;
	string afleet;
	string aboard;
	vector<string>vscore;
	vector<string>vnames;
	vector<string>vfleet;
	vector<string>vboard;
	while (getline(fichscore, name))
	{
		s >> name;
		getline(fichscore, sscore);
		s >> sscore;
		getline(fichscore, afleet);
		s >> sscore;
		getline(fichscore, aboard);
		s >> sscore;
		vnames.push_back(name);
		vscore.push_back(sscore);
		vfleet.push_back(afleet);
		vboard.push_back(aboard);

	}

	for (int i = 9; i > 0; i--)
	{
		if (score>=atof((vscore[0]).c_str()))
		{
			vscore[0] = to_string(score);
			vnames[0] = player;
			vfleet[0] = to_string(fleet);
			vboard[0] = to_string(board);
			cout << "Conquistou o primeiro lugar!" << endl;
			cout << "Deseja ver a tabela de scores?(Y/N) ";
			cin >> answer;
			if (answer == 'Y' || answer == 'y')
			{
				for (int i = 0; i < 10; i++)
				{
					cout << (i + 1) << " - " << vnames[i] << " " << vscore[i] << " " << vfleet[i] << " " << vboard[i] << endl;
				}
			}
			else {
				cout << "FIM DO JOGO";
			}

			break;
		}
		else if (score >= atof(vscore[i].c_str()))
		{
			if (score < atof(vscore[i - 1].c_str()))
			{
				vscore[i] = to_string(score);
				vnames[i] = player;
				vfleet[i] = to_string(fleet);
				vboard[i] = to_string(board);
				cout << "Conquistou o " << (i + 1) << " lugar!" << endl;
				cout << "Deseja ver a tabela de scores?(Y/N) ";
				cin >> answer;
				if (answer == 'Y' || answer == 'y')
				{
					for (int i = 0; i < 10; i++)
					{
						cout << (i + 1) << " - " << vnames[i] << " " << vscore[i] << " " << atof(vfleet[i].c_str()) << " " << atof(vboard[i].c_str()) << endl;
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
		float x = atof(vscore[i].c_str());
		string player = vnames[i];
		float fleets = atof(vfleet[i].c_str());
		float boards = atof(vboard[i].c_str());

		myfile << player;
		myfile << '\n';
		myfile << x;
		myfile << '\n';
		myfile << fleets;
		myfile << '\n';
		myfile << boards;
		myfile << '\n';
	}
	myfile.close();

}

void showScore() // Mostra a tabela dos scores
{
	ifstream fichscore("score.txt");
	stringstream s;
	string sscore;
	string name;
	string afleet;
	string aboard;
	vector<string>vscore;
	vector<string>vnames;
	vector<string>vfleet;
	vector<string>vboard;
	while (getline(fichscore, name))
	{
		s >> name;
		getline(fichscore, sscore);
		s >> sscore;
		getline(fichscore, afleet);
		s >> afleet;
		getline(fichscore, aboard);
		s >> aboard;
		vnames.push_back(name);
		vscore.push_back(sscore);
		vfleet.push_back(afleet);
		vboard.push_back(aboard);
	}

	for (int i = 0; i < 10; i++)
	{
		cout << (i + 1) << " - " << vnames[i] << " " << vscore[i] << " " << vfleet[i] << " " << vboard[i] << endl;
	}
}

void Jogar() // Estrutura do jogo
{
	float t1 = 0;
	float t2 = 0;
	string Player1;
	string Player2;
	srand((unsigned int)time(NULL));
	cout << "Jogador 1 - ";
	Player1 = PedirNomeJogador();
	Player jogador1 = Player(Player1, PedirFicheiro());
	jogador1.showBoard();
	cout << "Jogador 2 - ";
	Player2 = PedirNomeJogador();
	Player jogador2 = Player(Player2, PedirFicheiro());
	jogador2.showBoard();
	fflush(stdin);
	cout << "Prontos para comecar o jogo (Press any button) ?";
	bool ValidInput = true;
	while (ValidInput)
	{
		if (cin.get())
		{
			cout << " ";
			ValidInput = false;
		}
		clrscr();
	}
	fflush(stdin);


	int var2 = rand() % 2; //escolhe de forma random quem começa primeiro
	if (var2)
	{
		bool flag = true;
		cout << Player1 << " joga primeiro !" << endl;
		while (flag)
		{
			cout << endl;
			cout << "Vez do " << Player1 << ". "; //Joga o Player 1
			fflush(stdin);
			cout << "Pronto (Press any button) ?";
			if (cin.get())
				cout << " ";
			fflush(stdin);
			const clock_t begin_time1 = clock(); //começa a contar o tempo de jogo do player1
			clrscr();

			jogador2.showBoard();
			jogador2.attackBoard(jogador1.getBomb());
			if (jogador2.playerLost()) //Jogador 2 perdeu
			{
				cout << Player1 << " Ganhou, Parabéns!" << endl;
				cout << "Score = ";
				cout << (t1*(jogador2.FleetArea()) / (jogador2.BoardArea())) << endl;
				float x = (t1*(jogador2.FleetArea()) / (jogador2.BoardArea()));
				Score(x, Player1, (jogador2.FleetArea()), (jogador2.BoardArea())); //coloca o score na tabela dos 10 melhores caso seja possivel
				flag = false;
				break;
			}
			jogador2.showBoard();
			t1 = t1 + float(clock() - begin_time1) / CLOCKS_PER_SEC;

			cout << endl;
			cout << "Vez do " << Player2 << ". "; //Joga o Player 2

			fflush(stdin);
			cout << "Pronto (Press any button) ?";
			if (cin.get())
				cout << " ";
			fflush(stdin);
			const clock_t begin_time2 = clock(); //começa a contar o tempo de jogo do player2
			clrscr();


			jogador1.showBoard();
			jogador1.attackBoard(jogador1.getBomb());
			if (jogador1.playerLost()) //Jogador 1 perdeu
			{
				cout << Player2 << " Ganhou, Parabéns!" << endl;
				cout << "Score = ";
				cout << (t2*(jogador1.FleetArea()) / (jogador1.BoardArea())) << endl;
				float x = (t2*(jogador1.FleetArea()) / (jogador1.BoardArea()));
				Score(x, Player2, (jogador1.FleetArea()), (jogador1.BoardArea()));
				flag = false;
				break;
			}
			jogador1.showBoard();
			t2 = t2 + float(clock() - begin_time2) / CLOCKS_PER_SEC;

		}

	}
	else {
		bool flag = true;
		cout << Player2 << " joga primeiro !" << endl;
		while (flag)
		{
			cout << endl;
			cout << "Vez do " << Player2 << ". "; //Joga o Player 2

			fflush(stdin);
			cout << "Pronto (Press any button) ?";
			if (cin.get())
				cout << " ";
			fflush(stdin);
			const clock_t begin_time2 = clock(); //começa a contar o tempo de jogo do player2
			clrscr();

			jogador1.showBoard();
			jogador1.attackBoard(jogador1.getBomb());
			if (jogador1.playerLost()) //Jogador 1 perdeu
			{
				cout << Player2 << " Ganhou, Parabéns!" << endl;
				cout << "Score = ";
				cout << (t2*(jogador1.FleetArea()) / (jogador1.BoardArea())) << endl;
				float x = (t2*(jogador1.FleetArea()) / (jogador1.BoardArea()));
				Score(x, Player2, (jogador1.FleetArea()), (jogador1.BoardArea()));
				flag = false;
				break;
			}
			jogador1.showBoard();
			t2 = t2 + float(clock() - begin_time2) / CLOCKS_PER_SEC;

			cout << endl;
			cout << "Vez do " << Player1 << ". "; //Joga o Player 1

			fflush(stdin);
			cout << "Pronto (Press any button) ?";
			if (cin.get())
				cout << " ";
			fflush(stdin);
			const clock_t begin_time1 = clock(); //começa a contar o tempo de jogo do player1
			clrscr();

			jogador2.showBoard();
			jogador2.attackBoard(jogador1.getBomb());
			if (jogador2.playerLost()) //Jogador 2 perdeu
			{
				cout << Player1 << " Ganhou, Parabéns!" << endl;
				cout << "Score = ";
				cout << (t1*(jogador2.FleetArea()) / (jogador2.BoardArea())) << endl;
				float x = (t1*(jogador2.FleetArea()) / (jogador2.BoardArea()));
				Score(x, Player1, (jogador2.FleetArea()), (jogador2.BoardArea()));
				flag = false;
				break;
			}
			jogador2.showBoard();
			t1 = t1 + float(clock() - begin_time1) / CLOCKS_PER_SEC;
		}
	}
}

void WaitIn() // Para esperar ate o jogador ja ter visto score(opcao do intro)
{
	string lixo;
	cout << "Carregue enter para menu..." << endl;
	cin.ignore(1000, '\n');
	getline(cin, lixo);
}

int intro() // Introducao do jogo para o jogador definir a opcao que deseja
{
	int Opcao;
	cout << "                       __    __    __ " << endl;
	cout << "                      |==|  |==|  |==|" << endl;
	cout << "                    __|__|__|__|__|__| _" << endl;
	cout << "                 __| ___________________|___" << endl;
	cout << "              __|__[]__[]__[]__[]__[]__[]__ |___" << endl;
	cout << "             |..........BATALHA.NAVAL......... /" << endl;
	cout << "              \.............................../" << endl;
	cout << "            _,~')_,~')_,~')_,~')_,~')_,~')_,~')/,~')_\n" << endl;
	cout << "                      _________________" << endl;
	cout << "                      _____1-Jogar_____" << endl;
	cout << "                      ___2-Ver Score___" << endl;
	cout << "                      ______3-Sair_____" << endl;
	cout << "                      _________________" << endl;
	cin >> Opcao;
	return Opcao;

}

int main()
{
	bool Option = true;
	while (Option)
	{
		switch (intro())
		{
		case 1:
			clrscr();
			Jogar();
			Option = false;
			break;
		case 2:
			clrscr();
			showScore();
			WaitIn();
			clrscr();
			break;

		case 3:
			clrscr();
			return 1;
			break;
		}
	}
	return 0;
}