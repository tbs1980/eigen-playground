# A minimal version of Eigen

Here, I collect a minimal set of Eigen headers so that I
can learn what gets called from where.

We work with the following commit of Eigen

```
commit 0259a52b0efe75c78f48f8a21b8092cd3fff319f (HEAD -> master, origin/master, origin/HEAD)
Author: Markus Vieth <mvieth@techfak.uni-bielefeld.de>
Date:   Mon Mar 17 19:32:43 2025 +0100

    Use more .noalias()

```

We start with the definition of `Eigen::VectorXf`. You can find this
at Line 478 of `Core/Matrix.h`

```c++
EIGEN_MAKE_TYPEDEFS_ALL_SIZES(float, f)
```

This actually calls a macro defined just above in line 468.

```c++
#define EIGEN_MAKE_TYPEDEFS_ALL_SIZES(Type, TypeSuffix) \
  EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 2, 2)           \
  EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 3, 3)           \
  EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 4, 4)           \
  EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, Dynamic, X)     \
  EIGEN_MAKE_FIXED_TYPEDEFS(Type, TypeSuffix, 2)        \
  EIGEN_MAKE_FIXED_TYPEDEFS(Type, TypeSuffix, 3)        \
  EIGEN_MAKE_FIXED_TYPEDEFS(Type, TypeSuffix, 4)
```

