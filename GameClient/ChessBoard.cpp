#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pieces.h"
#include "ChessBoard.h"
#include <fstream>

int spritepositions[64] = {
    0,1,2,3,4,5,6,7,
    8,9,10,11,12,13,14,15,
    64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,
    48,49,50,51,52,53,54,55,
    56,57,58,59,60,61,62,63 };

int board_2[64] = {
   -1,-2,-3,-4,-5,-3,-2,-1,
   -6,-6,-6,-6,-6,-6,-6,-6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    6, 6, 6, 6, 6, 6, 6, 6,
    1, 2, 3, 4, 5, 3, 2, 1 };

void ChessBoard::loadtextures(Texture texture[64]) 
{
    for (int i = 0; i < 64; i++) 
    {
        if (spritepositions[i] == 0 || spritepositions[i] == 7)
            texture[i].loadFromFile("images/blackRook.png");
        if (spritepositions[i] == 1 || spritepositions[i] == 6)
            texture[i].loadFromFile("images/blackKnight.png");
        if (spritepositions[i] == 2 || spritepositions[i] == 5)
            texture[i].loadFromFile("images/blackBishop.png");
        if (spritepositions[i] == 3)
            texture[i].loadFromFile("images/blackQueen.png");
        if (spritepositions[i] == 4)
            texture[i].loadFromFile("images/blackKing.png");
        if (spritepositions[i] >= 8 & spritepositions[i] <= 15)
            texture[i].loadFromFile("images/blackPawn.png");
        if (spritepositions[i] == 63 || spritepositions[i] == 56)
            texture[i].loadFromFile("images/whiteRook.png");
        if (spritepositions[i] == 62 || spritepositions[i] == 57)
            texture[i].loadFromFile("images/whiteKnight.png");
        if (spritepositions[i] == 61 || spritepositions[i] == 58)
            texture[i].loadFromFile("images/whiteBishop.png");
        if (spritepositions[i] == 59)
            texture[i].loadFromFile("images/whiteQueen.png");
        if (spritepositions[i] == 60)
            texture[i].loadFromFile("images/whiteKing.png");
        if (spritepositions[i] >= 48 & spritepositions[i] <= 55)
            texture[i].loadFromFile("images/whitePawn.png");
    }
}
void ChessBoard::loadboard(Texture texture[64], RectangleShape rectangle[64], Sprite sprite[64]) 
{
    for (int j = 0; j < 64; j++) 
    {
        sprite[j].setTexture(texture[j]);
        sprite[j].setScale(1.7f, 1.7f);
    }
    for (int j = 0; j < 64; ++j)
    {
        rectangle[j].setSize(sf::Vector2f(WIDTH / 8.0f, HEIGTH / 8.0f));
    }
    int counter = 0;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            rectangle[counter].setPosition(j * rectangle[counter].getSize().y, i * rectangle[counter].getSize().x);  ///x,y
            sprite[counter].setPosition(j * rectangle[counter].getSize().y, i * rectangle[counter].getSize().x);
            if ((i + j) % 2 == 0)
                rectangle[counter].setFillColor(sf::Color::White);
            else
                rectangle[counter].setFillColor(sf::Color::Blue);
            counter++;
        }
    }
}

void ChessBoard::run()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "Chess The Game Of Kings!");
    sf::RectangleShape rectangle[64];
    sf::Texture texture[65];
    sf::Sprite sprite[65];
    loadtextures(texture);
    loadboard(texture, rectangle, sprite);
    Identity box;
    bool isMove;
    float dx = 0, dy = 0;
    Vector2f oldPos, newPos;
    int n;
    int cc, turn = 1;
    int alience, position;
    Vector2f firstpos, secondpos;
    int v; int q[64];
    static int cap = 0;
    for (int j = 0; j < 64; ++j)
        q[j] = 64;
    Vector2i pos;
    while (window.isOpen())
    {
        pos = Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
            {
                // Black pieces turn
                for (int j = 0; j < 64; ++j) 
                {
                    if (turn % 2 == 0 & board_2[j] < 0) 
                    {
                        if (rectangle[j].getGlobalBounds().contains(pos.x, pos.y))
                        {
                            n = j;
                            firstpos = rectangle[j].getPosition();
                            v = spritepositions[j];
                            rectangle[n].setFillColor(sf::Color::Red);
                            if (spritepositions[n] != 64)
                                cap++;
                        }
                    }
                }
                // White pieces turn
                for (int j = 0; j < 64; ++j) 
                {
                    if (turn % 2 != 0 & board_2[j] > 0) 
                    {
                        if (rectangle[j].getGlobalBounds().contains(pos.x, pos.y))
                        {
                            n = j;
                            firstpos = rectangle[j].getPosition();
                            v = spritepositions[j];
                            rectangle[n].setFillColor(sf::Color::Red);
                            if (spritepositions[n] != 64)
                                cap++;
                        }
                    }
                }

            }
            if (cap != 0)
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
                {
                    for (int j = 0; j < 64; ++j) 
                    {
                        if (rectangle[j].getGlobalBounds().contains(pos.x, pos.y)) 
                        {
                            isMove = box.identifier(n, j, board_2[n], board_2);//<<"=identity"<<endl;
                            secondpos = rectangle[j].getPosition();
                            int spritepos = spritepositions[n];
                            if (isMove) 
                            {
                                turn++;
                                cc = q[j] = spritepositions[j];
                                if (j != n) 
                                {
                                    sprite[spritepos].setPosition(secondpos);
                                    sprite[cc].setPosition(100000000, 100000000);
                                    int suppos = spritepositions[j];
                                    spritepositions[j] = spritepositions[n];
                                    spritepositions[n] = 64;
                                    if (board_2[j] == -5 || board_2[j] == 5) 
                                    {
                                        window.close();
                                    }
                                    if (j <= 63 & j >= 56 & board_2[n] == -6) 
                                    {
                                        board_2[j] = -4;
                                    }
                                    else if (j >= 0 & j <= 7 & board_2[n] == 6) 
                                    {
                                        board_2[j] = 4;
                                    }
                                    else 
                                    {
                                        board_2[j] = board_2[n];
                                        board_2[n] = 0;
                                    }
                                    n = j;
                                }
                            }
                            int counter = 0;
                            for (int i = 0; i < 8; ++i) {
                                for (int j = 0; j < 8; ++j) {
                                    if ((i + j) % 2 == 0)
                                        rectangle[counter].setFillColor(sf::Color::White);
                                    else
                                        rectangle[counter].setFillColor(sf::Color::Blue);
                                    counter++;

                                }

                            }

                        }
                    }
                    cap = 0;

                    }
            
        }

        window.clear();
        for (int j = 0; j < 64; ++j)
            window.draw(rectangle[j]);
        for (int j = 0; j < 65; j++) {
            if (q[j] == 64)
                window.draw(sprite[j]);
        }

        window.display();
    }
}
