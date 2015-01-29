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
#include "php_array.h"


//定义参数类型，此处定义了两个数组类型参数
ZEND_BEGIN_ARG_INFO(array_greet_arginfo, 0)
    ZEND_ARG_ARRAY_INFO(0, names, 1)
    ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(array_greet) {
    HashTable *names, *options = NULL;
    HashPosition pos;
    zval **val;
    zend_bool hello = 1;
    zend_bool key_exist;

    //读取hashTable*值
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "h|h!", &names, &options) == FAILURE) {
        return;
    }


    key_exist = zend_hash_exists(options, "key", sizeof("key"));
    if (key_exist == 1) {
        php_printf("key is exist!!! \n");
    }else{
        php_printf("key is not exist!!! \n");
    }

    if (options && zend_hash_find(options, "hello", sizeof("hello"), (void **)&val) == SUCCESS) {
        hello = zend_is_true(*val);
    }


    char *k1 = "key1";
    zval *v1;
    MAKE_STD_ZVAL(v1);
    ZVAL_STRING(v1, "value1", 1);
    zend_hash_add(names, k1, sizeof(k1), &v1, sizeof(zval *), NULL);

    zval *v2;
    MAKE_STD_ZVAL(v2);
    ZVAL_STRING(v2, "value2", 1);
    zend_hash_update(names, "name", sizeof("name"), &v2, sizeof(zval *), NULL);


    zend_hash_del(names, k1, sizeof(k1));


    zval *v3;
    MAKE_STD_ZVAL(v3);
    ZVAL_STRING(v3, "value3", 1);
    zend_hash_index_update(names, 0, &v3, sizeof(zval *), NULL);


    zval **v4;
    zend_hash_index_find(names, 1, &v4);
    php_printf("v4 : ");
    PHPWRITE(Z_STRVAL_PP(v4), Z_STRLEN_PP(v4));
    php_printf("\n");

    ulong idx;
    idx = zend_hash_index_exists(names, 10);
    php_printf("index 2 exists : %d \n", (int)idx);

    zend_hash_index_del(names, 2);

    // zval *v5;
    // MAKE_STD_ZVAL(v5);
    // ZVAL_STRING(v5, "value5", 1);
    // zend_hash_index_add(names, 2, v5);


    for (zend_hash_internal_pointer_reset_ex(names, &pos); zend_hash_get_current_data_ex(names, (void**) &val, &pos) == SUCCESS; zend_hash_move_forward_ex(names, &pos)) {


        if (Z_TYPE_PP(val) != IS_STRING) {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "All names must be strings, ignoring");
            continue;
        }

        char *key = NULL;
        uint klen;
        ulong index;
        if (zend_hash_get_current_key_ex(names, &key, &klen, &index, 0, &pos) == HASH_KEY_IS_LONG) {
            php_printf("%s  %d ", (hello?"hello":"goodbye"), index);
        }else{
            php_printf("%s  %s ", (hello?"hello":"goodbye"), key);
        }

        PHPWRITE(Z_STRVAL_PP(val), Z_STRLEN_PP(val));
        php_printf("\n");
    }

}


const zend_function_entry array_functions[] = {
	PHP_FE(array_greet,	array_greet_arginfo)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in array_functions[] */
};


zend_module_entry array_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"array",
	array_functions,
	NULL,
	NULL,
	NULL,		/* Replace with NULL if there's nothing to do at request start */
	NULL,	/* Replace with NULL if there's nothing to do at request end */
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	PHP_ARRAY_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_ARRAY
ZEND_GET_MODULE(array)
#endif




/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
