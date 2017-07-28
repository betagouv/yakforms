<?php phpinfo(); ?>

<?php
echo "current mb_internal_encoding: ".mb_internal_encoding()."<br />";
echo "changing mb_internal_encoding to UTF-8<br />";
mb_internal_encoding("UTF-8");
echo "new mb_internal_encoding: ".mb_internal_encoding()."<br />";

echo "current mb_regex_encoding: ".mb_regex_encoding()."<br />";
echo "changing mb_regex_encoding to UTF-8<br />";
mb_regex_encoding('UTF-8');
echo "new mb_regex_encoding: ".mb_regex_encoding()."<br />";
?>