git submodule update --init --recursive

mkdir -p build
cd build

cmake -G "MSYS Makefiles" ..
mingw32-make -j 8

cd tests
tests.exe
cd ..

:: make package_source
mingw32-make package

:: mkdir -p ~/glRender/builds/${NODE_NAME}/"build-Arch=${Arch}WithTests=${WithTests}"/${BUILD_ID}

:: cp glRender*.deb ~/glRender/builds/${NODE_NAME}/"build-Arch=${Arch}WithTests=${WithTests}"/${BUILD_ID}
:: cp glRender*.zip ~/glRender/builds/${NODE_NAME}/"build-Arch=${Arch}WithTests=${WithTests}"/${BUILD_ID}	

:: PUBLIC_DIR=~/public
:: PROJECT_DIR=glRender
:: BUILDS_DIR=${PUBLIC_DIR}/${PROJECT_DIR}/builds
:: HEAD_SHA=$(git rev-parse --short HEAD)

:: mkdir -p ${BUILDS_DIR}/${label}/${HEAD_SHA}/${BUILD_ID}/
:: rm -rf ${BUILDS_DIR}/${label}/${HEAD_SHA}/${BUILD_ID}/*
:: cp -r glRender*.* ${BUILDS_DIR}/${label}/${HEAD_SHA}/${BUILD_ID}/

:: mkdir -p ${BUILDS_DIR}/${label}/latest/
:: rm -rf ${BUILDS_DIR}/${label}/latest/*
:: cp -r glRender*.* ${BUILDS_DIR}/${label}/latest/
:: echo ${HEAD_SHA} > ${BUILDS_DIR}/${label}/latest/COMMIT_SHA.txt
