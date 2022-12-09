#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define NCARD 52
#define AI 17
#define SPADE "♠"
#define CLUB "♣"
#define DIA "◆"
#define HEART "♥"

enum shape { spade, club, dia, heart };
enum number { ace = 1, jack = 11, queen = 12, king = 13 };

typedef struct card {
	int number;
	char shape;
} CARD;

typedef struct player {
	int nCard;		// 몇 장의 카드를 소지하는지
	int score;		// 플레이어 점수 
	CARD list[10];	// 플레이어가 소지한 카드
} PLAYER;

void init_card(CARD* c) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			c->number = j + 1;
			c->shape = i;
			c++;
		}
	}
}

void swap(CARD* c1, CARD* c2) {
	int card_num_temp = c1->number;
	char card_shape_temp = c1->shape;
	*c1 = *c2;
	c2->number = card_num_temp;
	c2->shape = card_shape_temp;
}

void shuffle(CARD* c) {
	srand(time(NULL)); // card shuffle
	int index = 0;
	for (int iter = 0; iter < NCARD; iter++) {
		index = rand() % NCARD;
		swap(c + iter, c + index);
	}
}

void print_card(CARD* c) {
	printf("--------\n");
	switch (c->shape) {
	case spade:
		printf("|%s    |\n", SPADE);
		break;
	case club:
		printf("|%s    |\n", CLUB);
		break;
	case dia:
		printf("|%s    |\n", DIA);
		break;
	case heart:
		printf("|%s    |\n", HEART);
		break;
	}
	switch (c->number) {
	case 1:
		printf("|   A  |\n");
		break;
	case 11:
		printf("|   J  |\n");
		break;
	case 12:
		printf("|   Q  |\n");
		break;
	case 13:
		printf("|   K  |\n");
		break;
	default:
		printf("|  %02d  |\n", c->number);
	}
	switch (c->shape) {
	case spade:
		printf("|    %s|\n", SPADE);
		break;
	case club:
		printf("|    %s|\n", CLUB);
		break;
	case dia:
		printf("|    %s|\n", DIA);
		break;
	case heart:
		printf("|    %s|\n", HEART);
		break;
	}
	printf("--------\n");
}

void hit(PLAYER* p, CARD* c, int flag,int isPlayer) {
	// p: nCard, score, list
	p->nCard++;
	p->list[p->nCard - 1] = *c;

	int A_choice;
	if (flag) {
		print_card(c);
		if (c->number==1) {
			if (isPlayer) {
				printf("A카드를 얻었습니다. 1점과 11점 중 선택하여 득점합니다.\n 몇 점으로 하시겠습니까?\n");
				printf("획득할 점수 (1 혹은 11 중 하나를 입력해주세요.): ");
				scanf("%d", &A_choice);
				if (A_choice >= 6) {
					printf("11점을 득점합니다.\n");
					p->list[p->nCard - 1].number = 14;
				}
				else {
					printf("1점을 득점합니다.\n");
					p->list[p->nCard - 1].number = 1;
				}
			}
			else { // is dealer
				if (p->nCard + 11<=21) {
					p->list[p->nCard - 1].number = 14;
				}
				else {
					p->list[p->nCard - 1].number = 1;
				}
			}
		}
	}
}

void calc_score(PLAYER* p) {
	int num = p->nCard;
	int score = 0;

	int A_choice;
	for (int i = 0; i < num; i++) {
		switch (p->list[i].number) {
		case 11:
		case 12:
		case 13:
			score += 10;
			break;
		case 14:
			score += 11;
			break;
		default:
			score += p->list[i].number;
			break;
		}
	}
	p->score = score;
}


