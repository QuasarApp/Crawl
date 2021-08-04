//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef PLAYABLEOBJECT_H
#define PLAYABLEOBJECT_H

#include "global.h"
#include "iworlditem.h"
#include "Extensions/movableobject.h"

namespace CRAWL {


class IControl;

/**
 * @brief The PlayableObject class support works withe the IControl child classes.
 * **How to is works**? You need to override the  PlayableObject::setControl method for adding your own cpntroll classes. By Default This class use The DefaultControl class.
 */
class CRAWL_EXPORT PlayableObject: public IWorldItem, public MovableObject {
    Q_OBJECT
public:
    PlayableObject(const QString& name,
            const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
            QObject *ptr = nullptr);

    /**
     * @brief setControl This method should be connect player object with control object.
     * @param control This is control object.
     * @note This method can invoked two or more times, for example connect with AI control object and player control object. So your implementation should be contains disconnect methods.
     *
     * ### Example of use
     *
     * @code{cpp}
        void MyPlayableObject::setControl(const IControl *control) {


            if (auto oldControl = dynamic_cast<const DefaultControl*>(_currentControl)) {
                disconnect(oldControl, &DefaultControl::userTap, this, &PlayableObject::onTap);
                // some disconnect methodots
            }

            auto defaultControl = dynamic_cast<const DefaultControl*>(control);
            _currentControl = defaultControl;

            if (_currentControl) {
                connect(defaultControl, &DefaultControl::userTap, this, &PlayableObject::onTap);
                // some connect methodots

            }
        }
     * @endcode
     */
    virtual void setControl(const IControl* control);

protected:
    void render(unsigned int tbfMsec) override;

protected slots:
    /**
     * @brief onTap This method invoked when user tap on screen.
     * @note method connected in the IPlayer::setControl function. So if you overrid the IPlayer::setControl method then please invoke method of a parent class.
     */
    virtual void onTap() = 0;


private:
    const IControl * _currentControl = nullptr;

};

}

#endif // PLAYABLEOBJECT_H
