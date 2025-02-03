#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#define DEBUG //test etmek için bunu açabilrsiniz 

#define GUESSCOUNT 5

const char *words[20] = {
        "anxiety", "amazing", "anticipate", "authority", "breathe",
        "beautiful", "break", "challenge", "ceiling", "digital",
        "deeply", "environmental", "engine", "framework", "goal",
        "incident", "improvement", "justice", "knowledge", "village" };

int score = 0;
int flag = 1;

void executeLoop();
void boardPrint(char **board, int index);

int main() {
    srand(time(NULL));
    while (1) {
        printf("Play the game: (1)\nExit: (0)\nAnswer: ");
        int tmp = 0;
        scanf("%d", &tmp);
        if (tmp == 1 && flag == 1) {
            executeLoop();
        }
        else {
            break;
        }
    }

    printf("Score: %d", score);
}

void executeLoop() {
    int index = rand() % 20;
    int len = strlen(words[index]);

    char **board = malloc(GUESSCOUNT * sizeof(char *));
    for (int i = 0; i < GUESSCOUNT; i++) {
        board[i] = malloc(len * sizeof(char));
        for (int j = 0; j < len; j++) board[i][j] = ' ';
    }

    boardPrint(board, index);

    flag = 0;

    for (int _ = 0; _ < GUESSCOUNT; _++) {

        printf("You need to write a word with %d letters lenght: ", len);
        char word[len];
        scanf("%s", word);

        for (int i = 0; i < len; i++) board[_][i] = word[i];

        boardPrint(board, index);

        if (strcmp(word, words[index]) == 0) {
            printf("\n\nYou won!!!\n\n");
            flag = 1;
            _ = GUESSCOUNT;
            score++;
        }
        else {
            for (int i = 0; i < len; i++) {
                if (word[i] == words[index][i]) {
                    printf("%d. letter is in the rigth place.\n", i + 1);
                }
                else {
                    int dummy = 0;
                    for (int j = 0; j < len; j++) {

                        if (word[i] == words[index][j]) dummy++;

                        if (dummy == 1) {
                            printf("%d. letter is not in the rigth place.\n", i + 1);
                            j = len;
                        }
                    }

                    if (dummy == 0) {
                        printf("%d. letter doesn't exist.\n", i + 1);
                    }
                }
            }
        }
    }

    printf("\n\nWord is: %s\n\n", words[index]);

}

void boardPrint(char **board, int index) {
    int len = strlen(words[index]);
    printf("\e[1;1H\e[2J");

    for (int i = 0; i < len; i++) printf("----");
    printf("-\n");

    #ifdef DEBUG

    for (int i = 0; i < len; i++) printf("| %c ", words[index][i]);
    printf("|\n");

    for (int i = 0; i < len; i++) printf("----");
    printf("-\n");

    #endif

    for (int i = 0; i < GUESSCOUNT; i++) {
        for (int j = 0; j < len; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");

        for (int i = 0; i < len; i++) printf("----");
        printf("-\n");
    }
    printf("\n");
}