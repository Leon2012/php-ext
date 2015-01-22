PHP_ARG_ENABLE(inis, whether to enable inis support,
  [  --enable-inis           Enable inis support])

if test "$PHP_INIS" != "no"; then
  PHP_NEW_EXTENSION(inis, inis.c, $ext_shared)
fi
