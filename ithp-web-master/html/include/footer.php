<?php defined("ITHP_PAGE") or die(); ?>
<footer class="footer navbar-fixed-bottom ithp-footer">
  <hr>
  <div class="container">
    <div class="text-center col-md-6 col-md-offset-3">
      <p>
      <?php echo htmlspecialchars($strings["links"][$lang]); ?>
      <?php foreach ($links as $k=>$link) { ?>
      &middot;
      <a href="<?php echo $link["target"]; ?>" target="_blank"><?php echo $link[$lang]; ?></a>
      <?php } ?>
      </p>
      <p>Copyright &copy; 2018-2021 &middot; Institute of Touhou Project &middot; All Rights Reserved &middot; <a href="#">Top</a></p>
      <p><br></p>
    </div>
  </div>
</footer>

