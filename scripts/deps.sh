set -x
set -e

echo "Building mixr dependencies in debug mode"
conan create ./deps/jsbsim  --build=missing --settings=build_type=Debug
conan create ./deps/openrti --build=missing --settings=build_type=Debug

echo "Building mixr dependencies in release mode"
conan create ./deps/jsbsim  --build=missing --settings=build_type=Release
conan create ./deps/openrti --build=missing --settings=build_type=Release
