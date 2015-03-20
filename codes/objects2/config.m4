PHP_ARG_WITH(objects2, for objects2 support,
  [  --enable-objects2             Enable objects2 support])


if test "$PHP_OBJECTS2" != "no"; then
  PHP_NEW_EXTENSION(objects2, objects2.c, $ext_shared)
fi


if test -z "$PHP_DEBUG"; then 
  AC_ARG_ENABLE(debug,
  [ --enable-debug      compile with debugging symbols],[
    PHP_DEBUG=$enableval
  ],[ PHP_DEBUG=no
  ])
fi
