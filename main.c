#include <stdio.h>
#include <stdlib.h>

/* простая программа игры в крестики-нолики */
#define SPACE 	' '
#define RESULTS 'Z'
#define ROWS	3
#define COLUMNS 3

int disp_pole(char *p, int row, int col);
int init_pole(char *p, int row, int col, char s);
int get_player_move(char *p, int row, int col);
int get_computer_move(char *p, int row, int col);
int check(char *p, int row, int col, char *result);
int internal_test(char *p, int row, int col, char *result);

int main() {

	/* поле для крестиков-ноликов */
	char *pole;	
	pole = malloc(ROWS * COLUMNS * sizeof(char));

	/* результат проверки */
	char *result;
	result = malloc(sizeof(char));
	*result = SPACE;

	if ( internal_test(pole, ROWS, COLUMNS, result) != 0 ) {
		printf("Internal test failed.\n");
		exit(4);
	}

	printf("Press any key.\n");
	/* Ожидание нажатия клавиши */
	/* getch() возвращает код нажатой клавиши, но нам важен только факт нажатия */
	getch();

	init_pole(pole, ROWS, COLUMNS, SPACE);

	printf("You will be playing against the computer.\n");
	
	do {
		/* вывод игровой доски */
		disp_pole(pole, ROWS, COLUMNS);

		/* ходит игрок */
		if (get_player_move(pole, ROWS, COLUMNS) != 0 ) break;

		/* проверка на победу */
		check(pole, ROWS, COLUMNS, result);

		/* есть победитель */
		if(*result != SPACE) break;
			
		/* ходит компьютер */
		if ( get_computer_move(pole, ROWS, COLUMNS) != 0 ) break;

		/* проверка на победу */
		check(pole, ROWS, COLUMNS, result);
	} while(*result==SPACE);

	/* отображение результирующего положения */
	disp_pole(pole, ROWS, COLUMNS);
	
	if(*result=='X') printf("You won!\n");
	else if(*result=='O') printf("I won!\n");
	else printf("End of game no free cells.\n");

	free(pole);
	free(result);

	return 0;
}

/* ввод хода игрока */
int get_player_move(char *p, int row, int col) {

	int x, y;
	char *c;
	size_t t;

	/* провека достуных ячеек */
	c=p;
	for (t=0; *c!=SPACE && t<9; ++t) c++;
	if(t==9) {
		printf("No free cells.\n");
		return 5;
	}

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
	return 0;
}

/* инициализация поля сомволами */
int init_pole(char *p, int row, int col, char s) {

	size_t j,i;
	char *c;

	for (j = 0 ; j < row; j++) {
		for (i = 0 ; i < col; i++) {
			c=p+j*col+i;
			*c=s;
		}
	}
	return 0;
}

/* печать игрового поля */
int disp_pole(char *p, int row, int col) {

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
	return 0;
}

/* ход компьютера */
int get_computer_move(char *p, int row, int col) {

	size_t t;

	/* Задаем "зерно" на основании которого генерируются случайные числа */
	srand(time(NULL));

	int rnd = rand()%(row*col-1); /* Для получения числа из диапазона от 0 до до максимального элемента массива */

	/* Если случано выбранный элемент массива SPACE ставим на нем 'O' и выходим*/
	if (*(p+rnd) == SPACE ) {
		*(p+rnd) = 'O';
		return 0;
	}

	/* если сучайный элемент не SPACE берем первый свободный */
	for (t=0; *p!=SPACE && t<9; ++t) p++;
	if(t==9) {
		return(3);
	} else *p = 'O';
	return 0;
}

/* проверка на победу */
int check(char *p, int row, int col, char *result) {

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

	/* в случае если проверка проходит но строки либо диагонали заполенены символами отличными от опстимых */
	if (*result != 'O' && *result != 'X' && *result != SPACE) {
		*result = RESULTS;
		return 2;
	}
	else return 0;

}

/* Функция тестирования функций */
int internal_test(char *p, int row, int col, char *result) {

	printf("Chek int disp_pole(char *p, int row, int col) function\n");
	printf("Press any key.\n");
	getch();
	init_pole(p, row, col, RESULTS);
	if ( disp_pole(p, row, col) != 0 ) {
		printf("Chek failed\n");
		return 1;
	} else {
		printf("Chek passed\n");
	}


	printf("Chek int init_pole(char *p, int row, int col, char s) function\n");
	init_pole(p, row, col, RESULTS);
	if ( *p == RESULTS ) {
		printf("Chek passed\n");
	} else {
		printf("Chek failed\n");
		return 1;
	}

	printf("Chek int check(char *p, int row, int col, char *result) function\n");
	init_pole(p, row, col, SPACE);

	int a;
	char *r;
	r = malloc(sizeof(char));
	*r = SPACE;
	check(p, ROWS, COLUMNS, r);

	if ( *r == SPACE ) {
		printf("Chek passed\n");
	} else {
		printf("Chek failed\n");
		return 1;
	}

	printf("Chek int get_computer_move(char *p, int row, int col) function\n");
	init_pole(p, row, col, RESULTS);
	*p= SPACE;
	a = get_computer_move(p, row, col);
	if ( a != 0 || *p != 'O') {
		printf("Chek failed\n");
		return 1;
	} else {
		printf("Chek passed\n");
	}

	printf("Chek int get_player_move(char *p, int row, int col) function\n");
	init_pole(p, row, col, RESULTS);
	a = get_player_move(p, row, col);
	if ( a == 0 || *p != RESULTS) {
		printf("Chek failed\n");
		return 1;
	} else {
		printf("Chek passed\n");
	}

	printf("Chek int printf(char c) function\n");
	if ( printf("%c\n", RESULTS) < 0 ) {
		printf("Chek failed\n");
		return 1;
	} else {
		printf("Chek passed\n");
	}

	printf("Chek int rand() function\n");
	srand(time(NULL));
	if ( rand() != rand() ) {
		printf("Chek passed\n");
	} else {
		printf("Chek failed\n");
		return 1;
	}

	free(r);
	return 0;
}
