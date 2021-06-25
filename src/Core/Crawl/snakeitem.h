//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef SNAKEITEM_H
#define SNAKEITEM_H

#include "singleclasterworlditem.h"
#include "Extensions/movableobject.h"

class CRAWL_EXPORT SnakeItem: public SingleClasterWorldItem, protected MovableObject
{
    Q_OBJECT
public:
    SnakeItem(const QString itemName = "SnakeItem");

    /**
     * @brief setPrev This method sets id of the previous snake item.
     * @param newPrev this is new value of the id of previous snake item.
     */
    void setPrev(int newPrev);
    void render(unsigned int tbfMsec) override;

    /**
     * @brief prev This method return prev object of snake
     * @return id of the prev objects of the snake
     */
    int prev() const;

private:
    int _prev = -1;
};

#endif // SNAKEITEM_H
