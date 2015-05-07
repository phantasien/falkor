CURDIR := $(shell pwd)

lowercase = $(shell echo $1 | tr A-Z a-z)

MNC_SRC := $(shell find src -name "*.cc")
MNC_V8_OBJ := $(foreach src,${MNC_SRC}, $(subst .cc,.v8.o,$(src)))
MNC_JSC_OBJ := $(foreach src,${MNC_SRC}, $(subst .cc,.jsc.o,$(src)))

V8_TEST_SRC := $(shell find test/v8 -name "*.cc")
V8_TEST_OBJ := $(foreach src,${V8_TEST_SRC}, $(subst .cc,.o,$(src)))

JSC_TEST_SRC := $(shell find test/jsc -name "*.cc")
JSC_TEST_OBJ := $(foreach src,${JSC_TEST_SRC}, $(subst .cc,.o,$(src)))

TEST_SUITE_SRC := $(shell find ./test -maxdepth 1 -name "*.cc")
TEST_SUITE_V8_OBJ := $(foreach src,${TEST_SUITE_SRC}, $(subst .cc,.v8.o,$(src)))
TEST_SUITE_JSC_OBJ := $(foreach src,${TEST_SUITE_SRC}, $(subst .cc,.jsc.o,$(src)))

SYS_NAME := $(shell uname -s)
SYS_NAME_LOWER := $(call lowercase,${SYS_NAME})

ifeq (${SYS_NAME_LOWER},linux)
	V8_LIBS_PATH := ${CURDIR}/deps/v8/out/native/obj.target/tools/gyp
	SYS_CXX_FLAGS :=
	SYS_CMAKE_FLAGS :=
else
	V8_LIBS_PATH := ${CURDIR}/deps/v8/out/native
	SYS_CXX_FLAGS := -stdlib=libstdc++
	SYS_CMAKE_FLAGS := -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libstdc++ -U__STRICT_ANSI__"
endif


V8_CXX_FLAGS := -I${CURDIR}/include \
    -I${CURDIR}/deps/gtest/include \
    -I${CURDIR}/deps/v8/include \
    -DMNC_V8 \
    -w \
    -L${CURDIR}/deps/gtest/cbuild \
    -L${V8_LIBS_PATH} \
    ${SYS_CXX_FLAGS} \
    -lgtest -lgtest_main -lpthread \
    -lv8_base -lv8_libbase -lv8_snapshot -lv8_libplatform

JSC_CXX_FLAGS := -I${CURDIR}/include \
    -I${CURDIR}/deps/gtest/include \
    -DMNC_JSC \
    -w \
    -L${CURDIR}/deps/gtest/cbuild \
    ${SYS_CXX_FLAGS} \
    -lgtest -lgtest_main -lpthread \
    -fobjc-arc -framework JavascriptCore

clean:
	@find test -name "run" -exec rm {} ';'
	@find test -name "*.o" -exec rm {} ';'
	@find src -name "*.o" -exec rm {} ';'

src/%.v8.o: src/%.cc
	@g++ -o $@ -c $< ${V8_CXX_FLAGS}

src/%.jsc.o: src/%.cc
	@g++ -o $@ -c $< ${JSC_CXX_FLAGS}

test/%.v8.o: test/%.cc
	@g++ -o $@ -c $< ${V8_CXX_FLAGS}

test/%.jsc.o: test/%.cc
	@g++ -o $@ -c $< ${JSC_CXX_FLAGS}

test/v8/%.o: test/v8/%.cc
	@g++ -o $@ -c $< ${V8_CXX_FLAGS}

test/jsc/%.o: test/jsc/%.cc
	@g++ -o $@ -c $< ${JSC_CXX_FLAGS}

test/v8/run: deps/v8 deps/gtest ${MNC_V8_OBJ} ${V8_TEST_OBJ} ${TEST_SUITE_V8_OBJ}
	@g++ -o test/v8/run ${MNC_V8_OBJ} ${V8_TEST_OBJ} ${TEST_SUITE_V8_OBJ} ${V8_CXX_FLAGS}

test/jsc/run: deps/gtest ${MNC_JSC_OBJ} ${JSC_TEST_OBJ} ${TEST_SUITE_JSC_OBJ}
	@g++ -o test/jsc/run ${MNC_JSC_OBJ} ${JSC_TEST_OBJ} ${TEST_SUITE_JSC_OBJ} ${JSC_CXX_FLAGS}

test-jsc: test/jsc/run
	@./test/jsc/run

test-v8: test/v8/run
	@./test/v8/run

test: test-v8 test-jsc

deps/v8:
	@mkdir -p deps
	@git clone --depth=1 https://github.com/phantasien/v8 deps/v8
	@make -C deps/v8 builddeps
	@make -C deps/v8 native -j4 i18nsupport=off werror=no

deps/gtest: deps/gtest.zip

deps/gtest.zip:
	@-curl -L https://googletest.googlecode.com/files/gtest-1.7.0.zip > deps/gtest.zip
	@unzip -d deps deps/gtest.zip
	@mv deps/gtest-1.7.0 deps/gtest
	@mkdir deps/gtest/cbuild
	@cd deps/gtest/cbuild && cmake -G"Unix Makefiles" ${SYS_CMAKE_FLAGS} .. && make

.PHONY: test


