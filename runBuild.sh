#!/bin/bash
git submodule update --init --recursive

mkdir -p build
cd build

cmake ..
make -j 2

./tests/tests

make package_source
make package

#mkdir -p ~/glRender/builds/${NODE_NAME}/"build-Arch=${Arch}WithTests=${WithTests}"/${BUILD_ID}

#cp glRender*.deb ~/glRender/builds/${NODE_NAME}/"build-Arch=${Arch}WithTests=${WithTests}"/${BUILD_ID}
#cp glRender*.zip ~/glRender/builds/${NODE_NAME}/"build-Arch=${Arch}WithTests=${WithTests}"/${BUILD_ID}	

PUBLIC_DIR=~/public
PROJECT_DIR=glRender
BUILDS_DIR=${PUBLIC_DIR}/${PROJECT_DIR}/builds
HEAD_SHA=$(git rev-parse --short HEAD)

mkdir -p ${BUILDS_DIR}/${label}/${HEAD_SHA}/${BUILD_ID}/
rm -rf ${BUILDS_DIR}/${label}/${HEAD_SHA}/${BUILD_ID}/*
cp -r glRender*.* ${BUILDS_DIR}/${label}/${HEAD_SHA}/${BUILD_ID}/

mkdir -p ${BUILDS_DIR}/${label}/latest/
rm -rf ${BUILDS_DIR}/${label}/latest/*
cp -r glRender*.* ${BUILDS_DIR}/${label}/latest/
echo ${HEAD_SHA} > ${BUILDS_DIR}/${label}/latest/COMMIT_SHA.txt
