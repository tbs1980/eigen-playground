# eigen-playground
An effort learn internals of [Eigen Linear Algebra Library](https://eigen.tuxfamily.org/index.php?title=Main_Page)


# Installing `Eigen`

Clone the repository

```bash
git clone https://gitlab.com/libeigen/eigen.git
cd eigen
mkdir build
cd build
cmake -D CMAKE_INSTALL_PREFIX=/home/sree/linalg/installations/ ../
make install
```

This will install all the necessary header files to `/home/sree/linalg/installations/`.
That's it. `Eigen` is now installed!