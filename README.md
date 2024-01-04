# octopus-code


## 1. download `vcpkg`:

```shell
$ git clone https://github.com/microsoft/vcpkg.git 
$ git clone https://gitee.com/mirrors/vcpkg
```

## 2. set environment VCPKG_ROOT
```shell
export VCPKG_ROOT= vcpkg_dir
export PATH=${VCPKG_ROOT}:${PATH}
```

## 3. compile

```shell
$ cmake  --preset=default
$ cmake --build build
```

# TODO
1. gtest and google-benchmark
2. add support for c++20
3. add ci for multiple platforms
4. support windows

