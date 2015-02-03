<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('global')) {
	dl('global.' . PHP_SHLIB_SUFFIX);
}

// global_inc();
// echo global_get()."\n";

// global_inc();
// global_inc();
// echo global_get()."\n";

// echo global_name("leon") . "\n";
// //echo global_get_name()."\n";

// echo global_name("jacky") . "\n";
// //echo global_get_name()."\n";

// print_r(print_server_vars());

// $val = print_server_var("GOPATH");
// if (is_null($val)) {
//     echo "not found!!!";
// }else{
//     echo $val."\n";
// }


//print_r($GLOBALS);
add_globals_vars();
add_globals_var("_name", "leon");
print_r($GLOBALS);


?>
