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

    depthBias: (model)? model.depthBias: 0
    emitRate: (model)? model.emitRate: 0

    enabled: (model)? model.enabled: false
    lifeSpan: (model)? model.lifeSpan: 0
    lifeSpanVariation: (model)? model.lifeSpanVariation: 0
    particleEndScale: (model)? model.particleEndScale: 0
    particleRotation: (model)? model.particleRotation: Qt.vector3d(0, 0, 0)
    particleRotationVariation: (model)? model.particleRotationVariation: Qt.vector3d(0, 0, 0)
    particleRotationVelocity: (model)? model.particleRotationVelocity: Qt.vector3d(0, 0, 0)
    particleRotationVelocityVariation: (model)? model.particleRotationVelocityVariation: Qt.vector3d(0, 0, 0)
    particleScaleVariation: (model)? model.particleScaleVariation: 0

    onModelChanged: () => {
                        if (root.model) {
                            root.model.viewObject = root;
                        }
                    }

    Item {
        id: privateRoot
        property var velosity: (model)? model.velocity: null
        property string delegate: (model)? model.particleDelegate: ""
        property string particleShape: (model)? model.particleShape: ""
        property var view: null

        onVelosityChanged: () => {
                               if (!root.model)
                                   return;

                               const objModel = root.model.velocity;

                               if (!objModel) {
                                   if (view) {
                                       view.distory();
                                   }

                                   root.velocity = view = null;
                                   return;
                               }

                               const viewTemplate = objModel.viewTemplate;

                               if (!view || (view.path !== viewTemplate)) {
                                   let temp = Qt.createComponent(viewTemplate)

                                   if (!temp)
                                       return

                                   if (temp.status === Component.Ready) {
                                       let obj = temp.createObject(root)
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
        onDelegateChanged: () => {
                               let temp = Qt.createComponent(privateRoot.delegate)

                               if (!temp)
                                   return

                               if (temp.status === Component.Ready) {
                                   root.particle =  temp.createObject(root.parent);
                               } else {
                                   console.log("wrong viewTemplate in model " + temp.errorString());
                               }
                           }

        onParticleShapeChanged: () => {
                                    let temp = Qt.createComponent(privateRoot.particleShape)

                                    if (!temp)
                                        return

                                    if (temp.status === Component.Ready) {
                                        root.shape =  temp.createObject(root.parent);
                                    } else {
                                        console.log("wrong viewTemplate in model " + temp.errorString());
                                    }
                                }
    }
}
