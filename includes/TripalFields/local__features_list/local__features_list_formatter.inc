<?php
/**
 * @class
 * Purpose:
 *
 * Display:
 * Configuration:
 */
class local__features_list_formatter extends ChadoFieldFormatter {

  // The default label for this field.
  public static $default_label = 'Features List';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = array('local__features_list');

  // The list of default settings for this formatter.
  public static $default_settings = array(
    'setting1' => 'default_value',
  );

   /**
    * @see ChadoFieldFormatter::settingsForm()
    *
    **/

  public function settingsForm($view_mode, $form, &$form_state) {

  }

    /**
    * @see ChadoFieldFormatter::View()
    *
    **/

  public function view(&$element, $entity_type, $entity, $langcode, $items, $display) {
    // Get the settings
    $settings = $display['settings'];
    $feature_names = $items[0]['value'];
    $element[0] =
      [
        "#type"=>"markup",
        "#markup"=>theme('table',[
        "header"=>['feature name'],
        "rows"=>$feature_names
        ])
      ];
  }

    /**
    * @see ChadoFieldFormatter::settingsSummary()
    *
    **/

  public function settingsSummary($view_mode) {
    return '';
  }

}
