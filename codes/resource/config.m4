dnl $Id$
dnl config.m4 for extension resource

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(resource, for resource support,
dnl Make sure that the comment is aligned:
dnl [  --with-resource             Include resource support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(resource, whether to enable resource support,
dnl Make sure that the comment is aligned:
  [  --enable-resource           Enable resource support])

if test "$PHP_RESOURCE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-resource -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/resource.h"  # you most likely want to change this
  dnl if test -r $PHP_RESOURCE/$SEARCH_FOR; then # path given as parameter
  dnl   RESOURCE_DIR=$PHP_RESOURCE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for resource files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       RESOURCE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$RESOURCE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the resource distribution])
  dnl fi

  dnl # --with-resource -> add include path
  dnl PHP_ADD_INCLUDE($RESOURCE_DIR/include)

  dnl # --with-resource -> check for lib and symbol presence
  dnl LIBNAME=resource # you may want to change this
  dnl LIBSYMBOL=resource # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $RESOURCE_DIR/$PHP_LIBDIR, RESOURCE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_RESOURCELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong resource lib version or lib not found])
  dnl ],[
  dnl   -L$RESOURCE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(RESOURCE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(resource, resource.c, $ext_shared)
fi
