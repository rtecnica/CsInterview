#!/usr/bin/bash

WORKING_DIR=$(pwd)
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

mkdir "$SCRIPT_DIR/$1"
mkdir "$SCRIPT_DIR/$1/inc"
mkdir "$SCRIPT_DIR/$1/src"
mkdir "$SCRIPT_DIR/$1/bin"
touch "$SCRIPT_DIR/$1/$1.py"
touch "$SCRIPT_DIR/$1/inc/lib.h"
echo "#include \"../inc/lib.h\"" > "$SCRIPT_DIR/$1/src/lib.c"
echo "#include \"inc/lib.h\"" > "$SCRIPT_DIR/$1/$1.c"


sed "s/<<target>>/$1/" "$SCRIPT_DIR/Makefile_template" > "$SCRIPT_DIR/$1/Makefile"

