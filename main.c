#include <stdio.h>
#include <stdlib.h>

/* простая программа игры в крестики-нолики */
#define SPACE 	' '
#define ROWS	3
#define COLUMNS 3

void disp_pole(char *p, int row, int col);
void init_pole(char *p, int row, int col);
char check(char *p, int row, int col);
void get_player_move(char *p, int row, int col);
void get_computer_move(char *p, int row, int col);

int main() {

	/* поле для крестиков-ноликов */
	char *pole;	
	pole = malloc(ROWS * COLUMNS * sizeof(char));

	/* результат проверки */
	char done;

	init_pole(&pole, ROWS, COLUMNS);
	disp_pole(&pole, ROWS, COLUMNS);
	
	printf("You will be playing against the computer.\n");
	printf("You symbol 'X'.\n");
	printf("My symbol 'O'.\n");
	done = SPACE;
	do {
		 /* вывод игровой доски */
		disp_pole(&pole, ROWS, COLUMNS);

		/* ходит игрок */
		get_player_move(&pole, ROWS, COLUMNS);

		/* проверка на победу */
		done = check(&pole, ROWS, COLUMNS);

		if (done!=SPACE) 
			break; /* победитель */
			
		/* ходит компьютер */		
		get_computer_move(&pole, ROWS, COLUMNS); 

		/* проверка на победу */
		done = check(&pole, ROWS, COLUMNS);
	} while(done==SPACE);
	
	if(done=='X') printf("You won!\n");
	else 
		printf("I won!!!!\n");

	/* отображение результирующего положения */
	disp_pole(&pole, ROWS, COLUMNS);
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
	register int j,i;
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
	register int r,i;
	char *c, *u;
	
	for (r = 0  ;  r<row; r++) {
		for (i = 0 ; i < col; i++){
			c=(char *)*(p+r*col+i);
			printf("|%c|",c);
		}
		printf("\n");
	}
	printf("\n");
}

/* ход компьютера */
void get_computer_move(char *p, int row, int col) {
	size_t t;
	for (t=0; *p!=SPACE && t<9; ++t) p++;
	if(t==9) {
		printf("draw\n");
		exit(0); /* game over */
	}
	else *p = 'O';
}

/* проверка на победу */
char check(char *p, int row, int col) {

	size_t t;

	/* проверка строк */	
	for(t=0; t<row; t++) {
		if ((*(p + t*col)  == *(p+1+ t*col)) && (*(p+ t*col) == *(p+2 + t*col))) {
			return *(p+t*col);
		}
	}
	
	/* проверка столбцов */
	for(t=0; t<col; t++) { 
		if(*(p + t) == *(p+3 + t) && *(p+3+ t)==*(p+6 +t)) {
			return *(p + t);
		}
	}

	/* проверка диагонали \ */
	if(*p==*(p+4) && *(p+4)==*(p+8)) {
		return *p;
	}

	/* проверка диагонали / */
	if(*(p+2)==*(p+4) && *(p+4)==*(p+6)) {
		return *(p+2);
	}

	free(t);
	return SPACE;
}

