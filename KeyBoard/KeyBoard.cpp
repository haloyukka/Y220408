#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define KEYMAP_WIDTH 15
#define KEYMAP_HEIGHT 3

#define DISP_MAX_LENGTH 48
#define KEYMAP_MAX_LENGTH 60

int cursorX = 0;
int cursorY = 1;
int disp_cursorX;
//int disp_cursorY;

char SoftKeyboard_Disp[DISP_MAX_LENGTH] = {};	// 上半分
char SoftKeyboard_Map[KEYMAP_MAX_LENGTH] = {};	// 下半分
unsigned int len;								// 配列に格納されている文字列の長さ


// 構造体定義
typedef struct converter {
	int softkey_index;
	char out_c;
}converter;

typedef struct char_code {
	//	int softkey_index;
	//	char out_c;
	char lower_code; // 小文字
	char upper_code; // 大文字
	char symbol_code; // 記号
	//const char* app_variable;
}char_code;

struct char_code table[KEYMAP_MAX_LENGTH] =
{
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x0,0x0,0x0 },
	{ 0x30,0x30,0x30 },
	{ 0x31,0x31,0x31 },
	{ 0x32,0x32,0x32 },
	{ 0x33,0x33,0x33 },
	{ 0x34,0x34,0x34 },
	{ 0x35,0x35,0x35 },
	{ 0x36,0x36,0x36 },
	{ 0x37,0x37,0x37 },
	{ 0x38,0x38,0x38 },
	{ 0x39,0x39,0x39 },
	{ 0x2E,0x2E,0x2E },
	{ 0x2C,0x2C,0x2C },
	{ 0x2D,0x2D,0x2D },
	{ 0x5F,0x5F,0x5F },
	{ 0x2F,0x2F,0x2F },
	{ 0x61,0x41,0x3F },
	{ 0x62,0x42,0x21 },
	{ 0x63,0x43,0x22 },
	{ 0x64,0x44,0x23 },
	{ 0x65,0x45,0x24 },
	{ 0x66,0x46,0x25 },
	{ 0x67,0x47,0x26 },
	{ 0x68,0x48,0x27 },
	{ 0x69,0x49,0x28 },
	{ 0x6A,0x4A,0x29 },
	{ 0x6B,0x4B,0x3D },
	{ 0x6C,0x4C,0x40 },
	{ 0x6D,0x4D,0x5B },
	{ 0x6E,0x4E,0x5D },
	{ 0x6F,0x4F,0x2A },
	{ 0x70,0x50,0x2B },
	{ 0x71,0x51,0x3C },
	{ 0x72,0x52,0x3E },
	{ 0x73,0x53,0x3B },
	{ 0x74,0x54,0x3A },
	{ 0x75,0x55,0x60 },
	{ 0x76,0x56,0x0 },
	{ 0x77,0x57,0x0 },
	{ 0x78,0x58,0x0 },
	{ 0x79,0x59,0x0 },
	{ 0x7A,0x5A,0x0 },
	{ 0x20,0x20,0x20 },
	{ 0x20,0x20,0x20 },
	{ 0x20,0x20,0x20 },
	{ 0x20,0x20,0x20 }
};



