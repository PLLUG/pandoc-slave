TEMPLATE = subdirs

CONFIG += c++14

SUBDIRS += runner \
    builder

tests.CONFIG = recursive
QMAKE_EXTRA_TARGETS += tests
