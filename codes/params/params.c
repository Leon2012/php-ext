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
#include "php_params.h"

#define PRINT_ZVAL(zv) \
    php_printf("%s:%d   PRINT_ZVAL %x, refcount=%d, is_ref=%d, value = ", \
        __FILE__, __LINE__, zv, Z_REFCOUNT_P(zv), Z_ISREF_P(zv)); \
    Z_ADDREF_P((zv)); \
    zend_print_zval_r((zv), 0 TSRMLS_CC); \
    Z_DELREF_P((zv));

//字符串类型参数
ZEND_BEGIN_ARG_INFO(params_str_arginfo, 0)
    ZEND_ARG_INFO(0, a)
    ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

static PHP_FUNCTION(params_str) {
    char *str = "";
    int str_len = 0;
    long i = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sl", &str, &str_len, &i) == FAILURE) {
        return;
    }

    php_printf("string(%d) value:", str_len);
    PHPWRITE(str, str_len);
    php_printf("\n");

    php_printf("int(%d)\n", i);
    php_printf("\n");
}



//基本类型参数
ZEND_BEGIN_ARG_INFO(params_add_arginfo, 0)
    ZEND_ARG_INFO(0, a)
    ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

static PHP_FUNCTION(params_add) {
    long a,b;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &a, &b) == FAILURE) {
        return;
    }

    RETURN_LONG(a+b);
}

//打印所有的数组值
ZEND_BEGIN_ARG_INFO(params_dump_arginfo, 0)
    ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

static PHP_FUNCTION(params_dump) {
    zval *arg;//定义参数值,zval可以表示所有的参数的值

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &arg) == FAILURE) {
        return;
    }

    switch(Z_TYPE_P(arg)) {
        case IS_NULL://arg is null
            php_printf("NULL\n");
            break;
        case IS_BOOL://arg is true, false
            php_printf("bool(%s)\n", Z_BVAL_P(arg)?"true":"false");
            break;
        case IS_LONG:
            php_printf("int(%d)\n", Z_LVAL_P(arg));
            break;
        case IS_DOUBLE:
            php_printf("float(%f)\n", Z_DVAL_P(arg));
            break;
        case IS_STRING:
            php_printf("string(%d)\n", Z_STRLEN_P(arg));
            PHPWRITE(Z_STRVAL_P(arg), Z_STRLEN_P(arg));
            php_printf("\n");
            break;
        case IS_ARRAY:
            php_printf("array(%d){...}\n", zend_hash_num_elements(Z_ARRVAL_P(arg)));
            break;
        case IS_RESOURCE:{
            const char *type_name = zend_rsrc_list_get_rsrc_type(Z_RESVAL_P(arg) TSRMLS_CC);
            php_printf("resource#%ld(%s)\n", Z_RESVAL_P(arg), type_name?type_name:"Unknown");
            break;
        }
        case IS_OBJECT:{
            const zend_class_entry *ce = Z_OBJCE_P(arg);
            php_printf("object#%u(%s)\n", Z_OBJ_HANDLE_P(arg), (ce && ce->name)?ce->name:"Unknown");
            break;
        }
        default:
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unknown type: %d\n", Z_TYPE_P(arg));
    }

}


//array类型参数
ZEND_BEGIN_ARG_INFO(params_array_arginfo, 0)
    ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

static PHP_FUNCTION(params_array) {
    HashTable *options = NULL;
    zval *v;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &v) == FAILURE) {
        RETURN_FALSE;
    }

    options = Z_ARRVAL_P(v);//读取array类型的值

    //zend_hash_internal_pointer_reset 
    //zend_hash_has_more_elements 判断HashTable是否有元素
    //zend_hash_move_forward 移动HashTable到顶端
    //zend_hash_get_current_key_ex 读取HashTable当前的key，HashTable的key有两种，一种是指定字符串，另一种是顺序的0-n下标
    //zend_hash_get_current_data 读取HashTable当前的值到zval
    //zend_hash_get_current_key_type 获取当前key的类型

    for(zend_hash_internal_pointer_reset(options); SUCCESS == zend_hash_has_more_elements(options); zend_hash_move_forward(options)) {
        char *k1;
        ulong nkey = -1, keylen;
        zval **z;
        zend_hash_get_current_key_ex(options, &k1, &keylen, &nkey, 0, NULL);
        zend_hash_get_current_data(options, (void **)&z);
        php_printf(" key: ");

        if (HASH_KEY_IS_STRING == zend_hash_get_current_key_type(options)) {
            PHPWRITE(k1, keylen);
        }else{
            php_printf("%ld", nkey);
        }

        php_printf("  value: ");
        if (Z_TYPE_P(*z) == IS_STRING) {
            //php_printf("string(%d)\n", Z_STRLEN_P(*z));
            PHPWRITE(Z_STRVAL_P(*z), Z_STRLEN_P(*z));
        }else{
            zend_print_zval_r((*z), 0 TSRMLS_CC); 
        }
        php_printf("\n");
    }

    RETURN_TRUE;
}


//object类型参数
ZEND_BEGIN_ARG_INFO(params_object_arginfo, 0)
    ZEND_ARG_OBJ_INFO(0, student, studentObj, 0)
ZEND_END_ARG_INFO()



/* {{{ params_functions[]
 *
 * Every user visible function must have an entry in params_functions[].
 */
const zend_function_entry params_functions[] = {
	PHP_FE(params_add,	params_add_arginfo)		
    PHP_FE(params_dump, params_dump_arginfo)
    PHP_FE(params_array, params_array_arginfo)
    PHP_FE(params_str, params_str_arginfo)
	PHP_FE_END	
};
/* }}} */

/* {{{ params_module_entry
 */
zend_module_entry params_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"params",
	params_functions,
	NULL,
	NULL,
	NULL,		/* Replace with NULL if there's nothing to do at request start */
	NULL,	/* Replace with NULL if there's nothing to do at request end */
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	PHP_PARAMS_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PARAMS
ZEND_GET_MODULE(params)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
