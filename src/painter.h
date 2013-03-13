#ifndef PAINTER_H
#define PAINTER_H

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Text.hpp"
#include "rendernode.h"

class Painter
{
public:
    Painter(RenderNode *node);
    static void paintNode(RenderNode *node, sf::RenderWindow *window);

private:

};

#endif // PAINTER_H
