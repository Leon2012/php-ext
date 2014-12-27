PHP_ARG_ENABLE(php_hello, whether to enable php_hello support,
  Make sure that the comment is aligned:
[  --enable-php_hello           Enable php_hello support])

if test "$PHP_PHP_HELLO" != "no"; then
  PHP_NEW_EXTENSION(php_hello, php_hello.c, $ext_shared)
fi
