#! /bin/sh
DIR=$1
if [ ! -d $DIR ]; then
  echo "Directory $DIR not found"
  exit 1
fi
CLANG_FORMAT_CMD=$(locate --regex /clang-format$)
if [ $? -ne 0 ]; then
  echo "clang-format command not found. Please install it before running this script."
  exit 2
else
  echo "clang-format binary used is $CLANG_FORMAT_CMD"
fi

find $DIR \( -name '*.h' -o -name '*.cpp' \) -execdir $CLANG_FORMAT_CMD -style=llvm -i {} +

