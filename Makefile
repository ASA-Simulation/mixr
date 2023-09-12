.PHONY: clean install-dbg install-rel configure-dbg configure-rel build test package

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
	rm -f ./build/CMakeCache.txt
	cmake -S ./ -B ./build/ -G Ninja \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_TOOLCHAIN_FILE=./Debug/generators/conan_toolchain.cmake \
		-DCMAKE_INSTALL_PREFIX=../bin/ \
		-DCMAKE_BUILD_TYPE=Debug
	cp ./build/compile_commands.json .

configure-rel:
	rm -f ./build/CMakeCache.txt
	cmake -S ./ -B ./build/ -G Ninja \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_TOOLCHAIN_FILE=./Release/generators/conan_toolchain.cmake \
		-DCMAKE_INSTALL_PREFIX=../bin/ \
		-DCMAKE_BUILD_TYPE=Release
	cp ./build/compile_commands.json .

build:
	cmake --build ./build/
	cmake --install ./build/

test:
	rm -rf ./test_pkg/build/
	mkdir -p ./test_pkg/build/
	conan test ./test_pkg/ mixr/1.0.0 --build=missing --settings=build_type=Debug
	conan test ./test_pkg/ mixr/1.0.0 --build=missing --settings=build_type=Release

package:
	conan create ./ --build=missing --settings=build_type=Debug
	conan create ./ --build=missing --settings=build_type=Release
