<?php

	function allotment_list_approve_form($form, &$form_state) {
	
		$allotment_process_date =  isset($form_state['values']['allotment_process_date']) && !empty($form_state['values']['allotment_process_date']) ? $form_state['values']['allotment_process_date'] : '';
		
		$allotment_process_no =  isset($form_state['values']['allotment_process_no']) && !empty($form_state['values']['allotment_process_no']) ? $form_state['values']['allotment_process_no'] : '';
		
		$allotment_process_type =  isset($form_state['values']['allotment_process_type']) && !empty($form_state['values']['allotment_process_type']) ? $form_state['values']['allotment_process_type'] : '';
		
		// Git repo created ----
		$form['allotment_process_date'] = array(
			'#title' => t('Allotment Process Date'),
			'#type' => 'select',
			'#options' => allotment_process_date(),
			'#required' => TRUE,
			'#attributes' => array('class' => array('dropdown3')),
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_process_no',
					   'method' => 'replace',
			),
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#default_value' => $allotment_process_date,
	  	);
		
		
		$form['allotment_process_no'] = array(
			/*'#title' => t('Allotment Process No.'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			'#attributes' => array('class' => array('dropdown3')),
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_process_type',
					   'method' => 'replace',
			),*/
			'#prefix' => '<div class="three" id="allotment_process_no_replace">',
			'#suffix' => '</div>',
			//'#default_value' => $allotment_process_no,
		);		

		
		if($allotment_process_date != '') {
			$form['allotment_process_no'] = array(
				'#title' => t('Allotment Process No.'),
				'#type' => 'select',
				'#options' => allotment_process_no($allotment_process_date),
				'#required' => TRUE,
				'#attributes' => array('class' => array('dropdown3')),
				'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_allotment_process_type',
						   'method' => 'replace',
				),
				'#prefix' => '<div class="three" id="allotment_process_no_replace">',
				'#suffix' => '</div>',
				'#default_value' => $allotment_process_no,
			);
		}
		
		$form['allotment_process_type'] = array(
			/*'#title' => t('Allotment Type'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			'#attributes' => array('class' => array('dropdown3')),
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_list',
					   'method' => 'replace',
			),*/
			'#prefix' => '<div class="three" id="allotment_process_type_replace">',
			'#suffix' => '</div>',
			//'#default_value' => $allotment_process_type,
		);		

		
		if($allotment_process_date != '' && $allotment_process_no != '') {
			$form['allotment_process_type'] = array(
				'#title' => t('Allotment Process Type'),
				'#type' => 'select',
				'#options' => array('' => 'Select Allotment Process Type', 'NAL' => 'New Allotment', 'VSAL' => 'Floor Shifting', 'CSAL' => 'Category Shifting'),
				'#required' => TRUE,
				'#attributes' => array('class' => array('dropdown3')),
				'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_allottee_list',
						   'method' => 'replace',
				),
				'#prefix' => '<div class="three" id="allotment_process_type_replace">',
				'#suffix' => '</div>',
				'#default_value' => $allotment_process_type,
			);
		}
		
		$form['submit_approve'] = array(
			'#prefix' => '<div id="submit_approve_allotteelist">',
			'#suffix' => '</div>',
  		);
		$form['submit_reject'] = array(
			'#prefix' => '<div id="submit_reject_allotteelist">',
			'#suffix' => '</div>',
  		);
		$form['allottee_info'] = array(
			'#prefix' => '<div id="allottee_info">',
			'#suffix' => '</div>',
		);
		
		
		if($allotment_process_date != '' && $allotment_process_no != '' && $allotment_process_type != '') {
			$result = fetch_all_allottee_details_for_approve($allotment_process_date, $allotment_process_no, $allotment_process_type);
			
			$header = array();
			
			if($allotment_process_type == 'NAL') {
				$header = array(
					'sl_no' => array('data' => 'Sl. No.'),
					'name_desig' => array('data' => 'Name and Designation'),
					'app_no_posting_doa' => array('data' => '1. Application No.<br>2. Place of Posting<br>3. Date of Application'),
					'flat_allotted' => array('data' => 'Flat Allotted'),
					'floor' => array('data' => 'Floor'),
					'rhe_name' => array('data' => 'Name of R.H.E.'),
					'dor' => array('data' => 'Date of Retirement'),
					'remarks' => array('data' => 'Remarks'),
				);
			} else if($allotment_process_type == 'VSAL' || $allotment_process_type == 'CSAL') {
				$header = array(
					'sl_no' => array('data' => 'Sl. No.'),
					'applicant_name' => array('data' => 'Name'),
					'dop_doa_dor' => array('data' => '1. Date of Possession<br>2. Date of Application<br>3. Date of Retirement'),
					'flat_allotted' => array('data' => 'Allotted Flat No.'),
					'flat_type' => array('data' => 'Type of Flat'),
					'floor' => array('data' => 'Floor'),
					'from_flat_no' => array('data' => 'From Flat No.'),
					'to_flat_no' => array('data' => 'To Flat No.'),
					'remarks' => array('data' => 'Remarks'),
				);
			}
			
			$i = 1;
			$onclick="return confirm('Are you sure you want to Approve?')";
			$onclick1="return confirm('Are you sure you want to Reject?')";
			
			if($result->rowCount() > 0) {
				$form['submit_approve'] = array(
					'#type' => 'submit',
					'#value' => t('Click to Approve Allotment'),
					'#attributes' => array('onclick' => $onclick),
					'#prefix' => '<div class="two-one" id="submit_approve_allotteelist" style="height: 50%">',
					'#suffix' => '</div>',
				);
				$form['submit_reject'] = array(
					'#type' => 'submit',
					'#value' => t('Click to Reject Allotment'),
					'#attributes' => array('onclick' => $onclick1),
					'#submit' => array('allottee_list_reject'),
					'#prefix' => '<div class="four" id="submit_reject_allotteelist" style="height: 50%">',
					'#suffix' => '</div>',
				);
			}
			
			$options = array();
			
			foreach($result as $record) {
				
				if(trim($record->floor) == 'F') {
					$floor = '1st';	
				} else if(trim($record->floor) == 'S') {
					$floor = '2nd';	
				} else {
					$floor = $record->floor;	
				}
				
				if($record->allowed_for_floor_shifting != '' && $record->allowed_for_floor_shifting == 'N') {
					$allowed_for_fs = 'No Floor Shifting Henceforth';		
				} else {
					$allowed_for_fs = '';	
				}
				
				if($allotment_process_type == 'NAL') {
					if($record->roaster_vacancy_position != '') {
						if($record->roaster_vacancy_position == 1 || $record->roaster_vacancy_position == 21) {
							$remarks = $record->roaster_vacancy_position.'st Vacancy<br>'.$record->allotment_reason.'<br>'.$allowed_for_fs;	
						} else if($record->roaster_vacancy_position == 2 || $record->roaster_vacancy_position == 22) {
							$remarks = $record->roaster_vacancy_position.'nd Vacancy<br>'.$record->allotment_reason.'<br>'.$allowed_for_fs;	
						} else if($record->roaster_vacancy_position == 3 || $record->roaster_vacancy_position == 23) {
							$remarks = $record->roaster_vacancy_position.'rd Vacancy<br>'.$record->allotment_reason.'<br>'.$allowed_for_fs;	
						} else {
							$remarks = $record->roaster_vacancy_position.'th Vacancy<br>'.$record->allotment_reason.'<br>'.$allowed_for_fs;
						}
					} else {
						$remarks = $allowed_for_fs;		
					}
					
					$options[$record->online_application_id] = array(
						'sl_no' => $i,
						'name_desig' => $record->applicant_name.'<br>'.$record->applicant_designation,
						'app_no_posting_doa' => '1. '.$record->application_no.'<br>'.'2. '.$record->applicant_posting_place.'<br>'.'3. '.implode('/', array_reverse(explode('-', $record->date_of_application))),
						'flat_allotted' => $record->flat_no,
						'floor' => $floor,
						'rhe_name' => $record->estate_name,
						'dor' => implode('/', array_reverse(explode('-', $record->date_of_retirement))),
						'remarks' => $remarks,
					);
					
				} else if($allotment_process_type == 'VSAL' || $allotment_process_type == 'CSAL') {
					if($allotment_process_type == 'VSAL') {
						$occupied_flat = $record->occupied_flat_vs;
						$remarks = 'Floor Shifting';	
					} else if($allotment_process_type == 'VSAL' || $allotment_process_type == 'CSAL') {
						$occupied_flat = $record->occupied_flat_cs;
						$remarks = 'Category Shifting';	
					}
					
					$options[$record->online_application_id] = array(
						'sl_no' => $i,
						'applicant_name' => $record->applicant_name,
						'dop_doa_dor' => '1. '.implode('/', array_reverse(explode('-', $record->possession_date))).'<br>'.'2. '.implode('/', array_reverse(explode('-', $record->date_of_application))).'<br>'.'3. '.implode('/', array_reverse(explode('-', $record->date_of_retirement))),
						'flat_allotted' => $record->flat_no,
						'flat_type' => $record->flat_type,
						'floor' => $floor,
						'from_flat_no' => $occupied_flat,
						'to_flat_no' => $record->flat_no,
						'remarks' => $remarks,
					);	
					
				}
				
				$i++;
			}
		
			$form['allottee_info'] = array(
				'#type' => 'tableselect',
				'#header' => $header,
				'#options' => $options,
				'#empty' => t('No allottee available.'),
				'#prefix' => '<div id="allottee_info">',
				'#suffix' => '</div>',
			); 	
			
	  	}
		
		return $form;
	}
	
	function allotment_list_approve_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
		
		$i = 0;
		$all_allottee = $form_state['values']['allottee_info'];
		foreach($all_allottee as $allottee_app_id => $selected_allottee) {
			if($selected_allottee != 0) {
				$i = 1;	
			}
		}
		if($i == 0) {
			form_set_error($selected_allottee, t('No allottees are selected for allotment approve or reject!!!'));	
		}
	}
	
	function allotment_list_approve_form_submit($form, &$form_state) {
		//$form_state['rebuild'] = TRUE;
		
		$all_allottee = $form_state['values']['allottee_info'];
	
		foreach($all_allottee as $allottee_app_id => $selected_allottee) {
			if($selected_allottee != 0) {
				db_update('housing_online_application')
				->fields(array(
					'status' => 'allotted_approved',
					)
				)
				->condition('online_application_id', $allottee_app_id, '=')
				->execute();
				
				db_update('housing_flat_occupant')
				->fields(array(
					'allotment_approve_or_reject_date' => date('Y-m-d'),
					)
				)
				->condition('online_application_id', $allottee_app_id, '=')
				->execute();
				
			//code for allottee email list array for email send
				$query_sendmail = db_select('users', 'u');
				$query_sendmail->innerJoin('housing_applicant_official_detail', 'haod', 'u.uid = haod.uid');
				$query_sendmail->innerJoin('housing_online_application', 'hoa', 'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
				$query_sendmail->fields('u', array('mail'));
				$query_sendmail->condition('hoa.online_application_id', $allottee_app_id, '=');
				$result_sendmail = $query_sendmail->execute();
				$data_sendmail = $result_sendmail->fetchObject();
				
				$receiver_email_arr[] = $data_sendmail->mail;
			}
		}
		
	//code for email send to approved allottee
		$receiver_email_list[] = $receiver_email_arr;
		$email_subject = 'Offer of Allotment';
		$message = '<html><body>Dear Applicant,<br><br>		
		A flat has been allotted to you. Please login to your account and accept the Offer of Allotment within 30 days from the date you receive this mail to avoid cancellation of the flat allotment.
		<br><br>			
		Regards,<br>
		Housing Department<br>
		Government of West Bengal
		</html></body>';
				
		sendmail_allotment($receiver_email_list, $email_subject, $message);
	
		drupal_set_message(t('Allotment of Allottees are Approved.'));
		
	}
	
	function allottee_list_reject($form, &$form_state) {
		//$form_state['rebuild'] = TRUE;
		
		$all_allottee = $form_state['values']['allottee_info'];
	
		foreach($all_allottee as $allottee_app_id => $selected_allottee) {
			if($selected_allottee != 0) {
				
				db_update('housing_online_application')
				->fields(array(
					'status' => 'allotted_rejected',
					)
				)
				->condition('online_application_id', $allottee_app_id, '=')
				->execute();
				
				db_update('housing_flat_occupant')
				->fields(array(
					'accept_reject_status' => 'Cancel',
					'allotment_approve_or_reject_date' => date('Y-m-d'),
					)
				)
				->condition('online_application_id', $allottee_app_id, '=')
				->execute();
				
				$query = db_select('housing_online_application', 'hoa');
				$query->innerJoin('housing_flat_occupant', 'hfo', 'hoa.online_application_id = hfo.online_application_id');
				$query->addField('hfo', 'flat_id');
				$query->condition('hfo.online_application_id', $allottee_app_id, '=');
				$result = $query->execute();
				$data = $result->fetchObject();
				
				db_update('housing_flat')
				->fields(array(
					'flat_status_id' => 1,
					)
				)
				->condition('flat_id', $data->flat_id, '=')
				->execute();
				
			}
		}
		drupal_set_message(t('Occupants are successfully rejected.'));
	}
	
	function _reload_allotment_process_no($form, &$form_state) {
		$commands[] = ajax_command_replace('#allotment_process_no_replace', drupal_render($form['allotment_process_no']));
		$commands[] = ajax_command_replace('#allotment_process_type_replace', drupal_render($form['allotment_process_type']));
		$commands[] = ajax_command_replace("#submit_approve_allotteelist", drupal_render($form['submit_approve']));
		$commands[] = ajax_command_replace("#submit_reject_allotteelist", drupal_render($form['submit_reject']));
		$commands[] = ajax_command_replace("#allottee_info", drupal_render($form['allottee_info']));
		return array('#type' => 'ajax', '#commands' => $commands);
 
	}
	
	function _reload_allotment_process_type($form, &$form_state) {
		$commands[] = ajax_command_replace('#allotment_process_type_replace', drupal_render($form['allotment_process_type']));
		$commands[] = ajax_command_replace("#submit_approve_allotteelist", drupal_render($form['submit_approve']));
		$commands[] = ajax_command_replace("#submit_reject_allotteelist", drupal_render($form['submit_reject']));
		$commands[] = ajax_command_replace("#allottee_info", drupal_render($form['allottee_info']));
		return array('#type' => 'ajax', '#commands' => $commands);
 
	}
	
	function _reload_allottee_list($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#submit_approve_allotteelist", drupal_render($form['submit_approve']));
		$commands[] = ajax_command_replace("#submit_reject_allotteelist", drupal_render($form['submit_reject']));
		$commands[] = ajax_command_replace("#allottee_info", drupal_render($form['allottee_info']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}