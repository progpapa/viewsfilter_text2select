<?php
/**
 * @file
 * Custom views filter definition to turn text input field into dropdowns.
 */

/**
 * Custom views filter definition to turn text input field into dropdowns.
 *
 * @ingroup views_filter_handlers
 */
class viewsfilter_text2select_filter extends views_handler_filter_string {

  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);
    // Use parent if the filter is not configured to be a dropdown.
    if (empty($this->options['text2select'])) {
      return;
    }
    $query = 'SELECT DISTINCT(' . $this->field . ') FROM {' . $this->table . '}';
    $options = db_query($query)->fetchCol();
    if (empty($options)) {
      $form['value'] = array(
        '#markup' => t('No available options for this field.'),
      );
    }
    else {
      $form['value']['#type'] = 'select';
      $form['value']['#multiple'] = FALSE;
      $form['value']['#options'] = array_combine($options, $options);
      // This prevents the "An illegal choice..." message when no value selected.
      // 'All' is hard-coded into views_handler_filter::build_group_form()?
      if (empty($form_state['input'][$this->field])) {
        $form_state['input'][$this->field] = 'All';
        $form_state['view']->exposed_input[$this->field] = 'All';
      }
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    // This is required to store our custom values and set their defaults.
    $options['text2select'] = array('default' => FALSE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['text2select'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use select list'),
      '#description' => t('Changes the text input into a select dropdown. Exposed operators will be limited to "@equal" and "@notequal".',
          array('@equal' => t('Is equal to'), '@notequal' => t('Is not equal to'))),
      '#default_value' => $this->options['text2select'],
    );
  }

  /**
   * If a textfield is transformed to a dropdown and the operator is exposed,
   * this makes sure that only the "Is equal to" and "Is not equal to" operators
   * are allowed.
   */
  public function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);
    if (empty($form_state['values']['options']['text2select'])
        OR empty($form_state['values']['options']['expose']['use_operator'])) {
      return;
    }
    $select_operators = array('=' => '=', '!=' => '!=');
    foreach ($select_operators as $key => $value) {
      if ($key === '=' OR $key === '!=') {
        $select_operators[$key] = $key;
      }
      else {
        $select_operators[$key] = NULL;
      }
    }
    $form_state['values']['options']['expose']['limit_operators'] = TRUE;
    $form_state['values']['options']['expose']['available_operators']
      = $select_operators;
  }
}