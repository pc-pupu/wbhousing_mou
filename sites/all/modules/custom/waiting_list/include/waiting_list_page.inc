<?php

	//form for search application waiting list position of a particular applicant
	function waiting_list_form($form,&$form_state) {
		
		$application_no = isset($form_state['values']['application_no']) && !empty($form_state['values']['application_no']) ? $form_state['values']['application_no'] : '' ;
		$form['application_no']=array(
			'#title' => t('Enter Application No.'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#attributes' => array('placeholder' => 'Enter application no.'),
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#weight' =>2
		);
		$form['search'] = array(
			'#value' => t('Search'),
			'#type' => 'submit',
			'#prefix' => '<div class="two" style="margin-top:43px;height: 30px;">',
			'#suffix' => '</div>',
			'#weight' =>3
	  	);
		
		$form['#attributes'] = array('onsubmit' => 'return validate_waiting_list()');
		
		if(!empty($application_no)) {	  
			$output = waiting_list_page($application_no);
			$form['breadcrumb'] = array(
				'#type' => 'markup',
				'#markup' => $output,
				'#weight' => 5
			);
		}
	  
	  return $form;	
	}
	
	function waiting_list_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}


	function waiting_list_page($application_no = '') {
		$output = '';
		$online_application_id = 0;
		$result = application_fetch_detail($online_application_id, trim($application_no));
		$rows =array();
		$header = array();
		$header[] = array('data' => 'Application No.', 'class' => array('text-font-l'));
		$header[] = array('data' => 'Flat Type', 'class' => array('text-font-c'));
		//$header[] = array('data' => 'Status');
		//$header[] = array('data' => 'Combined Waiting No', 'class' => array('text-font-r'));
		$header[] = array('data' => 'Flat Type Wise Waiting No', 'class' => array('text-font-r'));
	
		//$flat_type_id = 0;
		 while($data = $result->fetchObject()) {
				 $fields = array();
				 $returns = check_application_entity(0,$data->online_application_id);
				 $entityList = $returns[0];
				 $fields[] = array('data' => $data->application_no, 'class' => array('text-font-l'));
				 $fields[] = array('data' => $data->flat_type, 'class' => array('text-font-c'));
				 //$fields[] =$data->status;
				 /*$wait_no = get_individual_waiting_no($data->application_no);
		 		 $fields[] = array('data' => $wait_no != 0 ? $wait_no : '', 'class' => array('text-font-r'));*/
				 $flat_type_wait_no = flat_type_wise_waiting_no($data->application_no, $data->flat_type_id);
		 		 $fields[] = array('data' => $flat_type_wait_no != 0 ? $flat_type_wait_no : 'Pending', 'class' => array('text-font-r'));
				 $rows[] = $fields;
		 }
		
		$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('class' => array('table-css')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');
	  
	  return $output;
	}