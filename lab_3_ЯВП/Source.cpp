#include "TicTacToe.h"

int main() {
	setlocale(LC_ALL, "ru");

	cout << "Сыграем в крестики-нолики?)\n\nНажмите любую клавишу, чтобы продолжить, или Esc, чтобы выйти." << endl;
	if (_getch() == 27) {
		system("cls");
		cout << "ШТОШ, до встречи, Чемпион!" << endl;
		return 0;
	}

	vector <Player> players;
	fstream fpin;
	fpin.open("LiderBoard.ttt");

	while (true) {
		system("cls");
		TicTacToe game;

		cout << "Выбери, пожалуйста, уровень сложности:" << endl << endl;
		cout << "1. Легкий - поле 3х3, для победы 3 в ряд" << endl;
		cout << "2. Средний - поле 4х4, для победы 3 в ряд" << endl;
		cout << "3. Сложный - поле 6х6, для победы 4 в ряд" << endl;
		cout << "4. Суперсложный - поле 10х10, для победы 5 в ряд" << endl << endl;
		cout << "* На самом деле, можно и больше сделать:) *" << endl;
		string level;
		while (level.empty()) {
			getline(cin, level);
			switch (level[0]) {
			case '1': game.sizeAndBlock(3, 3); break;
			case '2': game.sizeAndBlock(4, 3); break;
			case '3': game.sizeAndBlock(6, 4); break;
  			case '4': game.sizeAndBlock(10, 5); break;                                                                                               
			default:                                                                                  
				cout << "Хм, что-то не то... Попробуй еще)\n";
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

		cout << "Хотите взглянуть на таблицу лидеров?\nЧтобы отказаться, нажми Esc, чтобы продолжить, - любую другую клавишу.\n";
		if (_getch() != 27) {
			system("cls");
			if (!players.empty()) {
				for (auto i = 0; i < players.size(); i++)
					printf(" %3i | %20s | %3i | %3i\n", i + 1, players[i].nick, players[i].wins, players[i].games);
			}
			else
				cout << "Или что-то пошло не так, и файл с данными оказался пуст, или вы наш первый игрок!)" << endl;
			system("pause");
		}

		system("cls");
		cout << "Понравилось? У тебя есть уникальная возможность сыграть еще) Хочешь сыграть еще?\nЧтобы отказаться, нажми Esc, чтобы продолжить, - любую другую клавишу.";
		if (_getch() == 27) {
			system("cls");
			cout << "ШТОШ, до встречи, Чемпион!" << endl;
			return 0;
		}
	}
}