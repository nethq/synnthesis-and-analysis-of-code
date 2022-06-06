#define EPS 0.0001
#define MAX_LEN 100

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

char getChar(char n) /* Р’СЂСЉС‰Р° СЃРёРјРІРѕР»Р°, СЃСЉРѕС‚РІРµС‚СЃС‚РІР°С‰ РЅР° n */
{  return (n < 10) ? n + '0' : n + 'A' - 10; }

char getValue(char c) /* Р’СЂСЉС‰Р° СЃС‚РѕР№РЅРѕСЃС‚С‚Р° РЅР° СЃРёРјРІРѕР»Р° c */
{  return (c >= '0' && c <= '9') ? c - '0' : c - 'A' + 10; }

void reverse(char *pch)
{ char *pEnd;
  for (pEnd = pch + strlen(pch) - 1; pch < pEnd; pch++, pEnd--) {
	char c = *pch;
	*pch = *pEnd;
	*pEnd = c;
  }
}

void convert(char *rslt, unsigned long n, unsigned char base)
/* РџСЂРµРѕР±СЂР°Р·СѓРІР° С†СЏР»РѕС‚Рѕ РґРµСЃРµС‚РёС‡РЅРѕ С‡РёСЃР»Рѕ n (n >= 0) РІ Р±СЂРѕР№РЅР° СЃРёСЃС‚РµРјР° СЃ РѕСЃРЅРѕРІР° base */
{ char *saveRslt = rslt;
  while (n > 0) {
	*rslt++ = getChar((char)(n % base));
	n /= base;
  }
  *rslt = '\0';
  reverse(saveRslt);
}

void convertLessThan1(char *rslt, double n, unsigned char base, unsigned char cnt)
/* РџСЂРµРѕР±СЂР°Р·СѓРІР° РґРµСЃРµС‚РёС‡РЅРѕС‚Рѕ С‡РёСЃР»Рѕ 0 <= n < 1 РІ Р±СЂРѕР№РЅР° СЃРёСЃС‚РµРјР° СЃ РѕСЃРЅРѕРІР° base
   СЃ РЅРµ РїРѕРІРµС‡Рµ РѕС‚ cnt РЅР° Р±СЂРѕР№ С†РёС„СЂРё СЃР»РµРґ РґРµСЃРµС‚РёС‡РЅР°С‚Р° Р·Р°РїРµС‚Р°СЏ */
{ 
  while (cnt--) {
    /* Р”Р°Р»Рё РЅРµ СЃРјРµ РїРѕР»СѓС‡РёР»Рё 0? */
	if (fabs(n) < EPS) break;
	/* РџРѕР»СѓС‡Р°РІР°РЅРµ РЅР° СЃР»РµРґРІР°С‰Р°С‚Р° С†РёС„СЂР° */
    n *= base;
	*rslt++ = getChar((char)(int)floor(n));
    n -= floor(n);
  }
  *rslt = '\0';
}

void convertReal(char *rslt, double n, unsigned char base, unsigned char cnt)
  /* РџСЂРµРѕР±СЂР°Р·СѓРІР° РґРµСЃРµС‚РёС‡РЅРѕС‚Рѕ СЂРµР°Р»РЅРѕ С‡РёСЃР»Рѕ n РІ Р±СЂРѕР№РЅР° СЃРёСЃС‚РµРјР° СЃ РѕСЃРЅРѕРІР° base */
{ double integer, fraction;

  /* РќР°РјРёСЂР°РЅРµ РЅР° Р·РЅР°РєР° */
  if (n < 0) {
	*rslt++ = '-';
	n = -n;
  }

  /* Р Р°Р·Р±РёРІР°РЅРµ РЅР° С†СЏР»Р° Рё РґСЂРѕР±РЅР° С‡Р°СЃС‚ */
  fraction = modf(n, &integer); 

  /* РљРѕРЅРІРµСЂС‚РёСЂР°РЅРµ РЅР° С†СЏР»Р°С‚Р° С‡Р°СЃС‚ */
  convert(rslt, (unsigned long)integer, base);

  /* РџРѕСЃС‚Р°РІСЏРЅРµ РЅР° РґРµСЃРµС‚РёС‡РЅР° С‚РѕС‡РєР° */
  if ('\0' == *rslt)
	*rslt++ = '0';
  else
	rslt += strlen(rslt);
  *rslt++ = '.';

  /* РљРѕРЅРІРµСЂС‚РёСЂР°РЅРµ РЅР° РґСЂРѕР±РЅР°С‚Р° С‡Р°СЃС‚ */
  convertLessThan1(rslt, fraction, base, cnt);
  if ('\0' == *rslt) {
	*rslt++ = '0';
	*rslt = '\0';
  }
}

