//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef CRAWL_SNAKE_H
#define CRAWL_SNAKE_H

#include "playableobject.h"
#include "Extensions/autogenerateclaster.h"

namespace CRAWL {

class SnakeItem;

/**
 * @brief The Snake class This class implement render mehod for snake object.
 */
class CRAWL_EXPORT Snake : public PlayableObject, public AutoGenerateClaster
{
    Q_OBJECT
public:
    Snake(const QString& name,
          const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
          QObject *ptr = nullptr);
    ~Snake() override;

    QString itemTextType() const override;

    /**
     * @brief type This method return const string value of the all world types.
     * @return const string value of the all world types.
     * @see IItem::itemTextType
     * @see IItem::type
     */
    static QString typeText();

    /**
     * @brief type This is wrapper of the IWorld::typeText method that invoke the qHash function for results string.
     * @return integer type object id.
     */
    static unsigned int type();

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

    /**
     * @brief lengthBetwinItemsMap This method return map with lengths betwin items.
     * The key of map are position of snake Body and the value are length  betwin this current and parent items.
     *  The default map of snake are:
     *  ```
     *  0.0 - 0.8
     *  0.6 - 1.2
     *  1   - 0.5
     *  ```
     * @return  length betwin items map of snake body.
     */
    const QMap<float, float> &lengthBetwinItemsMap() const;

    /**
     * @brief setLengthBetwinItemsMap This method sets new valud of the length betwin items map.
     * @param newLengthBetwinItemsMap this is new value of the length betwin tems map.
     * @note for get more information see the lengthBetwinItemsMap method.
     */
    void setLengthBetwinItemsMap(const QMap<float, float> &newLengthBetwinItemsMap);

    /**
     * @brief getValueFromMap This method return near value from the map by position.
     * @param map This is map that contains list of the values.
     * @param position This requried position from map.
     * @param defaultValue This value will be returned when map are empty.
     * @return near value of the requried position.
     *
     * @note This function works as a gradient.
     */
    float getValueFromMap(const QMap<float, float> &map,
                          float position,
                          float defaultValue = 1);

protected slots:
    void onTap() override;


private:
    void generateItems() override;


    QMap<float, float> _scales;
    QMap<float, float> _lengthBetwinItemsMap;

    float _lengthBetwinItems;
    const IWorldItem* _lastSnakeItem = nullptr;
    unsigned int _clickIndex;
    QVector3D* _vectors;
    float _speed;

    int _hp = 100;

};

}

#endif // CRAWL_SNAKE_H
