#include <stdio.h>

#define MAX_ROWS 10
#define MAX_COLS 10

char map[MAX_ROWS][MAX_COLS];
int playerRow, playerCol;
int startRow, startCol;

void initializeMap(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char c;
    int row = 0, col = 0;

    while ((c = fgetc(file)) != EOF && row < MAX_ROWS) {
        if (c == '\n') {
            row++;
            col = 0;
        } else {
            map[row][col] = c;

            if (c == 'S') {
                startRow = row;
                startCol = col;
            }
            col++;
        }
    }

    playerRow = startRow;
    playerCol = startCol;
    map[playerRow][playerCol] = 'X';

    fclose(file);
}

void displayMap() {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

int canMove(int newRow, int newCol) {
    if (newRow < 0 || newRow >= MAX_ROWS || newCol < 0 || newCol >= MAX_COLS) {
        return 0;
    }

    return map[newRow][newCol] == ' ' || map[newRow][newCol] == 'E';
}

void makeMove(int newRow, int newCol) {
    map[playerRow][playerCol] = ' ';
    map[startRow][startCol] = 'S';
    map[newRow][newCol] = 'X';
    playerRow = newRow;
    playerCol = newCol;
}

int main() {
    char filePath[] = "map.txt";
    initializeMap(filePath);

    char action;
    int newPlayerRow, newPlayerCol;

    while (1) {
        printf("Enter move (w/a/s/d) or 'M' to view the map: ");
        scanf(" %c", &action);

        if (action == 'M' || action == 'm') {
            displayMap();
            continue;
        }

        newPlayerRow = playerRow;
        newPlayerCol = playerCol;

        switch (action) {
            case 'w':
                newPlayerRow--;
                break;
            case 's':
                newPlayerRow++;
                break;
            case 'a':
                newPlayerCol--;
                break;
            case 'd':
                newPlayerCol++;
                break;
            default:
                printf("Invalid move. Use 'w', 'a', 's', or 'd'.\n");
                continue;
        }

        if (canMove(newPlayerRow, newPlayerCol)) {
            makeMove(newPlayerRow, newPlayerCol);
        } else {
            printf("Cannot move to the specified position.\n");
        }

        if (playerRow == 4 && playerCol == 3) {
            printf("Congratulations! You win!\n");
            break;
        }
    }

    return 0;
}
