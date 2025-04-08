int main_menu_cursor_x = 56; // 메인 메뉴 커서 좌표값 초기화
int main_menu_cursor_y = 20;
int menu_01_cursor_x;
int menu_01_cursor_y;
COLOR_TYPE user_color = LIGHTWHITE;
void Cursor(int x, int y, COLOR_TYPE t, COLOR_TYPE b)
{
	gotoxy(x, y);
	setcolor(t, b);
	printf("▶");
	setcolor(user_color, BLACK);
}



Cursor(main_menu_cursor_x, main_menu_cursor_y, ORANGE, BLACK); // 해당 좌표에 커서 출력


main_menu_cursor_input = _getch();
if (main_menu_cursor_input == 72) // 위 키
{
	main_menu_cursor_y = main_menu_cursor_y - 4;
	menu_choice = menu_choice - 1;
}
else if (main_menu_cursor_input == 80) // 아래 키
{
	main_menu_cursor_y = main_menu_cursor_y + 4;
	menu_choice = menu_choice + 1;
}
else if (main_menu_cursor_input == 13)// 엔터 입력
{

}
else // 다른 입력
{

}

if (main_menu_cursor_y < 20)
{
	main_menu_cursor_y = 20;
	menu_choice = menu_choice + 1;
}
if (main_menu_cursor_y > 40)
{
	main_menu_cursor_y = 40;
	menu_choice = menu_choice - 1;
}