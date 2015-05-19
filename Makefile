CURDIR := $(shell pwd)

lowercase = $(shell echo $1 | tr A-Z a-z)

GTEST_LIBS_PATH := deps/gtest/cbuild
SYS_NAME := $(shell uname -s)
SYS_NAME_LOWER := $(call lowercase,${SYS_NAME})
RUN_TEST := ./out/Debug/test-bastian

ifeq (${SYS_NAME_LOWER},linux)
	SYS_CMAKE_FLAGS :=
else
	SYS_CMAKE_FLAGS := -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libstdc++ -U__STRICT_ANSI__"
endif


clean:
	@rm -rf out/Debug/obj.target/bastian
	@rm -rf ${RUN_TEST}

test-v8: clean ${GTEST_LIBS_PATH}
	@./tools/gyp_bastian test/test.gyp -Dbastian_engine=v8 -Dhost_arch=x64
	@make -C out
	@${RUN_TEST}

test-jsc: clean ${GTEST_LIBS_PATH}
	@./tools/gyp_bastian test/test.gyp -Dbastian_engine=jsc -Dhost_arch=x64
	@make -C out
	@${RUN_TEST}

test: test-v8 test-jsc

${GTEST_LIBS_PATH}:
	@mkdir ${GTEST_LIBS_PATH}
	@cd ${GTEST_LIBS_PATH} && cmake -G"Unix Makefiles" ${SYS_CMAKE_FLAGS} .. && make


.PHONY: test
