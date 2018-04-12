#!/bin/bash
FILES=tests/Cualitativos/*.txt
for f in $FILES
do
  ./../build/tp $f 0.8
done
