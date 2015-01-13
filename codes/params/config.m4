PHP_ARG_ENABLE(params, 
              whether to enable params support,
[  --enable-params           Enable params support])

if test "$PHP_PARAMS" != "no"; then
  PHP_NEW_EXTENSION(params, params.c, $ext_shared)
fi
