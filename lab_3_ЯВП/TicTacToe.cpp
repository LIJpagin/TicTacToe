#include "TicTacToe.h"

//‘”Ќ ÷»я:
//template <typename T> void Print(T buf, int x, int y, byte color)
//template <typename T> void Print(T buf, byte color)
//÷≈Ћ№: передвижение курсора консоли в строку y и столбец x, вывод в консоль строки цветом, заданным color
//ѕј–јћ≈“–џ:
//buf - строка дл€ вывода
//x - столбец в консоли
//y - строка в консоли
//color - цвет текста и фона 
template <typename T> void Print(T buf, int x, int y, byte color) {
	SetConsoleTextAttribute(hndl, (WORD)((0 << 4) | color));
	COORD p = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hndl, p);
	cout << buf;
	SetConsoleTextAttribute(hndl, (WORD)((0 << 4) | 15));
}
template <typename T> void Print(T buf, int x, int y) {
	SetConsoleTextAttribute(hndl, (WORD)((0 << 4) | 15));
	COORD p = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hndl, p);
	cout << buf;
}
template <typename T> void Print(T buf, byte color) {
	SetConsoleTextAttribute(hndl, (WORD)((0 << 4) | color));
	cout << buf;
	SetConsoleTextAttribute(hndl, (WORD)((0 << 4) | 15));
}

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
void Color(byte color) {
	SetConsoleTextAttribute(hndl, (WORD)((0 << 4) | color));
}

void TicTacToe::addPlayers() {
	Print(symbol_ == 'X' ? nick_player1_ : nick_player2_, 2, 1, symbol_ == 'X' ? 31 : 79);
	cout << ", введите свой ник, если хотите: ";
	string nick; getline(cin, nick);
	if (!nick.empty()) nick_player1_ = nick;
	system("cls");
	Print(symbol_ == 'O' ? nick_player2_ : nick_player2_, 2, 1, symbol_ == 'O' ? 31 : 79);
	cout << ", введите свой ник, если хотите: ";
	getline(cin, nick);
	if (!nick.empty()) nick_player2_ = nick;
	system("cls");
}

void TicTacToe::drawMap() const {
	CONSOLE_SCREEN_BUFFER_INFO csbiData;
	GetConsoleScreenBufferInfo(hndl, &csbiData);
	unsigned cell_size_x = 9, cell_size_y = 5;
	unsigned offset_x = (csbiData.dwSize.X - (cell_size_x - 1) * size_) / 2, offset_y = 3;
	byte color = 224;
	string horizontal = " ", vertical = " ";
	for (unsigned i = 0; i < size_ * (cell_size_x - 1) + 1; i++) {
		if (i % (cell_size_x - 1) == 0)
			horizontal += "+", vertical += "|";
		else
			horizontal += "-", vertical += " ";
	}
	horizontal += " ", vertical += " ";
	for (unsigned i = 0; i < size_ * (cell_size_y - 1) + 1; i++) {
		if (i % (cell_size_y - 1) == 0)
			Print(horizontal, offset_x - 1, i + offset_y, color);
		else
			Print(vertical, offset_x - 1, i + offset_y, color);
	}
	for (auto i = 0; i < size_ * size_; i++) {
		Print(i, (i % size_) * (cell_size_x - 1) + offset_x + 1,
			(i / size_) * (cell_size_y - 1) + offset_y + 1, color);
		if (map_[i % size_][i / size_])
			Print(map_[i % size_][i / size_],
				(i % size_) * (cell_size_x - 1) + offset_x + cell_size_x / 2,
				(i / size_) * (cell_size_y - 1) + offset_y + cell_size_y / 2,
				map_[i % size_][i / size_] == 'X' ? color + 1: color + 4);
	}
}

void TicTacToe::makeMove() {
	Print(symbol_ == 'X' ? nick_player1_ : nick_player2_, 2, 1, symbol_ == 'X' ? 31 : 79);
	cout << +" ваш ход: ";
	bool flag = true;
	while (flag) {
		string str;
		getline(cin, str);
		if (!str.empty()) {
			int num = stoi(str);
			if (num >= 0 && num < size_ * size_)
				if (map_[num % size_][num / size_] == '\0') {
					map_[num % size_][num / size_] = symbol_;
					symbol_ == 'X' ? symbol_ = symbol_ = 'O' : symbol_ = 'X';
					flag = false;
				}
		}
	}
}

bool TicTacToe::isFull() const {
	for (auto col = 0; col < size_; col++)
		for (auto row = 0; row < size_; row++)
			if (map_[col][row] == NULL)
				return false;
	return true;
}

bool TicTacToe::checkDiagonal(char symbol) const {
	for (auto row = 0; row <= size_ - block_; row++)
		for (auto col = 0; col <= size_ - block_; col++) {
			bool toright = true, toleft = true;
			for (auto i = 0; i < block_; i++) {
				toright &= (map_[(size_t)i + row][(size_t)i + col] == symbol);
				toleft &= (map_[(size_t)block_ - 1 - i + row][(size_t)i + col] == symbol);
			}
			if (toright || toleft) return true;
		}
	return false;
}

bool TicTacToe::checkLanes(char symbol) const {
	for (auto offset = 0; offset <= size_ - block_; offset++)
		for (auto row = 0; row < size_; row++) {
			bool cols = true, rows = true;
			for (auto col = offset; col < offset + block_; col++) {
				cols &= (map_[(size_t)row][(size_t)col] == symbol);
				rows &= (map_[(size_t)col][(size_t)row] == symbol);
			}
			if (cols || rows) return true;
		}
	return false;
}

bool TicTacToe::checkWin() {
	bool player1 = checkLanes('X') || checkDiagonal('X');
	bool player2 = checkLanes('O') || checkDiagonal('O');
	if (player1)
		winner_ = nick_player1_;
	if (player2)
		winner_ = nick_player2_;
	return (player1 || player2);
}

void TicTacToe::play() {
	while (!isFull() && !checkWin()) {
		drawMap();
		makeMove();
		system("cls");
	}
	system("cls");
	if (!winner_.empty()) Print("ѕоздравл€ем, " + winner_ + ", ты победил!", 2, 1);
	else Print("—егодн€ победила дружба!", 2, 1);
	_getch();
	system("cls");
}