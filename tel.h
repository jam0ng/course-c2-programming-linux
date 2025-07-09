#pragma once

// 이중 연결 리스트의 노드 구조체를 정의
typedef struct ListNode {		// 구조체
	struct ListNode* llink;		// 선행 노드 링크
	char name[30];				// 이름 데이터
	char phone[20];				// 전화번호 데이터
	char memo[50];				// 메모 데이터
	struct ListNode* rlink;		// 다음 노드 링키
} listNode;


typedef struct {				// 리스트 시작을 나타내는 head 노드
	listNode* head;
}  List_h;

// 공백 리스트 생성하는 함수
List_h* createList_h(void);	
// 리스트에 노드를 삽입하는 함수
void insertNode(List_h* List, listNode* pre, char* nameptr, char* phoneptr, char* memoptr);
// 리스트에서 노드를 삭제하는 함수
void deleteNode(List_h* List, listNode* old);
// name을 가지고 리스트에서 찾는 함수
listNode* searchname(List_h* List, char* nameptr);
// 리스트 전체를 메모리 해제하는 함수
void freeList(List_h* List);
// 정렬하는 함수
void bubbleSortList(List_h* List);


//(임시) 프린트 함수
void printList(List_h* List);
