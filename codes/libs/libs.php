<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('libs')) {
	dl('libs.' . PHP_SHLIB_SUFFIX);
}

echo libs_curl_version()."\n";

?>
