.PHONY: clean install-dbg install-rel configure-dbg configure-rel build-dbg build-rel test package

clean:
	rm -rf ./build/
	rm -f ./CMakeUserPresets.json

	rm -rf ./test_pkg/build/
	rm -f ./test_pkg/CMakeUserPresets.json

install-dbg:
	rm -rf ./build/Debug/
	mkdir -p ./build/Debug/
	conan install ./ --build=missing --settings=build_type=Debug

install-rel:
	rm -rf ./build/Debug/
	mkdir -p ./build/Debug/
	conan install ./ --build=missing --settings=build_type=Release

configure-dbg:
	rm -f ./build/Debug/CMakeCache.txt
	cmake -S ./ -B ./build/Debug/ -G Ninja \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_TOOLCHAIN_FILE=./generators/conan_toolchain.cmake \
		-DCMAKE_INSTALL_PREFIX=../../../bin/ \
		-DCMAKE_BUILD_TYPE=Debug

configure-rel:
	rm -f ./build/Release/CMakeCache.txt
	cmake -S ./ -B ./build/Release/ -G Ninja \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_TOOLCHAIN_FILE=./generators/conan_toolchain.cmake \
		-DCMAKE_INSTALL_PREFIX=../../../bin/ \
		-DCMAKE_BUILD_TYPE=Release

build-dbg:
	cmake --build ./build/Debug/
	cmake --install ./build/Debug/

build-rel:
	cmake --build ./build/Release/
	cmake --install ./build/Release/

test:
	rm -rf ./test_pkg/build/
	mkdir -p ./test_pkg/build/
	conan test ./test_pkg/ mixr/1.0.0 --build=missing --settings=build_type=Debug
	conan test ./test_pkg/ mixr/1.0.0 --build=missing --settings=build_type=Release

package:
	conan create ./ --build=missing --settings=build_type=Debug
	conan create ./ --build=missing --settings=build_type=Release