unsigned long calculate(const char *numb, unsigned char base)
/* РќР°РјРёСЂР° РґРµСЃРµС‚РёС‡РЅР°С‚Р° СЃС‚РѕР№РЅРѕСЃС‚ РЅР° С‡РёСЃР»РѕС‚Рѕ numb, Р·Р°РґР°РґРµРЅРѕ РІ Р±СЂРѕР№РЅР° СЃРёСЃС‚РµРјР°
    СЃ РѕСЃРЅРѕРІР° base, numb >= 0 */
{ unsigned long result;
  for (result = 0; '\0' != *numb; numb++)
    result = result*base + getValue(*numb);
  return result;
}

double calculateLessThan1(const char *numb, unsigned char base)
/* РќР°РјРёСЂР° РґРµСЃРµС‚РёС‡РЅР°С‚Р° СЃС‚РѕР№РЅРѕСЃС‚ РЅР° С‡РёСЃР»РѕС‚Рѕ numb (0 < numb < 1),
   Р·Р°РґР°РґРµРЅРѕ РІ Р±СЂРѕР№РЅР° СЃРёСЃС‚РµРјР° СЃ РѕСЃРЅРѕРІР° base */
{ const char *end;
  double result;
  for (end = numb + strlen(numb) - 1, result = 0.0; end >= numb; end--)
    result = (result + getValue(*end)) / base;
  return result;
}

double calculateReal(char *numb, unsigned char base)
/* РќР°РјРёСЂР° РґРµСЃРµС‚РёС‡РЅР°С‚Р° СЃС‚РѕР№РЅРѕСЃС‚ РЅР° СЂРµР°Р»РЅРѕС‚Рѕ С‡РёСЃР»Рѕ numb, Р·Р°РґР°РґРµРЅРѕ
   РІ Р±СЂРѕР№РЅР° СЃРёСЃС‚РµРјР° СЃ РѕСЃРЅРѕРІР° base */
{ char *pointPos;
  char minus;
  double result;

  /* РџСЂРѕРІРµСЂРєР° Р·Р° РјРёРЅСѓСЃ */
  if ('-' == *numb) {
	minus = -1;
	numb++;
  }
  else
	minus = 1;

  if (NULL == (pointPos = strchr(numb, '.')))
    return calculate(numb, base); /* РќСЏРјР° РґСЂРѕР±РЅР° С‡Р°СЃС‚ */
  
  /* РџСЂРµСЃРјСЏС‚Р°РЅРµ РЅР° С†СЏР»Р°С‚Р° С‡Р°СЃС‚ */
  *pointPos = '\0';
  result = calculate(numb, base);
  *pointPos = '.';

  /* РџСЂРёР±Р°РІСЏРЅРµ РЅР° РґСЂРѕР±РЅР°С‚Р° С‡Р°СЃС‚ */
  result += calculateLessThan1(pointPos+1, base);

  return minus*result;

}

int main(void) {
  char numb[MAX_LEN];
  printf("!!! Р”РµРјРѕРЅСЃС‚СЂР°С†РёСЏ РЅР° РїСЂРµРѕР±СЂР°Р·СѓРІР°РЅРµС‚Рѕ РјРµР¶РґСѓ Р±СЂРѕР№РЅРё СЃРёСЃС‚РµРјРё !!!\n");
  convertReal(numb, 777.777, 7, 10); printf("РЎРµРґРјРёС‡РЅРёСЏС‚ Р·Р°РїРёСЃ РЅР° 777.777 (10) Рµ %s\n", numb);
  strcpy(numb,"11.D873");
  printf("Р”РµСЃРµС‚РёС‡РЅРёСЏС‚ Р·Р°РїРёСЃ РЅР° 11.D873 (16) Рµ: %0.10lf\n",calculateReal(numb,16));
  return 0;
}
