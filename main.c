#include <stdio.h>
#include <stdlib.h>

/* простая программа игры в крестики-нолики */
#define SPACE 	' '
#define ROWS	3
#define COLUMNS 3

void disp_pole(char *p, int row, int col);
void init_pole(char *p, int row, int col);
void get_player_move(char *p, int row, int col);
void get_computer_move(char *p, int row, int col);
void check(char *p, int row, int col, char *result);
void internal_test(char *p, int row, int col, char *result);

int main() {

	/* поле для крестиков-ноликов */
	char *pole;	
	pole = malloc(ROWS * COLUMNS * sizeof(char));

	/* результат проверки */
	char *result;
	result = malloc(sizeof(char));
	*result = SPACE;

	internal_test(pole, ROWS, COLUMNS, result);
	
	printf("Press any key.\n");
	/* Ожидание нажатия клавиши */
	/* getch() возвращает код нажатой клавиши, но нам важен только факт нажатия */
	getch();

	init_pole(pole, ROWS, COLUMNS);

	printf("You will be playing against the computer.\n");
	
	do {
		/* вывод игровой доски */
		disp_pole(pole, ROWS, COLUMNS);

		/* ходит игрок */
		get_player_move(pole, ROWS, COLUMNS);

		/* проверка на победу */
		check(pole, ROWS, COLUMNS, result);

		/* есть победитель */
		if(*result != SPACE) 
			break; 
			
		/* ходит компьютер */
		get_computer_move(pole, ROWS, COLUMNS); 

		/* проверка на победу */
		check(pole, ROWS, COLUMNS, result);
	} while(*result==SPACE);

	/* отображение результирующего положения */
	disp_pole(pole, ROWS, COLUMNS);
	
	if(*result=='X') printf("You won!\n");
	else 
		printf("I won!!!!\n");

	free(pole);
	free(result);

	return 0;
}

/* ввод хода игрока */
void get_player_move(char *p, int row, int col) {
	int x, y;
	char *c;
	printf("_Enter coordinates for your X.\n");
	printf("_Row? ");
	scanf("%d", &x);
	printf("_Column? ");
	scanf("%d", &y);
	x--;
	y--;
	if (x<0 || y<0 || x>col-1 || y>row-1) {
		printf("Out of range2, try again.\n");
		get_player_move(p,row ,col);
	} else {
		c=p+x*col+y;
		if (*c != SPACE) {
			printf("Invalid move2, try again.\n");
			get_player_move(p,row ,col);
		} else {
			*c = 'X';
		}
	}
}

/* инициализация поля сомволами SPACE */
void init_pole(char *p, int row, int col) {
	size_t j,i;
	char *c;
	
	for (j = 0  ;  j < row; j++) {
		for (i = 0 ; i < col; i++) {
			c=p+j*col+i;
			*c=SPACE;
		}
	}
}

/* печать игрового поля */
void disp_pole(char *p, int row, int col) {

	size_t j,i;
	char *c;
	system("cls");
	printf("You symbol 'X'.\n");
	printf("My symbol 'O'.\n");

	for (j = 0  ;  j<row; j++) {
		for (i = 0 ; i < col; i++){
			c=p+j*col+i;
			printf("|%c|",*c);
		}
		printf("\n");
	}
	printf("\n");
}

/* ход компьютера */
void get_computer_move(char *p, int row, int col) {

	size_t t;

	/* Задаем "зерно" на основании которого генерируются случайные числа */
	srand(time(NULL));

	int rnd = rand()%(row*col-1); /* Для получения числа из диапазона от 0 до до максимального элемента массива */

	/* Если случано выбранный элемент массива SPACE ставим на нем 'O' и выходим*/
	if (*(p+rnd) == SPACE ) {
		*(p+rnd) = 'O';
		return;
	}

	/* если сучайный элемент не SPACE берем первый свободный */
	for (t=0; *p!=SPACE && t<9; ++t) p++;
	if(t==9) {
		printf("draw\n");
		exit(0); /* End of game */
	}
	else *p = 'O';
}

/* проверка на победу */
void check(char *p, int row, int col, char *result) {

	size_t t;

	/* проверка строк */
	for(t=0; t<row; t++) {
		if ((*(p + t*col)  == *(p+1+ t*col)) && (*(p+ t*col) == *(p+2 + t*col))) {
			*result = *(p+t*col);
		}
	}
	
	/* проверка столбцов */
	for(t=0; t<col; t++) { 
		if(*(p + t) == *(p+3 + t) && *(p+3+ t)==*(p+6 +t) && *result == SPACE) {
			*result = *(p + t);
		}
	}

	/* проверка диагонали \ */
	if(*p==*(p+4) && *(p+4)==*(p+8) && *result == SPACE) {
		*result = *p;
	}

	/* проверка диагонали / */
	if(*(p+2)==*(p+4) && *(p+4)==*(p+6) && *result == SPACE) {
		*result = *(p+2);
	}

}

/* Функция тестирования функций */
void internal_test(char *p, int row, int col, char *result) {

	printf("Chek init_pole(char *p, int row, int col) function\n");
	init_pole(p, row, col);
	if (*p == SPACE ) {
		printf("Chek passed\n");
	} else {
		printf("Chek failed\n");
		exit(1);
	}

	init_pole(p, row, col);

	printf("Chek void check(char *p, int row, int col, char *result) function\n");

	char *r;
	r = malloc(sizeof(char));
	*r = SPACE;
	check(p, ROWS, COLUMNS, r);

	if ( *r == SPACE ) {
		printf("Chek passed\n");
	} else {
		printf("Chek failed\n");
		exit(1);
	}

}
