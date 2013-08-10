#!/bin/bash

MY_PWD=`pwd`

PROJECT_DIR="$(dirname $(dirname $(readlink -m $0)))"

if [ "$1" = "recreate" ];then
  shift
  echo "Doing internal cleaning ..."
  rm -Rf $PROJECT_DIR/build $PROJECT_DIR/bin $PROJECT_DIR/lib
  if [ "$?" = "0" ];then
    echo "Doing internal cleaning [   OK   ]"
  else
    echo "Doing internal cleaning [ FAILED ]"
    exit 1
  fi
fi

if [ ! -d $PROJECT_DIR/build ];then
    mkdir -p $PROJECT_DIR/build
fi

cd $PROJECT_DIR/build

if [ ! -f Makefile ];then
  cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="$PROJECT_DIR" ../
fi

CMD="nice -n 15"
CMD="$CMD make $*"
$CMD || exit $?

cd $MY_PWD
