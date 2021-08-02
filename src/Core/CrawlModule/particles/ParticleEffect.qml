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

    Connections {
        id: privateRoot
        target: model

        property var view: null

        function onVelocityChanged() {
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

        function onParticleDelegateChanged () {
            const viewTemplate = root.model.particleDelegate
            let temp = Qt.createComponent(viewTemplate)
            if (temp.status === Component.Ready) {
                root.particle =  temp.createObject();
            } else {
                console.log("wrong viewTemplate in model " + temp.errorString());
            }
        }

        function onParticleShapeChanged() {
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
