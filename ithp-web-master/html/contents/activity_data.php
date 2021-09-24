<?php

defined("ITHP_PAGE") or die();

function echo_name_and_space($name, $space){
    if ($name == "" || $space == ""){
        echo $name;
    }
    else{
        echo "<a href=$space target='_blank'>$name</a>";
    }
}

function echo_comma($name){
    if ($name != ""){
        echo "、";
    }
}

function echo_seprt($name){
    if ($name != ""){
        echo " · ";
    }
}

$game = array();

$game["game_01"] = array(
    "game_number"       => "th16_NM",
    "game_name"         => "天空璋Lunatic混关",
    "game_video"        => "https://www.bilibili.com/video/BV1wv411p7qS",
    "game_time"         => "7.11-Sun 15:00",

    "gamer1_name"       => "折翼的天子",
    "gamer1_space"      => "https://space.bilibili.com/6702969/",
    "gamer1_score"      => "8-0",
    "gamer1_jf"         => "2",
    "gamer1_odds"       => "1.14937",

    "gamer2_name"       => "筱蓝",
    "gamer2_space"      => "https://space.bilibili.com/8012418/",
    "gamer2_score"      => "5-3",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "10.019",

    "gamer3_name"       => "THN",
    "gamer3_space"      => "https://space.bilibili.com/32680359/",
    "gamer3_score"      => "5-0",
    "gamer3_jf"         => "0",
    "gamer3_odds"       => "33.1708",

    "speaker1_name"     => "审判长四季",
    "speaker1_space"    => "https://space.bilibili.com/175080260/",

    "speaker2_name"     => "EH_tl",
    "speaker2_space"    => "https://space.bilibili.com/53720267/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_02"] = array(
    "game_number"       => "th14_NB",
    "game_name"         => "辉针城Lunatic避弹",
    "game_video"        => "https://www.bilibili.com/video/BV1mV411W7wi",
    "game_time"         => "7.11-Sun 20:00",

    "gamer1_name"       => "",
    "gamer1_space"      => "",
    "gamer1_score"      => "",
    "gamer1_jf"         => "",
    "gamer1_odds"       => "inf",

    "gamer2_name"       => "吃货子sama",
    "gamer2_space"      => "https://space.bilibili.com/5491269/",
    "gamer2_score"      => "梦B 3M 11.62pts",
    "gamer2_jf"         => "2",
    "gamer2_odds"       => "1.35427",

    "gamer3_name"       => "marksman",
    "gamer3_space"      => "https://space.bilibili.com/148148389/",
    "gamer3_score"      => "魔B 5M 8.62pts",
    "gamer3_jf"         => "1",
    "gamer3_odds"       => "3.82273",

    "speaker1_name"     => "葵",
    "speaker1_space"    => "https://space.bilibili.com/162140829/",

    "speaker2_name"     => "YukariM",
    "speaker2_space"    => "https://space.bilibili.com/49892452/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_03"] = array(
    "game_number"       => "th13_NM",
    "game_name"         => "神灵庙Lunatic混关",
    "game_video"        => "https://www.bilibili.com/video/BV1uy4y1j7kV",
    "game_time"         => "7.17-Sat 15:00",

    "gamer1_name"       => "SV",
    "gamer1_space"      => "https://space.bilibili.com/4636287/",
    "gamer1_score"      => "5-0",
    "gamer1_jf"         => "1",
    "gamer1_odds"       => "77.55",

    "gamer2_name"       => "CZW",
    "gamer2_space"      => "https://space.bilibili.com/4861197/",
    "gamer2_score"      => "4-0",
    "gamer2_jf"         => "0",
    "gamer2_odds"       => "1.16529",

    "gamer3_name"       => "影月",
    "gamer3_space"      => "https://space.bilibili.com/3182660/",
    "gamer3_score"      => "5-1",
    "gamer3_jf"         => "2",
    "gamer3_odds"       => "7.755",

    "speaker1_name"     => "THN",
    "speaker1_space"    => "https://space.bilibili.com/32680359/",

    "speaker2_name"     => "H3PO4⑨",
    "speaker2_space"    => "https://space.bilibili.com/16076021/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_04"] = array(
    "game_number"       => "th07_NB",
    "game_name"         => "妖妖梦Lunatic避弹",
    "game_video"        => "https://www.bilibili.com/video/BV1Rh411B7MY",
    "game_time"         => "7.17-Sat 20:00",

    "gamer1_name"       => "INT",
    "gamer1_space"      => "https://space.bilibili.com/645643925/",
    "gamer1_score"      => "咲A 4M 6.32pts",
    "gamer1_jf"         => "1",
    "gamer1_odds"       => "6.01867",

    "gamer2_name"       => "zxxsmart",
    "gamer2_space"      => "https://space.bilibili.com/3434266/",
    "gamer2_score"      => "魔B 2M 9.25pts",
    "gamer2_jf"         => "3",
    "gamer2_odds"       => "1.43804",

    "gamer3_name"       => "Doll",
    "gamer3_space"      => "https://space.bilibili.com/3345076/",
    "gamer3_score"      => "梦A 1M 9.17pts",
    "gamer3_jf"         => "2",
    "gamer3_odds"       => "7.2224",

    "speaker1_name"     => "LKY",
    "speaker1_space"    => "https://space.bilibili.com/305575617/",

    "speaker2_name"     => "EnK",
    "speaker2_space"    => "https://space.bilibili.com/4275270/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_05"] = array(
    "game_number"       => "th11_NM",
    "game_name"         => "地灵殿Lunatic混关",
    "game_video"        => "https://www.bilibili.com/video/BV14g411M7PT",
    "game_time"         => "7.18-Sun 15:00",

    "gamer1_name"       => "Roidt",
    "gamer1_space"      => "",
    "gamer1_score"      => "7-0",
    "gamer1_jf"         => "0",
    "gamer1_odds"       => "10.2727",

    "gamer2_name"       => "A_zz",
    "gamer2_space"      => "https://space.bilibili.com/42320287/",
    "gamer2_score"      => "7-4",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "1.13",

    "gamer3_name"       => "mianaya",
    "gamer3_space"      => "https://space.bilibili.com/87462796/",
    "gamer3_score"      => "8-1.9",
    "gamer3_jf"         => "2",
    "gamer3_odds"       => "56.5",

    "speaker1_name"     => "THN",
    "speaker1_space"    => "https://space.bilibili.com/32680359/",

    "speaker2_name"     => "小田原シクラメン",
    "speaker2_space"    => "https://space.bilibili.com/20192515/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_06"] = array(
    "game_number"       => "th06_NM",
    "game_name"         => "红魔乡Lunatic混关",
    "game_video"        => "https://www.bilibili.com/video/BV1J64y167rF",
    "game_time"         => "7.18-Sun 20:00",

    "gamer1_name"       => "风祝chan",
    "gamer1_space"      => "https://space.bilibili.com/11829618/",
    "gamer1_score"      => "3-0",
    "gamer1_jf"         => "0",
    "gamer1_odds"       => "1.088",

    "gamer2_name"       => "MNY",
    "gamer2_space"      => "",
    "gamer2_score"      => "4-0",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "22.6667",

    "gamer3_name"       => "",
    "gamer3_space"      => "",
    "gamer3_score"      => "",
    "gamer3_jf"         => "",
    "gamer3_odds"       => "27.2",

    "speaker1_name"     => "A_zz",
    "speaker1_space"    => "https://space.bilibili.com/42320287/",

    "speaker2_name"     => "折翼的天子",
    "speaker2_space"    => "https://space.bilibili.com/6702969/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_07"] = array(
    "game_number"       => "th18_EX",
    "game_name"         => "虹龙洞Extra避弹",
    "game_video"        => "https://www.bilibili.com/video/BV1tw411R7Zm",
    "game_time"         => "7.24-Sat 15:00",

    "gamer1_name"       => "",
    "gamer1_space"      => "",
    "gamer1_score"      => "",
    "gamer1_jf"         => "",
    "gamer1_odds"       => "15",

    "gamer2_name"       => "Death",
    "gamer2_space"      => "https://space.bilibili.com/6967402/",
    "gamer2_score"      => "苗机 1M 9.30pts",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "1.875",

    "gamer3_name"       => "xxoxx",
    "gamer3_space"      => "https://space.bilibili.com/44575054/",
    "gamer3_score"      => "魔机 3M 7.70pts",
    "gamer3_jf"         => "0",
    "gamer3_odds"       => "2.5",

    "speaker1_name"     => "YukariM",
    "speaker1_space"    => "https://space.bilibili.com/49892452/",

    "speaker2_name"     => "Sky_W",
    "speaker2_space"    => "https://space.bilibili.com/199620410/",

    "speaker3_name"     => "WD",
    "speaker3_space"    => "https://space.bilibili.com/23058964/",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_08"] = array(
    "game_number"       => "th06_NB",
    "game_name"         => "红魔乡Lunatic避弹",
    "game_video"        => "https://www.bilibili.com/video/BV1MM4y1N7iL",
    "game_time"         => "7.24-Sat 20:00",

    "gamer1_name"       => "山舞银蛇",
    "gamer1_space"      => "https://space.bilibili.com/132935710/",
    "gamer1_score"      => "梦B 7M 3.00pts",
    "gamer1_jf"         => "2",
    "gamer1_odds"       => "1.21493",

    "gamer2_name"       => "DXN",
    "gamer2_space"      => "https://space.bilibili.com/12482431/",
    "gamer2_score"      => "梦B 8M 2.00pts",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "344.81",

    "gamer3_name"       => "",
    "gamer3_space"      => "",
    "gamer3_score"      => "",
    "gamer3_jf"         => "",
    "gamer3_odds"       => "5.74683",

    "speaker1_name"     => "nkn",
    "speaker1_space"    => "https://space.bilibili.com/10753448/",

    "speaker2_name"     => "蓬莱山辉夜",
    "speaker2_space"    => "https://space.bilibili.com/7876940/",

    "speaker3_name"     => "YukariM",
    "speaker3_space"    => "https://space.bilibili.com/49892452/",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_09"] = array(
    "game_number"       => "th10_EX",
    "game_name"         => "风神录Extra避弹",
    "game_video"        => "https://www.bilibili.com/video/BV1KU4y1H7GC",
    "game_time"         => "7.25-Sun 15:00",

    "gamer1_name"       => "Sos",
    "gamer1_space"      => "https://space.bilibili.com/42907762/",
    "gamer1_score"      => "梦B 3M 7.00pts",
    "gamer1_jf"         => "0",
    "gamer1_odds"       => "1.13",

    "gamer2_name"       => "EJP",
    "gamer2_space"      => "https://space.bilibili.com/32700551/",
    "gamer2_score"      => "梦C 1M 10.00pts",
    "gamer2_jf"         => "1.5",
    "gamer2_odds"       => "11.3",

    "gamer3_name"       => "Helen",
    "gamer3_space"      => "https://space.bilibili.com/811068/",
    "gamer3_score"      => "梦B NN 10.00pts",
    "gamer3_jf"         => "1.5",
    "gamer3_odds"       => "37.6667",

    "speaker1_name"     => "折翼的天子",
    "speaker1_space"    => "https://space.bilibili.com/6702969/",

    "speaker2_name"     => "天眼通",
    "speaker2_space"    => "https://space.bilibili.com/935610/",

    "speaker3_name"     => "哈斯塔",
    "speaker3_space"    => "https://space.bilibili.com/8989439/",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_10"] = array(
    "game_number"       => "th101NB",
    "game_name"         => "风神录Lunatic避弹（第一场）",
    "game_video"        => "https://www.bilibili.com/video/BV1gv411K7C6",
    "game_time"         => "7.31-Sat 21:30",

    "gamer1_name"       => "LWR",
    "gamer1_space"      => "https://space.bilibili.com/438361247/",
    "gamer1_score"      => "魔C 4M 6.29pts",
    "gamer1_jf"         => "2",
    "gamer1_odds"       => "6.66",

    "gamer2_name"       => "Aisaka",
    "gamer2_space"      => "https://space.bilibili.com/286641286/",
    "gamer2_score"      => "梦B 6M 4.00pts",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "3.02988",

    "gamer3_name"       => "kdx",
    "gamer3_space"      => "https://space.bilibili.com/11359251/",
    "gamer3_score"      => "梦B 1M 9.00pts",
    "gamer3_jf"         => "3",
    "gamer3_odds"       => "1.9238",

    "speaker1_name"     => "nkn",
    "speaker1_space"    => "https://space.bilibili.com/10753448/",

    "speaker2_name"     => "CZW",
    "speaker2_space"    => "https://space.bilibili.com/4861197/",

    "speaker3_name"     => "冥土の灵",
    "speaker3_space"    => "https://space.bilibili.com/179380953/",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_11"] = array(
    "game_number"       => "th101NM",
    "game_name"         => "风神录Lunatic混关（第一场）",
    "game_video"        => "https://www.bilibili.com/video/BV1Ab4y1z7GH",
    "game_time"         => "8.01-Sun 15:00",

    "gamer1_name"       => "",
    "gamer1_space"      => "",
    "gamer1_score"      => "",
    "gamer1_jf"         => "",
    "gamer1_odds"       => "inf",

    "gamer2_name"       => "落鲸",
    "gamer2_space"      => "https://space.bilibili.com/313794293/",
    "gamer2_score"      => "3-2.20",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "1",

    "gamer3_name"       => "影儿",
    "gamer3_space"      => "https://space.bilibili.com/32202876/",
    "gamer3_score"      => "8-3.75",
    "gamer3_jf"         => "2",
    "gamer3_odds"       => "inf",

    "speaker1_name"     => "WD",
    "speaker1_space"    => "https://space.bilibili.com/23058964/",

    "speaker2_name"     => "THN",
    "speaker2_space"    => "https://space.bilibili.com/32680359/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_12"] = array(
    "game_number"       => "th07_NM",
    "game_name"         => "妖妖梦Lunatic混关",
    "game_video"        => "https://www.bilibili.com/video/BV1Tg411E7mz",
    "game_time"         => "8.01-Sun 20:00",

    "gamer1_name"       => "EnK",
    "gamer1_space"      => "https://space.bilibili.com/4275270/",
    "gamer1_score"      => "2-2",
    "gamer1_jf"         => "0",
    "gamer1_odds"       => "2.9502",

    "gamer2_name"       => "",
    "gamer2_space"      => "",
    "gamer2_score"      => "",
    "gamer2_jf"         => "",
    "gamer2_odds"       => "inf",

    "gamer3_name"       => "LKY",
    "gamer3_space"      => "https://space.bilibili.com/305575617/",
    "gamer3_score"      => "7-2",
    "gamer3_jf"         => "1",
    "gamer3_odds"       => "1.51277",

    "speaker1_name"     => "城南观云",
    "speaker1_space"    => "https://space.bilibili.com/68552095/",

    "speaker2_name"     => "吾亦醉汝何",
    "speaker2_space"    => "https://space.bilibili.com/123401909/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_13"] = array(
    "game_number"       => "th11_EX",
    "game_name"         => "地灵殿Extra避弹",
    "game_video"        => "https://www.bilibili.com/video/BV11g41177pz",
    "game_time"         => "8.01-Sun 21:30",

    "gamer1_name"       => "愉悦王",
    "gamer1_space"      => "https://space.bilibili.com/4816622/",
    "gamer1_score"      => "梦A 1M 9.00pts",
    "gamer1_jf"         => "1",
    "gamer1_odds"       => "377.4",

    "gamer2_name"       => "糖醋西瓜包",
    "gamer2_space"      => "https://space.bilibili.com/7939351/",
    "gamer2_score"      => "DNF",
    "gamer2_jf"         => "0",
    "gamer2_odds"       => "25.16",

    "gamer3_name"       => "秋兔珠乌",
    "gamer3_space"      => "https://space.bilibili.com/40805048/",
    "gamer3_score"      => "梦B NN 10.81pts",
    "gamer3_jf"         => "2",
    "gamer3_odds"       => "1.04427",

    "speaker1_name"     => "Azure_Mirage",
    "speaker1_space"    => "https://space.bilibili.com/75521311",

    "speaker2_name"     => "mianaya",
    "speaker2_space"    => "https://space.bilibili.com/87462796/",

    "speaker3_name"     => "Aisaka",
    "speaker3_space"    => "https://space.bilibili.com/286641286/",

    "speaker4_name"     => "H3PO4⑨",
    "speaker4_space"    => "https://space.bilibili.com/16076021/",
);

