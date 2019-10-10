This module offers the ability to turn a views filter for a textfield into a dropdown.

It gets all possible values for the field from the database and display them as select options.

Operators, if exposed, are automatically limited to "Is equal to" and "Is not equal to".

Usage:
1. Core text fields:
Edit the views filter for any textfield. There should be a "Use select list" checkbox. Simply check it and save, the exposed filter should be a dropdown instead of the usual text input form.

2. Custom fields:
If you expose a custom database field to views, simply add 'viewsfilter_text2select_filter' as the filter handler in hook_views_data().
e.g.:
  $data[YOURTABLE][YOURFIELD] = array(
    ...
    'filter' => array(
      'handler' => 'viewsfilter_text2select_filter',
    ),
    ...
  );
