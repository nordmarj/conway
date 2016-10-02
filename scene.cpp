#include "scene.h"
#include <vector>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

/*
 * The constructor for the scene takes the number of squares along the x and y axis, the square size in pixels l,
 * then creates a corresponding Game object, starts a timer for updating the game and paints the board.
 */
Scene::Scene(int x, int y, int l) :
    QGraphicsScene()
{
    boardHeight = y;
    boardWidth = x;
    squareSize = l;
    currentGame = new Game(x,y);
    this->setSceneRect(0,0,x*l,y*l);
    this->paintBoard();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(200);
}

/*
 * When a mousebutton is pressed the timer is stopped and handleMouseClick called.
 */
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    Qt::MouseButtons button = event->button();
    timer->blockSignals(true);
    this->handleMouseClick(x,y,button);
}

/*
 * Holding mousebuttons while moving the mouse is handled in the same way as a mouseclick.
 */
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    Qt::MouseButtons button = event->buttons();
    this->handleMouseClick(x,y,button);
}

/*
 * When the mouebutton is released, the timer is started again so the game can continue.
 */
void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    timer->blockSignals(false);
}

/*
 * This function handles mouseclicks. Right button sets a cell to zero, left button sets it to one.
 */
void Scene::handleMouseClick(int x, int y, Qt::MouseButtons button)
{
    int gridX = (x - x%squareSize)/squareSize;
    int gridY = (y - y%squareSize)/squareSize;
    if(button & Qt::LeftButton)
    {
        currentGame->setSquare(gridX,gridY,1);
    }
    if(button & Qt::RightButton)
    {
        currentGame->setSquare(gridX,gridY,0);
    }
    this->paintBoard();
}

/*
 * Makes the game update, then repaints the board.
 */
void Scene::update()
{
    currentGame->advanceTime();
    paintBoard();
}

/*
 * This loops through all positions on the board and repaint them in either black or white
 * depending on their current state.
 */
void Scene::paintBoard()
{
    this->clear();
    for(int i = 0; i < boardWidth; i++)
    {
        for(int j = 0; j < boardHeight; j++)
        {
            QGraphicsRectItem* rect = new QGraphicsRectItem(i*squareSize,j*squareSize,squareSize,squareSize);
            if(currentGame->getSquare(i,j) == 1)
            {
                rect->setBrush(Qt::black);
            }
            if(currentGame->getSquare(i,j) == 0)
            {
                rect->setBrush(Qt::white);
            }
            this->addItem(rect);
        }
    }
}
