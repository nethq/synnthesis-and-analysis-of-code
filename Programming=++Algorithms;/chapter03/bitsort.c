#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 100

struct CElem {
  int key;
  /* .............
     ������� �����
     ............. */
};

struct CList {
  struct CElem data;
  struct CList *next;
};

struct CList *init(unsigned n) /* ������� ������ ��� �������� ���� ����� */
{ struct CList *head, *p;
  unsigned i;
  srand(time(NULL));
  for (head = NULL, i = 0; i < n; i++) {
    p = (struct CList *) malloc(sizeof(struct CList));
    p->data.key = rand();
    assert(p->data.key);
    p->next = head;
    head = p;
  }
  return head;
}

struct CList *bitSort(struct CList *head)
{ struct CList *zeroEnd, *oneEnd, *zero, *one;
  unsigned maxBit, bitPow2;

  /* 0. ���������� �� ������������ ������ ����� */
  maxBit = 1 << (8*sizeof(head->data.key)-1);

  /* 1. �������� ������� � �������� �� ��������� */
  zero = (struct CList *) malloc(sizeof(struct CList));
  one  = (struct CList *) malloc(sizeof(struct CList));

  /* 2. ��������� */
  for (bitPow2 = 1; bitPow2 < maxBit; bitPow2 <<= 1) {

    /* 2.1. ������������ �� ������� */
    for (zeroEnd = zero, oneEnd = one; NULL != head; head = head->next)
      if (!(head->data.key & bitPow2)) {
        zeroEnd->next = head;
	    zeroEnd = zeroEnd->next;
      }
      else {
        oneEnd->next = head;
        oneEnd = oneEnd->next;
      }

    /* 2.2. ���������� �� ��������� */
    oneEnd->next = NULL;
    zeroEnd->next = one->next;
    head = zero->next;
  }

  /* 3. ������������� �� ������� */
  free(zero);
  free(one);

  return head;
}

void print(struct CList *head)
{ for (; NULL != head; head = head->next)
    printf("%8d", head->data.key);
  printf("\n");
}

void check(struct CList *head)
{ if (NULL == head)
    return;
  for (; NULL != head->next; head = head->next)
    assert(head->data.key <= head->next->data.key);
}

void clear(struct CList *head)
{ struct CList *p = head;
  while (NULL != head) {
    head = (p = head)->next;
    free(p);
  }
}

int main(void) {
  struct CList *head;
  head = init(MAX);
  printf("������� ����� �����������:\n");
  print(head);
  head = bitSort(head);
  printf("������� ���� �����������:\n");
  print(head);
  check(head);
  clear(head);
  return 0;
}