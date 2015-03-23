PHP_ARG_WITH(objects3, for objects3 support,
   [  --with-objects3             Include objects3 support])

PHP_ARG_ENABLE(objects3, whether to enable objects3 support,
   [  --enable-objects3           Enable objects3 support])

if test "$PHP_OBJECTS3" != "no"; then
  PHP_NEW_EXTENSION(objects3, objects3.c, $ext_shared)
fi
