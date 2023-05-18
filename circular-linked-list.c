/* circular-linked-list.c
 *  이중 순환 연결 리스트
 *
 * 자료구조 8번째 과제
 * 충북대학교 2017015040 물리학과 강수
 */

#include<stdio.h>
#include<stdlib.h>

//이중노드
typedef struct Node {
	int key;//값
	struct Node* llink;//전노드,왼쪽 노드 링크
	struct Node* rlink;//후노드,오른쪽 노드 링크
} listNode;


//함수
int initialize(listNode** h);//초기화
int freeList(listNode* h);//메모리 해지

int insertLast(listNode* h, int key);//마지막에 노드 추가
int deleteLast(listNode* h);//마지막 노드 제거

int insertFirst(listNode* h, int key);// 처음에 노드 추가
int deleteFirst(listNode* h);//처음 노드 제거

int invertList(listNode* h);//역순

int insertNode(listNode* h, int key);//노드추가
int deleteNode(listNode* h, int key);//노드제거

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	printf("[----- [kang su] [2017015040] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;
}

//초기화
int initialize(listNode** h) {

	//기존 노드가 있을 경우 초기화
    if(*h != NULL)
		freeList(*h);

	//시작노드를 가르키는 주소할당
	*h = (listNode*)malloc(sizeof(listNode));//주소할당
	(*h)->rlink = *h;//처음 노드
	(*h)->llink = *h;//마지막 노드
	(*h)->key = -9999;//초기화
	return 1;
}

//전체 노드 해지
int freeList(listNode* h){
    
    listNode*p;//노드
	listNode* perv;//전 노드

	p = h->rlink;//첫 노드로 이동
	while(p != NULL && p != h) {//노드 있고 헤드 노드가 아닌경우 
        perv=p;//전노드 등록
		p = p->rlink;//다음노드로 이동
		free(perv);
	}
    free(h);

	return 0;
}



void printList(listNode* h) {
	int i = 0;//노드번호 0번부터 유효 노드
	listNode* p;//노드

	printf("\n---PRINT\n");

	if(h == NULL) {//초기화 전
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;//첫 노드로 이동

	while(p != NULL && p != h) {//노드 있고 헤드 노드가 아닌경우 
		printf("[ [%d]=%d ] ", i, p->key);//노드와 값출력
		p = p->rlink;//다음노드로 이동
		i++;
	}
	printf("  items = %d\n", i);

    //--이후 주소출력--
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
    //헤드노드 좌-자신-우 링크 주소 
	i = 0;
	p = h->rlink;//초기노드
	while(p != NULL && p != h) {//없거나 헤드노드
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		//이후노드 좌-자신-우 링크주소
        p = p->rlink;
		i++;
	}

}



//마지막에 노드추가
int insertLast(listNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode));//노드생성
	node->key = key;//노드 값 배정

    listNode* n = h->rlink;//처음노드 부터시작 ,n=h 경우 n=h
	while(n->rlink!= h) {//헤드노드 전에서 정지 ,n=h 경우 n=h
	    n = n->rlink;//다음 노드로 이동
	}
    //n은 지금 헤드노드 왼쪽노드, n=h 경우 n=h

	h->llink = node;//바꿀 노드는 헤드 노드의 왼쪽=추가된 노드, n=h의 경우 hL=node 
	node->rlink = h;//추가된 노드 우=헤드노드, n=h 경우 nodeR=h
    node->llink = n;//그리고 추가된 노드의 좌=헤드노드 왼쪽노드, n=h 경우 nodeL=h 
    n->rlink=node;//헤드 노드의 왼쪽노드의 오른쪽=추가된노드, n=h 경우 h=nodeR


	return 0;
}


//마지막 노드 제거
int deleteLast(listNode* h) {

	if (h->rlink == h)//지울 노드가 없는 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	//지울 노드가 있는경우

    listNode* n = h->rlink;//처음노드 부터시작 
	while(n->rlink!= h) {//헤드노드 전에서 정지 
	    n = n->rlink;//다음 노드로 이동
	}
    //n은 지금 헤드노드 왼쪽노드,노드가 하나인 경우 n->llink-h
    
    n->llink->rlink=h;//n의 전노드(n->llink,h)의 오른쪽(->rlink)은= h,노드가 하나인 경우 h->rlink=h
    h->llink=n->llink;//h의 왼쪽은 n의 전노드(n->llink,h),노드가 하나인 경우 h->llink=h

    free(n);//n의 메모리 해지

	return 0;
}


