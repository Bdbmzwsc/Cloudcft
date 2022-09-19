# build cloudcft
# check if build dir exist
if [ ! -d "./build" ]; then
    mkdir build
fi
rm -rf build/*
cd build
cmake ..
make
echo "build sueecsslly"