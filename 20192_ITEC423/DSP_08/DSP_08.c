// DSP_08_2018112749.c
// 2018112749 ������

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

FILE *fp1, *fp2;

typedef struct element {
	int key;
} element;

typedef struct treeNode* treePointer;
typedef struct treeNode {
	treePointer leftChild;
	treePointer rightChild;
	int bf;
	element data;
} treeNode;

void inorder(treePointer ptr) {  // inorder traversal
	if (ptr) {
		inorder(ptr->leftChild);
		fprintf(fp2, "%d(%d) ", ptr->data.key, ptr->bf);
		inorder(ptr->rightChild);
	}
}

void preorder(treePointer ptr) {  // preorder traversal
	if (ptr) {
		fprintf(fp2, "%d(%d) ", ptr->data.key, ptr->bf);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void leftRotation(treePointer *parent, int *unbalanced) {
	treePointer grandChild, child;
	child = (*parent)->leftChild;  // child: ���� ����� ���� �ڽ�
	if (child->bf == 1) {  // ���� �ڽĵ� left�� �ϳ��� �� ���� ���
		// LL Rotation
		(*parent)->leftChild = child->rightChild;
		child->rightChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}
	else {  // ���� �ڽ��� right�� �ϳ� �� ������ ���� ���
		// LR Rotation
		grandChild = child->rightChild;
		child->rightChild = grandChild->leftChild;
		grandChild->leftChild = child;
		(*parent)->leftChild = grandChild->rightChild;
		grandChild->rightChild = *parent;  // PPT�� ����
		
		switch (grandChild->bf) {
		case 1:
			(*parent)->bf = -1;
			child->bf = 0;
			break;
		case 0:
			(*parent)->bf = 0;
			child->bf = 0;
			break;
		case -1:
			(*parent)->bf = 0;
			child->bf = 1;
		}
		*parent = grandChild;
	}
	(*parent)->bf = 0;
	*unbalanced = FALSE;
}

// leftRotation�� ������ �Ȱ��� ���⸸ �޶� �ּ��� �����մϴ�.
void rightRotation(treePointer *parent, int *unbalanced) {
	treePointer grandChild, child;
	child = (*parent)->rightChild;
	if (child->bf == -1) {
		(*parent)->rightChild = child->leftChild;
		child->leftChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}
	else {
		grandChild = child->leftChild;
		child->leftChild = grandChild->rightChild;
		grandChild->rightChild = child;
		(*parent)->rightChild = grandChild->leftChild;
		grandChild->leftChild = *parent;  // PPT�� ����

		switch (grandChild->bf) {
		case 1:
			(*parent)->bf = -1;
			child->bf = 0;
			break;
		case 0:
			(*parent)->bf = 0;
			child->bf = 0;
			break;
		case -1:
			(*parent)->bf = 0;
			child->bf = 1;
		}
		*parent = grandChild;
	}
	(*parent)->bf = 0;
	*unbalanced = FALSE;
}

void avlInsert(treePointer *parent, element x, int *unbalanced) {
	if (!*parent) {  // �� �ڸ��� ��尡 ���� ���
		*unbalanced = TRUE;
		*parent = (treePointer)malloc(sizeof(treeNode));
		(*parent)->leftChild = (*parent)->rightChild = NULL;
		(*parent)->bf = 0; (*parent)->data = x;
	}
	else if (x.key < (*parent)->data.key) {
		// �����Ϸ��� key�� �� ���� ���, leftChild�� insert
		avlInsert(&(*parent)->leftChild, x, unbalanced);
		if (*unbalanced) {  // �ö󰡸鼭 �θ� ����� bf ����
			switch ((*parent)->bf) {
			case -1: 
				(*parent)->bf = 0;
				*unbalanced = FALSE;  // bf�� 0�� �Ǿ����Ƿ� unbalanced = FALSE;
				break;
			case 0:
				(*parent)->bf = 1;
				break;
			case 1:  // bf�� 2�� �ǹǷ� leftRotation
				leftRotation(parent, unbalanced);
			}
		}
	}
	else if (x.key > (*parent)->data.key) {
		// �����Ϸ��� key�� �� Ŭ ���, rightChild�� insert
		avlInsert(&(*parent)->rightChild, x, unbalanced);
		if (*unbalanced) {
			switch ((*parent)->bf) {
			case 1:
				(*parent)->bf = 0;
				*unbalanced = FALSE;
				break;
			case 0:
				(*parent)->bf = -1;
				break;
			case -1:  // bf�� -2�� �ǹǷ� rightRotation
				rightRotation(parent, unbalanced);
			}
		}
	}
	else {
		*unbalanced = FALSE;
		printf("The key is already in the tree\n");
	}
}

int main(int argc, char* argv[]) {
	int n;  // key ����
	int i;
	element tmp;  // �Է¹޴� �뵵
	int ub_tmp;
	treePointer tree = NULL;  // AVL tree

	fp1 = fopen(argv[1], "r");  // argv[1] : input filename
	fp2 = fopen(argv[2], "w");  // argv[2] : output filename

	fscanf(fp1, "%d", &n);
	for (i = 0; i < n; i++) {
		fscanf(fp1, "%d", &tmp.key);
		avlInsert(&tree, tmp, &ub_tmp);

		fprintf(fp2, "AVL Tree:\n");
		fprintf(fp2, "Preorder: ");
		preorder(tree);
		fprintf(fp2, "\nInorder: ");
		inorder(tree);
		fprintf(fp2, "\n");
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}