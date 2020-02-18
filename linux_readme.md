# example build commands on linux

```
git clone https://github.com/janwilmans/copperspice-msvc.git
mkdir build
export CC=/usr/bin/clang-9
export CXX=/usr/bin/clang++-9
cmake -DCMAKE_INSTALL_PREFIX=install -G Ninja ..
ninja 
ninja install
```

* of cource the 'clang-9' is just an example, the export commands can be omitted entirely to use the 'system default' compiler
* the `-DCMAKE_INSTALL_PREFIX=install` installs the result in a relative build/install/ directory, so not root access is required to install


