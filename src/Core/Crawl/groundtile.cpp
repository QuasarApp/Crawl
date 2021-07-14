#include "groundtile.h"
namespace CRAWL {

GroundTile::GroundTile(const QString &name,
                       const QString &viewTempalte,
                       QObject *ptr):
    ClasterItem(name, viewTempalte, ptr) {

}

void CRAWL::GroundTile::render(unsigned int) {

}
}
