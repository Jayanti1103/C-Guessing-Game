#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    char name[30];
    int number, guess, attempts, level, maxAttempts, upperLimit;
    int score, highScore = 0;
    int achievements[5]; 
    char choice;

    FILE *fptr;

    srand(time(0));

    fptr = fopen("highscore.txt", "r");
    if (fptr != NULL) {
        fscanf(fptr, "%d", &highScore);
        fclose(fptr);
    }

    printf("===== Welcome to the Guessing Game =====\n");
    printf("Enter your name: ");
    scanf("%s", name);

    do {
        score = 0;
        memset(achievements, 0, sizeof(achievements));

        printf("\nChoose difficulty:\n");
        printf("1. Easy (1-50, 10 attempts)\n");
        printf("2. Medium (1-100, 7 attempts)\n");
        printf("3. Hard (1-200, 5 attempts)\n");
        printf("Enter choice: ");
        scanf("%d", &level);

        if (level == 1) { upperLimit = 50; maxAttempts = 10; }
        else if (level == 2) { upperLimit = 100; maxAttempts = 7; }
        else { upperLimit = 200; maxAttempts = 5; }

        number = rand() % upperLimit + 1;
        attempts = 0;
        int usedHint = 0;

        printf("\n--- Game Start ---\n");
        printf("Guess the number between 1 and %d (You have %d attempts)\n", upperLimit, maxAttempts);

        while (attempts < maxAttempts) {
            printf("Enter guess (or -1 for hint): ");
            scanf("%d", &guess);
            attempts++;

            if (guess == -1 && !usedHint) {
                if (number % 2 == 0)
                    printf("🔎 Hint: The number is even.\n");
                else
                    printf("🔎 Hint: The number is odd.\n");
                usedHint = 1;
                attempts--; 
                continue;
            } else if (guess == -1 && usedHint) {
                printf("❌ You already used your hint!\n");
                attempts--;
                continue;
            }

            if (guess == number) {
                printf("🎉 Correct! You guessed in %d attempts.\n", attempts);
                score += (upperLimit / attempts);
                if (attempts == 1) achievements[0] = 1;
                if (attempts == maxAttempts) achievements[1] = 1;
                break;
            } else if (guess > number) {
                printf("Too high!\n");
            } else {
                printf("Too low!\n");
            }
        }

        if (guess != number) {
            printf("❌ You failed! The number was %d\n", number);
        } else {
            achievements[2] = 1; 
        }

        printf("\n===== Game Over =====\n");
        printf("Player: %s\n", name);
        printf("Final Score: %d\n", score);

        // Save high score
        if (score > highScore) {
            printf("🏆 New High Score!\n");
            highScore = score;
            fptr = fopen("highscore.txt", "w");
            if (fptr != NULL) {
                fprintf(fptr, "%d", highScore);
                fclose(fptr);
            }
        }
        printf("High Score: %d\n", highScore);

 
        printf("\nAchievements:\n");
        if (achievements[0]) printf("🏅 Lucky Guess (guessed on first try)\n");
        if (achievements[1]) printf("🏅 Clutch (guessed on last try)\n");
        if (achievements[2]) printf("🏅 Champion (completed the game)\n");
        if (!achievements[0] && !achievements[1] && !achievements[2])
            printf("No special achievements unlocked.\n");

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("\nThanks for playing, %s! Goodbye 👋\n", name);

    return 0;
}


