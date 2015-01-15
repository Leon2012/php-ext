PHP_ARG_ENABLE(return, whether to enable return support,
  [  --enable-return           Enable return support])

if test "$PHP_RETURN" != "no"; then
  PHP_NEW_EXTENSION(return, return.c, $ext_shared)
fi
