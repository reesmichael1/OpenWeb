#include <iostream>
#include <string>
#include "paragraphnode.h"

ParagraphNode::ParagraphNode()
{
    setNeedsPainting(true);
    setTypeOfRenderNode("p");
}
