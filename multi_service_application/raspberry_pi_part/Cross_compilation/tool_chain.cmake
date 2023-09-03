
# # search headers and libraries in the target environment
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# set(CMAKE_SYSTEM_NAME Linux)
# set(CMAKE_SYSTEM_PROCESSOR arm)

# # Specify the cross-compiler
# set(CMAKE_C_COMPILER /home/ziad/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi-linux-gnu-g++)
# set(CMAKE_CXX_COMPILER /home/ziad/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi-linux-gnu-g++)
# set(CMAKE_FIND_ROOT_PATH  /home/ziad/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi-linux-gnu-g++)
# # Specify the root filesystem of your Raspberry Pi (optional)
# # set(CMAKE_FIND_ROOT_PATH /path/to/your/rpi/rootfs)

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

# Specify the cross compiler
SET(CMAKE_C_COMPILER $ENV{HOME}/home/ziad/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER $ENV{HOME}/home/ziad/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi-linux-gnu-g++)

# Where is the target environment
SET(CMAKE_FIND_ROOT_PATH /home/ziad/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi-linux-gnu-g++)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")
SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")

# Search for programs only in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search for libraries and headers only in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
