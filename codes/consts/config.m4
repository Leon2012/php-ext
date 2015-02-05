PHP_ARG_ENABLE(consts, whether to enable consts support,
  [  --enable-consts           Enable consts support])

if test "$PHP_CONSTS" != "no"; then
  PHP_NEW_EXTENSION(consts, consts.c, $ext_shared)
fi