int main(void) {
	// step 0. initialization
	//	card set: 52 = 4 shape (d,s,h,c), 13 (A ~ K)
	CARD all_cards[NCARD];
	init_card(all_cards);
	//printf("%d,%d,%d,%d\n", all_cards[0].number, all_cards[20].number, all_cards[30].number, all_cards[40].number);

	// step 1. input
	// cost : user input
	// users : input
	int cost;
	int users;
	printf("유저의 수를 입력하시오. (단위 : 명): ");
	scanf("%d",&users);
	printf("플레이어의 예산을 입력하십시오. (단위 : 만원): ");
	scanf("%d" ,&cost);

	// step 2. give cards
	shuffle(all_cards);
	//printf("%d,%d,%d,%d\n", all_cards[0].number, all_cards[20].number, all_cards[30].number, all_cards[40].number);

	PLAYER* players;

	players = (PLAYER *)malloc(sizeof(PLAYER) * users);

	int bet_cost;

	int card_index;
	char action;
	int i;

	//승패 판정
	int max_score;
	int winner;
	while (1) {
		//매판 점수 및 카드 초기화
		for (i = 0; i < users; i++) {
			players[i].score = 0;
			players[i].nCard = 0;
		}
		shuffle(all_cards);

		//베팅할 금액 입력
		// 베팅금액 : bet_cost
		//0원 베팅, 소지금액 없을시, 소지금액보다 큰 금액을 베팅할 시 반복종료
		printf("현재 당신은 %d만원을 가지고 있습니다.\n", cost);
		if (cost <= 0) {
			printf("소지 금액이 없습니다. 게임을 이용하실 수 없습니다.");
			break;
		}
		printf("베팅할 금액을 입력하십시오. (단위 : 만원): ");
		scanf("%d",&bet_cost);
		if(bet_cost > cost) {
			printf("해당 금액을 베팅 할 수 없습니다. 게임에서 퇴장됩니다.");
			break;
		}

		//게임 시작
		// 최초 카드 한장씩
		printf("딜러 카드:\n");
		hit(&players[0], &all_cards[0], 1,0);
		printf("플레이어카드:\n");
		hit(&players[1], &all_cards[1], 1,1);
		calc_score(&players[1]);

		card_index = 1;
		for (int i = 2; i < users;i++) {
			card_index++;
			printf("플레이어 %d 카드",i);
			hit(&players[i], &all_cards[card_index], 1, 0);
		}

		// step 3. player play:	HIT or STAY
		printf("HIT or STAY [h/s]: ");
		scanf(" %c", &action);
		while (action == 'h') { //h면 더줌
			card_index++;
			hit(&players[1], &all_cards[card_index], 1,1);
			calc_score(&players[1]);
			if (players[1].score > 21) {
				break;
			}
			printf("HIT or STAY [h/s]: ");
			scanf(" %c", &action);
		}

		// dealer's action
		while (players[0].score < AI) {
			card_index++;
			hit(&players[0], &all_cards[card_index], 0,0);
			calc_score(&players[0]);

			//다른 플레이어
			for (i = 2; i < users;i++) {
				card_index++;
				hit(&players[i], &all_cards[card_index], 0, 0);
				calc_score(&players[i]);
			}
		}
		players[0].nCard -= 1;
		calc_score(&players[0]);

		//printf("player score: %d, dealer score: %d", players[1].score, players[0].score);

		// step 4. win or loss
		if (players[1].score == 21) { // 배당 두배 승리
			printf("player score: %d\n", players[1].score);
			printf("player win\n");
			cost += (bet_cost * 2);
		}
		else if (players[1].score < 21) { // 플레이어가 21점 미만일 때
			//점수 출력
			max_score = players[1].score;
			winner = 1;
			printf("player score: %d\n", players[1].score);
			for (i = 2; i < users;i++) {
				printf("player%d score: %d\n",i, players[i].score);
				if(players[i].score >max_score){
					if (players[i].score <= 21) {
						max_score = players[i].score;
						winner = i;
					}
				}
			}
			if (players[0].score > max_score) {
				if (players[0].score <= 21) {
					max_score = players[i].score;
					winner = 0;
				}
			}
			printf("dealer score: %d\n", players[0].score);
			if (max_score == players[1].score) {
				printf("player win\n");
				cost += bet_cost;
			}
			else {
				if (winner == 0) {
					printf("dealer win\n");
					cost -= bet_cost;
				}
				else {
					printf("player %d win\n", winner);
					cost -= bet_cost;
				}
			}
		}
		else { // 패배
			printf("player score: %d\n", players[1].score);
			printf("you lose\n");
			cost -= bet_cost;
		}
	}

	return 0;
}