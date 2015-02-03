PHP_ARG_ENABLE(global, whether to enable global support,
  [  --enable-global           Enable global support])

if test "$PHP_GLOBAL" != "no"; then
  PHP_NEW_EXTENSION(global, global.c, $ext_shared)
fi
