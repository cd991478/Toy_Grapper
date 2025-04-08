////////////////////////////////////////////////////// 정의 ////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#define randomize() srand((unsigned)time(NULL))	
#define random(n) (rand() % (n))
#define cls system("cls")
#define delay(n) Sleep(n)
#define random_cost 1000

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
////////////////////////////////////////////////////// 유용한 기능 함수 /////////////////////////////////////////
void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
int wherex() // 현재 x 좌표 위치 조사
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.X;
}
int wherey() // 현재 y 좌표 위치 조사
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.Y;
}
typedef enum {
	NOCURSOR,
	SOLIDCURSOR,
	NORMALCURSOR
} CURSOR_TYPE;
typedef enum { // 색상 코드
	BLACK = 0, BLUE = 1, GREEN = 2, SKYBLUE = 3, RED = 4, PURPLE = 5, ORANGE = 6,
	WHITE = 7, GREY = 8, LIGHTBLUE = 9, LIGHTGREEN = 10, BLUEGREEN = 11, LIGHTRED = 12, LIGHTPURPLE = 13,
	YELLOW = 14, LIGHTWHITE = 15
} COLOR_TYPE;
typedef enum {
	Main_Cursor_Start_X = 76,
	Main_Cursor_Start_Y = 25,

} Cursor_Start_Pos;
typedef enum {
	Main_Menu = 0,
	Menu_1 = 1,
	Menu_2 = 2,
	Menu_3 = 3,
} Menu_Code;
void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
void setcolor(COLOR_TYPE text, COLOR_TYPE back) // 글자 색상, 글자뒤의 배경색 지정
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
void textcolor(COLOR_TYPE text) // 글자 색상만 지정
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

////////////////////////////////////////////////// 전역 변수 // 구조체 // 이미지 배열 ////////////////////////////////

int start = 0; // 플래그 변수
int total_cash = 0; // 총 금액 변수
int speed = 800; // delay 속도 변수 delay(speed) = 0.8초 
int text_speed = 10;
int img_speed = 200;
int text_color = LIGHTWHITE;
int cursor_color = ORANGE;
char cursor_shape[3] = "▶";

typedef struct doll // 인형 목록 구조체
{
	char name[30]; // 이름
	int number; // 고유 번호 1, 2, 3 ...
	int price; // 가격
	int stock; // 남은수량 (재고)
	char profile[100]; // 인형에 대한 설명

}DOLL;
DOLL doll[4] = { // 인형 구조체 변수 선언 {이름 / 고유번호 / 가격 / 재고수량 / 상세설명}
		{"인형이름 1", 1, 30000, 5, "설명내용"},
		{"인형이름 2", 2, 20000, 5, "설명내용"},
		{"인형이름 3", 3, 10000, 5, "설명내용"},
		{"인형이름 4", 4, 5000, 5, "설명내용"},
};

typedef struct cursor_pos
{
	const int start_x;
	const int start_y;
	int cur_x;
	int cur_y;
	const int menu_level;
	int cur_select;
}CURSOR_POS;
CURSOR_POS Main_Menu_Cursor = { Main_Cursor_Start_X, Main_Cursor_Start_Y, Main_Cursor_Start_X,Main_Cursor_Start_Y,0,1 };

