set -x
set -e

#
# sanity check: number of arguments
#

if [[ $# -ne 1 ]]; then
    echo "Expected exactly 1 parameter: the conan remote." >&2
    exit 1
fi

#
# set CONAN_REMOTE
#

CONAN_REMOTE=$1
echo "Uploading to conan remote: $1"

#
# building the conan package
#

echo "Building the current package in debug and release modes"

conan create . --build=missing --settings=build_type=Release
conan create . --build=missing --settings=build_type=Debug

#
# uploading local packages
#

echo "Uploading local packages to registry"

conan upload "*" --remote=$CONAN_REMOTE --confirm
