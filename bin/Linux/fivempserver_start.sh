#!/bin/bash
LIBRARYPATH="$(pwd)"

export LD_LIBRARY_PATH="${LIBRARYPATH}:$LD_LIBRARY_PATH"
./Server.Launcher.so
