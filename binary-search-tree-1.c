/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
 
/* you may add your own defined functions if necessary */

//트리가 비어있는지를 확인하는 메서드. 
int isEmptyTree(Node* head);


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	//매번 실행할때 initializeBST를 필히 실행해야함으로 main이 시작될때 먼저 실행시켜놓았습니다.
	initializeBST(&head);

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("          [----- [LeeHwaJin]  [2020037103] -----]               \n"); //학번이름 프린트
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);//시작할때 초기화시키는 함수라서 할당이 되어있으면 당연히 풀어주어야 함.

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */ //얘가 널이 아니면 바이너리서치트리가 존재. 널이면 아무값이없음.
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	//왼쪽노드 프린트 후 부모 프린트, 이후 왼쪽노드 프린트
	if(ptr != NULL) {
        inorderTraversal(ptr->left);
        printf("%d ", ptr->key);
        inorderTraversal(ptr->right);
    }
}

void preorderTraversal(Node* ptr)
{
	//부모부터 프린트 한 뒤 왼쪽노드 프린트, 이후 오른쪽 노드 프린트
	if(ptr != NULL) {
        printf("%d ", ptr->key);
        preorderTraversal(ptr->left);
        preorderTraversal(ptr->right);
    }
}

void postorderTraversal(Node* ptr)
{
	//왼쪽 child노드 프린트 후 오른쪽 차일드 노드 프린트, 이후 부모 프린트
	if(ptr != NULL) {
        postorderTraversal(ptr->left);
        postorderTraversal(ptr->right);
        printf("%d ", ptr->key);
    }
}


int insert(Node* head, int key)
{
	//일단 해당 키를 값으로 갖는 노드를 동적할당하여 만들기
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
    newNode->right = NULL;

	//바이너리서치트리가 존재하지 않으면 h에 ptr을 연결
	if((head->left) == NULL) {
		head->left = newNode;
		return 0;
	}else {
		//존재 한다면 위치를 찾아서 ptr연결
		//위치 찾기: 반복하여 헤드보다 크면 오른쪽 작으면 왼쪽으로 .. 들어가서 처리하는 방식 진행예정
		// 존재한다면 위치를 찾아서 ptr 연결
		Node* parent = NULL;
		Node* current = head->left;
		// current노드가 NULL이 될때까지 돌려서 현재 위치를 찾아감
		while (current != NULL) {
			parent = current;
			//파라미터로 받은 값이 currentKey보다 작을때는 왼쪽으로 current노드를 본인의 left노드로 제새팅하고 while문 재실행
			if (key < current->key) {
				current = current->left;
			//파라미터로 받은 값이 currentKey보다 클때는 오른쪽으로 current노드를 본인의 right노드로 제새팅하고 while문 재실행
			} else if (key > current->key) {
				current = current->right;
			} else {
				// 입력받았던 키와 current->key의 값과 같은 경우(중복값) 만들었던 노드 해제시키고 끝냄
				free(newNode);
				printf("중복된 코드입니다.");
				//아예 메서드를 끝내버림
				return 0;
			}
    	}
		// while문이 끝난다면 == currentNode가 NULL이라면 (parent의 key가 들어갈 child노드가 없다면)
		// 부모노드를 기준으로 키값이 작으면 왼쪽으로 크다면 오른쪽으로 연결
		if (key < parent->key) {
			parent->left = newNode;
		} else {
			parent->right = newNode;
		}
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
    // 트리가 비어있는지를 확인
    if (isEmptyTree(head)) {
        return 0;
    }

    Node* parentNode = NULL;
    Node* currentNode = head->left;

    // 파라미터로 들어왔던 key값의 노드 찾기
    while (currentNode != NULL) {
        if (key == currentNode->key) {
            // 해당 노드를 찾았으므로 break 처리해서 반복문 빠져나오기
            break;
        } else if (key < currentNode->key) {
            parentNode = currentNode;
            currentNode = currentNode->left;
        } else {
            parentNode = currentNode;
            currentNode = currentNode->right;
        }
    }

    // 반복문을 다 돌았는데도 currentNode가 NULL이라면 해당 트리에 key값을 가진 노드가 없는 것임
    if (currentNode == NULL) {
        printf("Cannot find the node [%d]\n", key);
        return 0;
    }

    // 리프 노드가 아닌 경우
    if (currentNode->left != NULL || currentNode->right != NULL) {
        printf("the node [%d] is not a leaf\n", key);
        return 0;
    }

    // 리프 노드를 찾았으니 삭제하는 로직
    if (parentNode != NULL) {
        if (parentNode->left == currentNode) {
            parentNode->left = NULL;
        } else {
            parentNode->right = NULL;
        }
    } else {
        // 루트노드가 리프노드였을 경우
        head->left = NULL;
    }
	
	//freeBST를사용할 필요가 없는 이유: 리프노드 확정이라 차일드 노드가 없기 때문에
	//현재 노드만 free처리 해주면 되니까. 
    free(currentNode);
    return 0;
}


Node* searchRecursive(Node* ptr, int key)
{
	//print되어야하는게 node[노드값] found at 노드의 주소
	//또는 cannot find the noe[노드값]
}

Node* searchIterative(Node* head, int key)
{
	//print되어야하는게 node[노드값] found at 노드의 주소
	//또는 cannot find the noe[노드값]
}


int freeBST(Node* head)
{
	//initializeBST()할때 할당 된 노드가 있다면 해제시켜주는 코드 작성해야함   
	//말고도 delete노드할때도 해줘야함. 

    // 왼쪽과 오른쪽 노드를 해제 한 후 본인(현재파라미터 head)을 해제. 
	//(모든 노드를 삭제해야하기 때문에 재귀처리)
    freeBST(head->left);
    freeBST(head->right);
    free(head);
}

//트리가 비어있는지를 확인하는 메서드. 
int isEmptyTree(Node* head) {
	if (head == NULL || head->left == NULL) {
        printf("Tree is empty.\n");
        return 1;
    }
	return 0;
}
