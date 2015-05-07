curdir := $(shell pwd)

mnc_src := $(shell find src -name "*.cc")
mnc_v8_obj := $(foreach src,${mnc_src}, $(subst .cc,.v8.o,$(src)))

v8_test_src := $(shell find test/v8 -name "*.cc")
v8_test_obj := $(foreach src,${v8_test_src}, $(subst .cc,.o,$(src)))

v8_cxx_flags := -I${curdir}/deps/v8/include \
    -I${curdir}/deps/gtest/include \
    -I${curdir}/src \
    -DMNC_V8 \
    -w \
    -L${curdir}/deps/gtest/cbuild \
    -L${curdir}/deps/v8/out/native \
    -lgtest -lgtest_main -lpthread \
    -stdlib=libstdc++ \
    -lv8_base -lv8_libbase -lv8_snapshot -lv8_libplatform

clean:
	@find test -name "*.o" -exec rm {} ';' 
	@find src -name "*.o" -exec rm {} ';' 

src/%.v8.o: src/%.cc
	@g++ -o $@ -c $< ${v8_cxx_flags}
	     

test/v8/%.o: test/v8/%.cc
	@g++ -o $@ -c $< ${v8_cxx_flags}

test/v8/run: deps/v8 deps/gtest ${mnc_v8_obj} ${v8_test_obj}
	@g++ -o test/v8/run ${mnc_v8_obj} ${v8_test_obj} ${v8_cxx_flags}

test: test-v8

test-v8: test/v8/run
	@./test/v8/run

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


