//Includes header file
#include "header.h"

//Obsacle object class

#define REMOVE 0
#define ADD 1

class Obstacle {
    public:
        /*
         * Obstacle constructor
         */
        Obstacle() {}

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
            if (x < 0) {
                resetPosition();
            }
            accel();
        }

        /*
         * Resets obstacle position
         */
        void resetPosition() {
            x = 300;
            maxSpeed = rand() % 5 + 2;

            //Randomize y position
            switch (rand() % 3) {
                case 0:
                    y = 190;
                    break;
                case 1:
                    y = 180;
                    break;
                case 2:
                    y = 160;
                    break;
            }
        }

         /*
         * Resets obstacle speed
         */
        void resetSpeed() {
            speed = 1;
        }

        /*
         * Accelerates object to max speed
         */
        void accel() {
            if (speed < maxSpeed) {
                speed += 1;
            } else if (speed > maxSpeed) {
                speed -= 1;
            }
            
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