$game["game_14"] = array(
    "game_number"       => "th102NB",
    "game_name"         => "风神录Lunatic避弹（第二场）",
    "game_video"        => "https://www.bilibili.com/video/BV1zU4y1J7Hn",
    "game_time"         => "8.07-Sat 15:00",

    "gamer1_name"       => "小小青蛙不惧风雨",
    "gamer1_space"      => "https://space.bilibili.com/27191380/",
    "gamer1_score"      => "梦B 3M 7.00pts",
    "gamer1_jf"         => "2",
    "gamer1_odds"       => "inf",

    "gamer2_name"       => "nkn",
    "gamer2_space"      => "https://space.bilibili.com/10753448/",
    "gamer2_score"      => "梦B 2M 8.00pts",
    "gamer2_jf"         => "3",
    "gamer2_odds"       => "1.51913",

    "gamer3_name"       => "zhzhzh",
    "gamer3_space"      => "https://space.bilibili.com/25283739/",
    "gamer3_score"      => "梦C 1M 9.53pts norep",
    "gamer3_jf"         => "1",
    "gamer3_odds"       => "2.92632",

    "speaker1_name"     => "LWR",
    "speaker1_space"    => "https://space.bilibili.com/438361247/",

    "speaker2_name"     => "Aisaka",
    "speaker2_space"    => "https://space.bilibili.com/286641286/",

    "speaker3_name"     => "kdx",
    "speaker3_space"    => "https://space.bilibili.com/11359251/",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_15"] = array(
    "game_number"       => "th06_EX",
    "game_name"         => "红魔乡Extra避弹",
    "game_video"        => "https://www.bilibili.com/video/BV1qf4y1V7q6",
    "game_time"         => "8.07-Sat 20:00",

    "gamer1_name"       => "SNY",
    "gamer1_space"      => "https://space.bilibili.com/234308182/",
    "gamer1_score"      => "梦B 3M 7.00pts",
    "gamer1_jf"         => "0",
    "gamer1_odds"       => "5.93277",

    "gamer2_name"       => "622",
    "gamer2_space"      => "https://space.bilibili.com/3661558/",
    "gamer2_score"      => "梦A 1M 9.58pts",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "1.20273",

    "gamer3_name"       => "",
    "gamer3_space"      => "",
    "gamer3_score"      => "",
    "gamer3_jf"         => "",
    "gamer3_odds"       => "inf",

    "speaker1_name"     => "折翼的天子",
    "speaker1_space"    => "https://space.bilibili.com/6702969/",

    "speaker2_name"     => "秋月まりな",
    "speaker2_space"    => "https://space.bilibili.com/86198011/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_16"] = array(
    "game_number"       => "th07_PH",
    "game_name"         => "妖妖梦Phantasm避弹",
    "game_video"        => "https://www.bilibili.com/video/BV1364y1z7Vb",
    "game_time"         => "8.08-Sun 20:00",

    "gamer1_name"       => "SAR",
    "gamer1_space"      => "https://space.bilibili.com/2323737/",
    "gamer1_score"      => "魔B NNN 10.91pts",
    "gamer1_jf"         => "2",
    "gamer1_odds"       => "inf",

    "gamer2_name"       => "娜露缇斯",
    "gamer2_space"      => "https://space.bilibili.com/5587598/",
    "gamer2_score"      => "梦A NNN 10.81pts",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "inf",

    "gamer3_name"       => "闲",
    "gamer3_space"      => "https://space.bilibili.com/12007285/",
    "gamer3_score"      => "魔B 1M 9.91pts",
    "gamer3_jf"         => "0",
    "gamer3_odds"       => "1",

    "speaker1_name"     => "莲子布丁",
    "speaker1_space"    => "https://space.bilibili.com/49916399/",

    "speaker2_name"     => "H3PO4⑨",
    "speaker2_space"    => "https://space.bilibili.com/16076021/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_17"] = array(
    "game_number"       => "th08_NM",
    "game_name"         => "永夜抄Lunatic混关",
    "game_video"        => "https://www.bilibili.com/video/BV1rP4y1W7nT",
    "game_time"         => "8.14-Sat 20:00",

    "gamer1_name"       => "紧闭的心之瞳",
    "gamer1_space"      => "https://space.bilibili.com/69027317/",
    "gamer1_score"      => "8-0",
    "gamer1_jf"         => "0",
    "gamer1_odds"       => "inf",

    "gamer2_name"       => "KST",
    "gamer2_space"      => "https://space.bilibili.com/34678049/",
    "gamer2_score"      => "8-3",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "1.21739",

    "gamer3_name"       => "",
    "gamer3_space"      => "",
    "gamer3_score"      => "",
    "gamer3_jf"         => "",
    "gamer3_odds"       => "5.6",

    "speaker1_name"     => "月之头脑_Eirin",
    "speaker1_space"    => "https://space.bilibili.com/395922749/",

    "speaker2_name"     => "折翼的天子",
    "speaker2_space"    => "https://space.bilibili.com/6702969/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_18"] = array(
    "game_number"       => "th102NM",
    "game_name"         => "风神录Lunatic混关（第二场）",
    "game_video"        => "https://www.bilibili.com/video/BV1RM4y157yd",
    "game_time"         => "8.14-Sat 22:00",

    "gamer1_name"       => "Xincl",
    "gamer1_space"      => "",
    "gamer1_score"      => "7-3.95",
    "gamer1_jf"         => "1",
    "gamer1_odds"       => "inf",

    "gamer2_name"       => "WD",
    "gamer2_space"      => "https://space.bilibili.com/23058964/",
    "gamer2_score"      => "6-3.00",
    "gamer2_jf"         => "0",
    "gamer2_odds"       => "1.93661",

    "gamer3_name"       => "lqybzx",
    "gamer3_space"      => "https://space.bilibili.com/925895/",
    "gamer3_score"      => "8-3.95",
    "gamer3_jf"         => "2",
    "gamer3_odds"       => "2.06768",

    "speaker1_name"     => "影月",
    "speaker1_space"    => "https://space.bilibili.com/3182660/",

    "speaker2_name"     => "Sakuya",
    "speaker2_space"    => "https://space.bilibili.com/12362937/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_19"] = array(
    "game_number"       => "th15_NM",
    "game_name"         => "绀珠传Lunatic混关",
    "game_video"        => "https://www.bilibili.com/video/BV1Zq4y1n7BS",
    "game_time"         => "8.15-Sun 09:30",

    "gamer1_name"       => "ZL",
    "gamer1_space"      => "https://space.bilibili.com/288564315/",
    "gamer1_score"      => "8-0-9e",
    "gamer1_jf"         => "2",
    "gamer1_odds"       => "52.694",

    "gamer2_name"       => "Mako",
    "gamer2_space"      => "https://space.bilibili.com/17805544/",
    "gamer2_score"      => "8-0-6e",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "1.01934",

    "gamer3_name"       => "Toby",
    "gamer3_space"      => "https://space.bilibili.com/433870841/",
    "gamer3_score"      => "7-3",
    "gamer3_jf"         => "0",
    "gamer3_odds"       => "inf",

    "speaker1_name"     => "Sky_W",
    "speaker1_space"    => "https://space.bilibili.com/199620410/",

    "speaker2_name"     => "kiri",
    "speaker2_space"    => "https://space.bilibili.com/43667650",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_20"] = array(
    "game_number"       => "th18_NM",
    "game_name"         => "虹龙洞Lunatic混关",
    "game_video"        => "https://www.bilibili.com/video/BV1RQ4y127yi",
    "game_time"         => "8.15-Sun 20:00",

    "gamer1_name"       => "只能通E的沙包",
    "gamer1_space"      => "https://space.bilibili.com/7281712/",
    "gamer1_score"      => "DNF",
    "gamer1_jf"         => "0",
    "gamer1_odds"       => "3.02",

    "gamer2_name"       => "Ting",
    "gamer2_space"      => "https://space.bilibili.com/277638813/",
    "gamer2_score"      => "0-0",
    "gamer2_jf"         => "1",
    "gamer2_odds"       => "151",

    "gamer3_name"       => "光子聚变",
    "gamer3_space"      => "https://space.bilibili.com/179007574/",
    "gamer3_score"      => "7-7",
    "gamer3_jf"         => "2",
    "gamer3_odds"       => "1.51",

    "speaker1_name"     => "城南观云",
    "speaker1_space"    => "https://space.bilibili.com/68552095/",

    "speaker2_name"     => "xxoxx",
    "speaker2_space"    => "https://space.bilibili.com/44575054/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_21"] = array(
    "game_number"       => "th14_EX",
    "game_name"         => "辉针城Extra避弹",
    "game_video"        => "https://www.bilibili.com/video/BV1oq4y1Q7Yk",
    "game_time"         => "8.15-Sun 22:00",

    "gamer1_name"       => "威光",
    "gamer1_space"      => "https://space.bilibili.com/773195/",
    "gamer1_score"      => "咲B 3miss & 梦B 2miss 9.00pts",
    "gamer1_jf"         => "0.5",
    "gamer1_odds"       => "1.64",

    "gamer2_name"       => "夏时雨",
    "gamer2_space"      => "https://space.bilibili.com/4351960/",
    "gamer2_score"      => "梦B 1miss 10.00pts",
    "gamer2_jf"         => "2",
    "gamer2_odds"       => "82",

    "gamer3_name"       => "电表",
    "gamer3_space"      => "https://space.bilibili.com/552341337/",
    "gamer3_score"      => "魔A 3miss 9.00pts",
    "gamer3_jf"         => "0.5",
    "gamer3_odds"       => "2.64516",

    "speaker1_name"     => "LWR",
    "speaker1_space"    => "https://space.bilibili.com/438361247/",

    "speaker2_name"     => "净琉璃世界",
    "speaker2_space"    => "https://space.bilibili.com/174107918/",

    "speaker3_name"     => "H3PO4⑨",
    "speaker3_space"    => "https://space.bilibili.com/16076021/",

    "speaker4_name"     => "哈斯塔",
    "speaker4_space"    => "https://space.bilibili.com/8989439/",
);

