#include <stdio.h>
#define MAX 10

typedef int data;
data stack[MAX];
int top;

void init(void) { top = 0; }

void push(data i)
{ if (MAX == top)
    fprintf(stderr, "РџСЂРµРїСЉР»РІР°РЅРµ РЅР° СЃС‚РµРєР°! \n");
  else
    stack[top++] = i;
}

data pop(void)
{ if (0 == top) {
    fprintf(stderr, "РЎС‚РµРєСЉС‚ Рµ РїСЂР°Р·РµРЅ! \n");
    return 0;
  }
  else
    return stack[--top];
}

int empty(void) { return (0 == top); } 

int main(void) {
  data p;
  init();

  /* Р§РµС‚Р°С‚ СЃРµ С†РµР»Рё С‡РёСЃР»Р° РѕС‚ РєР»Р°РІРёР°С‚СѓСЂР°С‚Р° РґРѕ РїСЂРѕС‡РёС‚Р°РЅРµ РЅР° 0 Рё СЃРµ РІРєР»СЋС‡РІР°С‚ РІ СЃС‚РµРєР° */
  scanf("%d", &p);
  while (0 != p) {
    push(p);
    scanf("%d", &p);
  };

  /* РР·РєР»СЋС‡РІР°С‚ СЃРµ РїРѕСЃР»РµРґРѕРІР°С‚РµР»РЅРѕ РІСЃРёС‡РєРё РµР»РµРјРµРЅС‚Рё РѕС‚ СЃС‚РµРєР° Рё СЃРµ РїРµС‡Р°С‚Р°С‚. РўРѕРІР° С‰Рµ
   * РґРѕРІРµРґРµ РґРѕ РѕС‚РїРµС‡Р°С‚РІР°РЅРµ РЅР° РїСЉСЂРІРѕРЅР°С‡Р°Р»РЅРѕ РІСЉРІРµРґРµРЅР°С‚Р° РїРѕСЃР»РµРґРѕРІР°С‚РµР»РЅРѕСЃС‚ РІ РѕР±СЂР°С‚РµРЅ СЂРµРґ
   */
  while (!empty()) printf("%d ", pop());
  printf("\n");
  return 0;
}
