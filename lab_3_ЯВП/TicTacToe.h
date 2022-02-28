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

//�������:
//template <typename T> void Print(T buf, int x, int y, byte color)
//template <typename T> void Print(T buf, byte color)
//����: ������������ ������� ������� � ������ y � ������� x, ����� � ������� ������ ������, �������� color
//���������:
//buf - ������ ��� ������
//x - ������� � �������
//y - ������ � �������
//color - ���� ������ � ���� 
template <typename T> void Print(T, int, int, byte);
template <typename T> void Print(T, int, int);
template <typename T> void Print(T, byte);

/*�������: void Color(byte color)
* ����: ������� ����� ���������� � ������� ������
* ���������: color - ���� ������ � ����
*
* �����
* 0, 7, 8, 15 - �� ������� �� ������
* 1, 3, 9, 11 - �� ������ �� ��������
* 4, 12 - �������
* 2, 10 - �������
* 5, 13 - ����������
* 6, 14 - ������
*
* ���
* 0..15 - ������
* 112..127, 128..143 - �����
* 240..255 - �����
* 32..47, 160..175 - �������
* 16..31, 48..63, 144..159, 176..191 - �����
* 64..79, 192..207 - �������
* 80..95, 208..223 - ����������
* 96..111, 224..239 - ������
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