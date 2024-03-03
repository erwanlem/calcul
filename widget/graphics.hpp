#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

enum class Position {center, no, custom};

#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include "image.hpp"
#include "button.hpp"
#include "entry.hpp"
#include "checkBox.hpp"

using namespace std;

int toPercent(int n, int percent);


#endif