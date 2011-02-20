<?php
//$Id$

/**
 * @file
 * Contains theme functions for the Tray
 */

/**
 * Theme function for the tray display
 */
function theme_tray_display() {
  
  //Update the 'blocks' DB table with the blocks currently exported by modules.
  _block_rehash();
  
  //get a list of blocks in the tray region
  $blocks = block_list('tray');
  
  $output = '<div id="tray-tray">';
  
  $output .= '<ul class="tray-main">';
  foreach($blocks as $block) {
    if ($block->module && ($block->delta || $block->delta === 0)) {
      $block_name = $block->module .'_'. $block->delta;
    }
    
    $options = array(
      'type' => variable_get('tray_display_type_'.$block_name , 'handle'),
      'ajax' => variable_get('tray_ajax_enabled_'.$block_name , 0),
      'position' => variable_get('tray_display_position_'.$block_name , 'left'),
    );
    
    $output .= ($options['type'] == 'full') ? theme('tray_block_full', array('block' => $block, 'options' => $options)) : theme('tray_block_handle', array('block' => $block, 'options' => $options));
  }
  $output .= '</ul>';
  $output .='</div>'; //end tray-tray
  
  return $output;

}

/**
 * Theme function for blocks inside the tray - display type handle
 */
function theme_tray_block_handle($data) {
  $block = $data['block'];
  $options = $data['options'];
  
  $classes = array();
  if($options['ajax']) {
    $classes[] = 'tray-item-ajax-processed';
  }
  
  $classes[] = 'tray-item-position-' . $options['position'];
  
  $output  = '<li class="tray-item ' . implode(' ', $classes) . '" id="tray-item-' . $block->bid . '">';
  $output .= '<a href="#" title="' . $block->subject . '" class="tray-item-handle">' . $block->subject . '</a>';
  $output .= '<div class="tray-item-block">';
  $output .= '<div class="tray-item-controls">';
  $output .= '<span>' . $block->subject . '</span>';
  $output .= '<ul>';
  $output .= '<li><a href="#" class="tray-item-minimize" title="' . t('Click here to minimize this item') . '">' . t('Minimize') . '</a></li>';
  $output .= '<li><a href="#" class="tray-item-close" title="' . t('Click here to close this item') . '">' . t('Close') . '</a></li>';
  $output .= '</ul>';
  $output .= '</div>';
  $output .= '<div class="tray-item-content">';
  
  //add the content if the block is not ajaxified
  if(!$options['ajax']) {
    $renderable_block=  _block_get_renderable_array(array($block));
    //we don't need the block title in the content so let's unset this here
    $renderable_block[0]['#block']->subject = '';
    $output .= drupal_render($renderable_block);
  }
  
  $output .= '</div>';
  $output .= '</div>';
  $output .= '</li>';
  
  return $output;
}

/**
 * Theme function for blocks inside the tray - display type full
 */
function theme_tray_block_full($data){
  $block = $data['block'];
  $options = $data['options'];
  
  $classes = array();
  $classes[] = 'tray-item-position-' . $options['position'];
  
  $output  = '<li class="tray-item tray-item-full ' . implode(' ', $classes) . '" id="tray-item-' . $block->bid . '">';
  
  $renderable_block=  _block_get_renderable_array(array($block));
  //we don't need the block title in the content so let's unset this here
  $renderable_block[0]['#block']->subject = '';
  $output .= drupal_render($renderable_block);
  
  $output .= '</li>';
  
  return $output;
}
