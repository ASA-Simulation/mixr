set -x
set -e

#
# sanity check: number of arguments
#

if [[ $# -ne 2 ]]; then
    echo "Expected exactly 2 parameters: NUM_JOBS and BUILD_TYPE" >&2
    exit 1
fi

#
# set NUM_JOBS
#

NUM_JOBS=$1
echo "Building with $1 parallel jobs"

#
# set BUILD_TYPE
#

BUILD_TYPE="$2"
echo "Building in type $BUILD_TYPE"

#
# setting up the task
#

echo "Cleaning bin folder"
rm -rf ./bin && mkdir ./bin

echo "Cleaning build folder"
rm -rf ./build && mkdir ./build

#
# starting the task
#

echo "Installing conan dependencies"
conan install ./ --build=missing --settings=build_type=$BUILD_TYPE

meson setup --reconfigure \
    --backend ninja \
    --buildtype "$(echo "$BUILD_TYPE" | tr '[:upper:]' '[:lower:]')" \
    --prefix="$(pwd)/bin" \
    -Dpkg_config_path="$(pwd)/build" \
    ./build/ .

meson install -C ./build

#
# closing the task
#

echo "Task ended successfully!"
