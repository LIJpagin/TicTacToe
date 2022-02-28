#pragma once

#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <fstream>
#include <locale>
#include <conio.h>
#include <algorithm> 
using namespace std;

static HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);

//‘”Ќ ÷»я:
//template <typename T> void Print(T buf, int x, int y, byte color)
//template <typename T> void Print(T buf, byte color)
//÷≈Ћ№: передвижение курсора консоли в строку y и столбец x, вывод в консоль строки цветом, заданным color
//ѕј–јћ≈“–џ:
//buf - строка дл€ вывода
//x - столбец в консоли
//y - строка в консоли
//color - цвет текста и фона 
template <typename T> void Print(T, int, int, byte);
template <typename T> void Print(T, int, int);
template <typename T> void Print(T, byte);

/*‘”Ќ ÷»я: void Color(byte color)
* ÷≈Ћ№: измение цвета выводимого в консоль текста
* ѕј–јћ≈“–џ: color - цвет текста и фона
*
* Ў–»‘“
* 0, 7, 8, 15 - от черного до белого
* 1, 3, 9, 11 - от синего до голубого
* 4, 12 - красный
* 2, 10 - зеленый
* 5, 13 - фиолетовый
* 6, 14 - желтый
*
* ‘ќЌ
* 0..15 - черный
* 112..127, 128..143 - серый
* 240..255 - белый
* 32..47, 160..175 - зеленый
* 16..31, 48..63, 144..159, 176..191 - синий
* 64..79, 192..207 - красный
* 80..95, 208..223 - фиолетовый
* 96..111, 224..239 - желтый
*/
void Color(byte);

class TicTacToe {
private:
	string nick_player1_, nick_player2_, winner_;
	int size_, block_;
	char symbol_ = 'X';
	vector <vector <char>> map_;

	bool checkDiagonal(char) const;
	bool checkLanes(char) const;
public:
	TicTacToe() : size_(3), block_(3) {
		nick_player1_ = "Player1";
		nick_player2_ = "Player2";
		map_.resize(3, vector<char>(3));
	}
	TicTacToe(int size) : size_(size) {
		nick_player1_ = "Player1", nick_player2_ = "Player2";
		(size_ == 3 || size_ == 4) ? block_ = 3 : block_ = 4;
		map_.resize(size_, vector<char>(size_));
	}
	TicTacToe(int size, int block) : size_(size), block_(block) {
		nick_player1_ = "Player1", nick_player2_ = "Player2";
		map_.resize(size_, vector<char>(size_));
	}
	void sizeAndBlock(int size, int block) {
		size_ = size, block_ = block;
		map_.clear();
		map_.resize(size, vector<char>(size));
	}

	void addPlayers();
	void drawMap() const;
	bool checkWin();
	bool isFull() const;
	void makeMove();
	void play();

	string nickPlayer1() { return nick_player1_; }
	string nickPlayer2() { return nick_player1_; }
	string nickWinner() { return winner_; }
};

typedef struct {
	string nick;
	unsigned wins, games;
} Player;