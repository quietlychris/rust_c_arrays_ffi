#!/bin/bash

rm -r build/*;
cd build;
cmake ..;
make;
cp pass_arrays ..;
cd ..;