// 本番では、[index][ascii]のテーブルに差し替える
// 大文字テーブル
struct converter s_upper[KEYMAP_MAX_LENGTH] =
{
	{0, '\0'},{1, '\0'},{2, '\0'},{3, '\0'},{4, '\0'},{5, '\0'},{6, '\0'},{7, '\0'},{8, '\0'},{9, '\0'},{10, '\0'},{11, '\0'},{12, '\0'},{13, '\0'},{14, '\0'},
	{15, '0'},{16, '1'},{17, '2'},{18, '3'},{19, '4'},{20, '5'},{21, '6'},{22, '7'},{23, '8'},{24, '9'},{25, '.'},{26, ','},{27, '-'},{28, '_'},{29, '/'},
	{30, 'A'},{31, 'B'},{32, 'C'},{33, 'D'},{34, 'E'},{35, 'F'},{36, 'G'},{37, 'H'},{38, 'I'},{39, 'J'},{40, 'K'},{41, 'L'},{42, 'M'},{43, 'N'},{44, 'O'},
	{45, 'P'},{46, 'Q'},{47, 'R'},{48, 'S'},{49, 'T'},{50, 'U'},{51, 'V'},{52, 'W'},{53, 'X'},{54, 'Y'},{55, 'Z'},{56, ' '},{57, ' '},{58, ' '},{59, ' '}
};
// 小文字テーブル
struct converter s_lower[KEYMAP_MAX_LENGTH] =
{
	{ 0, '\0' },{ 1, '\0' },{ 2, '\0' },{ 3, '\0' },{ 4, '\0' },{ 5, '\0' },{ 6, '\0' },{ 7, '\0' },{ 8, '\0' },{ 9, '\0' },{ 10, '\0' },{ 11, '\0' },{ 12, '\0' },{ 13, '\0' },{ 14, '\0' },
	{ 15, '0' },{ 16, '1' },{ 17, '2' },{ 18, '3' },{ 19, '4' },{ 20, '5' },{ 21, '6' },{ 22, '7' },{ 23, '8' },{ 24, '9' },{ 25, '.' },{ 26, ',' },{ 27, '-' },{ 28, '_' },{ 29, '/' },
	{ 30, 'a' },{ 31, 'b' },{ 32, 'c' },{ 33, 'd' },{ 34, 'e' },{ 35, 'f' },{ 36, 'g' },{ 37, 'h' },{ 38, 'i' },{ 39, 'j' },{ 40, 'k' },{ 41, 'l' },{ 42, 'm' },{ 43, 'n' },{ 44, 'o' },
	{ 45, 'p' },{ 46, 'q' },{ 47, 'r' },{ 48, 's' },{ 49, 't' },{ 50, 'u' },{ 51, 'v' },{ 52, 'w' },{ 53, 'x' },{ 54, 'y' },{ 55, 'z' },{ 56, ' ' },{ 57, ' ' },{ 58, ' ' },{ 59, ' ' }
};
// 記号テーブル
struct converter s_symbol[KEYMAP_MAX_LENGTH] =
{
	{ 0, '\0' },{ 1, '\0' },{ 2, '\0' },{ 3, '\0' },{ 4, '\0' },{ 5, '\0' },{ 6, '\0' },{ 7, '\0' },{ 8, '\0' },{ 9, '\0' },{ 10, '\0' },{ 11, '\0' },{ 12, '\0' },{ 13, '\0' },{ 14, '\0' },
	{ 15, '0' },{ 16, '1' },{ 17, '2' },{ 18, '3' },{ 19, '4' },{ 20, '5' },{ 21, '6' },{ 22, '7' },{ 23, '8' },{ 24, '9' },{ 25, '.' },{ 26, ',' },{ 27, '-' },{ 28, '_' },{ 29, '/' },
	{ 30, '?' },{ 31, '!' },{ 32, '"' },{ 33, '#' },{ 34, '$' },{ 35, '%' },{ 36, '&' },{ 37, '\'' },{ 38, '(' },{ 39, ')' },{ 40, '=' },{ 41, '@' },{ 42, '[' },{ 43, ']' },{ 44, '*' },
	{ 45, '+' },{ 46, '<' },{ 47, '>' },{ 48, ';' },{ 49, ':' },{ 50, '`' },{ 51, '\0' },{ 52, '\0' },{ 53, '\0' },{ 54, '\0' },{ 55, '\0' },{ 56, ' ' },{ 57, ' ' },{ 58, ' ' },{ 59, ' ' }
};

enum class InputMode {
	Upper = 0,
	Lower = 1,
	Symbol = 2,
};
InputMode SoftKeyboard_InputMode;		// 0:大文字 1:小文字 2:記号

// 関数プロトタイプ宣言 
void setchar(char);


