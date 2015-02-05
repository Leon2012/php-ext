<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('fcall')) {
	dl('fcall.' . PHP_SHLIB_SUFFIX);
}

function callback($msg) {
    $ret = "msg:".$msg . "\n";
    echo  $ret;
}


echo fcall_byname()."\n";

echo fcall_bycallback("callback")."\n";


?>
