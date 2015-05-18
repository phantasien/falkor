CURDIR := $(shell pwd)

clean:
	@make -C deps/v8 clean
	@rm -rf out

test-v8:
	@./tools/gyp_bastian bastian.gyp -Dhost_arch=x64
	@make -C out
