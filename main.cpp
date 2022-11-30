#include "character.h"
#include "screen_manager.h"

/* Entry point to the application */
int main() {
    //Declare variables
    double time;
    double gameStart;
    int x,y;
    struct game_state state;
    
    //Set inital game state
    state.screen = MENU;

    //Placeholder value
    strcpy(state.scoreNames[0], "Peter Sung");
    state.score[0] = 999;

    //Create the menu buttons
    FEHIcon::Icon menuButtons[5];
    DrawMenu(menuButtons);

    //Icon and labels for returning to menu
    FEHIcon::Icon menuIcon[1];
    char backLabel[1][20] = {"Back"};
    char menuLabel[1][20] = {"Return to Menu"};

    //Character & obstacle objects
    Character character;
    Obstacle obstacle = Obstacle();

    //Infinite loop
    while(1) {
        //Game screen logic
        if (state.screen == GAME) {
            time = TimeNow() - gameStart;
            character.drawCharacter(obstacle);

            LCD.WriteAt("Score: ", 180, 10);
            LCD.WriteAt((int) (time*10), 255, 10);
            LCD.WriteAt("Health: ", 30, 10);
            LCD.WriteAt(character.getHeath(), 120, 10);

            obstacle.moveObstacle();
            obstacle.resetPosition(character.collision(obstacle.getX(), obstacle.getY()));
            obstacle.accel((int) (time*10));

            if (character.getHeath() <= 0) {
                drawGameOver((int) (time*10));
                FEHIcon::DrawIconArray(menuIcon, 1, 1, 150, 50, 60, 60, menuLabel, WHITE, WHITE);
                state.screen = GAME_OVER;
            }
        }

        //Screen touched
        if (LCD.Touch(&x, &y)) {

            // If/else statments to recognize touches on different screens
            if (state.screen == MENU) {

                // If/else statements to recognize touches on menu buttons
                if (menuButtons[0].Pressed(x,y,0)) {
                    //Start button pressed

                    //Set start time for score
                    gameStart = TimeNow();

                    //Draws game screen
                    playGame(&state);

                    //Reset & draw character
                    character.reset();
                    character.drawCharacter(obstacle);

                    //Sets screen to game
                    state.screen = GAME;

                    //Buffer to prevent double touch
                    Sleep(0.5);
                } else if (menuButtons[1].Pressed(x,y,0)) {
                    //Instructions button pressed

                    //Set screen state
                    state.screen = OTHER;

                    //Draws instructions screen
                    displayInstructions();
                    FEHIcon::DrawIconArray(menuIcon, 1, 1, 200, 2, 2, 200, backLabel, WHITE, WHITE);

                    //Buffer to prevent double touch
                    Sleep(0.5);

                } else if (menuButtons[2].Pressed(x,y,0)) {
                    //High Scores button pressed

                    //Set screen state
                    state.screen = OTHER;

                    //Draws high scores screen
                    displayHighScores(&state);
                    FEHIcon::DrawIconArray(menuIcon, 1, 1, 200, 2, 2, 200, backLabel, WHITE, WHITE);

                    //Buffer to prevent double touch
                    Sleep(0.5);

                } else if (menuButtons[3].Pressed(x,y,0)) {
                    //Credits button pressed

                    //Set screen state
                    state.screen = OTHER;

                    //Draws credits screen
                    displayCredits();
                    FEHIcon::DrawIconArray(menuIcon, 1, 1, 200, 2, 2, 200, backLabel, WHITE, WHITE);

                    //Buffer to prevent double touch
                    Sleep(0.5);
                } else if (menuButtons[4].Pressed(x,y,0)) {
                    //Exit button pressed
                    return 0;
                }

            } else if (state.screen == OTHER) {
                if (menuIcon[0].Pressed(x,y,0)) {
                    //Back button pressed in instructions, high scores, or credits

                    //Set screen state to menu
                    state.screen = MENU;

                    //Draws menu screen
                    DrawMenu(menuButtons);

                    //Buffer to prevent double touch
                    Sleep(0.5);
                }
            } else if (state.screen == GAME) {
                //Character jump
                character.jump(&obstacle, gameStart);

            } else if (state.screen == GAME_OVER) {
                if (menuIcon[0].Pressed(x,y,0)) {
                    //Back button pressed in game over

                    //Set screen state to menu
                    state.screen = MENU;

                    //Draws menu screen
                    DrawMenu(menuButtons);

                    //Buffer to prevent double touch
                    Sleep(0.5);
                }
            }
            
        }
  
    }
    return 0;
}