int doll_image_01[25][25] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,15,15,15,15,15,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,15,15,14,14,14,14,14,15,15,15,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,15,14,14,14,14,14,14,14,14,14,14,15,0,0,0,0,0,0},
	{0,0,0,0,0,0,15,14,14,14,14,14,14,14,14,14,14,14,14,15,0,0,0,0,0},
	{0,0,0,0,0,15,14,14,14,14,14,14,14,14,14,14,14,14,14,15,0,0,0,0,0},
	{0,0,0,0,0,15,14,14,15,0,14,14,14,14,14,14,14,15,0,14,15,0,0,0,0},
	{0,0,0,0,15,14,14,14,0,0,14,14,0,0,0,0,14,0,0,14,15,0,0,0,0},
	{0,0,0,0,15,14,14,14,0,0,14,0,4,4,4,4,0,0,0,14,15,0,0,0,0},
	{0,0,0,0,15,14,14,14,14,14,0,0,0,0,0,0,0,14,14,14,15,15,0,0,0},
	{0,0,0,15,14,14,14,14,14,14,0,4,4,4,4,4,0,14,14,14,15,14,15,0,0},
	{0,0,15,14,14,14,14,14,14,14,14,0,0,0,0,0,14,14,14,14,15,14,14,15,0},
	{0,0,15,14,14,14,0,14,14,14,14,14,14,14,14,14,14,14,14,14,15,14,14,15,0},
	{0,0,15,14,14,0,0,14,0,0,0,0,0,0,0,0,14,14,14,14,15,15,14,15,0},
	{0,0,15,14,14,0,1,1,7,7,7,7,7,7,0,0,14,14,14,14,15,0,15,15,0},
	{0,0,0,15,14,0,1,1,7,7,7,7,7,0,0,14,14,14,14,14,15,0,0,0,0},
	{0,0,0,0,15,14,14,14,0,0,0,0,0,14,14,14,14,14,14,14,15,0,0,0,0},
	{0,0,0,0,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,0,0,0,0},
	{0,0,0,0,0,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,0,0,0,0},
	{0,0,0,0,0,15,15,15,15,14,14,14,14,14,14,14,14,14,14,15,15,0,0,0,0},
	{0,0,0,0,0,15,12,12,12,15,14,14,14,14,14,14,14,15,15,12,15,15,0,0,0},
	{0,0,0,0,0,15,12,12,12,12,15,14,14,14,14,14,15,12,12,12,12,15,0,0,0},
	{0,0,0,0,0,0,15,12,12,12,15,15,15,15,15,15,15,12,12,12,12,15,0,0,0},
	{0,0,0,0,0,0,0,15,15,15,15,0,0,0,0,0,15,15,15,15,15,15,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int doll_image_02[25][25] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,9,11,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,9,11,11,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,9,9,11,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,9,9,11,8,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,9,11,11,11,8,9,1,0,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,1,9,9,11,11,11,11,9,9,1,0,0,1,15,15,1,0,0,0},
		{0,0,0,0,1,1,9,9,11,11,11,11,11,9,9,9,1,1,15,11,11,1,0,0,0},
		{0,0,0,1,12,9,11,15,11,11,11,11,11,11,9,8,8,15,15,11,11,1,0,0,0},
		{0,0,0,0,1,12,9,0,11,11,11,15,11,9,12,12,8,15,9,15,15,1,0,0,0},
		{0,0,0,1,12,12,9,11,11,11,11,0,11,12,12,12,12,8,15,9,9,1,0,0,0},
		{0,0,0,0,1,1,12,15,11,11,11,11,9,12,12,12,8,8,9,9,1,0,0,0,0},
		{0,0,0,0,0,0,1,1,15,15,15,11,11,8,12,12,8,9,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,8,9,9,11,11,8,8,9,9,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,9,15,15,9,9,9,9,8,9,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,9,9,1,8,9,9,8,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,1,0,1,9,9,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int doll_image_03[25][25] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,12,12,12,12,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,12,12,4,4,4,4,12,12,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,12,4,4,4,4,4,4,4,4,12,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,12,4,4,4,4,4,4,4,4,4,12,12,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,12,0,0,0,0,0,4,4,4,4,4,4,12,0,0,0,0,0,0,0},
		{0,0,0,0,12,11,11,15,15,11,11,0,4,4,4,4,4,12,0,0,0,0,0,0,0},
		{0,0,0,0,12,11,15,15,15,11,11,11,0,4,4,4,4,4,12,0,0,0,0,0,0},
		{0,0,0,12,11,15,15,15,15,11,11,11,7,0,4,4,4,4,12,12,12,0,0,0,0},
		{0,0,0,12,11,11,11,11,11,11,11,7,7,0,4,4,4,4,12,4,4,12,12,0,0},
		{0,0,0,12,11,11,11,11,11,11,7,7,0,4,4,4,4,4,12,4,4,8,12,0,0},
		{0,0,0,12,11,11,11,11,7,7,7,0,0,4,4,4,4,8,12,4,4,8,12,0,0},
		{0,0,0,0,12,0,0,0,0,0,0,4,4,4,4,4,4,8,12,4,8,8,12,0,0},
		{0,0,0,0,12,4,4,4,4,4,4,4,4,4,4,4,4,8,12,8,8,8,12,0,0},
		{0,0,0,0,12,4,4,4,4,4,4,4,4,4,4,4,8,8,12,8,8,8,12,0,0},
		{0,0,0,0,12,4,4,4,4,4,4,4,4,4,4,4,8,8,12,8,8,12,12,0,0},
		{0,0,0,0,12,4,4,4,4,4,4,4,4,4,4,8,8,8,12,12,12,0,0,0,0},
		{0,0,0,0,12,4,4,4,8,8,8,8,8,4,4,8,8,8,12,0,0,0,0,0,0},
		{0,0,0,0,0,12,8,8,12,12,12,12,12,8,8,8,8,8,12,0,0,0,0,0,0},
		{0,0,0,0,0,12,8,8,12,0,0,0,12,8,8,8,8,12,0,0,0,0,0,0,0},
		{0,0,0,0,0,12,8,8,12,0,0,0,0,12,8,8,8,12,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,12,12,0,0,0,0,0,0,12,12,12,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int doll_image_04[25][25] = {
		{0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0},
		{0,0,0,0,0,8,1,9,8,0,0,0,0,0,0,0,8,1,9,8,0,0,0,0,0},
		{0,0,0,0,0,8,1,9,9,8,0,0,0,0,0,8,1,1,9,8,0,0,0,0,0},
		{0,0,0,0,0,8,9,9,9,9,8,8,8,8,8,1,1,9,9,8,0,0,0,0,0},
		{0,0,0,0,0,8,9,9,9,9,9,9,9,9,1,1,9,9,9,8,0,0,0,0,0},
		{0,0,0,0,8,9,9,9,9,9,9,9,15,9,9,9,9,9,9,9,8,0,0,0,0},
		{0,0,0,8,7,7,9,9,9,9,9,15,15,15,9,9,9,9,9,7,7,8,0,0,0},
		{0,0,0,8,7,15,15,15,0,15,15,15,15,15,15,15,0,15,15,15,7,8,0,0,0},
		{0,0,8,7,7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,7,8,0,0},
		{0,0,8,7,15,15,15,15,0,0,15,15,15,15,15,0,0,15,15,15,15,15,8,0,0},
		{0,0,8,15,15,15,15,0,15,0,0,15,15,15,0,15,0,0,15,15,15,15,8,0,0},
		{0,0,8,15,15,15,15,0,0,15,0,15,15,15,0,0,15,0,15,15,15,15,8,0,0},
		{0,0,8,15,15,12,12,12,0,0,15,15,15,15,15,0,0,12,12,12,15,7,8,0,0},
		{0,0,0,8,15,12,12,12,15,15,0,15,0,15,0,15,15,12,12,12,15,8,0,0,0},
		{0,0,0,8,15,15,15,15,15,15,15,0,0,0,15,15,15,15,15,15,7,8,0,0,0},
		{0,0,0,0,8,7,15,15,15,15,15,15,15,15,15,15,15,15,15,7,8,0,0,0,0},
		{0,0,0,0,0,0,8,7,7,15,15,15,15,15,15,15,7,7,8,0,0,0,0,0,0},
		{0,0,0,0,0,8,15,15,15,15,15,15,15,15,7,7,15,15,7,8,0,0,0,0,0},
		{0,0,0,0,8,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,8,0,0,0,0},
		{0,0,0,0,8,15,8,15,15,15,15,15,15,15,15,15,15,15,8,7,8,0,0,0,0},
		{0,0,0,0,0,8,8,15,15,15,15,15,15,15,15,15,15,15,8,8,0,0,0,0,0},
		{0,0,0,0,0,0,8,15,15,15,7,7,7,7,7,15,15,15,8,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,8,15,8,8,8,8,8,8,8,15,8,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,8,7,8,0,0,0,0,0,8,7,8,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,8,8,8,0,0,0,0,0,8,8,8,0,0,0,0,0,0,0},
};

//////////////////////////////////////////////// 사용자 정의 함수 (시각 효과 관련) ////////////////////////////////////////////////

void Make_Image(int image[25][25], int x, int y) // 이미지 배열 출력 함수 (출력할 이미지 배열 이름, 시작 좌표값 필요)
{
	for (int i = 0; i < 25; i = i + 1) // y
	{
		for (int j = 0; j < 25; j = j + 1) // x
		{
			gotoxy(x + (j * 2), y + i); // 전달한 시작 좌표로 이동
			textcolor(image[i][j]); // 해당 픽셀값 전달하여 색상변환
			printf("■"); // 출력
		}
	}
	textcolor(text_color); // 출력 다 끝나고 초기 색상으로 리셋
}

void Text_Effect(char text[])
{
	for (int i = 0; text[i] != '\0'; i++)
	{
		putchar(text[i]);
		delay(text_speed);
	}
}

void Make_Frame() // 테두리 출력
{
	gotoxy(2, 1); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n"); // 116
	for (int y = 2; y < 61; y++)
	{
		gotoxy(2, y); printf("■"); // 왼쪽 벽 출력
		gotoxy(232, y); printf("■"); // 오른쪽 벽 출력
	}
	gotoxy(2, 61); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n"); // 116
}

void Intro_Screen() // 인트로 화면 내용
{
	gotoxy(112, 8); printf("< 인형 뽑기 >"); // 제목

	gotoxy(220, 59); printf("Ver 1.0.0"); // 버젼
}
void Press_Key_Text()
{
	gotoxy(100, 55); printf("<  P R E S S  A N Y  K E Y  T O  S T A R T  >");
}
void Press_Key_Delete()
{
	gotoxy(100, 55); printf("　　　　　　　　　　　　　　　　　　　　　　　　　"); // 공백 25개
}
void Intro_Effect() // 인트로 화면
{
	for (;;)
	{
		Make_Frame(); // 테두리 출력
		Intro_Screen();// 간단한 메인 타이틀 인트로 화면 출력
		Press_Key_Text();
		delay(speed / 4); // 0.2초 대기
		Press_Key_Delete();
		if (_kbhit()) // 키 입력 받으면 탈출
		{
			break;
		}
		delay(speed / 4);
		if (_kbhit())
		{
			break;
		}
	}
}
/*void Cursor_Check(CURSOR_POS cursor_temp)
{
	if (cursor_temp.cur_select <= 0)
	{
		Main_Menu_Cursor.cur_select = 1;
		Main_Menu_Cursor.cur_x = Main_Menu_Cursor.start_y;
		Main_Menu_Cursor.cur_y = Main_Menu_Cursor.start_y;
	}
	if (cursor_temp.cur_select >= 7)
	{
		Main_Menu_Cursor.cur_select = 6;
		Main_Menu_Cursor.cur_x = Main_Menu_Cursor.start_y;
		Main_Menu_Cursor.cur_y = Main_Menu_Cursor.start_y+(4*5);
	}
}
*/
void Cursor_Make(CURSOR_POS cursor_temp)
{
	textcolor(cursor_color);
	switch (cursor_temp.menu_level)
	{
	case 0: // 메인메뉴인경우
	{
		gotoxy(cursor_temp.cur_x, cursor_temp.cur_y); // 메인 메뉴 목록 시작점 좌표로 이동
		puts(cursor_shape); // 커서 출력
	}
	}
	textcolor(text_color);
}
void Cursor_Delete(CURSOR_POS cursor_temp) // 커서 삭제 함수
{
	gotoxy(cursor_temp.cur_x, cursor_temp.cur_y);
	printf("　"); // 공백으로 삭제
}
void Cursor_Move_Up(CURSOR_POS cursor_temp)
{
	if (cursor_temp.menu_level == 0) // 메인 메뉴일경우
	{
		if(cursor_temp.cur_select >= 2)
		Main_Menu_Cursor.cur_y = Main_Menu_Cursor.cur_y - 4; // 커서 좌표값 변경
		Main_Menu_Cursor.cur_select = Main_Menu_Cursor.cur_select - 1; // 메뉴 값 감소
	}
}
void Cursor_Move_Down(CURSOR_POS cursor_temp) // 아래키 입력 함수
{
	
	if (cursor_temp.menu_level == 0 ) // 메인 메뉴일경우
	{
		if (cursor_temp.cur_select <= 5)
		{
			Main_Menu_Cursor.cur_y = Main_Menu_Cursor.cur_y + 4; // 커서 좌표값 변경
			Main_Menu_Cursor.cur_select = Main_Menu_Cursor.cur_select + 1; // 메뉴 값 증가
		}
	}

}
//////////////////////////////////////////////// 사용자 정의 함수 (기능 관련) ////////////////////////////////////////////////////

int Main_Screen(int x, int y) // 메인 메뉴 화면
{
	int menu_select = 0;
	int Distance = 4; // 간격
	Make_Image(doll_image_01, 5, 20);
	Make_Image(doll_image_02, 182, 20);
	gotoxy(112, 8);				printf("<  메 인 메 뉴  >");
	gotoxy(x, y);				printf("< 1 >   자 판 기   실 행");
	gotoxy(x, y + Distance * 1); printf("< 2 >   복 불 복   랜 덤 뽑 기");
	gotoxy(x, y + Distance * 2); printf("< 3 > ");
	gotoxy(x, y + Distance * 3); printf("< 4 >   환 경 설 정");
	gotoxy(x, y + Distance * 4); printf("< 5 >   도 움 말   /   정 보");
	gotoxy(x, y + Distance * 5); printf("< 6 >   종 료");
	gotoxy(100, 56);			printf("메뉴를 선택하세요 : ");
	


}

void Machine_Screen() // 인형 목록 화면
{
	gotoxy(80, 10); printf("<<<인형뽑기 자판기 화면 나와야하는곳>>>");
}

int Cash_System_Print(int x, int y) // 금액 투입 시스템 1 (출력 / 입력 기능)
{
	int Distance = 1;
	int cash_select = 0;
	gotoxy(x, y); printf("");
	gotoxy(x, y + Distance); printf("< 1 > 50000원");
	gotoxy(x, y + Distance * 2); printf("< 2 > 10000원");
	gotoxy(x, y + Distance * 3); printf("< 3 > 5000원");
	gotoxy(x, y + Distance * 4); printf("< 4 > 1000원");
	gotoxy(x, y + Distance * 5); printf("");
	gotoxy(x, y + Distance * 6); printf("< 7 > 투입 금액 반환");
	gotoxy(x, y + Distance * 7); printf("< 8 > 이전 단계 이동");
	gotoxy(x, y + Distance * 8); printf("< 9 > 다음 단계 이동");
	gotoxy(x, y + Distance * 9); printf("");
	gotoxy(x, y + Distance * 10); printf("< 현재 투입 총 금액 : %d 원 >", total_cash);
	gotoxy(x, y + Distance * 11); printf("");
	gotoxy(x, y + Distance * 12); printf("어떤 지폐를 투입 하시겠습니까? ");
	scanf("%d", &cash_select);
	return cash_select;
}
void Cash_System_Calculate(int cash_select, int x, int y) // 금액 투입 시스템 2 (충전 기능)
{
	char str[50];
	gotoxy(x, y);
	switch (cash_select) // 지폐 선택 [3]
	{
	case 1: // 5만원권을 선택한경우
	{
		strcpy(str, "< 5만원권을 투입하였습니다 >");
		Text_Effect(str);
		total_cash = total_cash + 50000;
		delay(speed);
		break;
	}
	case 2: // 1만원권 
	{
		strcpy(str, "< 1만원권을 투입하였습니다 >");
		Text_Effect(str);
		total_cash = total_cash + 10000;
		delay(speed);
		break;
	}
	case 3: // 5천원권
	{
		strcpy(str, "< 5천원권을 투입하였습니다 >");
		Text_Effect(str);
		total_cash = total_cash + 5000;
		delay(speed);
		break;
	}
	case 4: // 1천원권
	{
		strcpy(str, "< 1천원권을 투입하였습니다 >");
		Text_Effect(str);
		total_cash = total_cash + 1000;
		delay(speed);
		break;
	}
	case 7: // 환불
	{
		strcpy(str, "< 전액 환불 처리 되었습니다. >");
		Text_Effect(str);
		gotoxy(x, y + 1);
		strcpy(str, "환불 금액 : ");
		Text_Effect(str);
		printf("%d", total_cash);
		strcpy(str, "원");
		Text_Effect(str);
		total_cash = 0;
		delay(speed);
		break;
	}
	case 8: // 뒤로가기
	{
		strcpy(str, "<<< 이전 메뉴로 이동합니다 >>>");
		Text_Effect(str);
		delay(speed);
		start = -1;
		break;
	}
	case 9: // 투입 완료
	{
		strcpy(str, "<<< 다음 단계로 이동합니다 >>>");
		Text_Effect(str);
		start = 1; // 플래그 변수 전환 >> 탈출 후 인형뽑기로 진입
		delay(speed);
		break;
	}
	default:
	{
		strcpy(str, "잘못된 입력입니다.");
		Text_Effect(str);
		delay(speed);
		break;
	}
	}
}

int Machine_System_Print(int x, int y) // 인형 자판기 시스템 1 (출력 / 입력)
{
	int Distance = 1;
	int doll_select = 0;

	gotoxy(x, y); printf(""); // (80, 40)
	gotoxy(x, y + Distance); printf("< 1번 인형 > 가격 : %d 원 // 남은수량 : %d 개", doll[0].price, doll[0].stock);
	gotoxy(x, y + Distance * 2); printf("< 2번 인형 > 가격 : %d 원 // 남은수량 : %d 개", doll[1].price, doll[1].stock);
	gotoxy(x, y + Distance * 3); printf("< 3번 인형 > 가격 : %d 원 // 남은수량 : %d 개", doll[2].price, doll[2].stock);
	gotoxy(x, y + Distance * 4); printf("< 4번 인형 > 가격 : %d 원 // 남은수량 : %d 개", doll[3].price, doll[3].stock);
	gotoxy(x, y + Distance * 5); printf("< 8번 : 이전 메뉴로 이동 >");
	gotoxy(x, y + Distance * 6); printf("< 현재 투입 금액 : %d 원 >", total_cash);
	gotoxy(x, y + Distance * 7); printf("");
	gotoxy(x, y + Distance * 8); printf("뽑으실 인형의 번호를 선택해주세요 : "); // (80, 48) 다음줄 (80, 49)
	scanf("%d", &doll_select);
	return doll_select;
}
void Machine_System_Activate(int n, int x, int y) // 인형 자판기 시스템 2 (결제)
{
	char str[50];
	gotoxy(x, y);
	switch (n) // n = doll_select
	{
	case 1:
	case 2:
	case 3:
	case 4: // 인형 선택시 // 간소화 후 1~4의 경우를 모두 따로 적을 필요가 없음, 동일한 코드니 통일
	{
		if (total_cash < doll[n - 1].price) // 금액이 부족한경우
		{
			strcpy(str, "금액이 부족합니다.");
			Text_Effect(str);
			delay(speed);
			break;
		}
		else if (total_cash >= doll[n - 1].price) // 금액이 충분한 경우인데,
		{
			if (doll[n - 1].stock >= 1) // 재고가 있는경우 > 구매 성공
			{
				strcpy(str, "구매에 성공하였습니다.");
				Text_Effect(str);
				total_cash = total_cash - doll[n - 1].price;
				doll[n - 1].stock = doll[n - 1].stock - 1;
				delay(speed);
				break;
			}
			else if (doll[n - 1].stock <= 0) // 재고가 없는경우
			{
				strcpy(str, "남은 수량이 없습니다.");
				Text_Effect(str);
				delay(speed);
				break;
			}
		}
	}
	case 8: // 뒤로가기
	{
		start = 0; // 플래그 변수 초기화
		strcpy(str, "<<< 이전 메뉴로 이동합니다 >>>");
		Text_Effect(str);
		delay(speed);
		break;
	}
	default:
	{
		strcpy(str, "잘못 입력하였습니다");
		Text_Effect(str);
		delay(speed);
		break;
	}
	}
}

void Randomize_Doll_Stock(int n) // 인형 수량 랜덤화
{
	for (int i = 0; i < 4; i++)
	{
		doll[i].stock = random(n - 1) + 1; // 재고수량 랜덤 배정
	}
}

void Random_Game_Screen_Print(int x, int y) // 랜덤 뽑기 화면 출력
{
	int Distance = 1;
	gotoxy(x, y);				printf("<< 랜덤 뽑기 >>");
	gotoxy(x, y + Distance * 1); printf("----------------------------");
	gotoxy(x, y + Distance * 2); printf("1등 인형 당첨 확률 : 1%%");
	gotoxy(x, y + Distance * 3); printf("2등 인형 당첨 확률 : 4%%");
	gotoxy(x, y + Distance * 4); printf("3등 인형 당첨 확률 : 15%%");
	gotoxy(x, y + Distance * 5); printf("4등 인형 당첨 확률 : 30%%");
	gotoxy(x, y + Distance * 6); printf("꽝 확률 : 50%%");
	gotoxy(x, y + Distance * 7); printf("----------------------------");
}
int Random_Game_Message(int x, int y)
{
	int Distance = 1;
	int input = 0;
	gotoxy(x, y);				printf("< 1 > 랜덤 뽑기 진행 ");
	gotoxy(x, y + Distance * 1); printf("< 8 > 뒤로가기");
	gotoxy(x, y + Distance * 2); printf("----------------------------");
	gotoxy(x, y + Distance * 3); printf("현재 투입된 금액 : %d 원", total_cash);
	gotoxy(x, y + Distance * 4); printf("----------------------------");
	gotoxy(x, y + Distance * 5); printf("선택하세요 : ");
	scanf("%d", &input);
	return input;
}

void Random_Game_Start(int game_menu_select, int x, int y)
{
	int dice = random(100);
	gotoxy(x, y);
	switch (game_menu_select)
	{
	case 1: // 진행을 선택했는데,
	{
		if (total_cash < random_cost) // 돈이 부족한경우
		{
			printf("투입 금액이 부족합니다.");
			delay(speed);
			break;
		}
		else if (total_cash >= random_cost) // 돈이 충분한경우
		{
			printf("뽑기를 진행합니다.");
			delay(speed);
			total_cash = total_cash - random_cost;
			gotoxy(x, y + 1);
			if (dice < 1) // 0 = 1%
			{
				printf("1등 당첨 !!! dice값 : %d", dice);
				delay(speed);
			}
			else if (dice >= 1 && dice < 5) // 1~4 = 4%
			{
				printf("2등 당첨 !!! dice값 : %d", dice);
				delay(speed);
			}
			else if (dice >= 5 && dice < 20) // 5~20 15%
			{
				printf("3등 당첨 !!! dice값 : %d", dice);
				delay(speed);
			}
			else if (dice >= 20 && dice < 50) // 30%
			{
				printf("3등 당첨 !!! dice값 : %d", dice);
				delay(speed);
			}
			else if (dice >= 50 && dice < 100) // 50%
			{
				printf("꽝입니다... dice값 : %d", dice);
				delay(speed);
			}
			else
			{
				printf("알 수 없는 오류");
				delay(speed);
			}
		}
		break;
	}
	case 8: // 뒤로 이동
	{
		start = 0;
		printf("이전 메뉴로 이동합니다.");
		delay(speed);
		break;
	}
	default:
	{
		printf("잘못된 입력입니다.");
		delay(speed);
		break;
	}
	}
}

void Setting_Screen(int x, int y) // 환경 설정 메뉴
{
	int input = 0;
	gotoxy(x, y);
	printf("< 1 > 작동 속도 설정");
	printf("< 2 > 텍스트 출력 속도 설정");
	printf("< 3 > 애니메이션 속도 설정");
	printf("< 4 > 글씨 색상 설정");
	printf("< 5 > 테두리 모양 설정");
	printf("< 6 > 관리자 모드");
	printf("< 8 > 이전 메뉴로 이동");
	printf("설정하실 메뉴 번호를 입력하세요 : ");
	scanf("%d", &input);
}
void Information_Screen(int x, int y) // 도움말, 제작자 메뉴
{
	gotoxy(x, y);
	printf("< 도움말 >");
	printf("");
	gotoxy(x, y + 20);
	printf("< 만든사람들 >");
	printf("백성진 : ");
	printf("구윤서 : ");
	printf("류호환 : ");
	printf("정찬욱 : ");
	gotoxy(x, y + 30);
	printf("< 기타 >");
	printf("제작 기간 : 2024년 10월 31일 - 2024년 11월 일");
	printf("소속 : 대구 경북산업직업전문학교 ( AI 빅데이터 풀스택 개발자 과정반 - 3 팀 )");
	printf("");
}
void Exit_Screen(int x, int y)
{
	gotoxy(x, y);
	printf("프로그램을 종료합니다.\n");
}

//////////////////////////////////////////////////// 메인 ////////////////////////////////////////////////////////

void main()
{
	//int main_menu_cursor_input = 0; 커서 시스템 적용시 사용할 변수
	//int menu_choice = 1; // 현재 선택한 값
	int menu_select = 0;	// 메인 메뉴 선택 변수
	int cash_select = 1;	// 투입 금액 변수
	char str[50];
	int input = 0;
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);		// 창크기 전체화면
	setcolor(LIGHTWHITE, BLACK);	// 기본 글자 색상
	setcursortype(NORMALCURSOR);		// 커서 타입
	randomize();					// 랜덤함수사용
	Randomize_Doll_Stock(5);		// 재고 랜덤 1~5개 배정
	Intro_Effect();					// 인트로 출력
	cls;


	for (;;)	// 프로그램 시작	// 메인 무한 반복
	{
		start = 0;		// 플래그 변수
		Make_Frame();
		Main_Screen(80, 25); // 메뉴 선택화면 출력 함수
		Cursor_Make(Main_Menu_Cursor);
		
			if (_kbhit())
			{
				input = _getch();
				switch (input)
				{
				case 72: // 윗키
				{
					Cursor_Delete(Main_Menu_Cursor);
					Cursor_Move_Up(Main_Menu_Cursor);
					break;
				}
				case 80: // 아래키
				{
					Cursor_Delete(Main_Menu_Cursor);
					Cursor_Move_Down(Main_Menu_Cursor);
					break;
				}

				}
			}
		switch (menu_select) // 메인 메뉴 선택 [1]
		{
		case 1: // 1번메뉴 인형뽑기 진입 [2]
		{
			start = 0; // 플래그 변수 초기화 //
			for (; start == 0;) // 인형뽑기의 금액투입 반복 구문 [2] (플래그 변수 start가 0 일 경우 무한 실행)
			{
				cls;
				Make_Frame();
				Machine_Screen(); // 인형 목록
				cash_select = Cash_System_Print(80, 35); // 출력 및 입력 받기 함수 좌표에 출력
				Cash_System_Calculate(cash_select, 80, 50); // 계산 및 좌표에 출력

				for (; start == 1;) // 인형뽑기 무한 반복 구문 (플래그 변수가 1 일경우)
				{
					int doll_select = 0;
					cls;
					Make_Frame();
					Machine_Screen();
					doll_select = Machine_System_Print(80, 40); // 해당좌표에 출력
					Machine_System_Activate(doll_select, 80, 49);
				}
				if (start == -1)
				{
					break;
				}
			}// for(;;)
			break;
		} // case 1 인형 뽑기 메뉴 진입

		case 2: // 2번 메뉴 랜덤 뽑기 메뉴 진입
		{

			start = 0; // 플래그 변수 초기화 //
			for (; start == 0;) // 금액 투입 진행
			{
				cls;
				Make_Frame();
				Random_Game_Screen_Print(80, 35); // 확률 표 출력
				cash_select = Cash_System_Print(80, 43); // 출력 및 입력 받기 함수 좌표에 출력
				Cash_System_Calculate(cash_select, 80, 58); // 계산 및 좌표에 출력

				for (; start == 1;) // 랜덤 게임 진행
				{
					int random_menu_select = 0;
					cls;
					Make_Frame();
					Random_Game_Screen_Print(80, 46);
					random_menu_select = Random_Game_Message(80, 43);
					Random_Game_Start(random_menu_select, 80, 50);

				}
				if (start == -1)
				{
					break;
				}
			} // for (start == 0);
			break;
		} // case 2 :



		case 3: // 3번 메뉴 미구현
		{
			break;
		}
		case 4: // 환경설정
		{
			Setting_Screen(80, 20);
			_getch();
			break;
		}
		case 5: // 도움말 // 정보
		{
			cls;
			Information_Screen(80, 20);
			_getch();
			break;
		}
		case 6: // 종료
		{
			cls;
			Exit_Screen(80, 20);
			exit(0);
		}
		default: // 잘못입력된경우 (메인메뉴)
		{
			break;
		}

		} // 메인 메뉴 switch

	} // for(;;) = 메인 메뉴 반복

} // void main ()