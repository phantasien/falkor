test: deps

deps: deps/v8

deps/v8: 
	@mkdir -p deps
	@git clone --depth=1 https://github.com/phantasien/v8 deps/v8
	@make -C deps/v8 builddeps
	@make -C deps/v8 x64.release -j8 i18nsupport=off werror=no -j8

deps/gtest: deps/gtest.zip


deps/gtest.zip:
	@-curl -L https://googletest.googlecode.com/files/gtest-1.7.0.zip > deps/gtest.zip
	@unzip -d deps deps/gtest.zip
	@mv deps/gtest-1.7.0 deps/gtest
	@cd deps/gtest && ./configure && make

.PHONY: test
