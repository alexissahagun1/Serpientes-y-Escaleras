#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iterator>
#include "CDado.h"
#define snake 'S'
#define ladder 'D'
#define normal 'N'
#define CONTINUE 'C'
#define EXIT 'E'
using namespace std;

class Casilla
{

public:
    char tipo;
    int posicion;
    int penalizacion;
    int reward;
};

class Player
{
public:
    int posicion = 0;
    int id;
    bool special = false;
};

class Game
{
public:
    int turns;
    Casilla casll[100];
    Player ply[100];
};

class MyGame : public Game
{

public:
    CDado dice;
    char opcion, tipoJuego;
    int Tiles, Snakes, Ladders, Penalty, Reward, Players, Turns, turno = 1;
    void start()
    {
        int cont_s = 0;
        int cont_e = 0;
        bool juego = true;

        cout << "Type an opcion \n D: Juego Defaul \n S: Juego Personalizado" << endl;
        cin >> opcion;
        if (opcion == 'S')
        {
            cout << "Type the number of Tiles: \n";
            cin >> Tiles;
            cout << "Type the number of Snakes: \n";
            cin >> Snakes;
            cout << "Type the number of Ladders: \n";
            cin >> Ladders;
            cout << "Type the amount of the penalizacion: \n";
            cin >> Penalty;
            cout << "Type the amount of the Reward: \n";
            cin >> Reward;
            cout << "Type the number of Players: \n";
            cin >> Players;
            cout << "Type the number of Turns: \n";
            cin >> Turns;
            cout << "Type the game tipo: \n";
            cin >> tipoJuego;
        }
        else
        {
            Tiles = 30;
            Snakes = 6;
            Ladders = 6;
            Penalty = 6;
            Reward = 6;
            Players = 2;
            Turns = 30;
        }

        for (int i = 0; i < Tiles; i++)
        {
            switch (rand() % 3)
            {
                case 0:
                    if (cont_s < Snakes)
                    {
                        casll[i].tipo = snake;
                        cont_s++;
                    }
                    else
                    {
                        casll[i].tipo = normal;
                    }
                    break;
                case 1:
                    if (cont_s < Ladders)
                    {
                        casll[i].tipo = ladder;
                        cont_e++;
                    }
                    else
                    {
                        casll[i].tipo = normal;
                    }
                default:
                    casll[i].tipo = normal;
                    break;
            }
            casll[i].posicion = i + 1;
            casll[i].penalizacion = Penalty;
            casll[i].reward = Reward;
        }

        for (int i = 0; i < Players; i++)
        {
            ply[i].id = i + 1;
            ply[i].posicion = 1;
        }

        turno = 1;
        while (juego)
        {
            if (tipoJuego == 'M')
            {
                cout << "C: Quieres Continuar? \n E: Finalizar juego? \n";
                cin >> opcion;
                if (opcion == 'E')
                {
                    endgame(0, true);
                }
                else
                {
                    if (turn())
                    {
                        juego = false;
                    }
                }
            }
            else
            {
                if (turn())
                {
                    juego = false;
                }
            }
        }
    }

    bool turn()
    {
        int dado1;
        for (int i = 0; i < Players; i++)
        {
            dado1 = dice.GetValorDado();
            if (this->ply[i].posicion + dado1 >= Tiles || turno > Turns)
            {
                return endgame(i + 1, false);
            }
            else
            {
                cout << endl << turno;
                cout << " " << i+1;
                cout << " " << ply[1].posicion;
                cout << " " << dado1;
                ply[i].posicion += dado1;
                ply[i].posicion += this->special(casll[ply[i].posicion - 1].tipo);
                cout << " " << casll[ply[i].posicion - 1].tipo;
                cout << " " << ply[i].posicion;
                char tipo = casll[ply[i].posicion - 1].tipo;
                cout << endl;
            }
        }
        turno++;
        return false;
    }
    bool endgame(int player, bool stop)
    {
        if (stop)
        {
            cout << "GAME OVER";
        }
        else {
                if (turno == Turns) {

                    cout << "The maximum number of Turns has been reached...";
                }
                cout << "Player " << player << " wins!";
            }
        return true;
    }
    int special(char type)
    {
        if (type == snake)
        {
            return this->casll[0].penalizacion * -1;
        }
        else if (type == ladder)
        {
            return this->casll[0].penalizacion;
        }
        else
        {
            return 0;
        }
    }
};

int main()
{
    MyGame mg;
    mg.start();
    return 0;
}