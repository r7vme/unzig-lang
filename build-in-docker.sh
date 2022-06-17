#!/bin/bash
set -e
docker build -t unzig .
docker run --rm -ti -v $(pwd):/code unzig /bin/bash -c "cd /code; ./build.sh"
