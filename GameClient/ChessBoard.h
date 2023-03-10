#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Pieces.h"

using namespace sf;
using namespace std;


class ChessBoard{
  private:
    const float WIDTH = 650;
    const float HEIGTH = 650;
  public:
    void loadtextures(Texture texture[64]);
    void loadboard(Texture texture[64],RectangleShape rectangle[64],Sprite sprite[64]);
    void run(bool isWhite);
  
};
