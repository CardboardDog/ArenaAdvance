#!/bin/bash
rm -rf dist
mkdir dist
mkdir dist/source
cd dist/source
grit ../../graphics/daySky.png -gB4 -mLs -mR4 -ma 128 -p! -Zl
grit ../../graphics/bgpal.png ../../graphics/world.png -pS -gB8 -mRa -mLa -Zl -S bg
grit ../../graphics/objpal.png ../../graphics/tree.png -gt -gB4 -pS -Zl -S obj
cd ../../
cp source/** dist/source
cp makefiles/Makefile dist/Makefile
cd dist
make
rm -rf source
cd ../