<?php
/**
 * @file
 * Contains all field specific code outside the classes.
 */

/**
 * Implements hook_bundle_fields_info().
 *
 * This hook tells Drupal/Tripal about your new field type. Make sure you've created the
 * field (handles basic storage of your data), widget (provides user UI to set data),
 * and formatter (describes display of data on Entity Page) classes. These should be
 * located in the following directory: [your module]/includes/TripalFields/[classname].inc
 * with one file per class. Your field name should be [cv name]__[cvterm name] and the
 * classes should be named [field name], [field_name]_widget, [field name]_formatter
 * for the field, widget and formatter respectively. MAKE SURE YOU'VE CLEARED THE CACHE
 * SINCE ADDING THESE FILES so Tripal magic can find them or the following will fail.
 *
 * @param $entity_type
 *   This should be 'TripalEntity' for all Tripal Content.
 * @param $bundle
 *   This object describes the Type of Tripal Entity (e.g. Organism or Gene) this hook is
 *   being called for. However, since this hook creates field types (by definition not
 *   tied to a specific Tripal Content Type (bundle)) and since a field type will only be
 *   created if it doesn't already exist, this parameter doesn't actually matter.
 *   NOTE: If you do need to determine the bundle in this hook, we suggest inspecting
 *   the data_table since the label can be changed by site administrators.
 *
 * @return
 *   An array of field definitions. Each field in this array will be created if it
 *   doesn't already exist. To trigger create of fields when developing call
 *   tripal_refresh_bundle_fields() for the specific bundle.
 */
function noahs_test_module_bundle_fields_info($entity_type, $bundle) {
  $fields = array();

  $my_data_table = 'organism';
  // Because we are expecting data housed in Chado we can use the 'data_table'
  // property of the bundle to determine if this bundle is really the one
  // we want the field to be associated with.
  if (isset($bundle->data_table) AND ($bundle->data_table == $my_data_table)) {
    // First add my term.
    tripal_insert_cvterm(array(
      'id' => 'local:features_list',
      'name' => 'features_list',
      'cv_name' => 'local',
      'definition' => 'Displays a list of features. (this is test)',
    ));

    // Then describe the field defined by that term.
    $field_name = 'local__features_list';
    $field_type = 'local__features_list';
    $fields[$field_name] = array(
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => 1,
      'locked' => FALSE,
      'storage' => array(
        'type' => 'field_chado_storage',
      ),
    );
  }

  if (isset($bundle->data_table) AND ($bundle->data_table == $my_data_table)) {
    // First add my term.
    tripal_insert_cvterm(array(
      'id' => 'tripal:12345',
      'name' => 'noahs_test_field_cvterm',
      'cv_name' => 'organism',
      'definition' => 'This is a test field. It should print organism name.',
    ));

    // Then describe the field defined by that term.
    $field_name = 'tripal__noahs_test_field_cvterm';
    $field_type = 'tripal__noahs_test_field_cvterm';
    $fields[$field_name] = array(
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => 1,
      'locked' => FALSE,
      'storage' => array(
        'type' => 'field_chado_storage',
      ),
    );
  }

  $my_data_table = 'analysis';
  if (isset($bundle->data_table) AND ($bundle->data_table == $my_data_table)) {
    // First add my term.
    tripal_insert_cvterm(array(
      'id' => 'local:12345',
      'name' => 'expression_features',
      'cv_name' => 'local',
      'definition' => 'Table of expression features.',
    ));

    // Then describe the field defined by that term.
    $field_name = 'local__expression_features';
    $field_type = 'local__expression_features';
    $fields[$field_name] = array(
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => 1,
      'locked' => FALSE,
      'storage' => array(
        'type' => 'field_chado_storage',
      ),
    );
  }
  return $fields;
}

/**
 * Implements hook_bundle_instances_info().
 *
 * This hook tells Drupal/Tripal to create a field instance of a given field type on a
 * specific Tripal Content type (otherwise known as the bundle). Make sure to implement
 * hook_bundle_create_fields() to create your field type before trying to create an
 * instance of that field.
 *
 * @param $entity_type
 *   This should be 'TripalEntity' for all Tripal Content.
 * @param $bundle
 *   This object describes the Type of Tripal Entity (e.g. Organism or Gene) the field
 *   instances are being created for. Thus this hook is called once per Tripal Content Type on your
 *   site. The name of the bundle is the machine name of the type (e.g. bio_data_1) and
 *   the label of the bundle (e.g. Organism) is what you see in the interface. Since the
 *   label can be changed by site admin, we suggest checking the data_table to determine
 *   if this is the entity you want to add field instances to.
 * @return
 *   An array of field instance definitions. This is where you can define the defaults
 *   for any settings you use in your field. Each entry in this array will be used to
 *   create an instance of an already existing field.
 */
function noahs_test_module_bundle_instances_info($entity_type, $bundle) {
  $instances = array();

  $my_data_table = 'organism';
  if (isset($bundle->data_table) AND ($bundle->data_table == $my_data_table)) {
    $field_name = 'local__features_list';
    $field_type = 'local__features_list';
    $instances[$field_name] =  array(
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Features List',
      'description' => 'Displays a list of features. (this is test)',
      'required' => FALSE,
      'settings' => array(
        'term_vocabulary' => 'local',
        'term_name' => 'features_list',
        'term_accession' => 'features_list',
        'auto_attach' => FALSE,
        'chado_table' => $bundle->data_table,
        'chado_column' => 'organism_id',
        'base_table' => $bundle->data_table,
      ),
      'widget' => array(
        'type' => 'local__features_list_widget',
        'settings' => array(),
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'local__features_list_formatter',
          'settings' => array(),
        ),
      ),
    );

  }

  if (isset($bundle->data_table) AND ($bundle->data_table == $my_data_table)) {
    $field_name = 'tripal__noahs_test_field_cvterm';
    $field_type = 'tripal__noahs_test_field_cvterm';
    $instances[$field_name] = array(
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Noahs Test Field',
      'description' => 'This is a test field. It should print organism name.',
      'required' => FALSE,
      'settings' => array(
        'term_vocabulary' => 'tripal',
        'term_name' => 'noahs_test_field_cvterm',
        'term_accession' => '12345',
        'auto_attach' => FALSE,
        'chado_table' => $bundle->data_table,
        'chado_column' => 'organism_id',
        'base_table' => $bundle->data_table,
      ),
      'widget' => array(
        'type' => 'tripal__noahs_test_field_cvterm_widget',
        'settings' => array(),
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'tripal__noahs_test_field_cvterm_formatter',
          'settings' => array(),
        ),
      ),
    );
  }

  $my_data_table = 'analysis';
  if (isset($bundle->data_table) AND ($bundle->data_table == $my_data_table)) {
    $field_name = 'local__expression_features';
    $field_type = 'local__expression_features';
    $instances[$field_name] =  array(
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Expression Features',
      'description' => 'Table of expression features.',
      'required' => FALSE,
      'settings' => array(
        'term_vocabulary' => 'local',
        'term_name' => 'expression_features',
        'term_accession' => '12345',
        'auto_attach' => FALSE,
        'chado_table' => $bundle->data_table,
        'chado_column' => 'organism_id',
        'base_table' => $bundle->data_table,
      ),
      'widget' => array(
        'type' => 'local__expression_features_widget',
        'settings' => array(),
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'local__expression_features_formatter',
          'settings' => array(),
        ),
      ),
    );

  }
  return $instances;
}
