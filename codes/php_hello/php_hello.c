/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_php_hello.h"

/* If you declare any globals in php_php_hello.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(php_hello)
*/

/* True global resources - no need for thread safety here */
static int le_php_hello;

/* {{{ php_hello_functions[]
 *
 * Every user visible function must have an entry in php_hello_functions[].
 */
const zend_function_entry php_hello_functions[] = {
	PHP_FE(confirm_php_hello_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in php_hello_functions[] */
};
/* }}} */

/* {{{ php_hello_module_entry
 */
zend_module_entry php_hello_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"php_hello",
	php_hello_functions,
	PHP_MINIT(php_hello),
	PHP_MSHUTDOWN(php_hello),
	PHP_RINIT(php_hello),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(php_hello),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(php_hello),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_PHP_HELLO_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHP_HELLO
ZEND_GET_MODULE(php_hello)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("php_hello.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_php_hello_globals, php_hello_globals)
    STD_PHP_INI_ENTRY("php_hello.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_php_hello_globals, php_hello_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_php_hello_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_php_hello_init_globals(zend_php_hello_globals *php_hello_globals)
{
	php_hello_globals->global_value = 0;
	php_hello_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(php_hello)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(php_hello)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(php_hello)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(php_hello)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(php_hello)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "php_hello support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_php_hello_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_php_hello_compiled)
{
    php_printf("hello world!\n");
    return;
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
