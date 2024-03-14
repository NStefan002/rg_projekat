#!/bin/bash
mkdir -p build;
cmake -S . -G "Unix Makefiles" -B build; rm compile_commands.json; ln -s build/compile_commands.json .;
cd build; make; cd ..;
