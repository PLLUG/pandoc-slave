TEMPLATE = subdirs

SUBDIRS += runner \
    builder

tests.CONFIG = recursive
QMAKE_EXTRA_TARGETS += tests
