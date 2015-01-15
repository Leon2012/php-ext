<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('params')) {
	dl('params.' . PHP_SHLIB_SUFFIX);
}
$module = 'params';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";

// $func = "params_add";
// echo "result:".call_user_func($func, 8, 5)."\n";

// $func = "params_dump";
// call_user_func($func, 10)."\n";
// call_user_func($func, "hello")."\n";
// call_user_func($func, false)."\n";
// call_user_func($func, 3.50)."\n";
// call_user_func($func, array("a" => "a"))."\n";

// $foo = new stdClass();
// $foo->name = "leon";
// call_user_func($func, $foo)."\n";

// $fp = fopen("params.c", "r");
// call_user_func($func, $fp)."\n";
// fclose($fp);


// $func = "params_array";
// call_user_func($func, array("a" => "1", "b" => "2", "c" => "3"));


$func = "params_str";
call_user_func($func, "hello world", 10);
call_user_func($func);

?>
