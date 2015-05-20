CURDIR := $(shell pwd)

lowercase = $(shell echo $1 | tr A-Z a-z)

GYP := ${CURDIR}/deps/bastian/tools/gyp_bastian
SYS_NAME := $(shell uname -s)
SYS_NAME_LOWER := $(call lowercase,${SYS_NAME})
SYS_MACHINE := $(shell uname -m)
ANDROID_NDK_PREBUILT = ${ANDROID_NDK_ROOT}/toolchains/arm-linux-androideabi-4.8/prebuilt/${SYS_NAME_LOWER}-${SYS_MACHINE}


test: test-android

test-android: deps/bastian/out/v8-android_arm

deps/bastian/out/v8-android_arm:
	@cd deps/bastian && CC="${ANDROID_NDK_PREBUILT}/bin/arm-linux-androideabi-gcc" \
	CXX="${ANDROID_NDK_PREBUILT}/bin/arm-linux-androideabi-g++" \
	${GYP} -Dbastian_engine=v8 -Dtarget_arch=arm \
	       -Dandroid_target_platform=15 \
 	       -Darm_version=7 -Dhost_os=mac -DOS=android \
	       bastian.gyp
	@make -C deps/bastian/out/v8-android_arm

.PHONY: test