<?php defined("ITHP_PAGE") or die(); ?>
<?php require "activity_data.php"; ?>
<div class="container">
    <div class="row">
        <div class="col-sm-2">
            <ul class="ithp-sidebar">
                <li><?php href("activity_1", $lang); ?></li>
                <li><?php href("activity_2", $lang); ?></li>
                <li class="active"><?php href("activity_3", $lang); ?></li>
                <li><?php href("activity_4", $lang); ?></li>
            </ul>
        </div>
        <div class="col-sm-10 ithp-page-content-text">
            <h1>芹菜统计</h1>
                <hr>
                <h2>芹菜规则</h2>
                    <p>请阅读<a href="https://github.com/AkitsukiM/CTSL-celery/blob/master/README.md" target="_blank">这里</a>（时不时需要科学上网）</p>
                    <p>芹菜系统：链接</p>
                <hr>
                <h2>赔率报表</h2>
                    <table border="1"><tbody>
                        <tr>
                            <td style="width:100px"><body>编号</body></td>
                            <td style="width:200px"><body>项目</body></td>
                            <td style="width:200px"><body>Team North</body></td>
                            <td style="width:200px"><body>Team East</body></td>
                            <td style="width:200px"><body>Team South</body></td>
                            <td style="width:150px"><body>Team North 赔率</body></td>
                            <td style="width:150px"><body>Team East 赔率</body></td>
                            <td style="width:150px"><body>Team South 赔率</body></td>
                        </tr>
                        <?php foreach ($game as $k=>$q){ ?>
                        <tr>
                            <td><?php echo $q["game_number"] ?></td>
                            <td><?php echo $q["game_name"] ?></td>
                            <td><?php echo_name_and_space($q["gamer1_name"], $q["gamer1_space"]) ?></td>
                            <td><?php echo_name_and_space($q["gamer2_name"], $q["gamer2_space"]) ?></td>
                            <td><?php echo_name_and_space($q["gamer3_name"], $q["gamer3_space"]) ?></td>
                            <td><?php echo $q["gamer1_odds"] ?></td>
                            <td><?php echo $q["gamer2_odds"] ?></td>
                            <td><?php echo $q["gamer3_odds"] ?></td>
                        </tr>
                        <?php } ?>
                    </tbody></table>
                    <br>
                    <p>最近一次更新：2021年8月22日24:00</p>
                <hr>
                <h2>当前资金力状况</h2>
                    <table border="1"><tbody>
                        <!-- from THBWiki -->
                        <!-- <tr><th colspan="2">基本信息</th></tr> -->
                        <tr>
                            <td style="width:150px"><body>QQ号最后四位</body></td>
                            <td style="width:150px"><body>当前资金力</body></td>
                        </tr>
<tr><td><body>	8849	</body></td><td><body>	0	</body></td></tr>
<tr><td><body>	0409	</body></td><td><body>	144163	</body></td></tr>
<tr><td><body>	4718	</body></td><td><body>	40166	</body></td></tr>
<tr><td><body>	4843	</body></td><td><body>	26164	</body></td></tr>
<tr><td><body>	5057	</body></td><td><body>	0	</body></td></tr>
<tr><td><body>	0030	</body></td><td><body>	24000	</body></td></tr>
<tr><td><body>	3741	</body></td><td><body>	38995	</body></td></tr>
<tr><td><body>	3142	</body></td><td><body>	21536	</body></td></tr>
<tr><td><body>	4601	</body></td><td><body>	27647	</body></td></tr>
<tr><td><body>	3001	</body></td><td><body>	0	</body></td></tr>
<tr><td><body>	0189	</body></td><td><body>	27625	</body></td></tr>
<tr><td><body>	5643	</body></td><td><body>	16444	</body></td></tr>
<tr><td><body>	4660	</body></td><td><body>	28255	</body></td></tr>
<tr><td><body>	9679	</body></td><td><body>	25373	</body></td></tr>
<tr><td><body>	1454	</body></td><td><body>	25713	</body></td></tr>
<tr><td><body>	4212	</body></td><td><body>	28734	</body></td></tr>
<tr><td><body>	9975	</body></td><td><body>	22428	</body></td></tr>
<tr><td><body>	2212	</body></td><td><body>	80625	</body></td></tr>
<tr><td><body>	8459	</body></td><td><body>	24690	</body></td></tr>
<tr><td><body>	6233	</body></td><td><body>	0	</body></td></tr>
<tr><td><body>	1462	</body></td><td><body>	0	</body></td></tr>
<tr><td><body>	7349	</body></td><td><body>	5074	</body></td></tr>
<tr><td><body>	6665	</body></td><td><body>	25476	</body></td></tr>
<tr><td><body>	6296	</body></td><td><body>	38328	</body></td></tr>
<tr><td><body>	5020	</body></td><td><body>	6215	</body></td></tr>
<tr><td><body>	2692	</body></td><td><body>	10253	</body></td></tr>
<tr><td><body>	6529	</body></td><td><body>	0	</body></td></tr>
<tr><td><body>	9196	</body></td><td><body>	17488	</body></td></tr>
<tr><td><body>	2296	</body></td><td><body>	25672	</body></td></tr>
<tr><td><body>	4742	</body></td><td><body>	30587	</body></td></tr>
<tr><td><body>	6656	</body></td><td><body>	10314	</body></td></tr>
                    </tbody></table>
                    <br>
                    <p>最近一次更新：2021年8月22日24:00</p>
        </div>
    </div>
</div>

