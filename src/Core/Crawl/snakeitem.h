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

namespace CRAWL {


class CRAWL_EXPORT SnakeItem: public SingleClasterWorldItem, public MovableObject
{
    Q_OBJECT
public:
    SnakeItem(const QString& name,
              const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
              QObject *ptr = nullptr);

    /**
     * @brief setPrev This method sets id of the previous snake item.
     * @param newPrev this is new value of the previous snake item.
     */
    void setPrev(const IWorldItem * newPrev);
    void render(unsigned int tbfMsec) override;

    /**
     * @brief prev This method return prev object of snake
     * @return the prev objects of the snake
     */
    const IWorldItem * prev() const;

    /**
     * @brief lengthBetwinItems This method return current length betwin current and parew item.
     * @return current length betwin current and parew item.
     * @note See also the setPrev method.
     */
    float lengthBetwinItems() const;

    /**
     * @brief setLengthBetwinItems This method sets new valeu of the length betwin current and parew item.
     * @param newLengthBetwinItems This is new value of the length betwin current and parew item.
     */
    void setLengthBetwinItems(float newLengthBetwinItems);

private:
    const IWorldItem *_prevObject = nullptr;
    float _lengthBetwinItems = 1;
};

}

#endif // SNAKEITEM_H
