#!/bin/bash -e
git submodule update --init --recursive

# Build lib, unit-tests and integration-tests
mkdir -p build
cd build
cmake ..
make -j 2

# Run unit-tests ...
cd ./tests/
./unit-tests/tests

# Run and kill integration-tests one by one ...

#Xvfb :99 &
#export DISPLAY=:99

#cd ./integration-tests/
#for f in * ; do
#    if [[ -d $f ]]; then
       # echo "Run integration test $f"
        #cd ${f}
        #LD_LIBRARY_PATH=../../../lib/ ./${f} &
        #sleep 5s
        #echo "Stoping integration test $f..."
        #killall ${f}
        #cd ..
        #echo "Done"
    #fi
#done
#cd ../../

# Make binary package or installer depend to current platform
# make package_source
make package

# Deploy binares to 83.220.170.171
if [[ "${GLRENDER_DEPLOY_PACKAGES}" == "ON" ]]; then
    if [[ -z ${GLRENDER_SLAVE_NAME+x} ]]; then
        GLRENDER_SLAVE_NAME="$(uname -s)_$(uname -r)"
    fi
    PUBLIC_DIR=public
    PROJECT_DIR=glRender
    HEAD_SHA=$(git rev-parse --short HEAD)
    BUILD_DIR=${PROJECT_DIR}/${HEAD_SHA}/${GLRENDER_SLAVE_NAME}
    PACKAGES_DIR=${BUILD_DIR}/packages/
    DOCS_DIR=${BUILD_DIR}/docs/
    LATEST_BUILD_LINK=${PROJECT_DIR}/latest
    mkdir -p ${PACKAGES_DIR}
    rm -rf ${LATEST_BUILD_LINK}
    cd ${PROJECT_DIR}
        ln -s ${HEAD_SHA} latest
    cd ..
    echo ${HEAD_SHA} > ${LATEST_BUILD_LINK}/COMMIT_SHA.txt
    echo ${HEAD_SHA} > ${LATEST_BUILD_LINK}/${GLRENDER_SLAVE_NAME}/COMMIT_SHA.txt
    echo ${HEAD_SHA} > ${LATEST_BUILD_LINK}/${GLRENDER_SLAVE_NAME}/packages/COMMIT_SHA.txt

    cp *glRender*.* ${PACKAGES_DIR}
    scp -r ${PROJECT_DIR} jenkins@83.220.170.171:~/${PUBLIC_DIR}
    rm -rf ${PROJECT_DIR}
fi
