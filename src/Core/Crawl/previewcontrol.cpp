//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "previewcontrol.h"

namespace CRAWL {

PreviewControl::PreviewControl() {

}

QString PreviewControl::initQmlView() const {
    return "qrc:/CrawlModule/PreviewControl.qml";
}

}
