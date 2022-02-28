#include "TicTacToe.h"

int main() {
	setlocale(LC_ALL, "ru");

	cout << "������� � ��������-������?)\n\n������� ����� �������, ����� ����������, ��� Esc, ����� �����." << endl;
	if (_getch() == 27) {
		system("cls");
		cout << "����, �� �������, �������!" << endl;
		return 0;
	}

	vector <Player> players;
	fstream fpin;
	fpin.open("LiderBoard.ttt");

	while (true) {
		system("cls");
		TicTacToe game;

		cout << "������, ����������, ������� ���������:" << endl << endl;
		cout << "1. ������ - ���� 3�3, ��� ������ 3 � ���" << endl;
		cout << "2. ������� - ���� 4�4, ��� ������ 3 � ���" << endl;
		cout << "3. ������� - ���� 6�6, ��� ������ 4 � ���" << endl;
		cout << "4. ������������ - ���� 10�10, ��� ������ 5 � ���" << endl << endl;
		cout << "* �� ����� ����, ����� � ������ �������:) *" << endl;
		string level;
		while (level.empty()) {
			getline(cin, level);
			switch (level[0]) {
			case '1': game.sizeAndBlock(3, 3); break;
			case '2': game.sizeAndBlock(4, 3); break;
			case '3': game.sizeAndBlock(6, 4); break;
  			case '4': game.sizeAndBlock(10, 5); break;                                                                                               
			default:                                                                                  
				cout << "��, ���-�� �� ��... �������� ���)\n";
				level.clear();
				break;
			}
		}
		system("cls");

		game.addPlayers();
		game.play();

		if (!players.empty()) {
			if (fpin.is_open()) {
				fpin.clear();
				for (auto i = 0; i < players.size(); i++)
					fpin << players[i].games << players[i].wins << players[i].nick;
			}
		}

		if (fpin.is_open()) {
			while (!fpin.eof()) {
				Player temp;
				fpin >> temp.games >> temp.wins >> temp.nick;
				players.push_back(temp);
			}
			if (!players.empty()) {
				if (game.nickPlayer1() != "Player1") {
					bool flag = false;
					for (auto i = 0; i < players.size(); i++)
						if (game.nickPlayer1() == players[i].nick) {
							players[i].games++;
							if (game.nickWinner() == players[i].nick)
								players[i].wins++;
							flag = true;
							exit;
						}
					if (!flag) {
						Player temp; temp.nick = game.nickPlayer1(), temp.games = 1;
						if (game.nickWinner() == temp.nick)
							temp.wins = 1;
						players.push_back(temp);
					}
				}
				if (game.nickPlayer2() != "Player2") {
					bool flag = false;
					for (auto i = 0; i < players.size(); i++)
						if (game.nickPlayer2() == players[i].nick) {
							players[i].games++;
							if (game.nickWinner() == players[i].nick)
								players[i].wins++;
							flag = true;
							exit;
						}
					if (!flag) {
						Player temp; temp.nick = game.nickPlayer2(), temp.games = 1;
						if (game.nickWinner() == temp.nick)
							temp.wins = 1;
						players.push_back(temp);
					}
				}
				sort(players.begin(), players.end(), [](const Player& player1, const Player& player2) -> bool
					{
						return player1.wins < player2.wins;
					}
				);
			}
		}

		cout << "������ ��������� �� ������� �������?\n����� ����������, ����� Esc, ����� ����������, - ����� ������ �������.\n";
		if (_getch() != 27) {
			system("cls");
			if (!players.empty()) {
				for (auto i = 0; i < players.size(); i++)
					printf(" %3i | %20s | %3i | %3i\n", i + 1, players[i].nick, players[i].wins, players[i].games);
			}
			else
				cout << "��� ���-�� ����� �� ���, � ���� � ������� �������� ����, ��� �� ��� ������ �����!)" << endl;
			system("pause");
		}

		system("cls");
		cout << "�����������? � ���� ���� ���������� ����������� ������� ���) ������ ������� ���?\n����� ����������, ����� Esc, ����� ����������, - ����� ������ �������.";
		if (_getch() == 27) {
			system("cls");
			cout << "����, �� �������, �������!" << endl;
			return 0;
		}
	}
}