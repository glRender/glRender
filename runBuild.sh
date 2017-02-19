#!/bin/bash
git submodule update --init --recursive

mkdir -p build
cd build

cmake ..
make -j 2

./tests/unit-tests/tests

# make package_source
make package

#mkdir -p ~/glRender/builds/${NODE_NAME}/"build-Arch=${Arch}WithTests=${WithTests}"/${BUILD_ID}

#cp glRender*.deb ~/glRender/builds/${NODE_NAME}/"build-Arch=${Arch}WithTests=${WithTests}"/${BUILD_ID}
#cp glRender*.zip ~/glRender/builds/${NODE_NAME}/"build-Arch=${Arch}WithTests=${WithTests}"/${BUILD_ID}	

# PUBLIC_DIR=~/public
# PROJECT_DIR=glRender
# BUILDS_DIR=${PUBLIC_DIR}/${PROJECT_DIR}/builds
# HEAD_SHA=$(git rev-parse --short HEAD)

# mkdir -p ${BUILDS_DIR}/${label}/${HEAD_SHA}/${BUILD_ID}/
# rm -rf ${BUILDS_DIR}/${label}/${HEAD_SHA}/${BUILD_ID}/*
# cp -r glRender*.* ${BUILDS_DIR}/${label}/${HEAD_SHA}/${BUILD_ID}/

# mkdir -p ${BUILDS_DIR}/${label}/latest/
# rm -rf ${BUILDS_DIR}/${label}/latest/*
# cp -r glRender*.* ${BUILDS_DIR}/${label}/latest/
# echo ${HEAD_SHA} > ${BUILDS_DIR}/${label}/latest/COMMIT_SHA.txt

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