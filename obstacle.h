//Includes FEHLCD.h & FEHUtility.h
#include "header.h"

//Temp preprocessor for print debugging
#include "stdio.h"
#include "math.h"

class Obstacle {
    public:
        /*
         * Obstacle constructor
         */
        Obstacle() {
        }

        /*
         * Draws obstacle
         */
        void drawObstacle() {
            LCD.DrawCircle(x,y, SIZE);
            LCD.DrawLine(0, 200, 319, 200);
        }

        /*
         * Moves obstacle
         */
        void moveObstacle() {
            x -= speed;
        }

        /*
         * Resets obstacle position if: 
         *    1. obstacle reaches end of screen
         *    2. obstacle collides with character
         * 
         * @param hit: true if obstacle collides with character
         */
        void resetPosition(bool hit) {
            if (x <= 0 && !hit) {
                x = 319;
            } else if (hit) {
                x = 319;
                speed = 0;
                Sleep(1.0);
            }
        }

        /*
         * Accelerates object to max speed
         *
         * @param score: current score
         */
        void accel(int score) {
            if (speed < maxSpeed) {
                speed += 1;
            }

            // if (score % 100 == 0) {
            //     speed += 1;
            // }
            
        }

        /*
         * Returns x position of obstacle
         *
         * @return x: x position of obstacle
         */
        int getX() {
            return x;
        }

        /*
         * Returns y position of obstacle
         *
         * @return y: y position of obstacle
         */
        int getY() {
            return y;
        }

    private:
        //Obstacle size
        const int SIZE = 9;
        //Obstacle position
        int x = 300;
        int y = 190;
        //Obstacle speed
        int speed = 2;
        int maxSpeed = 2;
};