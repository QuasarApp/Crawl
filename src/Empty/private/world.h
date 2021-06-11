#ifndef WORLD_H
#define WORLD_H

#include "SnakeProject/iworld.h"

class World : public IWorld {

    // IWorld interface
public:
    IGround *generateGroundTile() override;
    IPlayer *initPlayer() const override;
    WorldRule *initWorldRules() const override;
    QString initHdrBackGround() const override;
    QString description() const override;
    QString imagePreview() const override;
    QString name() const override;
    int costToUnlock() const override;
    QVector3D initCameraPosition() override;

protected:
    IWorldItem *generate(const QString &objectType) const override;
};

#endif // WORLD_H
