CURDIR := $(shell pwd)

lowercase = $(shell echo $1 | tr A-Z a-z)

GTEST_LIBS_PATH := deps/gtest/cbuild
SYS_NAME := $(shell uname -s)
SYS_NAME_LOWER := $(call lowercase,${SYS_NAME})


ifeq (${SYS_NAME_LOWER},linux)
	SYS_CMAKE_FLAGS :=
else
	SYS_CMAKE_FLAGS := -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libstdc++ -U__STRICT_ANSI__"
endif


clean:
	@rm -rf out

lib-v8:
	@./tools/gyp_bastian bastian.gyp -Dhost_arch=x64
	@make -C out

test/v8/run: ${GTEST_LIBS_PATH} lib-v8
	@g++ -o test/v8/run -L${CURDIR}/${GTEST_LIBS_PATH} -lgtest -lgtest_main

test-v8: test/v8/run
	@./test/v8/run

${GTEST_LIBS_PATH}:
	@mkdir ${GTEST_LIBS_PATH}
	@cd ${GTEST_LIBS_PATH} && cmake -G"Unix Makefiles" ${SYS_CMAKE_FLAGS} .. && make