int main() {
	// 初期値
	SoftKeyboard_InputMode = InputMode::Upper;
	bool Is_mode_upper = true;			// true : 大文字(upper) false : 小文字(lower)
	bool Is_mode_before_upper = true;	// true(直前の入力モード大文字), false(直前の入力モード小文字)
	bool Is_mode_symbol = false;		// true : 入 false : 切 

	// main loop
	while (1) {
		system("cls");
		// test
		printf("%c\n", table[36].lower_code);
		printf("%c\n", table[36].upper_code);
		printf("%c\n", table[36].symbol_code);

		// 操作ガイド
		printf("+------操作ガイド----------------------------+\n");
		printf("+ [ o ]       : OK ボタン                    +\n");
		printf("+ [ w a s d ] : ↑ ← ↓→  (キーボード移動) +\n");
		printf("+ [q e]       : ← →       (カーソル移動)   +\n");
		printf("+ [ 1 ]       : 削除                         +\n");
		printf("+ ※カーソル位置を # で表示する※            +\n");

		// 2次元 -> 1次元 :[y][x]形式から[index]形式へ変換
		int idx = cursorY * KEYMAP_WIDTH + cursorX;

		// InputDisp Field作成-------------------------------
		printf("+--------------------------------------------+\n");
		for (int i = 0; i < DISP_MAX_LENGTH; i++) {
			if (0 == i % 16) {
				printf("\n");
				printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
			}
			if (i == disp_cursorX) {
				printf("#"); // 現在位置にXを表示する
			}
			else {
				printf("|");
			}
			printf("%c", SoftKeyboard_Disp[i]);
		}
		printf("\n");
		printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n");
		printf("=============================================\n");
		printf(" 入力モード : [%d] (0:大文字 1:小文字 2:記号)\n", SoftKeyboard_InputMode);
		printf("=============================================\n");
		// SoftwareKeyboard Field作成-------------------------
		for (int i = 0; i < KEYMAP_MAX_LENGTH; i++) {

			if (0 == i % 15) {
				printf("\n");
			}
			if (i == idx) {
				printf("◆");
			}
			else if (0 <= i && i <= 4) {
				printf("◎");
			}
			else if (5 <= i && i <= 9) {
				printf("☆");
			}
			else if (10 <= i && i <= 14) {
				printf("△");
			}
			else if (SoftKeyboard_InputMode == InputMode::Symbol && 51 <= i && i <= 55) {
				printf("＃");
			}
			else if (SoftKeyboard_InputMode != InputMode::Symbol && 51 <= i && i <= 55) {
				printf("□");
			}
			else if (56 <= i && i <= 60) {
				printf("■");
			}
			else {
				printf("□");
			}
		}
		printf("\n");

		// key入力を判定し、現在座標を操作---------------------
		int ch = 0;
		ch = _getch();

		switch (ch) {
			// ↑上移動
		case 'w':
			// 入力モード記号の時
			//if (SoftKeyboard_InputMode == 2) {
			if (SoftKeyboard_InputMode == InputMode::Symbol) {
				//if (idx == 6 || idx == 7 || idx == 8 || idx == 9 || idx == 10) {
				if ((6 <= idx) && (idx <= 10)) {
					cursorY = 2;
					break;
				}
			}

			if (0 <= idx && idx <= 14) {
				cursorY = 3;
			}
			else if (cursorY != 0) {
				cursorY--;
			}
			break;

			//↓下移動
		case 's':
			// 入力モード記号の時
			if (SoftKeyboard_InputMode == InputMode::Symbol) {
				//if (idx == 36 || idx == 37 || idx == 38 || idx == 39 || idx == 40) {
				if ((36 <= idx) && (idx <= 40)) {
					cursorY = 0;
					break;
				}
			}
			if (45 <= idx && idx <= 59) {
				cursorY = 0;
			}
			else if (cursorY != 3) {
				cursorY++;

			}
			break;

			// ←左移動
		case 'a':
			// 入力モード記号の時
			if (SoftKeyboard_InputMode == InputMode::Symbol) {
				if (56 <= idx && idx <= 59) {
					cursorX = 5;
					cursorY = 3;
					break;
				}
			}

			//if (idx == 0 || idx == 1 || idx == 2 || idx == 3 || idx == 4) {
			if ((0 <= idx) && (idx <= 4)) {
				cursorX = 14;
				cursorY = 3;
			}
			//else if (idx == 5 || idx == 6 || idx == 7 || idx == 8 || idx == 9) {
			else if ((5 <= idx) && (idx <= 9)) {
				cursorX -= 5;
				cursorY = 0;
			}
			//else if (idx == 10 || idx == 11 || idx == 12 || idx == 13 || idx == 14) {
			else if ((10 <= idx) && (idx <= 14)) {
				cursorX -= 5;
				cursorY = 0;
			}
			//else if (idx == 56 || idx == 57 || idx == 58 || idx == 59) {
			else if ((56 <= idx) && (idx <= 59)) {
				cursorX = 10;
				cursorY = 3;
			}
			else {
				cursorX--;
				// 行を変更
				if (cursorX < 0) {
					cursorX = 14;
					cursorY--;
				}
			}
			break;

			// →右移動
		case 'd':
			// 入力モード記号の時
			if (SoftKeyboard_InputMode == InputMode::Symbol) {
				if (idx == 50) {
					cursorX += 6;
					break;
				}
			}

			//if (idx == 0 || idx == 1 || idx == 2 || idx == 3 || idx == 4) {
			if ((0 <= idx) && (idx <= 4)) {
				cursorX += 5;
			}
			//else if (idx == 5 || idx == 6 || idx == 7 || idx == 8 || idx == 9) {
			else if ((5 <= idx) && (idx <= 9)) {
				cursorX += 5;
			}
			//else if (idx == 10 || idx == 11 || idx == 12 || idx == 13 || idx == 14) {
			else if ((10 <= idx) && (idx <= 14)) {
				cursorX = 0;
				cursorY = 1;
			}
			//else if (idx == 56 || idx == 57 || idx == 58 || idx == 59) {
			else if ((56 <= idx) && (idx <= 59)) {
				cursorX = 0;
				cursorY = 0;
			}
			else {
				cursorX++;
				// 行を変更
				if (cursorX > 14) {
					cursorX = 0;
					cursorY++;
				}
			}
			break;

		case 'q':
			if (disp_cursorX > 0) {
				disp_cursorX--;
			}
			break;

		case 'e':
			len = strlen(SoftKeyboard_Disp);
			// カーソル位置が文字の長さを超えない
			if (disp_cursorX < len) {
				disp_cursorX++;
			}
			break;

			// OKボタンの押下処理
		case 'o':

			// 大文字/小文字切替 処理
			//if (idx == 0 || idx == 1 || idx == 2 || idx == 3 || idx == 4) {
			if ((0 <= idx) && (idx <= 4)) {
				// 大文字→小文字
				if (Is_mode_upper == true && Is_mode_symbol == false) {
					Is_mode_upper = false;
					Is_mode_before_upper = false;

					//SoftKeyboard_InputMode = 1;
					SoftKeyboard_InputMode = InputMode::Lower;
				}
				// 小文字→大文字
				else if (Is_mode_upper == false && Is_mode_symbol == false) {
					Is_mode_upper = true;
					Is_mode_before_upper = true;

					//SoftKeyboard_InputMode = 0;
					SoftKeyboard_InputMode = InputMode::Upper;
				}
				// 記号→大文字
				else if (Is_mode_symbol == true && Is_mode_before_upper == true) {
					Is_mode_upper = true;
					Is_mode_symbol = false;

					//SoftKeyboard_InputMode = 0;
					SoftKeyboard_InputMode = InputMode::Upper;
				}
				// 記号→小文字
				else if (Is_mode_symbol == true && Is_mode_before_upper == false) {
					Is_mode_upper = false;
					Is_mode_symbol = false;

					//SoftKeyboard_InputMode = 1;
					SoftKeyboard_InputMode = InputMode::Lower;
				}
				break;
			}
			// 記号切替 処理
			//if (idx == 5 || idx == 6 || idx == 7 || idx == 8 || idx == 9) {
			if ((5 <= idx) && (idx <= 9)) {
				// 大文字→記号
				if (Is_mode_upper == true && Is_mode_symbol == false) {
					Is_mode_symbol = true;
					Is_mode_before_upper = true;

					//SoftKeyboard_InputMode = 2;
					SoftKeyboard_InputMode = InputMode::Symbol;
				}
				// 小文字→記号
				else if (Is_mode_upper == false && Is_mode_symbol == false) {
					Is_mode_symbol = true;
					Is_mode_before_upper = false;

					//SoftKeyboard_InputMode = 2;
					SoftKeyboard_InputMode = InputMode::Symbol;
				}
				break;
			}

			//if (idx == 10 || idx == 11 || idx == 12 || idx == 13 || idx == 14) {
			if ((10 <= idx) && (idx <= 14)) {
				// FINISHボタンが選択されている時の処理
				break;
			}

			// 大文字
			if (SoftKeyboard_InputMode == InputMode::Upper) {
				for (int i = 0; i < sizeof(table); i++) {
					if (i == idx) {
						setchar(table[i].upper_code);
						break;
					}
				}
			}
			// 小文字
			if (SoftKeyboard_InputMode == InputMode::Lower) {
				for (int i = 0; i < sizeof(table); i++) {
					if (i == idx) {
						setchar(table[i].lower_code);
						break;
					}
				}
			}
			// 記号
			if (SoftKeyboard_InputMode == InputMode::Symbol) {
				for (int i = 0; i < sizeof(table); i++) {
					if (51 <= i && i <= 55) {
						// 記号入力モードの未使用部分はスキップする
						continue;
					}
					if (i == idx) {
						setchar(table[i].symbol_code);
						break;
					}
				}
			}
			break;

		case '1':
			// 文字削除：選択座標にnullを入れる
			if (disp_cursorX > 0) {
				len = strlen(SoftKeyboard_Disp);

				// カーソルが49番目にある場合
				if (disp_cursorX == DISP_MAX_LENGTH) {
					disp_cursorX--;
					SoftKeyboard_Disp[disp_cursorX] = NULL;
				}
				else {
					// カーソル位置-1にnullを入れる
					SoftKeyboard_Disp[disp_cursorX - 1] = NULL;

					// 現在地の座標+1の座標から最後までの値を現在地の座標を先頭にしてmove
					memmove(&SoftKeyboard_Disp[disp_cursorX - 1], &SoftKeyboard_Disp[disp_cursorX], DISP_MAX_LENGTH - disp_cursorX);
					//末端処理
					SoftKeyboard_Disp[DISP_MAX_LENGTH - 1] = NULL;
					disp_cursorX--;
				}
			}
			break;

		default:
			printf("Not Assign");
			_getch();
			break;
		}
	}
	return 0;
}

// 関数定義-----------------------------------------------------------------

/**
* @fn
* ソフトウェアキーボードで入力した文字を表示用の配列に格納する
* @brief 要約説明
* @param (inputchar) 文字列
* @return なし
* @detail 詳細な説明
*/
void setchar(char inputchar) {
	// 文字挿入処理：入力されている文字列の途中から
	len = strlen(SoftKeyboard_Disp); //null文字までの長さを取得

	if (len < DISP_MAX_LENGTH) {
		// 現在座標から文字列のサイズ分のデータを現在座標+1を先頭にしたアドレスにコピー
		memmove(&SoftKeyboard_Disp[disp_cursorX + 1], &SoftKeyboard_Disp[disp_cursorX], len - disp_cursorX);
		SoftKeyboard_Disp[disp_cursorX] = { inputchar };
	}

	// 文字上書き処理：現在座標が最後(49番目)にある場合文字を上書き
	if (disp_cursorX == DISP_MAX_LENGTH) {
		SoftKeyboard_Disp[disp_cursorX - 1] = { inputchar };
	}

	// 範囲を超えない
	if (disp_cursorX < DISP_MAX_LENGTH && len != DISP_MAX_LENGTH) {
		disp_cursorX++;
	}
}