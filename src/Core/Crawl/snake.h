//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef CRAWL_SNAKE_H
#define CRAWL_SNAKE_H

#include "iplayer.h"
#include "Extensions/autogenerateclaster.h"

namespace CRAWL {

class SnakeItem;

/**
 * @brief The Snake class This class implement render mehod for snake object.
 */
class CRAWL_EXPORT Snake : public IPlayer, public AutoGenerateClaster
{
    Q_OBJECT
public:
    Snake(const QString& name,
          const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
          QObject *ptr = nullptr);
    ~Snake() override;

    void render(unsigned int tbfMsec) override;

    void add(ClasterItem *object) override;
    void remove(ClasterItem *object) override;
    void remove(int id) override;
    void init() override;


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

    /**
     * @brief scales This method return the map of the snake body scales.
     *  The key of map are position of snake Body and the value are scale factor of current body item.
     *  The default scales map of snake are:
     *  ```
     *  0.0 - 0.8
     *  0.6 - 1.2
     *  1   - 0.5
     *  ```
     * @return scales map of snake body.
     */
    const QMap<float, float> &scales() const;

    /**
     * @brief setScales This method sets new scales map for snake body.
     * @param newScales This is new value of the scales map.
     */
    void setScales(const QMap<float, float> &newScales);

    /**
     * @brief speed This method return current speed snake speed.
     * @return snake speed
     */
    float speed() const;

    /**
     * @brief setSpeed This method sets new current speed of the snake.
     * @param newSpeed new value of the snake speed.
     */
    void setSpeed(float newSpeed);

    unsigned int itemsCount() const override;

protected slots:
    void onTap() override;


private:
    void generateItems() override;

    QMap<float, float> _scales;

    float _lengthBetwinItems;
    const IWorldItem* _lastSnakeItem = nullptr;
    unsigned int _clickIndex;
    QVector3D* _vectors;
    float _speed;

};

}

#endif // CRAWL_SNAKE_H
