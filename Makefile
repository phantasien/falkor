clean:
	@rm -rf build bastian.xcodeproj

test-v8:
	@./tools/gyp/gyp -DBASTIAN_ENGINE=v8 -Dv8_use_snapshot=true -Dtarget_arch=x64 -Dhost_arch=x64 -Dcomponent=static_library -Dv8_optimized_debug=0 -Dv8_enable_i18n_support=0 --depth bastian.gyp
	@xcodebuild -project bastian.xcodeproj

test-jsc:
	@./tools/gyp/gyp -DBASTIAN_ENGINE=jsc --depth=./ bastian.gyp
	@xcodebuild -project bastian.xcodeproj
