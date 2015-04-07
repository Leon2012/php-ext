/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
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
#include "php_zval1.h"


ZEND_BEGIN_ARG_INFO(DUMP_ZVAL_TYPE_ARGINFO, 0)
	ZEND_ARG_INFO(0, zv)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO(DUMP_ZVAL_VALUE_ARGINFO, 0)
	ZEND_ARG_INFO(0, zv)
ZEND_END_ARG_INFO()

/* If you declare any globals in php_zval1.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(zval1)
*/

/* True global resources - no need for thread safety here */
static int le_zval1;

/* {{{ zval1_functions[]
 *
 * Every user visible function must have an entry in zval1_functions[].
 */
const zend_function_entry zval1_functions[] = {
	PHP_FE(dump_zval_type,	DUMP_ZVAL_TYPE_ARGINFO)		
	PHP_FE(dump_zval_value, DUMP_ZVAL_VALUE_ARGINFO)
	PHP_FE(convert_zval, DUMP_ZVAL_VALUE_ARGINFO)
	PHP_FE_END	/* Must be the last line in zval1_functions[] */
};
/* }}} */

/* {{{ zval1_module_entry
 */
zend_module_entry zval1_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"zval1",
	zval1_functions,
	PHP_MINIT(zval1),
	PHP_MSHUTDOWN(zval1),
	PHP_RINIT(zval1),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(zval1),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(zval1),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_ZVAL1_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ZVAL1
ZEND_GET_MODULE(zval1)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("zval1.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_zval1_globals, zval1_globals)
    STD_PHP_INI_ENTRY("zval1.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_zval1_globals, zval1_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_zval1_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_zval1_init_globals(zend_zval1_globals *zval1_globals)
{
	zval1_globals->global_value = 0;
	zval1_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(zval1)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(zval1)
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
PHP_RINIT_FUNCTION(zval1)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(zval1)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(zval1)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "zval1 support", "enabled");
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
/* {{{ proto string confirm_zval1_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(dump_zval_type)
{
	zval *zv;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &zv) == FAILURE) {
		return;
	}

	RETURN_LONG(Z_TYPE_P(zv));
}
/* }}} */

PHP_FUNCTION(dump_zval_value)
{
	zval *zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &zv) == FAILURE) {
		return;
	}

	switch(Z_TYPE_P(zv)) {
		case IS_NULL:
			RETURN_NULL();
			break;

		case IS_LONG:
			RETURN_LONG(Z_LVAL_P(zv));
			break;

		case IS_DOUBLE:
			RETURN_DOUBLE(Z_DVAL_P(zv));
			break;

		case IS_BOOL:
			RETURN_BOOL(Z_BVAL_P(zv));
			break;

		case IS_ARRAY:
			RETURN_ZVAL(zv, 1, 0);
			break;

		case IS_STRING:
			RETURN_STRING(Z_STRVAL_P(zv), 0)
			break;

		case IS_OBJECT:
			RETURN_ZVAL(zv, 1, 0);
			break;

	}

}


PHP_FUNCTION(convert_zval)
{
	zval *zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &zv) == FAILURE) {
		return;
	}

	convert_to_double(zv);
	RETURN_ZVAL(zv, 1, 0);
}


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
