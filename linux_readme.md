# example build commands on linux

```
git clone https://github.com/janwilmans/copperspice-msvc.git
mkdir build
export CC=/usr/bin/clang-9
export CXX=/usr/bin/clang++-9
cmake -DCMAKE_INSTALL_PREFIX=install -G Ninja ..
ninja
```


