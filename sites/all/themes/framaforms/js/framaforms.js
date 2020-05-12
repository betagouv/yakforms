jQuery(function($){
  Drupal.node_edit_protection = {};
  var click = false; // Allow Submit/Edit button
  var edit = false; // Dirty form flag

  Drupal.behaviors.nodeEditProtection = {
    attach : function(context) {
      // If they leave an input field, assume they changed it.
      $(".page-node-webform :input").each(function() {
        $(this).blur(function() {
          edit = true;
        });
      });

      // Let all form submit buttons through
      $(".page-node-webform input[type='submit']").each(function() {
        $(this).addClass('node-edit-protection-processed');
        $(this).click(function() {
          click = true;
        });
      });

      // Catch all links and buttons EXCEPT for "#" links
      $("a, button, input[type='submit']:not(.node-edit-protection-processed)")
          .each(function() {
            $(this).click(function() {
              // return when a "#" link is clicked so as to skip the
              // window.onbeforeunload function
              if (edit && $(this).attr("href") != "#") {
                return 0;
              }
            });
          });
   

      // Handle backbutton, exit etc.
      window.onbeforeunload = function() {
        // Add CKEditor support
        if (typeof (CKEDITOR) != 'undefined' && typeof (CKEDITOR.instances) != 'undefined') {
          for ( var i in CKEDITOR.instances) {
            if (CKEDITOR.instances[i].checkDirty()) {
              edit = true;
              break;
            }
          }
        }
        if (edit && !click) {
          click = false;
          return (Drupal.t("By leaving this page, you will lose all unsaved work."));
        }
      }
    }
  };

  /* Get progress bar title and replace progress bar with the title of the current page 
  * for mobiles. 
  */
  if(window.screen.width < 768 || window.screen.height < 1024){
    // get current and last page numbers
    var currentPage = $(".webform-progressbar-page.current > .webform-progressbar-page-number").text(); 
    var lastPage = $(".webform-progressbar-page-number:last").text(); 
    var currentTitle = $(".webform-progressbar-page.current > .webform-progressbar-page-label").text(); 

    // Replace progress bar with textual element
    $(".webform-progressbar")
      .replaceWith("<h4>"+ currentTitle + ": " + currentPage + " / " + lastPage + "</h5>");
 }
}); 
