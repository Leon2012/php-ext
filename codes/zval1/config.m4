
dnl PHP_ARG_WITH(zval1, for zval1 support,
dnl Make sure that the comment is aligned:
dnl [  --with-zval1             Include zval1 support])


PHP_ARG_ENABLE(zval1, whether to enable zval1 support,
  [  --enable-zval1           Enable zval1 support])

if test "$PHP_ZVAL1" != "no"; then
  PHP_NEW_EXTENSION(zval1, zval1.c, $ext_shared)
fi
