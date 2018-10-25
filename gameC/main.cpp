#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
#include <cmath>
#include <vector>
#include <Windows.h>


using namespace std;

const int m = 11, n = 70;


enum So
{
	Up, Down, Left, Right, Die
};



class User
{
public:
	int x, y;
	So Sost;
};

class Time
{
public:
	int f, l;
};

class Bullet
{
public:
	int x, y, s = 5;
	So sost;
};

class Block
{
public:
	int x, y;
};





User Mario;
Time t;
Bullet b;

Block mas[100],T,MenuPos;

int a, win;



string map[m] = {
	"###############################################################                    ",
	"#   #    #                                    # Move    up: w #                    ",
	"#   #@   #                                    # Move  down: s #                    ",
	"# ###   @##                                   # Move  left: a #                    ",
	"# #  @  @ #                                   # Move right: d #                    ",
	"### # ##  #   ######                          # You: T        #                    ",
	"#   # ##  #*###  XX    @@@@@                  #################                    ",
	"# @  @           XX                                           #                                                      ",
	"##### #### #P##  XX      @@@@                                 #                                                      ",
	"#   #      #########                                          #                                                      ",
	"###############################################################                                                      ",
};

string mapb[m] = {
	"                                                                                                                     ",
	"                                                                                                                     ",
	"                                                                                                                     ",
	"                                                                                                                     ",
	"                                                                                                                     ",
	"                                                                                                                     ",
	"                                                                                                                     ",
	"                                                                                                                     ",
	"                                                                                                                     ",
	"                                                                                                                     ",
	"                                                                                                                     ",
};


void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}

void DrawStatic(){
	system("cls");
	for (int i = 0; i < m; i++) {
		string s;
		for (int j = 0; j < n; j++) {
			if (mapb[i][j] != '@') if ( map[i][j] == '*'){
			    map[i][j] = ' ';
                s+='#';
			} else s += map[i][j];
			else s += '@';
		}
		cout << s << endl;
	}
	gotoxy(Mario.x, Mario.y);
	cout << '^';
	gotoxy(T.x, T.y);
	cout << '^';
	gotoxy(0, 0);
	gotoxy(11,6);
	cout << '#';
	gotoxy(19,6);
    cout << '#';
    gotoxy(19,7);
    cout << '#';
    gotoxy(19,8);
    cout << '#';
    gotoxy(0, 0);
}

void DrawCollisionBlock(){
	gotoxy(Mario.x, Mario.y);
	switch (Mario.Sost){
	case Up:
		cout << '^';
		gotoxy(T.x, T.y);
		cout << '^';
		gotoxy(Mario.x, Mario.y + 1);
		if (map[Mario.y + 1][Mario.x] == 'X') {
			cout << 'X';
		} else cout << ' ';
		gotoxy(0, 0);
		break;
	case Down:
		cout << 'v';
		gotoxy(T.x, T.y);
		cout << 'V';
		gotoxy(Mario.x, Mario.y - 1);
		if (map[Mario.y - 1][Mario.x] == 'X') {
			cout << 'X';
		}
		else cout << ' ';
		gotoxy(0, 0);
		break;
	case Left:
		cout << '<';
		gotoxy(T.x, T.y);
		cout << '<';
		gotoxy(Mario.x + 1, Mario.y);
		if (map[Mario.y][Mario.x + 1] == 'X') {
			cout << 'X';
		}
		else cout << ' ';
		gotoxy(0, 0);
		break;
	case Right:
		cout << '>';
		gotoxy(T.x, T.y);
		cout << '>';
		gotoxy(Mario.x - 1, Mario.y);
		if (map[Mario.y][Mario.x - 1] == 'X') {
			cout << 'X';
		}
		else cout << ' ';
		gotoxy(0, 0);
		break;
	}
	gotoxy(11,6);
	cout << '#';
	gotoxy(19,6);
    cout << '#';
    gotoxy(19,7);
    cout << '#';
    gotoxy(19,8);
    cout << '#';
    gotoxy(0, 0);
}

void DrawMario() {

	gotoxy(Mario.x, Mario.y);
	switch (Mario.Sost)
	{
		case Up:
			cout << '^';
			gotoxy(T.x, T.y);
			cout << '^';
			gotoxy(0, 0);
			break;
		case Down:
			cout << 'v';
			gotoxy(T.x, T.y);
			cout << 'v';
			gotoxy(0, 0);
			break;
		case Left:
			cout << '<';
			gotoxy(T.x, T.y);
			cout << '<';
			gotoxy(0, 0);
			break;
		case Right:
			cout << '>';
			gotoxy(T.x, T.y);
			cout << '>';
			gotoxy(0, 0);
			break;

	}
	gotoxy(11,6);
	cout << '#';
	gotoxy(19,6);
    cout << '#';
    gotoxy(19,7);
    cout << '#';
    gotoxy(19,8);
    cout << '#';
    gotoxy(0, 0);
}

