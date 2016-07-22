TEMPLATE = subdirs

SUBDIRS += auto

tests.CONFIG = recursive

QMAKE_EXTRA_TARGETS += tests
