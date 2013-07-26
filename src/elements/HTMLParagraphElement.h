#ifndef HTMLPELEMENT_H
#define HTMLPELEMENT_H

#include "HTMLElement.h"
#include "nodes/paragraphnode.h"

class HTMLParagraphElement : HTMLElement
{
public:
    HTMLParagraphElement();
    virtual ParagraphNode *returnNode();

private:
    ParagraphNode *paragraphNode;
};

#endif // HTMLPELEMENT_H
