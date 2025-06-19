#!/bin/bash
set -Eeuo pipefail

if [ -z "$OHOS_SDK" ]; then
	echo "[TIPS] please set OHOS_SDK env first"
	exit 0
fi

ARCH=x86_64
# ARCH=aarch64

CFLAGS="-Wno-unused-command-line-argument -fPIC -D__MUSL__=1 -D__OPENHARMONY__=1"
CXXFLAGS="-Wno-shorten-64-to-32 $CFLAGS"

OUTPUT_DIR=$(dirname $(readlink -f $0))/ohos-build

CMAKE=$OHOS_SDK/native/build-tools/cmake/bin/cmake

${CMAKE} -B ${OUTPUT_DIR} \
    -DCMAKE_TOOLCHAIN_FILE=${OHOS_SDK}/native/build/cmake/ohos.toolchain.cmake \
    -DOHOS_ARCH=x86_64 \
    -DCMAKE_C_FLAGS="${CFLAGS}" \
    -DCMAKE_CXX_FLAGS="${CXXFLAGS}"

${CMAKE} --build ${OUTPUT_DIR}

find ${OUTPUT_DIR}/lib -type f -name "*.so*" | xargs -i patchelf --set-rpath '$ORIGIN' {}

