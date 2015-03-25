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
#include "php_globalss.h"
#include "main/SAPI.h"

/* If you declare any globals in php_globalss.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(globalss)
*/

/* True global resources - no need for thread safety here */
static int le_globalss;

/* {{{ globalss_functions[]
 *
 * Every user visible function must have an entry in globalss_functions[].
 */
const zend_function_entry globalss_functions[] = {
	PHP_FE(test_sapi_global,	NULL)		/* For testing, remove later. */
    PHP_FE(test_zend_global,    NULL)
    PHP_FE(test_php_global,     NULL)
	PHP_FE_END	/* Must be the last line in globalss_functions[] */
};
/* }}} */

/* {{{ globalss_module_entry
 */
zend_module_entry globalss_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"globalss",
	globalss_functions,
	PHP_MINIT(globalss),
	PHP_MSHUTDOWN(globalss),
	PHP_RINIT(globalss),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(globalss),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(globalss),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_GLOBALSS_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GLOBALSS
ZEND_GET_MODULE(globalss)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("globalss.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_globalss_globals, globalss_globals)
    STD_PHP_INI_ENTRY("globalss.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_globalss_globals, globalss_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_globalss_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_globalss_init_globals(zend_globalss_globals *globalss_globals)
{
	globalss_globals->global_value = 0;
	globalss_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(globalss)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(globalss)
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
PHP_RINIT_FUNCTION(globalss)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(globalss)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(globalss)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "globalss support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */



PHP_FUNCTION(test_sapi_global)
{
    php_printf("default_mimetype : %s\n", SG(default_mimetype));
}

PHP_FUNCTION(test_zend_global)
{
    php_printf("compiled_filename : %s\n", CG(compiled_filename));
}

PHP_FUNCTION(test_php_global)
{
    php_printf("user_ini_filename : %s\n", PG(user_ini_filename));
}
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
