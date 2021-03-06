/*
  +----------------------------------------------------------------------+
  | Yet Another Framework                                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Xinchen Hui  <laruence@php.net>                              |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_YAF_H
#define PHP_YAF_H

extern zend_module_entry yaf_module_entry;
#define phpext_yaf_ptr &yaf_module_entry

#ifdef PHP_WIN32
#define PHP_YAF_API __declspec(dllexport)
#ifndef _MSC_VER
#define _MSC_VER 1600
#endif
#else
#define PHP_YAF_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#ifdef ZTS
#define YAF_G(v) TSRMG(yaf_globals_id, zend_yaf_globals *, v)
#else
#define YAF_G(v) (yaf_globals.v)
#endif

#define PHP_YAF_VERSION 					"3.0.5-dev"

// module init  函数
#define YAF_STARTUP_FUNCTION(module)   	ZEND_MINIT_FUNCTION(yaf_##module)
#define YAF_RINIT_FUNCTION(module)		ZEND_RINIT_FUNCTION(yaf_##module)
#define YAF_STARTUP(module)	 		  	ZEND_MODULE_STARTUP_N(yaf_##module)(INIT_FUNC_ARGS_PASSTHRU)
#define YAF_SHUTDOWN_FUNCTION(module)  	ZEND_MSHUTDOWN_FUNCTION(yaf_##module)
#define YAF_SHUTDOWN(module)	 	    ZEND_MODULE_SHUTDOWN_N(yaf_##module)(INIT_FUNC_ARGS_PASSTHRU)

#define yaf_application_t	zval
#define yaf_view_t 			zval
#define yaf_controller_t	zval
#define yaf_request_t		zval
#define yaf_router_t		zval
#define yaf_route_t			zval
#define yaf_dispatcher_t	zval
#define yaf_action_t		zval
#define yaf_loader_t		zval
#define yaf_response_t		zval
#define yaf_config_t		zval
#define yaf_registry_t		zval
#define yaf_plugin_t		zval
#define yaf_session_t		zval
#define yaf_exception_t		zval

#define YAF_ME(c, m, a, f) {m, PHP_MN(c), a, (uint) (sizeof(a)/sizeof(struct _zend_arg_info)-1), f},

extern PHPAPI void php_var_dump(zval **struc, int level);
extern PHPAPI void php_debug_zval_dump(zval **struc, int level);

// yaf 扩展 全局变量定义
ZEND_BEGIN_MODULE_GLOBALS(yaf)
	zend_string	*ext;						// 扩展名, php
	zend_string *base_uri;					
	zend_string *directory;
	zend_string *local_library;				// 本地library目录，通过application.library 配置
	zend_string *local_namespaces;
	zend_string *view_directory;
	zend_string *view_ext;					// view 模板的文件扩展名
	zend_string *default_module;			// 默认module Index
	zend_string *default_controller;		// 默认controller Index
	zend_string *default_action;			// 默认action 

	zend_string *bootstrap;
	char         *global_library;
    char         *environ_name;				// 配置节
    char         *name_separator;
    size_t        name_separator_len;
	zend_bool 	lowcase_path;
	zend_bool 	use_spl_autoload;
	zend_bool 	throw_exception;
	zend_bool   action_prefer;
	zend_bool	name_suffix;
	zend_bool  	autoload_started;
	zend_bool  	running;
	zend_bool  	in_exception;
	zend_bool  	catch_exception;
	zend_bool   suppressing_warning;
/* {{{ This only effects internally */
	zend_bool  	st_compatible;
/* }}} */
	long		forward_limit;
	HashTable	*configs;
	zval 		 modules;					// array, 保存多个模块的name
	zval        *default_route;
	zval        active_ini_file_section;
	zval        *ini_wanted_section;		// 设置的配置节
	uint        parsing_flag;
	zend_bool	use_namespace;
ZEND_END_MODULE_GLOBALS(yaf)

// 函数申明, php 扩展模块的执行模块
// 1. init module
// 2. shutdown module
// 3. request init
// 4. request shutdown
// 5. module infomation
//
// 顺序为: 1, 3, 4, 2


PHP_MINIT_FUNCTION(yaf);
PHP_MSHUTDOWN_FUNCTION(yaf);
PHP_RINIT_FUNCTION(yaf);
PHP_RSHUTDOWN_FUNCTION(yaf);

// 输出的扩展信息, 在php -i 中输出
PHP_MINFO_FUNCTION(yaf);

extern ZEND_DECLARE_MODULE_GLOBALS(yaf);

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
