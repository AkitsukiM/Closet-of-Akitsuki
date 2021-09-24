<?php
define("ITHP_PAGE", "");
require "include/common.php";
?>
<!DOCTYPE html>
<html>
<?php require "include/head.php"; ?>
<body>
<?php 
require "include/nav.php";
// if (file_exists("contents/$page-$lang.php")) {
//   require "contents/$page-$lang.php";
// }
// else 
if (file_exists("contents/$page-zh_cn.php")) {
  require "contents/$page-zh_cn.php";
}
else {
  redirect_page("home", "zh_cn");
}
require "include/footer.php";
?>
</body>
</html>