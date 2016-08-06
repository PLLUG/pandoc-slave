QT += testlib xml

# Location of autotests project dir
TESTS_DIR = $$_PRO_FILE_PWD_/..

CONFIG += silent

DESTDIR = $$TESTS_DIR

COMMAND = $${TESTS_DIR}/$${TARGET}
win32 {
    tests.commands = $$replace(COMMAND, /, \\)
} else {
    tests.commands = $$COMMAND
}
QMAKE_EXTRA_TARGETS += tests

DEFINES += EXECUTABLE_PATH=\\\"$$PWD/..\\\"
