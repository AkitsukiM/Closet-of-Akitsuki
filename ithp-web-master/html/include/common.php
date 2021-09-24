<?php

defined("ITHP_PAGE") or die();

function redirect($url) {
  header("Location: $url");
  exit();
}

function link_to($page, $lang) {
  return "?p=$page&l=$lang";
}

function redirect_page($page, $lang) {
  redirect(link_to($page, $lang));
}

$langs = array(
  "zh_cn" => "简体中文", 
  "en_us" => "English is not supported"
);

$pages = array();
$nav_folders = array();

$pages['home'] = array(
  "zh_cn" => "东方工程研究院", 
  "en_us" => "东方工程研究院" // "Institute of Touhou Project"
);

// ===== ===== ===== ===== ===== ===== ===== ===== ===== =====

$nav_folders['touhou'] = array(
  "zh_cn" => "东方是什么", 
  "en_us" => "东方是什么" // "What is Touhou?"
);

$pages['touhou_gensokyo'] = array(
  "zh_cn" => "关于幻想乡", 
  "en_us" => "关于幻想乡" // "Gensokyo"
);

$pages['touhou_zun'] = array(
  "zh_cn" => "关于ZUN", 
  "en_us" => "关于ZUN" // "ZUN"
);

// ===== ===== ===== ===== ===== ===== ===== ===== ===== =====

$nav_folders['intro'] = array(
  "zh_cn" => "东工院概况", 
  "en_us" => "东工院概况" // "What is IThP?"
);

$pages['intro_organization'] = array(
  "zh_cn" => "组织与成员", 
  "en_us" => "组织与成员" // "Organization"
);

$pages['intro_events'] = array(
  "zh_cn" => "小事记", 
  "en_us" => "小事记" // "Events"
);

// ===== ===== ===== ===== ===== ===== ===== ===== ===== =====

$nav_folders['activity'] = array(
  "zh_cn" => "活动专题：CTSL", 
  "en_us" => "活动专题：CTSL"
);

$pages['activity_1'] = array(
  "zh_cn" => "赛事简介", 
  "en_us" => "赛事简介"
);

$pages['activity_2'] = array(
  "zh_cn" => "赛程赛况", 
  "en_us" => "赛程赛况"
);

$pages['activity_3'] = array(
  "zh_cn" => "芹菜统计", 
  "en_us" => "芹菜统计"
);

$pages['activity_4'] = array(
  "zh_cn" => "比赛赞助", 
  "en_us" => "比赛赞助"
);

// ===== ===== ===== ===== ===== ===== ===== ===== ===== =====

$nav_folders['contact'] = array(
  "zh_cn" => "联系我们",
  "en_us" => "联系我们" // "Contact Us"
);

$contact = array();

$contact['contact_1'] = array(
  "zh_cn" => "东方工程研究院交流群",
  "en_us" => "东方工程研究院交流群",
  "target"  => "https://qm.qq.com/cgi-bin/qm/qr?k=eYoyZ7yBI5j8f8XuEV3GHlpMjR6Z839N&jump_from=webapi"
);

$contact['contact_2'] = array(
  "zh_cn" => "东方STG高校联赛交流群",
  "en_us" => "东方STG高校联赛交流群",
  "target"  => "https://qm.qq.com/cgi-bin/qm/qr?k=r6Q8uEbZmlrZTz8QZGCjU-kDAoGwmp4G&jump_from=webapi"
);

$contact['contact_3'] = array(
  "zh_cn" => "GitHub",
  "en_us" => "GitHub",
  "target"  => "https://github.com/AkitsukiM"
);

$nav_folders['lang'] = array(
  "zh_cn" => "语言", 
  "en_us" => "语言" // "Language"
);

function href($page, $lang, $text="", $class="") {
  global $pages;
  echo "<a class=\"$class\" href=\"" . htmlspecialchars(link_to($page, $lang)) . "\">" .
        ($text=="" ? htmlspecialchars($pages[$page][$lang]) : $text) . "</a>";
}

// $attachments = array(
//   "fothp"     => "foundations-of-touhou-project-rev.pdf"
// );

// function href_attachment($name, $text) {
//   global $attachments;
//   if (array_key_exists($name, $attachments)) {
//     echo "<a href=\"attachments/" . $attachments[$name] . "\">$text</a>";
//   }
// }

$strings = array();

$strings['links'] = array(
  "zh_cn" => "友情链接",
  "en_us" => "友情链接" // "Links"
);

$strings['home'] = array(
  "zh_cn" => "主页",
  "en_us" => "主页" // "Home Page"
);

$links = array();

$links['cas'] = array(
  "zh_cn" => "中国科学院",
  "en_us" => "中国科学院", // "Chinese Academy of Sciences",
  "target"  => "http://www.cas.cn/"
);

$links['ucas'] = array(
  "zh_cn" => "中国科学院大学",
  "en_us" => "中国科学院大学", // "University of Chinese Academy of Sciences",
  "target"  => "http://www.ucas.ac.cn/"
);

$links['tsa'] = array(
  "zh_cn" => "上海アリス幻樂団",
  "en_us" => "上海アリス幻樂団", // "Team Shanghai Alice",
  "target"  => "http://www16.big.or.jp/~zun/"
);

$links['thbwiki'] = array(
  "zh_cn" => "THBWiki",
  "en_us" => "THBWiki",
  "target"  => "https://thwiki.cc/"
);

$page = $_GET["p"];
$lang = $_GET["l"];
array_key_exists($page, $pages) or redirect_page("home", "zh_cn");
array_key_exists($lang, $langs) or redirect_page($page, "zh_cn");

?>

