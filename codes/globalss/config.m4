 PHP_ARG_WITH(globalss, for globalss support,
   [  --with-globalss             Include globalss support])

 PHP_ARG_ENABLE(globalss, whether to enable globalss support,
   [  --enable-globalss           Enable globalss support])

if test "$PHP_GLOBALSS" != "no"; then
  PHP_NEW_EXTENSION(globalss, globalss.c, $ext_shared)
fi
