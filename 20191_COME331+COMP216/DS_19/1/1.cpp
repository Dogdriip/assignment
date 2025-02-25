/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

// 53~56행에서 RLV, LRV 방식 변경이 가능합니다.

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_ELEMENTS 100

typedef struct {
	int key;
} element;

int n;

int listMerge(element a[], int link[], int start1, int start2) {
	int last1, last2, lastResult = 0;
	int i;
	for (last1 = start1, last2 = start2; last1 && last2;) {
		if (a[last1].key <= a[last2].key) {
			link[lastResult] = last1;
			lastResult = last1; last1 = link[last1];
		}
		else {
			link[lastResult] = last2;
			lastResult = last2; last2 = link[last2];
		}
	}

	if (last1 == 0) link[lastResult] = last2;
	else link[lastResult] = last1;

	printf("\nlistMerge(a, link, %d, %d)\n", start1, start2);
	printf("%6s", "");
	for (i = 0; i <= n; i++) printf("[%2d]", i);
	printf("\n%6s", "link:");
	for (i = 0; i <= n; i++) printf("%4d", link[i]);
	printf("\n%6s", "a:");
	for (i = 0; i <= n; i++) (i ? printf("%4d", a[i].key) : printf("%4c", '-'));
	printf("\n\n");

	return link[0];
}

int rmergeSort(element a[], int link[], int left, int right) {
	int mid;
	printf("rmergeSort(a, link, %d, %d)\n", left, right);

	if (left >= right) return left;
	mid = (left + right) / 2;
	
	// RLV
	return listMerge(a, link, rmergeSort(a, link, left, mid), rmergeSort(a, link, mid + 1, right));
	// LRV
	// return listMerge(a, link, rmergeSort(a, link, mid + 1, right), rmergeSort(a, link, left, mid));
}

void printList(element a[], int link[]) {
	int i;
	for (i = 0; link[i];) {
		printf("%d ", a[link[i]].key);
		i = link[i];
	}
}

int main() {
	element a[MAX_ELEMENTS];
	int link[MAX_ELEMENTS];
	int i;
	FILE *fp = fopen("input.txt", "r");
	
	fscanf(fp, "%d", &n);
	for (i = 1; i <= n; i++) {
		fscanf(fp, "%d", &a[i].key);
	}

	memset(link, 0, sizeof(link));
	printf("<<<<<<<< starting from initial %d chains. >>>>>>>>\n", n);
	printf("<<<<<<<< each of which has one node >>>>>>>>\n");
	
	printf("%6s", "");
	for (i = 0; i <= n; i++) printf("[%2d]", i);
	printf("\n%6s", "link:");
	for (i = 0; i <= n; i++) printf("%4d", link[i]);
	printf("\n%6s", "a:");
	for (i = 0; i <= n; i++) (i ? printf("%4d", a[i].key) : printf("%4c", '-'));

	printf("\n\n<<<<<<<< executing recursive merge sort >>>>>>>>\n");
	rmergeSort(a, link, 1, 10);
	
	printf("<<<<<<<< Sorted List >>>>>>>>\n");
	printList(a, link);
	printf("\n\n");

	return 0;
}