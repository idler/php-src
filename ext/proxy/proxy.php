<?php

class myTest
{
  protected $txt = 'Some text';
  function thisIsNoMethod()
  {
    return "is not very strange";
  }

}

$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('proxy')) {
	dl('proxy.' . PHP_SHLIB_SUFFIX);
}
$module = 'proxy';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
$function = 'confirm_' . $module . '_compiled';
if (extension_loaded($module)) {
	$str = $function($module);
} else {
	$str = "Module $module is not compiled into PHP";
}
echo "$str\n";
$p = new Proxy('myTest');
$t = new Proxy('myTest');
$t->alive=false;
var_dump(array($p,$p->getme(),$t,$t->getme()));

var_dump(array($p->resolve(),$p->notexists_property,$p->thisIsNoMethod()));

?>
