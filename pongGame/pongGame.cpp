#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool gameOver;
bool start;

int width, height;
const int barLenght = 7;
int barX[2][barLenght];
int barY[2][barLenght];
int ballX, ballY;
int pasBallX, pasBallY ;
int score;
int ballSpeedCounter;
int ballSpeed;

enum eDirection { STOP = 0, LEFT, RIGHT };
eDirection dir;



void Setup() {

    
     gameOver = false;
     start = false;

    width = 30;
    height = 15;

    pasBallX = 0, pasBallY = 0;
    score = 0;
    ballSpeedCounter = 0;
    ballSpeed = 7;
    dir = STOP;

    ballX = rand() % (width/2 - 3) + 3;
    ballY = rand() % (height / 2 - 2) + 1;

    for (int i = 0; i < barLenght; i++) {
        barX[0][i] = i + 1;
        barY[0][i] = 0;

        barX[1][i] = i + 1;
        barY[1][i] = height - 3;
    }
}

void Draw() {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

    cout << "Score: " << score << endl;

    for (int i = 0; i < width; i++) cout << "*";
    cout << endl;

    for (int i = 0; i < height - 2; i++) {
        cout << "*";
        for (int j = 0; j < width - 2; j++) {
            bool print = false;

            for (int k = 0; k < barLenght; k++) {
                if ((barX[0][k] == j) && (barY[0][k] == i)) { cout << "="; print = true; }
                if ((barX[1][k] == j) && (barY[1][k] == i)) { cout << "="; print = true; }
            }

            if (!print) {
                if (ballX == j && ballY == i) 
                    cout << "O";
                else cout << " ";
            }
        }
        cout << "*" << endl;
    }

    for (int i = 0; i < width; i++) cout << "*";
    cout << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) 
        {
        case 75: 
            dir = LEFT; 
            break;
        case 77: 
            dir = RIGHT; 
            break;
        case 'x': 
            gameOver = true; 
            break;
        default:
            break;
        }

        if (!start)
        {
            pasBallX = 1;
            pasBallY = 1;

            dir = RIGHT;
            start = true;
        }
    }
}

void Logic() {

    //c changement de direction des barres
    if (barX[0][0] <= 0) dir = RIGHT;
    if (barX[0][barLenght - 1] >= width - 2) dir = LEFT;

    for (int i = 0; i < barLenght; i++) {
        // la balle touche la barre inferieure
        if ((ballY == height - 4) && (ballX == barX[1][i]) && pasBallY > 0) {
            pasBallY = -1; score += 5;

            // augmenter la vitesse de la balle en fonction du score
            if ((score % 20 == 0) && score > 0) ballSpeed--;

            break;
        }
        // la ball touche la barre superieure
        else if ((ballY == 1) && (ballX == barX[0][i]) && pasBallY < 0)
        {
            pasBallY = 1; score += 5;
            // augmenter la vitesse de la balle en fonction du score
            if ((score % 20 == 0) && score > 0) ballSpeed--;

            break;
        }
    }

    // la balle touche le coté gauche ou droit
    if (ballX <= 1) pasBallX = 1;
    if (ballX >= width - 3) pasBallX = -1;

    // la balle touche completement le haut ou le bas de la surface
    if (ballY < 1 || ballY >= height - 3) {
        gameOver = true;
        cout << "Game Over! Final Score: " << score << endl;
    }

    // changer la direction des barres
    for (int i = 0; i < barLenght; i++) {
        if (dir == LEFT) { barX[0][i]--; barX[1][i]--; }
        if (dir == RIGHT) { barX[0][i]++; barX[1][i]++; }
    }


    if (ballSpeedCounter++ >= ballSpeed)
    {
        ballX += pasBallX;
        ballY += pasBallY;
        ballSpeedCounter = 0;
    }

}

int main() {

    string menu = "\n###################### Jeu de Pong ###################\n\n1-Jouer un tour\n0-Quitter";
    int choix;

    do {
        cout << menu << endl;
        cout << ">>";
        cin >> choix;
        
        if (choix == 1)
        {
            // Effacer l'écran pour passer uniquement au jeu
            system("cls");

            Setup();
            while (!gameOver) {
                Draw();
                Input();
                Logic();
                Sleep(10);
            }
        }
    } while (choix != 0);

    return 0;
}
