#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include "game.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
    
public:
    explicit Scene(int x = 10, int y = 10, int l = 10);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void handleMouseClick(int x, int y, Qt::MouseButtons button);
    void paintBoard();

private:
    int boardWidth;
    int boardHeight;
    int squareSize;
    Game * currentGame;
    QTimer * timer;

signals:
    void timeout();

public slots:
    void update();
};

#endif // SCENE_H
