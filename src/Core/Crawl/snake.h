//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef SNAKE_H
#define SNAKE_H

#include "iplayer.h"
#include "Extensions/claster.h"

/**
 * @brief The Snake class This class implement render mehod for snake object.
 */
class CRAWL_EXPORT Snake : public IPlayer, public Claster
{
    Q_OBJECT
public:
    Snake(const QString& name,
          const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
          QObject *ptr = nullptr);

    void render(unsigned int tbfMsec) override;

    void add(ClasterItem *object) override;
    void remove(ClasterItem *object) override;
    void remove(int id) override;

    // IPlayer interface
    /**
     * @brief lengthBetwinItems This method return length betwin snake items;
     * @return length betwin snake items
     */
    float lengthBetwinItems() const;

    /**
     * @brief setLengthBetwinItems This method sets length betwin snake items.
     * @param newLengthBetwinItems This is new value of the length betwin snake items.
     */
    void setLengthBetwinItems(float newLengthBetwinItems);

protected slots:
    void onTap() override;

private:
    float _lengthBetwinItems = 0;
    const IWorldItem* _lastSnakeItem = nullptr;

};

#endif // SNAKE_H
