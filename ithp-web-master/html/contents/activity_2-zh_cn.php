<?php defined("ITHP_PAGE") or die(); ?>
<?php require "activity_data.php"; ?>
<div class="container">
    <div class="row">
        <div class="col-sm-2">
            <ul class="ithp-sidebar">
                <li><?php href("activity_1", $lang); ?></li>
                <li class="active"><?php href("activity_2", $lang); ?></li>
                <li><?php href("activity_3", $lang); ?></li>
                <li><?php href("activity_4", $lang); ?></li>
            </ul>
        </div>
        <div class="col-sm-10 ithp-page-content-text">
            <h1>赛程赛况</h1>
                <hr>
                <a href="images/CTSL-schedule.png"><img src="images/CTSL-schedule.png" class="img-responsive center-block"></a>
                    <br>
                    <p>总积分：</p>
                    <p>北方队：21</p>
                    <p>东方队：24.5</p>
                    <p>南方队：25.5</p>
                <hr>
                    <?php foreach ($game as $k=>$q){ ?>
                    <p><div id="<?php echo $q['game_number'] ?>">===== ===== <?php echo_name_and_space($q["game_name"], $q["game_video"]) ?>（<?php echo $q["game_time"] ?>） ===== =====</div></p>
                    <p>北方队：
                        <?php echo_name_and_space($q["gamer1_name"], $q["gamer1_space"]) ?>
                        <?php echo_seprt($q["gamer1_score"]) ?><?php echo $q["gamer1_score"] ?>
                        <?php echo_seprt($q["gamer1_jf"]) ?><?php echo $q["gamer1_jf"] ?>
                    </p>
                    <p>东方队：
                        <?php echo_name_and_space($q["gamer2_name"], $q["gamer2_space"]) ?>
                        <?php echo_seprt($q["gamer2_score"]) ?><?php echo $q["gamer2_score"] ?>
                        <?php echo_seprt($q["gamer2_jf"]) ?><?php echo $q["gamer2_jf"] ?>
                    </p>
                    <p>南方队：
                        <?php echo_name_and_space($q["gamer3_name"], $q["gamer3_space"]) ?>
                        <?php echo_seprt($q["gamer3_score"]) ?><?php echo $q["gamer3_score"] ?>
                        <?php echo_seprt($q["gamer3_jf"]) ?><?php echo $q["gamer3_jf"] ?>
                    </p>
                    <p>解说：
                        <?php echo_name_and_space($q["speaker1_name"], $q["speaker1_space"]) ?>
                        <?php echo_comma($q["speaker2_name"]) ?><?php echo_name_and_space($q["speaker2_name"], $q["speaker2_space"]) ?>
                        <?php echo_comma($q["speaker3_name"]) ?><?php echo_name_and_space($q["speaker3_name"], $q["speaker3_space"]) ?>
                        <?php echo_comma($q["speaker4_name"]) ?><?php echo_name_and_space($q["speaker4_name"], $q["speaker4_space"]) ?>
                    </p>
                    <br>
                    <?php } ?>
        </div>
    </div>
</div>

