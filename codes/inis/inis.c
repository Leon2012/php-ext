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
#include "php_inis.h"


ZEND_DECLARE_MODULE_GLOBALS(inis)

PHP_FUNCTION(inis_report) {
    php_printf("Name:%s\n", INIS_G(name));
    php_printf("Level:%d\n", INIS_G(level));
}

const zend_function_entry inis_functions[] = {
	PHP_FE(inis_report,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in inis_functions[] */
};



zend_module_entry inis_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"inis",
	inis_functions,
	PHP_MINIT(inis),
	PHP_MSHUTDOWN(inis),
	PHP_RINIT(inis),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(inis),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(inis),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_INIS_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_INIS
ZEND_GET_MODULE(inis)
#endif


PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("inis.name",      "leon peng", PHP_INI_ALL, OnUpdateString, name, zend_inis_globals, inis_globals)
    STD_PHP_INI_ENTRY("inis.level", "100", PHP_INI_ALL, OnUpdateLong, level, zend_inis_globals, inis_globals)
PHP_INI_END()


static void php_inis_init_globals(zend_inis_globals *inis_globals)
{
	inis_globals->name = "leon";
	inis_globals->level = 10;
}



PHP_MINIT_FUNCTION(inis)
{
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}



PHP_MSHUTDOWN_FUNCTION(inis)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}



PHP_RINIT_FUNCTION(inis)
{
	return SUCCESS;
}



PHP_RSHUTDOWN_FUNCTION(inis)
{
	return SUCCESS;
}



PHP_MINFO_FUNCTION(inis)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "inis support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
