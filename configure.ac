#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([simple-fb2-reader], [1.0.6], [medved_cool@mail.ru], [], [https://github.com/Cactus64k/simple-fb2-reader])
# AM_INIT_AUTOMAKE
# AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([src/config.h])

# Checks for programs.
AC_PROG_CC_C99

# Checks for libraries.
PKG_CHECK_MODULES([XML],		[libxml-2.0 >= 2.8.0])
PKG_CHECK_MODULES([GLIB],		[glib-2.0 >= 2.32.4])
PKG_CHECK_MODULES([GTK],		[gtk+-3.0 >= 3.4.2])
PKG_CHECK_MODULES([ZIP],		[libzip >= 0.10.1])


# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stddef.h stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset setlocale strchr strerror])

AC_DEFINE_UNQUOTED([GUI_CONSTRUCT_PATH],	"${prefix}/share/${PACKAGE_NAME}/${PACKAGE_NAME}.glade")
AC_DEFINE_UNQUOTED([ENCODE_LIST_PATH],		"${sysconfdir}/simple-fb2-reader_encoding_list.cfg")
AC_DEFINE_UNQUOTED([PACKAGE_VERSION],		"${PACKAGE_VERSION}")


AC_CONFIG_FILES([makefile])
AC_OUTPUT
