#ifndef PAINTAREA_H
#define PAINTAREA_H

#include "document.h"

#include <QWidget>
#include <QPainter>
#include <QFont>

class PaintNode;

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = 0);
    void drawDocument(QPainter *qPainter);
    void drawDocument(QPainter *qPainter, std::vector<PaintNode*> *paintNodes);
    void paintCurrentNode(PaintNode *currentPaintNode, QPainter *qPainter);
    void setDocument(Document *documentToSet);
    void insertLineBreak();
    void updateCurrentPosition();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    Document *webpage;
    int currentX;
    int currentY;
    int totalWidth;
    bool positionSet;
    QString *currentCharacter;
    QFont currentFont;
    std::vector<PaintNode*> *paintNodesVector;
};

#endif // PAINTAREA_H
