all: build-xcode

build-xcode:
	cmake -B build-xcode -S . -GXcode -DCMAKE_TOOLCHAIN_FILE=/usr/local/sbin/vcpkg/scripts/buildsystems/vcpkg.cmake

clean:
	rm -rf build-xcode