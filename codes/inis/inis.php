<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('inis')) {
	dl('inis.' . PHP_SHLIB_SUFFIX);
}
$module = 'inis';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}


$func = "inis_report";
call_user_func($func);
?>
