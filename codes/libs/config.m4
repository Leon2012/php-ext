PHP_ARG_WITH(libs, for libs support,
  [  --with-libs             Include libs support])

PHP_ARG_ENABLE(libs, whether to enable libs support,
  [  --enable-libs           Enable libs support])

if test "$PHP_LIBS" != "no"; then
  dnl # --with-libs -> check with-path
  SEARCH_PATH="/usr/local /usr"     # you might want to change this
  SEARCH_FOR="/include/curl/curl.h"  # you most likely want to change this
  if test -r $PHP_LIBS/$SEARCH_FOR; then # path given as parameter
     LIBS_DIR=$PHP_LIBS
  else # search default path list
     AC_MSG_CHECKING([for libs files in default path])
     for i in $SEARCH_PATH ; do
       if test -r $i/$SEARCH_FOR; then
         LIBS_DIR=$i
         AC_MSG_RESULT(found in $i)
       fi
     done
  fi

  if test -z "$LIBS_DIR"; then
     AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Please reinstall the libs distribution])
  fi


  PHP_ADD_INCLUDE($LIBS_DIR/include)

  LIBNAME=curl 
  LIBSYMBOL=curl_version  

   PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
   [
     PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $LIBS_DIR/$PHP_LIBDIR, LIBS_SHARED_LIBADD)
     AC_DEFINE(HAVE_LIBSLIB,1,[ ])
   ],[
     AC_MSG_ERROR([wrong libs lib version or lib not found])
   ],[
     -L$LIBS_DIR/$PHP_LIBDIR -lm
   ])
  
   PHP_SUBST(LIBS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(libs, libs.c, $ext_shared)
fi