void DrawMenuStatik(){
	gotoxy(MenuPos.x , MenuPos.y);
	cout << ">Start<";
	gotoxy(MenuPos.x + 1, MenuPos.y + 1);
	cout << "Options";
	gotoxy(MenuPos.x + 1, MenuPos.y + 2);
	cout << "Exit";
	gotoxy(0, 0);
}



void Collision() {
	switch (Mario.Sost){
		case Up: {
			if ((map[Mario.y - 1][Mario.x] == ' ' || map[Mario.y - 1][Mario.x] == 'X') && mapb[Mario.y - 1][Mario.x] != '@') { Mario.y -= 1; DrawCollisionBlock(); break; }
			if (mapb[Mario.y - 1][Mario.x] == '@') {
				if ((map[Mario.y - 2][Mario.x] == ' ' || map[Mario.y - 2][Mario.x] == 'X') && mapb[Mario.y - 2][Mario.x] != '@') {
					gotoxy(Mario.x, Mario.y - 2);
					mapb[Mario.y - 2][Mario.x] = '@';
					mapb[Mario.y - 1][Mario.x] = ' ';
					cout << '@';
					gotoxy(Mario.x, Mario.y - 1);
					cout << ' ';
					Mario.y -= 1;
					DrawCollisionBlock();
					break;
				}
				else DrawMario(); break;
			}
			DrawMario();
			break;
		}
		case Down: {
			if ((map[Mario.y + 1][Mario.x] == ' ' || map[Mario.y + 1][Mario.x] == 'X') && mapb[Mario.y + 1][Mario.x] != '@') { Mario.y += 1;  DrawCollisionBlock(); break; }
			if (mapb[Mario.y + 1][Mario.x] == '@') {
				if ((map[Mario.y + 2][Mario.x] == ' ' || map[Mario.y + 2][Mario.x] == 'X') && mapb[Mario.y + 2][Mario.x] != '@') {
					gotoxy(Mario.x, Mario.y + 2);
					mapb[Mario.y + 2][Mario.x] = '@';
					mapb[Mario.y + 1][Mario.x] = ' ';
					cout << '@';
					gotoxy(Mario.x, Mario.y + 1);
					cout << ' ';
					Mario.y += 1;
					DrawCollisionBlock();
					break;
				}
				else DrawMario(); break;
			}
			DrawMario();
			break;
		}

		case Left: {
			if ((map[Mario.y][Mario.x - 1] == ' ' || map[Mario.y][Mario.x - 1] == 'X') && mapb[Mario.y][Mario.x - 1] != '@') { Mario.x -= 1;  DrawCollisionBlock(); break; }
			if (mapb[Mario.y][Mario.x - 1] == '@') {
				if ((map[Mario.y][Mario.x - 2] == ' ' || map[Mario.y][Mario.x - 2] == 'X') && mapb[Mario.y][Mario.x - 2] != '@') {
					gotoxy(Mario.x - 2, Mario.y);
					mapb[Mario.y][Mario.x - 2] = '@';
					mapb[Mario.y][Mario.x - 1] = ' ';
					cout << '@';
					gotoxy(Mario.x - 1, Mario.y);
					cout << ' ';
					Mario.x -= 1;
					DrawCollisionBlock();
					break;
				}
				else DrawMario(); break;
			}
			DrawMario();
			break;
		}
		case Right: {
			if ((map[Mario.y][Mario.x + 1] == ' ' || map[Mario.y][Mario.x + 1] == 'X') && mapb[Mario.y][Mario.x + 1] != '@') { Mario.x += 1;  DrawCollisionBlock(); break; }
			if (mapb[Mario.y][Mario.x + 1] == '@') {
				if ((map[Mario.y][Mario.x + 2] == ' ' || map[Mario.y][Mario.x + 2] == 'X') && mapb[Mario.y][Mario.x + 2] != '@')  {
					gotoxy(Mario.x + 2, Mario.y);
					mapb[Mario.y][Mario.x + 2] = '@';
					mapb[Mario.y][Mario.x + 1] = ' ';
					cout << '@';
					gotoxy(Mario.x + 1, Mario.y);
					cout << ' ';
					Mario.x += 1;
					DrawCollisionBlock();
					break;
				}
				else DrawMario(); break;
			}
			DrawMario();
			break;
		}

	}

}

void Input() {

	if (_kbhit()) {
		switch (_getch())
		{
		case 'w': Mario.Sost = Up; Collision();    break;
		case 's': Mario.Sost = Down; Collision();  break;
		case 'a': Mario.Sost = Left; Collision();  break;
		case 'd': Mario.Sost = Right; Collision(); break;
		case 'W': Mario.Sost = Up; Collision();    break;
		case 'S': Mario.Sost = Down; Collision();  break;
		case 'A': Mario.Sost = Left; Collision();  break;
		case 'D': Mario.Sost = Right; Collision(); break;
		case 'e': gotoxy(0, 14); exit(0);
		case 'E': gotoxy(0, 14); exit(0);
		}
	}
}