//처음 노드 추가
int insertFirst(listNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode));//노드생성
	node->key = key;//노드 값 배정

    listNode* n = h->rlink;//n은 첫노드,노드가 없을경우 n=h

	h->rlink = node;//h(헤드노드)R=node
	node->llink = h;//새노드L=h(헤드노드)
    node->rlink = n;//새노드R=n(첫노드)
    n->llink=node;//n(첫노드)L=새노드

	return 0;
}

//처음노드 제거
int deleteFirst(listNode* h) {

	if (h->rlink == h)//지울 노드가 없는 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	//지울 노드가 있는경우

    listNode* n = h->rlink;//처음노드 부터시작, 노드가 없을경우 n=h

    h->rlink=n->rlink;//h(헤드 노드)R=nR(n->rlink,h),노드가 하나인 경우 n->rlink=h
    n->rlink->llink=h;//nR(후 노드)의 L(전 노드)=h

    free(n);//n의 메모리 해지

	return 0;
}


//노드순서를 역으로
int invertList(listNode* h) {

	listNode *n = h;//헤드 노드부터 수정
	listNode *bnode = NULL;//백업노드
	
    //1회 초기 실행으로 헤드노드 처리
    do{
        bnode=n->rlink;//nR백업
		n->rlink=n->llink;//nR=nL
		n->llink=bnode;//nL=nR백업
		n=bnode;//nR백업으로 이동
	}while(n!=h);
	//마지막으로 헤드노드에서 정지


	return 0;
}



//노드 추가
int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));//노드생성
	node->key = key;//노드에 입력한 값을 저장한다

	if (h->rlink == h)//노드가 없는 경우
	{
		h->rlink = node;//h(헤드노드)R=node
		node->llink = h;//새노드L=h
    	node->rlink = h;//새노드R=h
	    h->llink=node;//n(첫노드)L=새노드

		return 0;
	}

	//노드가 있는 경우
    listNode* n = h;//처음노드 부터시작 
	while(n->rlink->key < key&&n->rlink!=h) {
		//해당 노드의 다음 노드의 값과 비교해서 큰경우,오른쪽 노드가 헤드노드가 아닌경우
	    n = n->rlink;//다음 노드로 이동
		//printf("%p \n",n);
	}
	//n은 node보다 작은 수 ,n=node의 전노드
	
	n->rlink->llink=node;//nR(node의 후노드)L=node
	node->rlink=n->rlink;//nodeR=nR(node의 후노드)
	n->rlink=node;//nR=node, nR데이터 변경
	node->llink=n;//nodeL=n
   
	return 0;
}

//삭제
int deleteNode(listNode* h, int key) {
	int samevl =1;//같은값이 있으면 0 없으면 1
	if (h->rlink == h)//지울 노드가 없는 경우
	{
		printf("nothing to delete node.\n");
		return 0;
	}

	//지울 노드가 있는경우

    listNode* n = h->rlink;//처음노드 부터시작
	while(n!=h) {//해당 노드와 비교해서 같지않거나 노드의 오른쪽이 후노드가 아닌경우
	

		if(n->key == key){//같은 값이 있는 경우 n은 지울노드
			n->llink->rlink=n->rlink;//nL(지울노드의 전노드)R(의 오른쪽)=nR(지울노드의 오른쪽 노드)
			n->rlink->llink=n->llink;//nR(지울노드의 후노드)L(의 왼쪽)=nL(지울노드의 왼쪽노드)
			free(n);//n의 메모리 해지
			samevl=0;//if문이 작동한 경우
			printf("delete %d\n",key);
		}
		    n = n->rlink;//다음 노드로 이동

	}
	
	if(samevl){//값이 틀렸고 오른쪽이 후노드인경우
		printf("nothing to delete same node.\n");
	}



	return 0;
}

