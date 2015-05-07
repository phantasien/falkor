curdir := $(shell pwd)

MNC_SRC := $(shell find src -name "*.cc")
MNC_V8_OBJ := $(foreach src,${MNC_SRC}, $(subst .cc,.v8.o,$(src)))
MNC_JSC_OBJ := $(foreach src,${MNC_SRC}, $(subst .cc,.jsc.o,$(src)))

V8_TEST_SRC := $(shell find test/v8 -name "*.cc")
V8_TEST_OBJ := $(foreach src,${V8_TEST_SRC}, $(subst .cc,.o,$(src)))

JSC_TEST_SRC := $(shell find test/jsc -name "*.cc")
JSC_TEST_OBJ := $(foreach src,${JSC_TEST_SRC}, $(subst .cc,.o,$(src)))

CMN_TEST_SRC := $(shell find test -depth 1 -name "*.cc")
CMN_TEST_V8_OBJ := $(foreach src,${CMN_TEST_SRC}, $(subst .cc,.v8.o,$(src)))
CMN_TEST_JSC_OBJ := $(foreach src,${CMN_TEST_SRC}, $(subst .cc,.jsc.o,$(src)))

V8_CXX_FLAGS := -I${curdir}/src \
    -I${curdir}/deps/gtest/include \
    -I${curdir}/deps/v8/include \
    -DMNC_V8 \
    -w \
    -L${curdir}/deps/gtest/cbuild \
    -L${curdir}/deps/v8/out/native \
    -lgtest -lgtest_main -lpthread \
    -stdlib=libstdc++ \
    -lv8_base -lv8_libbase -lv8_snapshot -lv8_libplatform

JSC_CXX_FLAGS := -I${curdir}/src \
    -I${curdir}/deps/gtest/include \
    -DMNC_JSC \
    -w \
    -L${curdir}/deps/gtest/cbuild \
    -lgtest -lgtest_main -lpthread \
    -stdlib=libstdc++ \
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

test/v8/run: deps/v8 deps/gtest ${MNC_V8_OBJ} ${V8_TEST_OBJ} ${CMN_TEST_V8_OBJ}
	@g++ -o test/v8/run ${MNC_V8_OBJ} ${V8_TEST_OBJ} ${CMN_TEST_V8_OBJ} ${V8_CXX_FLAGS}

test/jsc/run: deps/gtest ${MNC_JSC_OBJ} ${JSC_TEST_OBJ} ${CMN_TEST_JSC_OBJ}
	@g++ -o test/jsc/run ${MNC_JSC_OBJ} ${JSC_TEST_OBJ} ${CMN_TEST_JSC_OBJ} ${JSC_CXX_FLAGS}

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
	@cd deps/gtest/cbuild && cmake -G"Unix Makefiles" -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libstdc++ -U__STRICT_ANSI__" .. && make

.PHONY: test


