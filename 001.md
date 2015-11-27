# gdb调试PHP扩展函数

1，编译debug版的php

	git clone https://github.com/php/php-src.git
	cd php-src
	CFLAGS=-ggdb3
	./configure --prefix=/opt/php-debug --enable-debug --enable-cli --without-pear --enable-embed --enable-phpdbg
	make 
	make install
	mkdir /opt/php-debug/conf/
	cp php.ini-development /opt/php-debug/conf/php.ini
	
2，创建debug信息的扩展
	
	./ext_skel --extname=hello2
	cd hello2
	
	#vi config.m4
	#添加下面信息
	if test -z "$PHP_DEBUG"; then 
  	AC_ARG_ENABLE(debug,
  	[ --enable-debug      compile with debugging symbols],[
    	PHP_DEBUG=$enableval
  	],[ PHP_DEBUG=no
  	])
	fi
	
	/opt/php-debug/bin/phpize
	./configure --with-php-config=/opt/php-debug/bin/php-config --enable-debug
	make
	sudo make install
	
3，调试echo函数
	
	#查找符号表
	sh-3.2# nm /opt/php-debug/bin/php | grep  echo
	00000001004a9f70 t _zend_do_echo
	
	gdb /opt/php-debug/bin/php
	#设置断点
	(gdb) break zend_do_echo
	
	#运行
	(gdb) run -c /opt/php-debug/conf/php.ini -q /Users/kentchen/Downloads/test.php
	
	#输出堆栈
	(gdb) bt
	#0  zend_do_echo (arg=0x7fff5fbfc2a0) at Zend/zend_compile.c:866
	#1  0x0000000100474bbd in zendparse () at Zend/zend_language_parser.c:4469
	#2  0x000000010047b5be in compile_file (file_handle=0x7fff5fbff3b0, type=8) at Zend/zend_language_scanner.l:588
	#3  0x00000001002b8250 in phar_compile_file (file_handle=0x7fff5fbff3b0, type=8) at ext/phar/phar.c:3384
	#4  0x00000001004e51b5 in zend_execute_scripts (type=8, retval=0x0, file_count=3) at Zend/zend.c:1322
	#5  0x000000010043137c in php_execute_script (primary_file=0x7fff5fbff3b0) at main/main.c:2506
	#6  0x00000001005b0415 in do_cli (argc=5, argv=0x100c03f00) at sapi/cli/php_cli.c:994
	#7  0x00000001005af143 in main (argc=5, argv=0x100c03f00) at sapi/cli/php_cli.c:1378
	
	#继续执行，输出结果
	(gdb) c
	
	
4，调试扩展函数 

	#查找符号表
	nm /opt/php-debug/lib/php/extensions/debug-non-zts-20121212/hello2.so | grep  confirm_hello2_compiled
	0000000000000cf0 T _zif_confirm_hello2_compiled
	
	sh-3.2# gdb /opt/php-debug/bin/php
	
	#设置断点
	(gdb) break zif_confirm_hello2_compiled
	Function "zif_confirm_hello2_compiled" not defined.
	Make breakpoint pending on future shared library load? (y or [n]) y
	Breakpoint 1 (zif_confirm_hello2_compiled) pending.
	
	#执行php script
	(gdb) run -c /opt/php-debug/conf/php.ini -q hello2.php
	Starting program: /opt/php-debug/bin/php -c /opt/php-debug/conf/php.ini -q hello2.php
	
	#next
	(gdb) n
	160		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
	
	#next
	(gdb) n
	164		len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "hello2", arg);
	
	#输出变量arg
	(gdb) p arg
	$1 = 0x100d24c90 "hello2"
	
	#输出变量arg_len
	(gdb) p arg_len
	$2 = 6
	
	#next
	(gdb) n
	165		RETURN_STRINGL(strg, len, 0);
	
	#输出变量
	(gdb) p len
	$5 = 109
	
	(gdb) p strg
	$6 = 0x100be84a8 "Congratulations! You have successfully modified ext/hello2/config.m4. Module hello2 is now compiled into PHP."
	
	#Continuing
	(gdb) c
	Continuing.
	Congratulations! You have successfully modified ext/hello2/config.m4. Module hello2 is now compiled into PHP.
	warning: Temporarily disabling breakpoints for unloaded shared library "/opt/php-debug/lib/php/extensions/debug-non-zts-20121212/hello2.so"
	[Inferior 1 (process 3162) exited normally]
	
	(gdb) define phpbt
  		set $ed=execute_data
  		while $ed
    			print ((zend_execute_data *)$ed)->function_state.function->common.function_name
    			set $ed = ((zend_execute_data *)$ed)->prev_execute_data
  		end
	      end
	(gdb) define hashkeys
  		set $p = (HashTable*)$arg0->pListHead
		 while $p
    			output (Bucket*)$p
    		echo \t
		 x/s (char*)(((Bucket*)$p)->arKey)
    		set $p = ((Bucket*)$p)->pListNext
  		end
		end
	(gdb) define bucketdata
	      print **(zval**)(((struct bucket *) $arg0)->pData)
              end
	
	(gdb) hashkeys executor_globals.included_files
	(Bucket *) 0x7ffff7fe1be0	0x7ffff7fe1c28:	 "/temp/echo.php"
	
