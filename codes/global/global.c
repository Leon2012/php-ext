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
#include "php_global.h"

ZEND_DECLARE_MODULE_GLOBALS(global);


static PHP_FUNCTION(global_inc) {
    GLOBAL_G(counter)++;
}

static PHP_FUNCTION(global_get) {
    RETURN_LONG(GLOBAL_G(counter));
}

static PHP_FUNCTION(global_get_name) {
    RETURN_STRING(GLOBAL_G(name), 0);
}

ZEND_BEGIN_ARG_INFO(global_name_arginfo, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

static PHP_FUNCTION(global_name) {
    char *name = NULL;
    int name_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s!", &name, &name_len) == FAILURE) {
        return;
    }

    if (GLOBAL_G(name)) {
        if (name) {
            RETVAL_STRINGL(GLOBAL_G(name), GLOBAL_G(name_len), 0);
        }else{
            RETVAL_STRINGL(GLOBAL_G(name), GLOBAL_G(name_len), 1);
        }
    }

    if (name != NULL) {
        GLOBAL_G(name) = estrndup(name, name_len);
        GLOBAL_G(name_len) = name_len;
    }
}

static PHP_FUNCTION(print_get_vars) {
    zval **val;
    if (zend_hash_find(&EG(symbol_table), "_GET", sizeof("_GET"), (void **)&val) == SUCCESS) {
        //Z_ADDREF_PP(val);
        RETURN_ZVAL(*val, 1, 0);
    }else{
        RETURN_FALSE;
    }
}

static PHP_FUNCTION(print_server_vars) {
    zval **val;
    if (zend_hash_find(&EG(symbol_table), "_SERVER", sizeof("_SERVER"), (void **)&val) == SUCCESS) {
        //Z_ADDREF_PP(val);
        RETURN_ZVAL(*val, 1, 0);
    }else{
        RETURN_FALSE;
    }
}

ZEND_BEGIN_ARG_INFO(add_globals_var_arginfo, 0)
    ZEND_ARG_INFO(0, "key")
    ZEND_ARG_INFO(0, "val")
ZEND_END_ARG_INFO()

static PHP_FUNCTION(add_globals_var) {
    char *key;
    char *val;
    int key_len = 0;
    int val_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &key, &key_len, &val, &val_len) == FAILURE) {
        RETURN_FALSE;
    }

    SET_VAR_STRING(key, val);
    RETURN_TRUE;
}


static PHP_FUNCTION(add_globals_vars) {
    SET_VAR_LONG("_LONG", 10);
    SET_VAR_DOUBLE("_DOUBLE", 20.5);
    SET_VAR_STRING("_STRING", "string");

    zval *arr;
    MAKE_STD_ZVAL(arr);
    array_init(arr);
    add_assoc_string(arr, "e", "hello", 1);

    ZEND_SET_GLOBAL_VAR("_ARRS", arr);
}


ZEND_BEGIN_ARG_INFO(print_server_var_arginfo, 0)
    ZEND_ARG_INFO(0, "name")
ZEND_END_ARG_INFO()

static PHP_FUNCTION(print_server_var) {
    char *name;
    int name_len;
    zval **val;
    HashTable *ht_vars = NULL;
    HashPosition pos;
    zval **ret_val;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s!", &name, &name_len) == FAILURE) {
        RETURN_NULL();
    }

    if (zend_hash_find(&EG(symbol_table), "_SERVER", sizeof("_SERVER"), (void **)&val) == SUCCESS) {
        ht_vars = Z_ARRVAL_PP(val);
        php_printf("name, :%s len : %d \n", name, name_len);
        php_printf("name1 :%s, len1: %d \n", name, sizeof(name));


        // for (zend_hash_internal_pointer_reset_ex(ht_vars, &pos); 
        //         zend_hash_get_current_data_ex(ht_vars, (void**) &ret_val, &pos) == SUCCESS; 
        //         zend_hash_move_forward_ex(ht_vars, &pos)) {

        //     char *key = NULL;
        //     uint klen;
        //     ulong index;
        //     if (zend_hash_get_current_key_ex(ht_vars, &key, &klen, &index, 0, &pos) == HASH_KEY_IS_LONG) {
        //         php_printf("%d \n", index);
        //     }else{
        //         php_printf("%s \n", key);
        //     }

        // }

        if (zend_hash_find(ht_vars, name, name_len+1, (void **)&ret_val) == SUCCESS) {
            RETURN_STRING(Z_STRVAL_PP(ret_val), 0);
        }else{
            php_printf("null ===== 2 \n");
            RETURN_NULL();
        }

        // RETURN_NULL();

    }else{

        RETURN_NULL();
    }
}


const zend_function_entry global_functions[] = {
	PHP_FE(global_name,	global_name_arginfo)		
    PHP_FE(global_inc, NULL)
    PHP_FE(global_get, NULL)
    PHP_FE(global_get_name, NULL)
    PHP_FE(print_get_vars, NULL)
    PHP_FE(print_server_vars, NULL)
    PHP_FE(print_server_var, print_server_var_arginfo)
    PHP_FE(add_globals_var, add_globals_var_arginfo)
    PHP_FE(add_globals_vars, NULL)
	PHP_FE_END	/* Must be the last line in global_functions[] */
};



zend_module_entry global_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"global",
	global_functions,
	PHP_MINIT(global),
	PHP_MSHUTDOWN(global),
	PHP_RINIT(global),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(global),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(global),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_GLOBAL_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GLOBAL
ZEND_GET_MODULE(global)
#endif


PHP_MINIT_FUNCTION(global)
{

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(global)
{

	return SUCCESS;
}



PHP_RINIT_FUNCTION(global)
{
    //初始化global变量
    GLOBAL_G(counter) = 0;
    GLOBAL_G(name) = NULL;

	return SUCCESS;
}



PHP_RSHUTDOWN_FUNCTION(global)
{
    //释放global变量
    if (GLOBAL_G(name)) {
        efree(GLOBAL_G(name));
        GLOBAL_G(name) = NULL;
    }

	return SUCCESS;
}



PHP_MINFO_FUNCTION(global)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "global support", "enabled");
	php_info_print_table_end();


}



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
