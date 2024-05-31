<?php
function rhe_allotment_form($form, $form_state) {	
	 $allotment_type =  !empty($form_state['values']['allotment_type']) ? $form_state['values']['allotment_type'] : '';
	 if(isset($form_state['values']['allotment'])) {
		$report_content = get_vacancy_applicant($allotment_type);
	} else {
		$report_content = '';
	}
	
	$form['allotment_type'] = array(
		'#title' => t('Select Allotment Type'),
		'#type' => 'select',
		'#options' => rhe_flat_type(),
		'#required' => TRUE,
		'#prefix' => '<div class="two">',
		'#suffix' => '</div>',
	);  
	  
	$form['allotment'] = array(
		'#type' => 'submit',
		'#value' => 'Show vacancy',
		'#prefix' => '<div class="two" style="margin-top:43px;height: 30px;">',
		'#suffix' => '</div>',
	);

	$form['divToPrint'] = array(
		'#prefix' => '<div class="printable"><div id="divToPrint" style="width:100% !important;">' . $report_content,
		'#suffix' => '</div></div>',
	);
	
	//$form['#attributes'] = array('onsubmit' => 'return validate_rhe_allotment_form()');
			
	return $form;
}

function get_vacancy_applicant($allotment_type) {
	global $base_url;

	$allvacancy = "";
	$allvacancy = get_estatewise_vacancy($allotment_type);

	$report_table = '<table class="allotment">
		<tr>
			<th rowspan="2">Housing</th>
			<th colspan="4">No. of Vacancy</th>
			<th colspan="3">No. of Applicant</th>
			<th rowspan="2">Action</th>
		</tr>
		<tr>
			<th>Floor-0</th>
			<th>Floor-1</th>
			<th>Floor-2</th>
			<th>Floor-3</th>
			<th>Floor shifting</th>
			<th>Category shifting</th>
			<th>New/ Fresh</th>
		</tr>';

		if($allvacancy -> rowCount() > 0) {
			$total_record = $allvacancy -> rowCount();
			$counter = 1; $applicant_fresh = 0; $rowspan = 0;
			foreach($allvacancy as $record) {
				$applicant_vs = get_no_of_applicant_vs($allotment_type, $record -> estate_id);
				$applicant_cs = get_no_of_applicant_cs($allotment_type, $record -> estate_id);
				if($counter == 1) {
					$applicant_fresh = get_no_of_applicant_fresh($allotment_type);
					$rowspan = $total_record;
				}
				
				$applicant_total = $applicant_vs + $applicant_cs + $applicant_fresh;

				$allotment_btn = ($applicant_total > 0) ? '<a class="button small round steel_blue" href="' . $base_url . '/rhe_allotment/' . $allotment_type . '/' . $record -> estate_id . '">Allot</a>' : '&nbsp;';
				
				if($counter == 1) {
					$report_table .= '<tr>
						<td>' . $record -> estate_name . '</td>
						<td>' . $record -> floor_0 . '</td>
						<td>' . $record -> floor_1 . '</td>
						<td>' . $record -> floor_2 . '</td>
						<td>' . $record -> floor_3 . '</td>
						<td>' . $applicant_vs . '</td>
						<td>' . $applicant_cs . '</td>
						<td rowspan = "' . $rowspan . '">' . $applicant_fresh . '</td>
						<td>' . $allotment_btn . '</td>
					</tr>';
				} else {
					$report_table .= '<tr>
						<td>' . $record -> estate_name . '</td>
						<td>' . $record -> floor_0 . '</td>
						<td>' . $record -> floor_1 . '</td>
						<td>' . $record -> floor_2 . '</td>
						<td>' . $record -> floor_3 . '</td>
						<td>' . $applicant_vs . '</td>
						<td>' . $applicant_cs . '</td>
						<td>' . $allotment_btn . '</td>
					</tr>';
				}	
				$counter++;			
			}
		}

		$report_table .= '</table>';

	return $report_table;

}

function rhe_allotment_form_submit($form, &$form_state) {
	$form_state['rebuild'] = TRUE;
}