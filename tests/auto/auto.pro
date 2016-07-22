TEMPLATE = subdirs

SUBDIRS += runner

tests.CONFIG = recursive
QMAKE_EXTRA_TARGETS += tests
