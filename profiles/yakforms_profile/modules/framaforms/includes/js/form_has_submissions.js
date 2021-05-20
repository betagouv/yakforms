let popupHasAppeared = false;

function warnUserFormFields () {
  if(!popupHasAppeared){
    alert(Drupal.t("You form already has submissions. You might loose your data by editing or removing form fields."));
    popupHasAppeared = true
  }
}

function warnUserFormTitle () {
  if(!popupHasAppeared){
    alert(Drupal.t("Changing this form's title will also change its URL. If you have already transmitted a link to your users, it will return an error."));
    popupHasAppeared = true
  }
}

(function($){
  $(window).on('load', function () {
    popupHasAppeared = false;
    $('.form-builder-wrapper, .form-builder-element, .form-builder-processed, .ui-draggable, .form-builder-links > a').on('click', warnUserFormFields);
    $('#edit-title').on('click', warnUserFormTitle);
  });
})(jQuery);
