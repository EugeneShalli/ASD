//Пример программы с измерением времени решения задачи 
//Вариант для ДОС-приложения, пригоден для старых компиляторов, начиная с Borland C++ 3.1
//Для Visual C++ может потребоваться доработка: некоторые библиотечные функции устарели

//Вычисление пересечения двух множеств целых цисел --------------- (c) Clgn, 27.03.08
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <mem.h>

double Ti(unsigned char *u)  //Измерение времени обращением к счётчику тактов процессора
//Аргумент - прочитанные 8 байтов. Результат - то же в double
{ struct W {
	unsigned long P;
	unsigned long Q;
		};
  	union {unsigned t[4];
		 unsigned char tb[8];
		W tt;} T;
asm { //Обращение к счётчику и сохранение результата в P и Q
   db 0x0f, 0x31, 0x66; mov WORD PTR T.tt.P, AX;
   db 0x66; mov WORD PTR T.tt.Q, DX;
  }
  memcpy(u, T.tb, 8); //Копирование отсчёта в аргумент (для контроля)
  return (double)T.tt.P/65536+T.tt.Q*65536; //Преобразование в double
}
void main()
{
	FILE *out;
	out = fopen("out\\in  .txt", "w"); //Открытие файла in.txt
	double m, n;
	unsigned char T2[8], T1[8];
	int  p=5, q=205, dp=5, A[410], B[410], C[410], i, j, k, l;
	clrscr();
	fprintf(out, "%d\n", (int)(q-p)/dp+1); //Выдача первой строки
	do { //Цикл опытов с изменением мощности с шагом p
	 for (i=0; i<p; i++) {A[i] = random(1000); B[i]=random(1000); }
	 m = Ti(T1); //Начало отсчёта времени
	 for(i=k=0; i<p; i++)
	   for(j=0; j<p; j++)
		 if(A[i] == B[j]) C[k++] = A[i];
	 n = Ti(T2);  //Конец отсчёта
	 printf("\np=%d k=%d T1=%le, T2=%le, Dt=%le\n", p, k, m, n, n-m);
	 for(i=0; i<8; i++) printf("%03u ", T1[7-i]);
	 printf("\n");
	 for(i=0; i<8; i++) printf("%03u ", T2[7-i]);
	 printf("\n");
	 fprintf(out, "%d %le\n", p, n-m);
//	 getch();
	} while ((p+=dp) <= q);
	puts("\n\n=== The End ==="); getch();
}
