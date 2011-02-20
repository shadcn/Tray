/* $Id$ */
(function ($) {
  Drupal.behaviors.tray = {
    attach: function() {
      
        //fix for right items block position
        $('li.tray-item-position-right').each(function() {
          var handle = $(this).find('.tray-item-handle');
          var p = handle.offset();
          $(this).find('.tray-item-block').css({
            right : parseInt($('body').width()) - (p.left + parseInt(handle.parent('li').width()) + 1)
          }); 
        });
      
        //on click event
        $('.tray-item-handle').click(function(e){
          e.preventDefault();
          var $item = $(this);
          //check if the item is ajax processed and fire the call if the event is open
          if($item.parent('li').hasClass('tray-item-ajax-processed') && !$item.parent('li').hasClass('tray-item-active')) {
            //add ajax classes
            $item.parent('li').addClass('tray-item-ajax-processing');
            var bid = parseInt($(this).parent('li').attr('id').replace('tray-item-', ''));
            $.post('?q=tray/content/' + bid, { }, function(j) {
              $('#tray-item-' + bid).find('.tray-item-content').html(j.content);
              //remove ajax classes
              $item.parent('li').removeClass('tray-item-ajax-processing');
              showItem($item);
            });
          } else {
            showItem($item);
          }
        });
        
        //minimize tray item
        $('.tray-item-minimize').click(function(e){
          e.preventDefault();
          minimizeActiveItem();
        });
        
        //close tray item
        $('.tray-item-close').click(function(e){
          e.preventDefault();
          closeActiveItem();
        });  
      }
  }
  
  function showItem($item) {
    $('.tray-item-active').removeClass('tray-item-active');
    $item.parent('li').toggleClass('tray-item-active');
    $('li.tray-item').each(function(){
      if(!$(this).hasClass('tray-item-active')){
          $(this).find('.tray-item-block').hide();
      }
    });
    $item.next('.tray-item-block').slideToggle(100);
  }
  
  function minimizeActiveItem() {
    $('.tray-item-active').find('.tray-item-block').slideToggle(100);
    $('.tray-item-active').removeClass('tray-item-active');
  }
  
  function closeActiveItem() {
    $('.tray-item-active').find('.tray-item-block').fadeOut(250);
    $('.tray-item-active').removeClass('tray-item-active');
  }
  
})(jQuery);  