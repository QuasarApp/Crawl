unix:exec = $$PWD/SnakeServer/serverProtocolTests/build/release/serverTests
win32:exec = $$PWD/SnakeServer/serverProtocolTests/build/release/serverTests.exe

deployTest.commands = cqtdeployer -bin $$exec clear -qmake $$QMAKE_QMAKE -targetDir $$PWD/deployTests -libDir $$PWD -recursiveDepth 5

test.depends = deployTest
unix:test.commands = $$PWD/deployTests/serverTests.sh
win32:test.commands = $$PWD/deployTests/serverTests.exe

QMAKE_EXTRA_TARGETS += \
    deployTest \
    test
