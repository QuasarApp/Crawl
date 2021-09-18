//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef LAYOUT_H
#define LAYOUT_H

#include <Crawl/groupobject.h>


namespace CRAWL {

/**
 * @brief The LayoutType enum Lists the shapes to convert the group object to.
 */
enum LayoutType {
    /// The circle property calls the drawCircle method, which recalculates and updates
    /// the coordinates of the passed object's positions.
    CIRCLE,

    /// The square property calls the drawSquare method, which updates the coordinates of
    /// the objects' positions, giving them the shape of a square.
    SQUARE,

    /// The LINE property calls the drawLine method, which updates the coordinates of the
    /// objects' positions, giving it a line shape.
    LINE
};

/**
 * @brief The Layout class The class that control position of group objects.
 * ### Requried child classes: IWorldItem
 *
 * This class overloads the add() and remove() methods, which add objects to the cluster while updating positions according to the selected LayoutType.
 * Has two public methods for setting the distance to the object and selecting the grouping of objects.
 *
 * ## Example of use
 *
 * ### For what this object uses
 * This object is convenient to use if you want to create a cluster object directly, within which subobjects are grouped into a circle or square, depending on the selected property.
 * For example : snake obstacle.
 *
 * ### Example of use
 *
 * 1. Create the GroupObjObstacle class.
 *
 * ```cpp
 *
 * class GroupObjObstacle: public CRAWL::Layout, public CRAWL::IWorldItem {
 *
 *      // sets the distance to the object from the center.
 *      setDistance(20);
 *
 *      // Set the property of grouping objects
 *      changeLayout(CRAWL::LayoutType::CIRCLE);
 *
 *      for(int i(0); i < 20; i++) {
 *          add(new BoxItem);
 *      }
 *
 * };
 * ```
 *
 * @note The added object must inherit from ClasterItem and have a child class required for overloading software renderers.
 *
 * All done. Now the added objects will be grouped into a circle shape.
 *
 * You can change the center-to-object distance and the shape of a group of objects using the setDistance and changeLayout methods.
 *
 * @note This class requried the GuiObject functions as a parent class.
 * @note This class requires an overload of the render method; The implementation must call the render methods of the parent classes.
 *
 */
class Layout: public GroupObject {
public:
    Layout();

// Claster interface
public:
    void add(ClasterItem *object);
    void remove(ClasterItem *object);

    /**
     * @brief changeLayout This method defines the shape of the group object.
     * @param fig This is the name of the figure to change the group object.
     */
    void changeLayout(const LayoutType &fig);

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
    LayoutType _shape;

};

}
#endif // LAYOUT_H
