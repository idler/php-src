/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Maxim Antonov <max.antonoff@gmail.com>                       |
  +----------------------------------------------------------------------+
   *
   * Idea of Proxy provided by Limb3 PHP Framwork ( http://limb-project.com/ )
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_proxy.h"



/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_proxy_construct, 0, 0, 1)
	ZEND_ARG_INFO(0, classname)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_proxy_get, 0, 0, 1)
	ZEND_ARG_INFO(0, arg)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_proxy_set, 0, 0, 1)
	ZEND_ARG_INFO(0, arga)
	ZEND_ARG_INFO(0, argb)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_proxy_call, 0, 0, 1)
	ZEND_ARG_INFO(0, arga)
	ZEND_ARG_INFO(0, argb)
ZEND_END_ARG_INFO()


/* }}} */

zend_class_entry *proxy_class_ce;

static zend_function_entry proxy_methods[] = {
	PHP_ME(Proxy, getme, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Proxy, createOriginalObject, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Proxy, resolve, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Proxy, __get, arginfo_proxy_get, ZEND_ACC_PUBLIC)
	PHP_ME(Proxy, __set, arginfo_proxy_set, ZEND_ACC_PUBLIC)
	PHP_ME(Proxy, __call, arginfo_proxy_call, ZEND_ACC_PUBLIC)
	PHP_ME(Proxy, __construct, arginfo_proxy_construct, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

void proxy_init_new(TSRMLS_D) {
  zend_class_entry ce;

  INIT_CLASS_ENTRY(ce, "Proxy", proxy_methods);
  proxy_class_ce = zend_register_internal_class(&ce TSRMLS_CC);


  /* fields */
  zend_declare_property_bool(proxy_class_ce, "alive", strlen("alive"), 1, ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_bool(proxy_class_ce, "is_resolved", strlen("is_resolved"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);
  zend_declare_property_null (proxy_class_ce, "original", strlen("original"), ZEND_ACC_PROTECTED TSRMLS_CC );
  /*zend_declare_property_bool(proxy_class_ce, "original", strlen("original"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);*/
  zend_declare_property_string(proxy_class_ce, "classname", strlen("classname"), "", ZEND_ACC_PROTECTED TSRMLS_CC );


}

PHP_METHOD(Proxy, __construct) {
	char *classname;
	int namelen;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &classname, &namelen) == FAILURE) {
		return;
	}
	 zend_update_property_stringl ( proxy_class_ce, this_ptr, "classname", strlen("classname"),
	 classname, namelen TSRMLS_CC );
  // TODO
}

PHP_METHOD(Proxy, getme) {
	RETURN_STRING("foo bar",1);
  // TODO
}

PHP_METHOD(Proxy, createOriginalObject) {
	RETURN_STRING("orig obj",1);
  // TODO
}
PHP_METHOD(Proxy, resolve) {
	RETURN_STRING("resolve",1);
  // TODO
}
PHP_METHOD(Proxy, __get) {
	RETURN_STRING("get",1);
  // TODO
}
PHP_METHOD(Proxy, __set) {
	RETURN_STRING("set",1);
  // TODO
}
PHP_METHOD(Proxy, __call) {

	char *arg1, *arg2;
	int l1,l2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &arg1, &l1, &arg2, &l2) == FAILURE) {
		return;
	}
	php_printf("Tring to call %s %s\n",arg1,arg2);

	RETURN_STRING("try to call ",1);
  // TODO
}
/* If you declare any globals in php_proxy.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(proxy)
*/

/* True global resources - no need for thread safety here */
//static int le_proxy;

/* {{{ proxy_functions[]
 *
 * Every user visible function must have an entry in proxy_functions[].
 */


const zend_function_entry proxy_functions[] = {
	PHP_FE(confirm_proxy_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in proxy_functions[] */
};
/* }}} */

/* {{{ proxy_module_entry
 */
zend_module_entry proxy_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"proxy",
	proxy_functions,
	PHP_MINIT(proxy),
	PHP_MSHUTDOWN(proxy),
	PHP_RINIT(proxy),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(proxy),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(proxy),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PROXY
ZEND_GET_MODULE(proxy)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("proxy.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_proxy_globals, proxy_globals)
    STD_PHP_INI_ENTRY("proxy.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_proxy_globals, proxy_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_proxy_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_proxy_init_globals(zend_proxy_globals *proxy_globals)
{
	proxy_globals->global_value = 0;
	proxy_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(proxy)
{
	proxy_init_new(TSRMLS_C);
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(proxy)
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
PHP_RINIT_FUNCTION(proxy)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(proxy)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(proxy)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "proxy support", "enabled");
	php_info_print_table_row(2, "proxy class version", PHP_PROXY_VER);
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_proxy_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_proxy_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "proxy", arg);
	RETURN_STRINGL(strg, len, 0);
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
