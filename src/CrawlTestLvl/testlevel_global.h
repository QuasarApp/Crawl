#ifndef Crawl_TEST_LEVEL_GLOBAL_H
#define Crawl_TEST_LEVEL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CRAWL_TEST_LEVEL_LIBRARY)
#  define CRAWL_TEST_LEVEL_EXPORT Q_DECL_EXPORT
#else
#  define CRAWL_TEST_LEVEL_EXPORT Q_DECL_IMPORT
#endif

#endif // Crawl_TEST_LEVEL_GLOBAL_H