void Detected() {
	a = -1;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n ; j++) {
			if (map[i][j] == 'T') {
				T.x = j;
				T.y = i;
				map[i][j] = ' ';
			}
			if (map[i][j] == 'X') {
				a++;
				mas[a].x = j;
				mas[a].y = i;
			}
			if (map[i][j] == '@') {
				mapb[i][j] = '@';
				map[i][j] = ' ';
			}
			if (map[i][j] == 'P') {
				Mario.y = i;
				Mario.x = j;
				map[i][j] = ' ';
			}
		}
	}
}

void LogicMenu(int a, char b) {
	if (a == 0) {
		if (b == '+') {
			gotoxy(MenuPos.x + 6, MenuPos.y + a);
			cout << ' ';
			gotoxy(MenuPos.x + 8, MenuPos.y + a + 1);
			cout << '<';
		}
	}
	if (a == 1) {
		gotoxy(MenuPos.x + 8, MenuPos.y + a);
		cout << ' ';
		if (b == '-') {
			gotoxy(MenuPos.x + 6, MenuPos.y + a - 1);
			cout << '<';
		}
		else {
			gotoxy(MenuPos.x + 5, MenuPos.y + a + 1);
			cout << '<';
		}
	}
	if (a == 2) {
		if (b == '-') {
			gotoxy(MenuPos.x + 5, MenuPos.y + a);
			cout << ' ';
			gotoxy(MenuPos.x + 8, MenuPos.y + a - 1);
			cout << '<';
		}
	}
}



void StartGame() {
	Mario.Sost = Up;

	Detected();
	DrawStatic();

	while (1) {

		//t.f = clock();
		Input();
		win = a;
		for (int c = 1; c <= a; c++) {
			if (mapb[mas[c].y][mas[c].x] == '@') {
				win--;
			}
		}
		if (win == 0) {
			system("cls");
			cout << "Congrats! You won!" << endl;
			system("pause");
			exit(0);
		}

	}
}

void MenuStart() {
	int a = 0;
	while (1) {
		switch (_getch())
		{
		case 'w':
			LogicMenu(a, '-');
			gotoxy(MenuPos.x, MenuPos.y + a);
			cout << ' ';
			if (a != 0) a -= 1;
			gotoxy(MenuPos.x, MenuPos.y + a);
			cout << '>';
			gotoxy(0, 0);
			break;
		case 'W':
			LogicMenu(a, '-');
			gotoxy(MenuPos.x, MenuPos.y + a);
			cout << ' ';
			if (a != 0) a -= 1;
			gotoxy(MenuPos.x, MenuPos.y + a);
			cout << '>';
			gotoxy(0, 0);
			break;
		case 's':
			LogicMenu(a, '+');
			gotoxy(MenuPos.x, MenuPos.y + a);
			cout << ' ';
			if (a != 2) a += 1;
			gotoxy(MenuPos.x, MenuPos.y + a);
			cout << '>';
			gotoxy(0, 0);
			break;
        case 'S':
			LogicMenu(a, '+');
			gotoxy(MenuPos.x, MenuPos.y + a);
			cout << ' ';
			if (a != 2) a += 1;
			gotoxy(MenuPos.x, MenuPos.y + a);
			cout << '>';
			gotoxy(0, 0);
			break;
		case 'e': {
				if (a == 0) {StartGame(); break;}
				if (a == 2) exit(0); break;
			}
        case 'E': {
				if (a == 0) {StartGame(); break;}
				if (a == 2) exit(0); break;
			}

		}
	}
}





int main() {
	MenuPos.x = 40;
	MenuPos.y = 5;



	DrawMenuStatik();

	MenuStart();










		/*
		while (1)
		{
		if (abs(t.f - t.l) < 25) t.f = clock();
		else
		{
		cout << ((float)t.f) / CLOCKS_PER_SEC << endl;
		t.l = t.f;
		break;
		}
		}

		if (i == Mario.y && j == Mario.x) {
				switch (Mario.Sost)
				{
				case Up: s += '^';
					break;
				case Down: s += 'v';
					break;
				case Left: s += '<';
					break;
				case Right: s += '>';
					break;
				}
			}
			else {
				for (int c = 0; c < a; c++)
				{
					if (mas[c].x == j && mas[c].y == i) {
						if (map[i][j] == '@') { s += '@'; break; }
						else { s += 'X'; break; }
					}
					if (c == a - 1) s += map[i][j];
				}
			}
		*/





}
