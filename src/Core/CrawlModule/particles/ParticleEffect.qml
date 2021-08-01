//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick
import QtQuick3D
import QtQuick3D.Particles3D

ParticleEmitter3D {

    id: root

    property var model: null
    property int guiId: (model) ? model.guiId : -1;

    rotation: (model)? model.rotation: Qt.quaternion(0, 0, 0, 0)
    scale: (model)? model.size: Qt.vector3d(0, 0, 0);
    position: (model) ? model.position: Qt.vector3d(0,0,0);
    visible: (model)? model.visible: false

    depthBias: (model)? model.depthBias: depthBias
    emitRate: (model)? model.emitRate: emitRate
    enabled: (model)? model.enabled: enabled
    lifeSpan: (model)? model.lifeSpan: lifeSpan
    lifeSpanVariation: (model)? model.lifeSpanVariation: lifeSpanVariation
    particle: (model)? model.particle: particle
    particleEndScale: (model)? model.particleEndScale: particleEndScale
    particleRotation: (model)? model.particleRotation: particleRotation
    particleRotationVariation: (model)? model.particleRotationVariation: particleRotationVariation
    particleRotationVelocity: (model)? model.particleRotationVelocity: particleRotationVelocity
    particleRotationVelocityVariation: (model)? model.particleRotationVelocityVariation: particleRotationVelocityVariation
    particleScaleVariation: (model)? model.particleScaleVariation: particleScaleVariation

    onModelChanged: () => {
                        if (root.model) {
                            root.model.viewObject = root;
                        }
                    }

    Connections {
        id: privateRoot
        target: model

        property var view: null

        onVelocityChanged: () => {
            const objModel = model.velocity;

            if (!objModel) {
                if (view) {
                    view.distory();
                }

                root.velocity = view = null;
                return;
            }

            const viewTemplate = objModel.viewTemplate;

            if (view.path !== viewTemplate) {
                let temp = Qt.createComponent(viewTemplate)
                if (temp.status === Component.Ready) {
                    let obj = temp.createObject()
                    obj.model = objModel;

                    if (view) {
                        view.distory();
                    }

                    root.velocity = view = obj;
                } else {
                    console.log("wrong viewTemplate in model " + temp.errorString());
                }
            }
        }

        onParticleDelegateChanged: () => {
                                       const viewTemplate = root.model.particleDelegate
                                       let temp = Qt.createComponent(viewTemplate)
                                       if (temp.status === Component.Ready) {
                                           root.particle =  temp.createObject();
                                       } else {
                                           console.log("wrong viewTemplate in model " + temp.errorString());
                                       }
                                   }

        onParticleShapeChanged: () => {
                                    const viewTemplate = root.model.particleShape
                                    let temp = Qt.createComponent(viewTemplate)
                                    if (temp.status === Component.Ready) {
                                        root.shape =  temp.createObject();
                                    } else {
                                        console.log("wrong viewTemplate in model " + temp.errorString());
                                    }
                                }
    }
}
