<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('consts')) {
	dl('consts.' . PHP_SHLIB_SUFFIX);
}

echo "CONSTS_MEANING_OF_LIFE:" . CONSTS_MEANING_OF_LIFE."\n";
echo "CONSTS_PI:".CONSTS_PI."\n";
echo "CONSTS_NAME:".CONSTS_NAME."\n";

echo "CONSTS_RAND:".CONSTS_RAND."\n";

echo "CONSTS_RAND_1:".CONSTS_RAND_1."\n";
?>
