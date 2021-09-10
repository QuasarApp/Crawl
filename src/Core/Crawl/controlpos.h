//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef CONTROLPOS_H
#define CONTROLPOS_H

#include <Crawl/groupobject.h>


namespace CRAWL {

/**
 * @brief The Refresh enum Lists the shapes to convert the group object to.
 */
enum Refresh {
    CIRCLE,
    SQUARE,
    LINE
};

/**
 * @brief The ControlPos class The class that control position of group objects.
 */
class ControlPos: public GroupObject {
public:
    ControlPos();

// Claster interface
public:
    void add(ClasterItem *object);
    void remove(ClasterItem *object);

    /**
     * @brief changeLayout This method defines the shape of the group object.
     * @param fig This is the name of the figure to change the group object.
     */
    void changeLayout(const Refresh &fig);

    /**
     * @brief setDistance This method sets, depending on the shape selected, the radius for the circle or the indentation for the square.
     * @param dist This is the radius or margin.
     */
    void setDistance(int dist);

private:


    /**
     * @brief updatePosition This method updates the coordinates of the positions of all objects.
     */
    void updatePosition();

    /**
     * @brief drawCircle This method updates the coordinates to a circle shape.
     */
    void drawCircle();

    /**
     * @brief drawSquare This method updates the coordinates to a square shape.
     */
    void drawSquare();

    /**
     * @brief drawLine This method updates the coordinates to a line shape.
     */
    void drawLine();
    
    int _distance;
    Refresh _shape;

};

}
#endif // CONTROLPOS_H
