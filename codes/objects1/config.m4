dnl $Id$
dnl config.m4 for extension objects1

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(objects1, for objects1 support,
dnl Make sure that the comment is aligned:
dnl [  --with-objects1             Include objects1 support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(objects1, whether to enable objects1 support,
dnl Make sure that the comment is aligned:
  [  --enable-objects1           Enable objects1 support])

if test "$PHP_OBJECTS1" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-objects1 -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/objects1.h"  # you most likely want to change this
  dnl if test -r $PHP_OBJECTS1/$SEARCH_FOR; then # path given as parameter
  dnl   OBJECTS1_DIR=$PHP_OBJECTS1
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for objects1 files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       OBJECTS1_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$OBJECTS1_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the objects1 distribution])
  dnl fi

  dnl # --with-objects1 -> add include path
  dnl PHP_ADD_INCLUDE($OBJECTS1_DIR/include)

  dnl # --with-objects1 -> check for lib and symbol presence
  dnl LIBNAME=objects1 # you may want to change this
  dnl LIBSYMBOL=objects1 # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $OBJECTS1_DIR/$PHP_LIBDIR, OBJECTS1_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_OBJECTS1LIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong objects1 lib version or lib not found])
  dnl ],[
  dnl   -L$OBJECTS1_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(OBJECTS1_SHARED_LIBADD)

  PHP_NEW_EXTENSION(objects1, objects1.c, $ext_shared)
fi
