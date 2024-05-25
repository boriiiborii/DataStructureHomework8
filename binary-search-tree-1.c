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


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

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
}

void preorderTraversal(Node* ptr)
{
	//부모부터 프린트 한 뒤 왼쪽노드 프린트, 이후 오른쪽 노드 프린트
}

void postorderTraversal(Node* ptr)
{
	//왼쪽 child노드 프린트 후 오른쪽 차일드 노드 프린트, 이후 부모 프린트
}


int insert(Node* head, int key)
{
	//바이너리서치트리가 존재하지 않으면 h에 ptr을 연결
	//존재 한다면 위치를 찾아서 ptr연결
}

int deleteLeafNode(Node* head, int key)
{
	//리프노드가 아닌걸 삭제하려고 한다면 
	//"the node [노드값] is not a leaf" 출력
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

    // 왼쪽과 오른쪽 노드를 해제 한 후 본인(현재파라미터 head)을 해제. 
	//(모든 노드를 삭제해야하기 때문에 재귀처리)
    freeBST(head->left);
    freeBST(head->right);
    free(head);
}





