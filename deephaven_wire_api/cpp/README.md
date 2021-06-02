Deephaven-CPP
-------------

This is the preliminary cpp client for deephaven core.

Build
-----

Building requires that you install the following libraries: apache arrow, protobuf, grpc, flatbuffers, and cmake.

At the moment several dependencies are hard-coded in the CMakeLists file. Do update them appropriately.

```
$ mkdir build
$ cd build
$ cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl -DOPENSSL_LIBRARIES=/usr/local/opt/openssl/lib ..
[...]

$ make
[...]

# Run it:
$ bin/example localhost:10000
```