$game["game_22"] = array(
    "game_number"       => "th12_EX",
    "game_name"         => "星莲船Extra避弹",
    "game_video"        => "https://www.bilibili.com/video/BV16f4y1P7hy",
    "game_time"         => "8.21-Sat 15:00",

    "gamer1_name"       => "城南观云",
    "gamer1_space"      => "https://space.bilibili.com/68552095/",
    "gamer1_score"      => "梦A NF 2miss 10.00pts",
    "gamer1_jf"         => "1.5",
    "gamer1_odds"       => "1",

    "gamer2_name"       => "莲子布丁",
    "gamer2_space"      => "https://space.bilibili.com/49916399/",
    "gamer2_score"      => "魔B 3miss 7.58pts",
    "gamer2_jf"         => "0",
    "gamer2_odds"       => "inf",

    "gamer3_name"       => "Sakuya",
    "gamer3_space"      => "https://space.bilibili.com/12362937/",
    "gamer3_score"      => "苗B NNNU 10.00pts",
    "gamer3_jf"         => "1.5",
    "gamer3_odds"       => "inf",

    "speaker1_name"     => "WD",
    "speaker1_space"    => "https://space.bilibili.com/23058964/",

    "speaker2_name"     => "xxoxx",
    "speaker2_space"    => "https://space.bilibili.com/44575054/",

    "speaker3_name"     => "",
    "speaker3_space"    => "",

    "speaker4_name"     => "",
    "speaker4_space"    => "",
);

