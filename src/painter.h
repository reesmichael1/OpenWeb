#ifndef PAINTER_H
#define PAINTER_H

#include "rendernode.h"

class Painter
{
public:
    Painter();
    static void paintNode(RenderNode *node);
};

#endif // PAINTER_H
