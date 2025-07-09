#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tel.h"

// 공백 연결 리스트를 생성하는 함수
List_h* createList_h(void){
	List_h* List;
	List = (List_h*)malloc(sizeof(List_h));		// 메모리 할당
	List->head = NULL;							// head에 NULL 저장(공백이므로)
	return List;
}

// (임시 출력 함수)
void printList(List_h* List){
	listNode* p = List->head;
	printf(" List = (");
	while(p != NULL){
		printf("%s:%s:%s", p->name, p->phone, p->memo);
		p = p->rlink;
		if (p != NULL) printf("\n");
	}
	printf(") \n");
}

// 리스트에 노드를 삽입하는 함수
void insertNode(List_h* List, listNode* pre, char* nameptr, char* phoneptr, char* memoptr) {
	listNode* newNode = (listNode*)malloc(sizeof(listNode));  // 새 노드 메모리 할당
	strcpy(newNode->name, nameptr);  // 이름 저장
	strcpy(newNode->phone, phoneptr);  // 전화번호 저장
	strcpy(newNode->memo, memoptr);  // 메모 저장
	newNode->llink = NULL;
	newNode->rlink = NULL;

	if (List->head == NULL) {  // 공백 리스트라면
		List->head = newNode;  // List head가 newNode를 가리키게 함
	}
	else {
		listNode* p = pre;
		if (p == NULL) {  // pre가 NULL이면 리스트 끝에 삽입
			p = List->head;
			while (p->rlink != NULL) {  // 리스트 끝으로 이동
				p = p->rlink;
			}
			p->rlink = newNode;
			newNode->llink = p;
		}
		else {  // pre가 지정된 위치 뒤에 삽입
			newNode->rlink = p->rlink;
			if (p->rlink != NULL) {
				p->rlink->llink = newNode;
			}
			p->rlink = newNode;
			newNode->llink = p;
		}
	}
}


// 리스트에 노드를 삭제하는 함수
void deleteNode(List_h* List, listNode* old){
	if(List->head == NULL || old == NULL) return;	// 공백 리스트인 경우와 삭제할 노드가 없는 경우 - 함수 종료
	
	if (old == List->head) {						// 삭제할 노드가 헤드 노드인 경우		
		List->head = old->rlink;					// 헤드 노드를 다음 노드로 변경
		if(List->head != NULL) {					// 다음 노드가 존재하면
			List->head->llink = NULL;				// 다음 노드의 llink를 NULL로 설정
		}
	}
	else {
		if (old->llink != NULL) {					// 이전 노드가 있는 경우
			old->llink->rlink = old->rlink;			// 이전 노드의 rlink를 현재 노드의 rlink로 설정
		}
		if (old->rlink != NULL) {					// 다음 노드가 있는 경우
			old->rlink->llink = old->llink;			// 다음 노드의 llink를 현재 노드의 llink로 설정
		}
	}
	free(old);										// 현재 노드 메모리 해제
}

// name을 가지고 리스트에서 찾는 함수
listNode* searchname(List_h* List, char* nameptr){
	listNode* temp;									// 이동하면서 x노드를 찾는 노드 포인터 temp
	temp = List->head;								
	while (temp != NULL) {							// 리스트가 공백이거나, 끝에 도달할 때까지
		if (strcmp(temp->name, nameptr) == 0) return temp;		// 찾았을 때 - temp 리턴 
		else temp = temp->rlink;								// 아니라면 temp을 다음 노드로 전진
	}
	return NULL;											// 값이 없는 경우
}

// 리스트 전체를 메모리 해제하는 함수
void freeList(List_h* List){
	listNode* p;
	while (List->head != NULL) {
		p = List->head;
		List->head = List->head->rlink;
		free(p);
		p = NULL;
	}
}


// 노드 교환 함수
void swap(listNode* p, listNode* q){         
	if (p == q) return;						// 같은 노드를 교환할 필요가 없으므로

    // name 필드 교환
    char tempName[30];
    strcpy(tempName, p->name);
    strcpy(p->name, q->name);
    strcpy(q->name, tempName);

    // phone 필드 교환
    char tempPhone[20];
    strcpy(tempPhone, p->phone);
    strcpy(p->phone, q->phone);
    strcpy(q->phone, tempPhone);

    // memo 필드 교환
    char tempMemo[50];
    strcpy(tempMemo, p->memo);
    strcpy(p->memo, q->memo);
    strcpy(q->memo, tempMemo);

}

// 리스트를 버블 정렬하는 함수
void bubbleSortList(List_h* List) {
    if (List->head == NULL) return;

    int swapped;
    listNode* p;
    listNode* q = NULL;

    do {
        swapped = 0;
        p = List->head;

        while (p->rlink != q) {
            if (strcmp(p->name, p->rlink->name) > 0) {
                // 노드 데이터 교환
                swap(p, p->rlink);
                swapped = 1;
            }
            p = p->rlink;
        }
        q = p;
    } while (swapped);
}
