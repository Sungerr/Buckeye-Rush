#include "header.h"

#define MENU 0
#define GAME 1
#define INSTRUCTIONS 2
#define HIGHSCORE 3
#define CREDITS 4

struct game_state {
    int screen;
    int health;
    int score[20];
    char scoreNames[20][20];
};

/*
 * Draws the game menu
*/
void DrawMenu(FEHIcon::Icon menuIcon[5]) {
    //Set background color & text color
    LCD.Clear( FEHLCD::Scarlet);
    LCD.SetFontColor( FEHLCD::White );
    
    //Button labels
    char labels[5][20] = {"Play", "Instructions", "High Scores", "Credits", "Exit"}; 

    //Draw the buttons
    FEHIcon::DrawIconArray(menuIcon, 5, 1, 5, 5, 20, 20, labels, WHITE, WHITE);
}

void playGame(game_state *state) {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("Play Game Here", 20, 20);
}

void displayInstructions() {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("Instructions button pressed", 0, 0);
    
}

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

void displayCredits() {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("Made by: Peter Sung", 0, 0);

    FEHIcon::Icon backIcon;
    backIcon.SetProperties("Back", 500, 1000, 100, 100, WHITE, WHITE);
    backIcon.Draw();
}

/* Entry point to the application */
int main() {
    int x,y;

    struct game_state state;

    state.screen = MENU;

    //Placeholder value
    strcpy(state.scoreNames[0], "Peter Sung");
    state.score[0] = 999;

    FEHIcon::Icon menuButtons[5];
    DrawMenu(menuButtons);
    while(1) {
        if (LCD.Touch(&x, &y)) {
            if (state.screen == MENU) {
                if (menuButtons[0].Pressed(x,y,0)) {
                    //Start button pressed
                    state.screen = GAME;
                    playGame(&state);
                    
                } else if (menuButtons[1].Pressed(x,y,0)) {
                    //Instructions button pressed
                    state.screen = INSTRUCTIONS;
                    displayInstructions();

                } else if (menuButtons[2].Pressed(x,y,0)) {
                    //High Scores button pressed
                    state.screen = HIGHSCORE;
                    displayHighScores(&state);

                } else if (menuButtons[3].Pressed(x,y,0)) {
                    //Credits button pressed
                    state.screen = CREDITS;
                    displayCredits();

                } else if (menuButtons[4].Pressed(x,y,0)) {
                    //Exit button pressed
                    return 0;
                }
            }
            
        }
        
    }
    return 0;
}