$game["game_23"] = array(
    "game_number"       => "th13_NB",
    "game_name"         => "神灵庙Lunatic避弹",
    "game_video"        => "https://www.bilibili.com/video/BV1wQ4y117S8",
    "game_time"         => "8.22-Sun 21:00",

    "gamer1_name"       => "園田琴梨",
    "gamer1_space"      => "https://space.bilibili.com/10039817/",
    "gamer1_score"      => "梦机 NNN & 苗机 1miss 10.47pts",
    "gamer1_jf"         => "3",
    "gamer1_odds"       => "5.76656",

    "gamer2_name"       => "Asahi",
    "gamer2_space"      => "https://space.bilibili.com/5899721/",
    "gamer2_score"      => "魔机 1miss 10.00pts",
    "gamer2_jf"         => "2",
    "gamer2_odds"       => "2.46801",

    "gamer3_name"       => "ZJM",
    "gamer3_space"      => "https://space.bilibili.com/33829126/",
    "gamer3_score"      => "梦机 1miss 9.00pts",
    "gamer3_jf"         => "1",
    "gamer3_odds"       => "2.37303",

    "speaker1_name"     => "LWR",
    "speaker1_space"    => "https://space.bilibili.com/438361247/",

    "speaker2_name"     => "威光",
    "speaker2_space"    => "https://space.bilibili.com/773195/",

    "speaker3_name"     => "YukariM",
    "speaker3_space"    => "https://space.bilibili.com/49892452/",

    "speaker4_name"     => "实况主本人",
    "speaker4_space"    => "https://space.bilibili.com/60109218/",
);

?>

