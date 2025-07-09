#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "tel.h"

#define MAX 100

int main()
{
	char name[30];
	char phone[20];
	char memo[50];

	List_h* List;
	List = createList_h();

	FILE* file = fopen("data.txt", "r");
	if (file == NULL) {
		printf("Could not open file. The program will continue without loading data.\n");
		return 0;
	}
	
	char line[MAX];
	while (fgets(line, MAX, file) != NULL) {
		char* name = strtok(line, ":");
		char* phone = strtok(NULL, ":");
		char* memo = strtok(NULL, ":");
	       
		name[strcspn(name, " \n")] = '\0';
		phone[strcspn(phone, " \n")] = '\0';
	    memo[strcspn(memo, " \n")] = '\0';

		insertNode(List, NULL, name, phone, memo);	
	}


	// 테스트 용
	listNode* p;
	char name1[] = "yoon";
	char phone1[] = "010-9093-0352";
	char memo1[] = "test telbook";

	char name2[] = "kim min su";
	char phone2[] = "010-9196-0132";
	char memo2[] = "test telbook2222!!!";
	
	printf("테스트\n");
	printList(List);
	
	printf("추가 name1\n");
	insertNode(List, NULL, name1, phone1, memo1);
	printList(List);
	
	printf("추가 name2\n");
	insertNode(List, NULL, name2, phone2, memo2);
	printList(List);

	printf("정렬\n");
	bubbleSortList(List);
	printList(List);

	printf("탐색\n");
	p = searchname(List, name1);
	printf("탐색한 결과: %s:%s:%s\n", p->name, p->phone, p->memo);
	
	printf("삭제\n");
	deleteNode(List, p);
	printList(List);
	
	printf("프리\n");
	freeList(List);
	printList(List);

	getchar();

	fclose(file);
	// 여기까지 나중에 삭제



/*    WINDOW *menu_win; // 메뉴를 출력할 윈도우 객체
    int highlight = 1; // 현재 하이라이트된 메뉴 항목을 추적
    int choice = 0; // 사용자가 선택한 메뉴 항목 번호
    int c; // 사용자의 키보드 입력을 임시 저장하는 변수

    initscr(); // ncurses모드 시작
    clear();
    noecho(); // 사용자 입력 키 화면 표시 x
    cbreak(); // 입력 버퍼 무시, 사용자 입력을 즉시 프로그램에 전달

    // 색상 초기화
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // 쌍1: 초록색
    init_pair(2, COLOR_BLUE, COLOR_BLACK);  // 쌍2: 파란색

    int Mx, My;
    getmaxyx(stdscr, My, Mx); // 현재 화면의 크기를 가져옴

    //새 윈도우를 만들고 이를 menu_win에 할당
    menu_win = newwin(9, Mx - 5, 6, 0);

    //menu_win에서 키보드 입력을 가져올 수 있게 설정
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Welcome to the TelBook Program with ncurses.\n");
    mvprintw(1, 0, "Please, select an operation from the menu:\n");
    mvprintw(2, 0, "1. Search - Find the phone number and memo by name.\n");
    mvprintw(3, 0, "2. Add - Create a new entry with name, phone number, and memo.\n");
    mvprintw(4, 0, "3. Delete - Remove an entry by content.\n");
    mvprintw(5, 0, "4. List - Sort and display all entries.\n");
    refresh();

    print_menu(menu_win, highlight); // 초기 메뉴 화면

    while (1) {
        c = wgetch(menu_win); // 키보드 입력을 가져옴
        switch (c) {
        case KEY_UP: // 사용자가 위쪽 화살표를 눌렀을때
            if (highlight == 1) // 첫 옵션이 하이라이트 되어있으면 
                highlight = n_choices; // 마지막 옵션을 하이라이트
            else
                --highlight; // 그렇지 않다면 하이라이트를 위로 옮김
            break;
        case KEY_DOWN:
            if (highlight == n_choices)
                highlight = 1; // 마지막 옵션이 하이라이트 되어있으면 첫번째 옵션을 하이라이트
            else
                ++highlight; // 그렇지 않으면 하이라이트를 아래로
            break;
        case 10:
            choice = highlight; // 사용자가 enter 키를 눌렀을때
            break;
        default:
            mvprintw(15, 0, "The pressed key is: '%c'", c);
            refresh();
            break;
        }
	// 하이라이트 위치가 바꼈을 수도 있으므로 메뉴 다시 출력
        print_menu(menu_win, highlight); 
        if (choice != 0) // 선택 완료시 루프 종료
            break;
    }
 // 사용자가 선택한 메뉴 항목을 화면에 출력
    mvprintw(16, 0, "You chose choice %d with choice string %s\n", choice, choices[choice-1]);
    clrtoeol();
    refresh();
    
    //선택된 메뉴 항목에 따라 각각 다른 작업을 수행
    if (choice == 1){
        char searchT[10]; // search 메뉴 선택시
	move(17,0);
        attron(COLOR_PAIR(1) | A_BOLD);
        printw("Enter the string you want to search: ");
        attroff(COLOR_PAIR(1));
	getstr(searchT);
	mvprintw(18,20, "Searching for entries with '%s'", searchT);
        attroff(A_BOLD);
       	search_tel("data.txt", searchT);
    } 
    else if (choice == 2) { // add 메뉴 선택시
        char name[30];
		char phone[20];
		char memo[50];

        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(17, 0, "Enter name: ");
        getstr(name);
        mvprintw(18, 0, "Enter phone: ");
        getstr(phone);
        mvprintw(19, 0, "Enter memo: ");
        getstr(memo);
        mvprintw(21, 0, "Name: %s", name);
        mvprintw(22, 0, "Phone: %s", phone);
        mvprintw(23, 0, "Memo: %s", memo);

        mvprintw(25, 0, "Are you sure you want to add this entry? (y/n): ");
        char answer[3];
        getstr(answer);
        attroff(A_BOLD);

        if (answer[0] == 'y' || answer[0] == 'Y') {
            insertNode(List, NULL, name, phone, memo);
            mvprintw(26, 0, "Added success");
        }
        else {
            mvprintw(26, 0, "canceled");
        }
        attroff(A_BOLD);
    }
    else if (choice == 3) { // delete 메뉴 선택시
        char name[30];
		listNode* p;
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(17, 0, "Enter name to delete: ");
        attroff(COLOR_PAIR(1));
	getstr(name);
	mvprintw(17,20, "%s", name);
	attroff(A_BOLD);
		p = searchname(List, name);
        deleteNode(List, p);
    }
    else if (choice == 4) { // list 메뉴 선택시
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(17, 0, "List of TelBook entries:\n");
        attroff(A_BOLD);
        //print_list("data.txt"); 구현필요
        mvprintw(27, 0, "List operation completed.");
    }

    mvprintw(My-1, 0, "Press any Key for Exit screen");
    getch();
    endwin();*/
    return 0;
}

/* void print_menu(WINDOW *menu_win, int highlight)
{
    int x, y, i;
    int Mx, My;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    mvwprintw(menu_win,0,1,"Select One");
    for(i=0 ; i < n_choices; ++i) {
        if(highlight == i+1) { // 현재 하이라이트 된 옵션인 경우
            wattron(menu_win, A_REVERSE); // 해당 메뉴의 반전된 색상을 적용하여 강조
            mvwprintw(menu_win, y, x, "%s", choices[i]); // 메뉴 옵션 문자열 출력
            wattroff(menu_win, A_REVERSE); //색상 반전 off
        } else // 하이라이트 되지 않은 옵션은 일반 색으로 출력
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y; //다음줄로 이동
    }
    wrefresh(menu_win); // 메뉴 윈도우를 화면에 출력
} */
