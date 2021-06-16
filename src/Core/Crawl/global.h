#ifndef Crawl_GLOBAL_H
#define Crawl_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CRAWL_LIBRARY)
#  define CRAWL_EXPORT Q_DECL_EXPORT
#else
#  define CRAWL_EXPORT Q_DECL_IMPORT
#endif

#endif // QTSECRET_GLOBAL_H
