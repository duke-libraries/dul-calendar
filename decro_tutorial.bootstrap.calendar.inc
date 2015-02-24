<?php

/**
 * Page callback for Boostrap-y Calendar Example
 */
function decro_tutorial_bootstrap_calendar() {
	$build = array();
	$t = time();
	$o = _decro_prepared_calendar_info($t);
	$interval = new DateInterval('P1D');

	$i = 0;
	$table_rows = array();
	$current_row = FALSE;
	while ($o->dateTime->getTimestamp() <= $o->last_cal_day) {
		$current_time = $o->dateTime->getTimestamp();

		if (($i % 7) == 0) {
			if ($current_row !== FALSE) {
				$table_rows[] = $current_row;
			}
			$current_row = array();
		}

		$elements = array();
		$elements[] = array(
			'#markup' => date('j', $current_time),
			'#prefix' => '<div class="text-left">',
			'#suffix' => '</div>',
		);
	  foreach (module_implements('calendar_day_elements') as $module) {
	    // will call all modules implementing hook_hook_name and 
	    // push the results onto the $result array
	    $new_elements = module_invoke($module, 'calendar_day_elements', getdate($current_time));
	    $elements = array_merge($elements, $new_elements);
	  }
		$cell = array(
			'data' => $elements,
		);
		if (date('z', $t) == date('z', $current_time)) {
			$cell['class'] = array('active');
		}
		$current_row[] = $cell;

		$o->dateTime->add($interval);
		$i++;
	}

	if ($current_row) {
		$table_rows[] = $current_row;
	}

	$build['calendar-table'] = array(
		'#theme' => 'table',
		'#rows' => $table_rows,
		'#attributes' => array(
			'class' => array('table', 'table-striped'),
		),
	);
	return $build;
}

function _decro_prepared_calendar_info($ts = NULL) {
	if ($ts == NULL) {
		$ts = time();
	}

	$iMonth = date('n', $ts);
	$iYear = date('Y', $ts);
	$iDaysInMonth = date('t', $ts);

	$first_day_month = mktime(0, 0, 0, $iMonth, 1, $iYear);
	$last_day_month = mktime(0, 0, 0, $iMonth, $iDaysInMonth, $iYear);

	$first_sunday = $first_day_month - (86400 * ((int)date('w', $first_day_month)));
	$last_saturday = $last_day_month + (86400 * (6 - (int)date('w', $last_day_month)));

	$datetime = new DateTime(date('r', $first_sunday));

	$o = new stdClass();
	$o->dateTime = $datetime;
	$o->days_in_month = $iDaysInMonth;
	$o->month = $iMonth;
	$o->first_cal_day = $first_sunday;
	$o->last_cal_day = $last_saturday;

	return $o;
}