<?php defined("ITHP_PAGE") or die(); ?>
<nav class="navbar navbar-default ithp-navbar">
  <div class="container"> 
    <!-- Brand and toggle get grouped for better mobile display -->
    <div class="navbar-header">
      <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#defaultNavbar1"><span class="sr-only">Toggle navigation</span><span class="icon-bar"></span><span class="icon-bar"></span><span class="icon-bar"></span></button>
      <div style="padding-top: 7px;">
        <?php href("home", $lang, "<img src=\"images/IThP-logo-horizontal-1200x500.png\" width=200 height=50>"); ?>
      </div>
    </div>
    <!-- Collect the nav links, forms, and other content for toggling -->
    <div class="collapse navbar-collapse" id="defaultNavbar1">
      <ul class="nav navbar-nav">
        <li class="dropdown"><a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"><?php echo $nav_folders["touhou"][$lang]; ?><span class="caret"></span></a>
          <ul class="dropdown-menu" role="menu">
            <li><?php href("touhou_gensokyo", $lang); ?></li>
            <li><?php href("touhou_zun", $lang); ?></li>
          </ul>
        </li>
        <li class="dropdown"><a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"><?php echo $nav_folders["intro"][$lang]; ?><span class="caret"></span></a>
          <ul class="dropdown-menu" role="menu">
            <li><?php href("intro_organization", $lang); ?></li>
            <li><?php href("intro_events", $lang); ?></li>
          </ul>
        </li>
        <li class="dropdown"><a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"><?php echo $nav_folders["activity"][$lang]; ?><span class="caret"></span></a>
          <ul class="dropdown-menu" role="menu">
            <li><?php href("activity_1", $lang); ?></li>
            <li><?php href("activity_2", $lang); ?></li>
            <li><?php href("activity_3", $lang); ?></li>
            <li><?php href("activity_4", $lang); ?></li>
          </ul>
        </li>
      </ul>
      <ul class="nav navbar-nav navbar-right">
        <li class="dropdown"><a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"><?php echo $nav_folders["contact"][$lang]; ?><span class="caret"></span></a>
          <ul class="dropdown-menu" role="menu">
            <?php foreach ($contact as $k=>$link) { ?>
            <li><a href="<?php echo $link["target"]; ?>" target="_blank"><?php echo $link[$lang]; ?></a></li>
            <?php } ?>
          </ul>
        </li>
        <li class="dropdown"><a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"><?php echo $nav_folders["lang"][$lang]; ?><span class="caret"></span></a>
          <ul class="dropdown-menu" role="menu">
            <?php foreach ($langs as $l=>$lname) { ?>
            <li><?php href($page, $l, $lname); ?></li>
            <?php } ?>
          </ul>
        </li>
      </ul>
    </div>
    <!-- /.navbar-collapse --> 
  </div>
  <!-- /.container-fluid --> 
</nav>