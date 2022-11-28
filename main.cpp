//Includes FEHLCD.h & FEHUtility.h
#include "header.h"

//Temp preprocessor for print debugging
#include "stdio.h"

//Constants for screen tracking
#define MENU 0
#define GAME 1
#define OTHER 2

//Struct for game tracking
struct game_state {
    int screen;
    int health;
    int score[20];
    char scoreNames[20][20];
};

//Draws menu screen
void DrawMenu(FEHIcon::Icon menuIcon[5]) {
    //Set background color & text color
    LCD.Clear( FEHLCD::Scarlet);
    LCD.SetFontColor( FEHLCD::White );
    
    //Button labels
    char labels[5][20] = {"Play", "Instructions", "High Scores", "Credits", "Exit"}; 

    //Draw the buttons
    FEHIcon::DrawIconArray(menuIcon, 5, 1, 5, 5, 20, 20, labels, WHITE, WHITE);
}

//Draws game screen
void playGame(game_state *state) {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("Play Game Here", 5, 20);
}

//Draws instructions screen
void displayInstructions() {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("Buckeye Rush", 90, 20);
    LCD.WriteAt("Click the screen to jump &", 5, 50);
    LCD.WriteAt("avoid obstacles!", 40, 70);
    LCD.WriteAt("Survive as long as you can", 5, 90);
    LCD.WriteAt("with 3 lives", 40, 110);
    LCD.WriteAt("The longer you go,", 5, 130);
    LCD.WriteAt("The higher your score!", 40, 150);
    
}

//Draws high scores screen
void displayHighScores(game_state *state) {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("Name", 30, 20);
    LCD.WriteAt("Score", 220, 20);
    LCD.DrawLine(0, 40, 320, 40);
    LCD.DrawLine(160, 0, 160, 320);

    char name[20];
    strcpy(name, (*state).scoreNames[0]);
    LCD.WriteAt(name, 30, 50);

    char score[2];
    sprintf(score, "%d", (*state).score[0]);
    LCD.WriteAt(score, 230, 50);
}

//Draws credits screen
void displayCredits() {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("Made by: Peter Sung", 5, 20);
}

/* Entry point to the application */
int main() {
    int x,y;
    struct game_state state;
    state.screen = MENU;

    //Placeholder value
    strcpy(state.scoreNames[0], "Peter Sung");
    state.score[0] = 999;

    //Create the menu buttons
    FEHIcon::Icon menuButtons[5];
    DrawMenu(menuButtons);

    FEHIcon::Icon backIcon[1];
    char backLabel[1][20] = {"Back"};

    while(1) {
        if (LCD.Touch(&x, &y)) {
            if (state.screen == MENU) {
                if (menuButtons[0].Pressed(x,y,0)) {
                    //Start button pressed
                    //state.screen = GAME;
                    playGame(&state);

                    //Temporary back button for menu testing
                    state.screen = OTHER;
                    FEHIcon::DrawIconArray(backIcon, 1, 1, 200, 2, 2, 200, backLabel, WHITE, WHITE);
                    Sleep(0.5);
                } else if (menuButtons[1].Pressed(x,y,0)) {
                    //Instructions button pressed
                    state.screen = OTHER;
                    displayInstructions();
                    FEHIcon::DrawIconArray(backIcon, 1, 1, 200, 2, 2, 200, backLabel, WHITE, WHITE);
                    Sleep(0.5);

                } else if (menuButtons[2].Pressed(x,y,0)) {
                    //High Scores button pressed
                    state.screen = OTHER;
                    displayHighScores(&state);
                    FEHIcon::DrawIconArray(backIcon, 1, 1, 200, 2, 2, 200, backLabel, WHITE, WHITE);
                    Sleep(0.5);

                } else if (menuButtons[3].Pressed(x,y,0)) {
                    //Credits button pressed
                    state.screen = OTHER;
                    displayCredits();
                    FEHIcon::DrawIconArray(backIcon, 1, 1, 200, 2, 2, 200, backLabel, WHITE, WHITE);
                    Sleep(0.5);
                } else if (menuButtons[4].Pressed(x,y,0)) {
                    //Exit button pressed
                    return 0;
                }
            } else if (state.screen == OTHER) {
                if (backIcon[0].Pressed(x,y,0)) {
                    //Back button pressed in instructions, high scores, or credits
                    printf("Test");
                    state.screen = MENU;
                    DrawMenu(menuButtons);
                    Sleep(0.5);
                }
            } 
        }
        
    }
    return 0;
}