@echo off
echo Current directory: %cd%
docker run --rm -v "%cd%:/root/env" devos /bin/bash -c "make build-x86_64"