<?php

	function existing_applicant_form($form, &$form_state) {
		
		$district = isset($form_state['values']['district']) && !empty($form_state['values']['district']) ? $form_state['values']['district'] : '';
		
		$designation = isset($form_state['values']['designation']) && !empty($form_state['values']['designation']) ? $form_state['values']['designation'] : '';
		$dob = isset($form_state['values']['dob']) && !empty($form_state['values']['dob']) ? $form_state['values']['dob'] : '';
		
		$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
	    $rhe_flat_type = rhe_flat_type_rst_pay_band_id($pay_band_id);
	    $reason = isset($form_state['values']['reason']) && !empty($form_state['values']['reason']) ? $form_state['values']['reason'] : '';
		
		$chk_permanent_address = isset($form_state['values']['chk_permanent_address']) ? $form_state['values']['chk_permanent_address'] : '';
		
		$form['form_begin'] = array(
			'#type' => 'markup',
			'#markup' => '<div class="online_application">',
			'#weight' => -2
		);
		
		//personal information
		$form['prrsonal_info'] = array(
			'#type' => 'fieldset',
			'#title' => t('Personal Information(According to Service Book)'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE,  // Added
		);
						
		$form['prrsonal_info']['applicant_name'] = array(
			'#title' => t('Applicant\'s Name'),
			'#type' => 'textfield',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_fullstop'), 
			'#required' => TRUE,
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);
		
		$form['prrsonal_info']['applicant_father_name'] = array(
			'#title' => t('Father / Husband Name'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_fullstop'), 
			'#required' => TRUE,
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);
		
	//Permanent Address
		$form['prrsonal_info']['permanent_address'] = array(
			'#type' => 'fieldset',
			'#title' => t('Permanent Address'),
			'#collapsible' => FALSE, // Added
			'#collapsed' => FALSE,  // Added
		);
		$form['prrsonal_info']['permanent_address']['permanent_street'] = array(
			'#title' => t('Address'),
			'#type' => 'textfield',
			//'#required' => TRUE,
			'#prefix' => '<div class="two-one">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_streetaddress'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);
		$form['prrsonal_info']['permanent_address']['permanent_city_town_village'] = array(
			'#title' => t('City / Town / Village'),
			'#type' => 'textfield',
			//'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);
		$form['prrsonal_info']['permanent_address']['permanent_post_office'] = array(
			'#title' => t('Post Office'),
			'#type' => 'textfield',
			//'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);
		$form['prrsonal_info']['permanent_address']['permanent_district'] = array(
			'#title' => t('District'),
			'#type' => 'select',
			'#options' => district_list(),
			//'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
        	)
		);
		$form['prrsonal_info']['permanent_address']['permanent_pincode'] = array(
			'#title' => t('Pincode'),
			'#type' => 'textfield',
			'#maxlength' => 6,
			//'#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		);
	//end
	
		$form['prrsonal_info']['chk_permanent_address'] = array(
			/*'#type' => 'checkboxes',
			'#title' => '',
			'#options' => array(1 => t('Check if Your Present Address is same as Your Permanent Address.')),*/
			
			'#type' => 'checkbox',
			'#title' => 'Check if Your Present Address is same as Your Permanent Address.',
			'#default_value' => '',
			//'#attributes' => array('id' => 'chk_present_address'),     //for this ajax callback not working.
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_present_address',
					   'wrapper' => 'replace_present_address',
					   'effect' => 'fade',
					   'progress' => array(
						  'type' => '',
						  'message' => '',
						), 
			 ),
	    );
		
		if($chk_permanent_address != 1) {
		//Present Address
			$form['prrsonal_info']['present_address'] = array(
				'#type' => 'fieldset',
				'#title' => t('Present Address'),
				'#collapsible' => FALSE, // Added
				'#collapsed' => FALSE,  // Added
				'#prefix' => '<div id="reload_present_address">',
				'#suffix' => '</div>',
			);
			$form['prrsonal_info']['present_address']['present_street'] = array(
				'#title' => t('Address'),
				'#type' => 'textfield',
				//'#required' => TRUE,
				'#prefix' => '<div class="two-one" id="reload_present_street">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_streetaddress'), 
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), //'id' => 'present_street', 
			);
			$form['prrsonal_info']['present_address']['present_city_town_village'] = array(
				'#title' => t('City / Town / Village'),
				'#type' => 'textfield',
				//'#required' => TRUE,
				'#prefix' => '<div class="three" id="reload_present_city_town_village">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_alphabatic_text'), 
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), //'id' => 'present_city_town_village', 
			);
			$form['prrsonal_info']['present_address']['present_post_office'] = array(
				'#title' => t('Post Office'),
				'#type' => 'textfield',
				//'#required' => TRUE,
				'#prefix' => '<div class="three" id="reload_present_post_office">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_alphabatic_text'), 
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), //'id' => 'present_post_office', 
			);
			$form['prrsonal_info']['present_address']['present_district'] = array(
				'#title' => t('District'),
				'#type' => 'select',
				'#options' => district_list(),
				//'#required' => TRUE,
				'#prefix' => '<div class="three" id="reload_present_district">',
				'#suffix' => '</div>',
				//'#attributes' => array('id' => 'present_district'),
				'#select2' => array(
					'width' => '500',
					//'placeholder' => '- Select -',
					'allowClear' => TRUE
				),
			);
			$form['prrsonal_info']['present_address']['present_pincode'] = array(
				'#title' => t('Pincode'),
				'#type' => 'textfield',
				'#maxlength' => 6,
				//'#required' => TRUE,
				'#element_validate' => array('element_validate_numeric_positive'), 
				'#prefix' => '<div class="four" id="reload_present_pincode">',
				'#suffix' => '</div>',
				'#attributes' => array('class' => array('numeric_positive')), //'id' => 'present_pincode', 
			);
		} else {
			$form['prrsonal_info']['present_address'] = array(
				'#prefix' => '<div id="reload_present_address">',
				'#suffix' => '</div>',
			);
			/*$form['prrsonal_info']['present_address']['present_street'] = array(
				'#prefix' => '<div id="reload_present_street">',
				'#suffix' => '</div>',
			);
			$form['prrsonal_info']['present_address']['present_city_town_village'] = array(
				'#prefix' => '<div id="reload_present_city_town_village">',
				'#suffix' => '</div>',
			);
			$form['prrsonal_info']['present_address']['present_post_office'] = array(
				'#prefix' => '<div id="reload_present_post_office">',
				'#suffix' => '</div>',
			);
			$form['prrsonal_info']['present_address']['present_district'] = array(
				'#prefix' => '<div id="reload_present_district">',
				'#suffix' => '</div>',
			);
			$form['prrsonal_info']['present_address']['present_pincode'] = array( 
				'#prefix' => '<div id="reload_present_pincode">',
				'#suffix' => '</div>',
			);*/
		}
	//end
	
		$form['prrsonal_info']['mobile'] = array(
			'#title' => t('Mobile no'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#maxlength' => 10,
			//'#required' => TRUE,
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_mobile'),
			'#attributes' => array('id' => 'mobile_no'),
		);
		$form['prrsonal_info']['email'] = array(
			'#title' => t('Email ID'),
			'#type' => 'textfield',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_email'),
			'#attributes' => array('oninput'=>"this.value=this.value.toLowerCase()"),
		);
		
		$form['prrsonal_info']['dob'] = array(
			'#title' => t('Date of Birth(According to Service Book)'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-dob'),
			'#required' => TRUE,
			//'#validated' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_date', 'element_validate_age'),
		);
		
		$form['prrsonal_info']['gender'] = array(
			'#title' => t('Gender'),
			'#type' => 'radios',
			'#options' => array('M' => 'Male', 'F' => 'Female'),
			'#attributes' => array('class' => array('gender')),
			'#default_value' => 'M',
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#required' => TRUE,
		);
		
		// applicant's official information
		$form['official_info'] = array(
			'#type' => 'fieldset',
			'#title' => t('Applicant\'s Official Information'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => TRUE,  // Added
		);
		$form['official_info']['hrms_id'] = array(
			'#title' => t('Employee HRMS ID'),
			'#type' => 'textfield',
			'#default_value' => '',
			//'#default_value' => $hrms_id,
			//for api or hrms custom table
			//'#attributes' => array('readonly' => 'readonly', 'class' => array('numeric_positive')),
			'#maxlength' => 10,
			'#attributes' => array('class' => array('numeric_positive')),
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_hrms_id'),
			//'#required' => TRUE,
		);
		$form['official_info']['app_designation'] = array(
			'#title' => t('Designation'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_textarea'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
			//'#attributes' => array('id' => 'edit-app-designation', 'oncopy' => "return false", 'onpaste' => "return false"),
		);
		
		$form['official_info']['pay_band'] = array(
			'#title' => t('Pay Band'),
			'#type' => 'select',
			'#options' => pay_band_list(),
			'#required' => TRUE,
			'#validated' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
		);
		$form['official_info']['pay_in'] = array(
			'#title' => t('Pay in the Pay Band'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		);
		
		$form['official_info']['grade_pay'] = array(
			'#title' => t('Grade Pay'),
			'#type' => 'textfield',
			//'#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		);
		
		/*$form['official_info']['gpf_no'] = array(
			'#title' => t('GPF No.'),
			'#type' => 'textfield',
			//'#required' => TRUE,
			'#element_validate' => array('gpf_no_validate'), 
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);*/
		
		$form['official_info']['app_posting_place'] = array(
			'#title' => t('Place of Posting'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		); 
		$form['official_info']['app_headquarter'] = array(
			'#title' => t('Headquarter'),
			'#type' => 'textfield',
			//'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);
		$form['official_info']['doj'] = array(
			'#title' => t('Date of Joining'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-doj'),
			'#default_value' => '',
			//'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
		);
		
		$form['official_info']['dor'] = array(
			'#title' => t('Date of Retirement(According to Service Book)'),
			'#type' => 'textfield',
			//'#attributes' => array('readonly' => 'readonly'),
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-dor'),
			'#default_value' => '',
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_date'),
		);
		
		
		// applicant's office address
		$form['office_add'] = array(
			'#type' => 'fieldset',
			'#title' => t('Name and Address of the Office'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => TRUE,  // Added
		);
		$form['office_add']['office_name'] = array(
			'#title' => t('Name of the Office'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="two-one">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_textarea'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);
		
		$form['office_add']['office_street'] = array(
			'#title' => t('Address'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="two-one">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_streetaddress'),
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
		);
		$form['office_add']['office_city'] = array(
			'#title' => t('City / Town / Village'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);
		$form['office_add']['office_post_office'] = array(
			'#title' => t('Post Office'),
			'#type' => 'textfield',
			//'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);
		$form['office_add']['office_district'] = array(
			'#title' => t('District'),
			'#type' => 'select',
			'#options' => district_list(),
			'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
        	)
		);
		$form['office_add']['office_pincode'] = array(
			'#title' => t('Pincode'),
			'#type' => 'textfield',
			'#maxlength' => 6,
			'#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		);
		$form['office_add']['office_phone_no'] = array(
			'#title' => t('Phone No.(With STD Code)'),
			'#type' => 'textfield',
			'#maxlength' => 15,
			//'#required' => TRUE,
			'#element_validate' => array('element_validate_telephoneno'), 
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		);
		
		// ddo details
		$form['ddo'] = array(
			'#type' => 'fieldset',
			'#title' => t('DDO with full address'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => TRUE,  // Added
		);
		$form['ddo']['district'] = array(
			'#title' => t('DDO District'),
			'#type' => 'select',
			'#options' => district_list(),
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_ddo_designation',
					  // 'wrapper' => 'replace_designation',
					   'effect' => 'fade',
					   'progress' => array(
						  'type' => '',
						  'message' => '',
						), 
			 ),
			'#required' => TRUE,
			'#validated' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
			)
		);
		
		
		$form['ddo']['designation'] = array(
			'#title' => t('DDO Designation'),
			'#type' => 'select',
			//'#options' => array('- Select -'),
			'#options' => ddo_desig_list($district),
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_ddo_address',
					   'wrapper' => 'replace_ddo_address',
					   'effect' => 'fade',
					   'progress' => array(
						  'type' => '',
						  'message' => '',
						 ),
			 ),
			'#default_value' => $designation,
			'#required' => TRUE,
			'#validated' => TRUE,
			'#prefix' => '<div id="replace_designation" class="two">',
			'#suffix' => '</div>',
			'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
			)
		);
		
		$form['ddo']['address'] = array(
			'#title' => t('DDO Address'),
			'#type' => 'textarea',
			'#attributes' => array('readonly' => 'readonly'),
			'#prefix' => '<div id="replace_ddo_address" >',
			'#suffix' => '</div>',
			//'#required' => TRUE,
			//'#validated' => TRUE,
		);
		
		//allotment type and category
		$form['allotment_reason'] = array(
			'#type' => 'fieldset',
			'#title' => t('Allotment Category'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => TRUE,  // Added
		);
		
		$form['allotment_reason']['rhe_flat_type'] = array(
			'#title' => t('Flat TYPE'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly'),
			'#default_value' => '',
			'#required' => TRUE,
			'#prefix' => '<div class="two" id="replace_rhe_flat_type" >',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_flat_type'),
		 );
	     
		 
		 $form['allotment_reason']['reason'] = array(
			'#title' => t('Allotment Category'),
			'#type' => 'select',
			//'#options' => array(''=>'- Select -'),
			'#options' => allotment_category_list(trim($rhe_flat_type)),
			'#default_value' => $reason,
			'#required' => TRUE,
			'#validated' => TRUE,
			'#prefix' => '<div id="replace_allotment_category" class="two">',
			'#suffix' => '</div>',
		 );
		 
		 $form['allotment_reason']['doa'] = array(
			'#title' => t('Date of Application'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-doa'),
			'#required' => TRUE,
			//'#validated' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_date'),
		);
		
		$form['allotment_reason']['computer_serial_no'] = array(
			'#title' => t('Computer Serial No.'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#element_validate' => array('element_validate_alphanumeric'), 
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
		);
		
		$form['allotment_reason']['remarks'] = array(
			'#title' => t('Remarks'),
			'#type' => 'textarea',
			'#prefix' => '<div class="one">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_textarea'), 
		);
		 
		 $form['official_info']['pay_band']['#ajax'] = array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_category',
					   'effect' => 'fade',
					   'progress' => array(
						  'type' => '',
						  'message' => '',
						 )
		);
		
		$form['#attributes'] = array('onsubmit' => 'return validate_existing_applicant_form()');
		
		$form['form_end'] = array(
			'#type' => 'markup',
			'#markup' => '</div>',
		);
		
		$form['submit_button']=array(
										'#type'=>'submit',
										'#value'=>t('Submit')
								);
								
		
		return $form; 
	}
	
	
	function existing_applicant_form_validate($form, &$form_state) {
		
		if($form_state['values']['pay_band'] == '') {
  			form_set_error('district', t('Please select payband.'));
		}
		if($form_state['values']['district'] == '') {
  			form_set_error('district', t('Please select district.'));
		}
		if($form_state['values']['designation'] == '') {
  			form_set_error('designation', t('Please select ddo designation.'));
		}
		if($form_state['values']['reason'] == '') {
  			form_set_error('reason', t('Please select allotment reason.'));
		}
		
		if(!empty($form_state['values']['mobile']) && is_numeric($form_state['values']['mobile'])) {
		   
			 $mobile = trim($form_state['values']['mobile']);
			 
			 $query = db_select('housing_applicant','applicant');
			 $query->addExpression('mobile_no','mobile');
			 $query->condition('mobile_no', $mobile);
			 $result =$query->execute();
			 
			 
			 if($result->rowCount() > 0)
			 	form_set_error('mobile', 'This mobile no. already exist.');
		
		}
		
		if(!empty($form_state['values']['email'])) {
		   
			$email = trim($form_state['values']['email']);
			
			$query = db_select('users','u');
			$query->addExpression('mail','email');
			$query->condition('mail', $email);
			$result =$query->execute();
			
			/*if (!valid_email_address($email)) {
				form_set_error('[email]', t('The email address appears to be invalid.'));
			}*/
			
			if($result->rowCount() > 0)
				form_set_error('email', 'This email address already exist.');
		
		}
		
		if(!empty($form_state['values']['hrms_id']) && is_numeric($form_state['values']['hrms_id'])) {
		   
			 $hrms_id = trim($form_state['values']['hrms_id']);
			 
			 $query = db_select('housing_applicant_official_detail','haod');
			 $query->fields('haod');
			 $query->condition('hrms_id', $hrms_id);
			 $result =$query->execute();
			 
			 
			 if($result->rowCount() > 0)
			 	form_set_error('hrms_id', 'This Employee HRMS ID already exist.');
		
		}
		
		
		if($form_state['values']['pay_band'] == 1) {
			if($form_state['values']['pay_in'] < 0 || $form_state['values']['pay_in'] > 7999) {
				form_set_error('pay_in', t('Please enter proper Pay in the Pay Band.'));	
			}
		}
		else if($form_state['values']['pay_band'] == 2) {
			if($form_state['values']['pay_in'] < 8000 || $form_state['values']['pay_in'] > 12499) {
				form_set_error('pay_in', t('Please enter proper Pay in the Pay Band.'));	
			}
		}
		else if($form_state['values']['pay_band'] == 3) {
			if($form_state['values']['pay_in'] < 12500 || $form_state['values']['pay_in'] > 15999) {
				form_set_error('pay_in', t('Please enter proper Pay in the Pay Band.'));	
			}
		}
		else if($form_state['values']['pay_band'] == 4) {
			if($form_state['values']['pay_in'] < 16000) {
				form_set_error('pay_in', t('Please enter proper Pay in the Pay Band.'));	
			}
			else {
				if($form_state['values']['grade_pay'] != '') {
					if($form_state['values']['grade_pay'] < 0 || $form_state['values']['grade_pay'] > 7599) {
						form_set_error('grade_pay', t('Please enter proper Grade Pay.'));	
					}
				}		
			}
		}
		else if($form_state['values']['pay_band'] == 5) {
			if($form_state['values']['pay_in'] < 16000) {
				form_set_error('pay_in', t('Please enter proper Pay in the Pay Band.'));	
			}
			else {
				if($form_state['values']['grade_pay'] != '') {
					if($form_state['values']['grade_pay'] < 7600) {
						form_set_error('grade_pay', t('Please enter proper Grade Pay.'));	
					}
				}		
			}
		}
		
	}
	
	
	function existing_applicant_form_submit($form, &$form_state) {
		//$name = strtolower(trim($form_state['values']['applicant_name']));
		//$name1 = str_replace(" ","",$name);
		//$username = str_replace(".","",$name1).rand();
		
		$word_c = str_word_count(trim($form_state['values']['applicant_name']));
		$splitter = " ";
		$pieces = explode($splitter, trim($form_state['values']['applicant_name']));
		
		if($word_c < 2) {
			$name = strtolower(substr($pieces[0], 0, 3));
		}
		else if($word_c == 2) {
			if($pieces[0] == 'Dr.' || $pieces[0] == 'Dr' || $pieces[0] == 'dr.' || $pieces[0] == 'dr' || $pieces[0] == 'DR.' || $pieces[0] == 'DR') {
				$name = strtolower(substr($pieces[1], 0, 3));
			}
			else {
				$name = strtolower(substr($pieces[0], 0, 3)).strtolower(substr($pieces[1], 0, 3));
			}
		}
		else {
			if($pieces[0] == 'Dr.' || $pieces[0] == 'Dr' || $pieces[0] == 'dr.' || $pieces[0] == 'dr' || $pieces[0] == 'DR.' || $pieces[0] == 'DR') {
				$name = strtolower(substr($pieces[1], 0, 3)).strtolower(substr($pieces[2], 0, 3));
			}
			else {
				$name = strtolower(substr($pieces[0], 0, 3)).strtolower(substr($pieces[1], 0, 3));
			}
		}
		
		$username = str_replace(".","",$name).rand(1, 100000);
		
		/*insert into user table*/
		$newUser	   	   = array();
		$newUser['name']   = $username;
		$newUser['pass']   = $username;
		/*$str[0].$str[1].trim($form_state['values']['username']).'@'.$dob_t.strrev($str1[0].$str1[1]);*/
		if($form_state['values']['email'] != '')																																																						
			$newUser['mail']   = trim($form_state['values']['email']);
			
		$newUser['status'] = 1;
		
		user_save(null, $newUser);
		
		/*get last inserted uid*/
		
		$query = db_select('users','u');
		$query->addExpression('MAX(uid)','max_uid');
		$result = $query->execute();
		$data = $result->fetchObject();
		
		/*insert into housing_applicant table*/
		
		$applicant_personal_detail_arr = array();
		$applicant_personal_detail_arr['uid'] 				=  $data->max_uid;
		$applicant_personal_detail_arr['applicant_name'] 	=  trim($form_state['values']['applicant_name']);
		$applicant_personal_detail_arr['guardian_name'] 		=  trim($form_state['values']['applicant_father_name']);
		$applicant_personal_detail_arr['date_of_birth'] 		=  trim(implode('-', array_reverse(explode('/', $form_state['values']['dob']))));
		$applicant_personal_detail_arr['gender'] 			=  trim($form_state['values']['gender']);
		
		if($form_state['values']['mobile'] != '')
			$applicant_personal_detail_arr['mobile_no'] 			=  trim($form_state['values']['mobile']);
		
		if($form_state['values']['permanent_street'] != '')	
			$applicant_personal_detail_arr['permanent_street']  =  strtoupper(trim($form_state['values']['permanent_street']));
		if($form_state['values']['permanent_city_town_village'] != '')
			$applicant_personal_detail_arr['permanent_city_town_village']  =  strtoupper(trim($form_state['values']['permanent_city_town_village']));
		if($form_state['values']['permanent_post_office'] != '')
			$applicant_personal_detail_arr['permanent_post_office']  =  strtoupper(trim($form_state['values']['permanent_post_office']));
		if($form_state['values']['permanent_district'] != '')
			$applicant_personal_detail_arr['permanent_district']  =  trim($form_state['values']['permanent_district']);
		if($form_state['values']['permanent_pincode'] != '')
			$applicant_personal_detail_arr['permanent_pincode']  =  trim($form_state['values']['permanent_pincode']);
		
		if(($form_state['values']['permanent_street'] != '') && ($form_state['values']['permanent_city_town_village'] != '') && ($form_state['values']['permanent_post_office'] != '') && ($form_state['values']['permanent_district'] != '') && ($form_state['values']['permanent_pincode'] != ''))
			$applicant_personal_detail_arr['permanent_present_same']  =  trim($form_state['values']['chk_permanent_address']);
		
		if(trim($form_state['values']['chk_permanent_address']) != 1) {
			//$applicant_personal_detail_arr['permanent_present_same'] = 0;
			if($form_state['values']['present_street'] != '')
				$applicant_personal_detail_arr['present_street']  =  strtoupper(trim($form_state['values']['present_street']));
			if($form_state['values']['present_city_town_village'] != '')
				$applicant_personal_detail_arr['present_city_town_village']  =  strtoupper(trim($form_state['values']['present_city_town_village']));
			if($form_state['values']['present_post_office'] != '')
				$applicant_personal_detail_arr['present_post_office']  =  strtoupper(trim($form_state['values']['present_post_office']));
			if($form_state['values']['present_district'] != '')
				$applicant_personal_detail_arr['present_district']  =  trim($form_state['values']['present_district']);
			if($form_state['values']['present_pincode'] != '')
				$applicant_personal_detail_arr['present_pincode']  =  trim($form_state['values']['present_pincode']);
		} else {
			$applicant_personal_detail_arr['present_street']  =  NULL;
			$applicant_personal_detail_arr['present_city_town_village']  =  NULL;
			$applicant_personal_detail_arr['present_post_office']  =  NULL;
			$applicant_personal_detail_arr['present_district']  =  NULL;
			$applicant_personal_detail_arr['present_pincode']  =  NULL;	
		}
		
		
		db_insert('housing_applicant')
		->fields($applicant_personal_detail_arr)
		->execute();
		
		/*assign user roles*/
		
		$arr_user_roles = array();
		$arr_user_roles['uid'] = $applicant_personal_detail_arr['uid'];
		$arr_user_roles['rid'] = 4;
		
		db_insert('users_roles')
		->fields($arr_user_roles)
		->execute();
		
		/*add applicant_official_detail  data*/
		$app_off_detail_arr = array();
		$app_off_detail_arr['uid']  =  $data->max_uid;
		if($form_state['values']['hrms_id'] != '')
			$app_off_detail_arr['hrms_id']  =  trim($form_state['values']['hrms_id']);
		
		$app_off_detail_arr['applicant_designation']  =  strtoupper(trim($form_state['values']['app_designation']));
		$app_off_detail_arr['pay_band_id']  =  trim($form_state['values']['pay_band']);
		$app_off_detail_arr['pay_in_the_pay_band']  =  trim($form_state['values']['pay_in']);
		if($form_state['values']['grade_pay'] != '')
			$app_off_detail_arr['grade_pay']  =  trim($form_state['values']['grade_pay']);
		
		/*if($form_state['values']['gpf_no'] != '')
			$app_off_detail_arr['gpf_no']  =  trim($form_state['values']['gpf_no']);*/
		
		$app_off_detail_arr['applicant_posting_place']  =  strtoupper(trim($form_state['values']['app_posting_place']));
		if($form_state['values']['app_headquarter'] != '')
			$app_off_detail_arr['applicant_headquarter']  =  strtoupper(trim($form_state['values']['app_headquarter']));
		
		if($form_state['values']['doj'] != '')
			$app_off_detail_arr['date_of_joining']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['doj']))));
		
		$app_off_detail_arr['date_of_retirement']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['dor']))));
		$app_off_detail_arr['office_name']  =  strtoupper(trim($form_state['values']['office_name']));
		$app_off_detail_arr['office_street']  =  strtoupper(trim($form_state['values']['office_street']));
		$app_off_detail_arr['office_city_town_village']  =  strtoupper(trim($form_state['values']['office_city']));
		if($form_state['values']['office_post_office'] != '')
			$app_off_detail_arr['office_post_office']  =  strtoupper(trim($form_state['values']['office_post_office']));
		
		$app_off_detail_arr['office_district']  =  trim($form_state['values']['office_district']);
		$app_off_detail_arr['office_pin_code']  =  trim($form_state['values']['office_pincode']);
		if($form_state['values']['office_phone_no'] != '')
			$app_off_detail_arr['office_phone_no']  =  trim($form_state['values']['office_phone_no']);
		
		$app_off_detail_arr['ddo_id']  =   trim($form_state['values']['designation']);
		
		
		db_insert('housing_applicant_official_detail')
  	  	->fields($app_off_detail_arr)
  	  	->execute();
		
		/*fetching applicant_official_detail_id*/
		$query1 = db_select('housing_applicant_official_detail', 'haod');
		$query1->addExpression('MAX(applicant_official_detail_id)','id');
		$query1->condition('haod.uid', $data->max_uid, '=');
		$result1 =$query1->execute();
		$data1 = $result1->fetchObject();
		
		/*add online application*/
		
		$online_app_arr = array();
		$online_app_arr['applicant_official_detail_id']  =  $data1->id;
		$online_app_arr['status']  =  'verified';
		$online_app_arr['date_of_application']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['doa']))));
		$online_app_arr['is_backlog_applicant']  =  1;
		$online_app_arr['computer_serial_no']  =  $form_state['values']['computer_serial_no'];
		if($form_state['values']['remarks'] != '')
			$online_app_arr['remarks'] = $form_state['values']['remarks'];
				
				
		db_insert('housing_online_application')
		->fields($online_app_arr)
		->execute();
		
		/*fetching online_application_id*/
		$query2 = db_select('housing_online_application', 'hoa');
		$query2->addExpression('MAX(online_application_id)','oid');
		$query2->condition('hoa.applicant_official_detail_id', $data1->id, '=');
		$result2 =$query2->execute();
		$data2 = $result2->fetchObject();
		
		$online_app_arr_upd = array();
		$online_app_arr_upd['application_no']  = 'NA-'.trim( implode(explode('/', $form_state['values']['doa']))).'-'.$data2->oid;
			
		db_update('housing_online_application')
		->fields($online_app_arr_upd)
		->condition('online_application_id', $data2->oid)
		->execute();
		
		/* add new alltment application*/  
		$new_allotment_app_arr = array();
		$new_allotment_app_arr['online_application_id']  =  $data2->oid;
		
		$new_allotment_app_arr['flat_type_id'] = fetch_rhe_flat_id(trim($form_state['values']['rhe_flat_type']));
		$new_allotment_app_arr['allotment_category']  =  trim($form_state['values']['reason']);
		
		db_insert('housing_new_allotment_application')
  	  	->fields($new_allotment_app_arr)
  	  	->execute();
		
		drupal_set_message('Data inserted successfully.');
	}