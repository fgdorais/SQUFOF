#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([SQUFOF], [1.1], [dorais@umich.edu])
# AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

# Check host.

AC_CANONICAL_HOST

case ${host} in
  [i[34567]86]-*-*)
    arith_arch="x86_32"
    ;;
  x86_64-*-*)
    arith_arch="x86_64"
    ;;
  powerpc-*-*)
    arith_arch="ppc32"
    ;;
  powerpc64-*-*)
    arith_arch="ppc64"
    ;;
  *)
    arith_arch="none"
    ;;
esac;

AC_CONFIG_LINKS(lib/arith-arch.h:lib/arith-$arith_arch.h)

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([inttypes.h stdint.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_UINT64_T

# Checks for library functions.

# Output

AC_CONFIG_FILES([Makefile src/Makefile lib/Makefile])
AC_OUTPUT
