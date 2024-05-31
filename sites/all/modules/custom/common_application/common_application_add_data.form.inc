 <?php
   
   function update_user_data($form, &$form_state){
   	/*update user table data*/
	    global $user;
		$user_arr = array();
		$user_arr['mail']  =  strtolower(trim($form_state['values']['email']));
		db_update('users')
		  ->fields($user_arr)
		  ->condition('uid', $user->uid, '=')
		  ->execute();
   }

   function update_applicant_personal_detail($form, &$form_state){
   		/*update housing_applicant table data*/ 
		
		global $user;
		
		$applicant_personal_detail_arr = array();
		$applicant_personal_detail_arr['applicant_name']  =  strtoupper(trim($form_state['values']['applicant_name']));
		$applicant_personal_detail_arr['guardian_name']  =  strtoupper(trim($form_state['values']['applicant_father_name']));
		$applicant_personal_detail_arr['gender']  =  trim($form_state['values']['gender']);
		$applicant_personal_detail_arr['date_of_birth']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['dob']))));
		$applicant_personal_detail_arr['mobile_no']  =  trim($form_state['values']['mobile']);
		
		$applicant_personal_detail_arr['permanent_street']  =  strtoupper(trim($form_state['values']['permanent_street']));
		$applicant_personal_detail_arr['permanent_city_town_village']  =  strtoupper(trim($form_state['values']['permanent_city_town_village']));
		$applicant_personal_detail_arr['permanent_post_office']  =  strtoupper(trim($form_state['values']['permanent_post_office']));
		$applicant_personal_detail_arr['permanent_district']  =  trim($form_state['values']['permanent_district']);
		$applicant_personal_detail_arr['permanent_pincode']  =  trim($form_state['values']['permanent_pincode']);
		
		$applicant_personal_detail_arr['permanent_present_same']  =  trim($form_state['values']['chk_permanent_address']);
		
		if(trim($form_state['values']['chk_permanent_address']) != 1) {
			//$applicant_personal_detail_arr['permanent_present_same'] = 0;
			$applicant_personal_detail_arr['present_street']  =  strtoupper(trim($form_state['values']['present_street']));
			$applicant_personal_detail_arr['present_city_town_village']  =  strtoupper(trim($form_state['values']['present_city_town_village']));
			$applicant_personal_detail_arr['present_post_office']  =  strtoupper(trim($form_state['values']['present_post_office']));
			$applicant_personal_detail_arr['present_district']  =  trim($form_state['values']['present_district']);
			$applicant_personal_detail_arr['present_pincode']  =  trim($form_state['values']['present_pincode']);
		} else {
			$applicant_personal_detail_arr['present_street']  =  NULL;
			$applicant_personal_detail_arr['present_city_town_village']  =  NULL;
			$applicant_personal_detail_arr['present_post_office']  =  NULL;
			$applicant_personal_detail_arr['present_district']  =  NULL;
			$applicant_personal_detail_arr['present_pincode']  =  NULL;	
		}
		
		/*echo '<pre>';
		print_r($applicant_personal_detail_arr);
		die();*/
		
		update_user_data($form, $form_state);
		db_update('housing_applicant')
		  ->fields($applicant_personal_detail_arr)
		  ->condition('uid', $user->uid, '=')
		  ->execute();
		
   }
    function add_applicant_official_detail($form, &$form_state, $app_type){
		
		global $user;
		
		/*echo '<pre>';
		print_r($app_off_detail_arr); die();*/
		
		/*if(trim($app_type) == 'NL' || trim($app_type) == 'VS' || trim($app_type) == 'VSL' || trim($app_type) == 'CS' || trim($app_type) == 'CSL') {
			db_insert
		} else if(trim($app_type) == 'NA') {
			update_applicant_official_detail	
		}*/
		
		$query1 = db_select('housing_applicant_official_detail', 'haod');
		$query1->innerJoin('housing_online_application', 'hoa', 'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
		$query1->addfield('haod', 'uid');
		$query1->condition('haod.uid', $user->uid, '=');
		$result1 = $query1->execute();
		if($result1->rowCount() > 0) {
		//echo "kjh";die;
			/*add applicant_official_detail data*/
			$app_off_detail_arr = array();
			$app_off_detail_arr['uid']  =  $user->uid;
			$app_off_detail_arr['ddo_id']  =   trim($form_state['values']['designation']);
			$app_off_detail_arr['hrms_id']  =  trim($form_state['values']['hrms_id']);
			$app_off_detail_arr['applicant_designation']  =  strtoupper(trim($form_state['values']['app_designation']));
			$app_off_detail_arr['applicant_headquarter']  =  strtoupper(trim($form_state['values']['app_headquarter']));
			$app_off_detail_arr['applicant_posting_place']  =  strtoupper(trim($form_state['values']['app_posting_place']));
			$app_off_detail_arr['pay_band_id']  =  trim($form_state['values']['pay_band']);
			$app_off_detail_arr['pay_in_the_pay_band']  =  trim($form_state['values']['pay_in']);
			//$app_off_detail_arr['grade_pay']  =  trim($form_state['values']['grade_pay']);
			//$app_off_detail_arr['gpf_no']  =  strtoupper(trim($form_state['values']['gpf_no']));
			
			$app_off_detail_arr['date_of_joining']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['doj']))));
			$app_off_detail_arr['date_of_retirement']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['dor']))));
			$app_off_detail_arr['office_name']  =  strtoupper(trim($form_state['values']['office_name']));
			$app_off_detail_arr['office_street']  =  strtoupper(trim($form_state['values']['office_street']));
			$app_off_detail_arr['office_city_town_village']  =  strtoupper(trim($form_state['values']['office_city']));
			$app_off_detail_arr['office_post_office']  =  strtoupper(trim($form_state['values']['office_post_office']));
			$app_off_detail_arr['office_pin_code']  =  trim($form_state['values']['office_pincode']);
			$app_off_detail_arr['office_district']  =  trim($form_state['values']['office_district']);
			$app_off_detail_arr['office_phone_no']  =  trim($form_state['values']['office_phone_no']);
			//echo "<pre>";print_r($app_off_detail_arr);die;
			db_insert('housing_applicant_official_detail')
			->fields($app_off_detail_arr)
			->execute();
			
			/*fetching applicant_official_detail_id*/
			$query = db_select('housing_applicant_official_detail', 'haod');
			$query->addExpression('MAX(applicant_official_detail_id)','id');
			$query->condition('haod.uid', $user->uid, '=');
			$result =$query->execute();
			$data = $result->fetchObject();
			
			return $data->id;	
			
		} else {
			/*fetching applicant_official_detail_id*/
			$query = db_select('housing_applicant_official_detail', 'haod');
			$query->addExpression('MAX(applicant_official_detail_id)','id');
			$query->condition('haod.uid', $user->uid, '=');
			$result =$query->execute();
			$data = $result->fetchObject();
			
			update_applicant_official_detail($form, $form_state, $data->id);
			
			return $data->id;	
			
		}
		
   }
   
   /*add into housing_online_application*/
   function add_online_application($status,$app_type,$form,&$form_state){
	   	
		update_applicant_personal_detail($form, $form_state);
		
		global $user;
		
		//insertion of computer serial no continuation of existing applicant's computer serial no
		
		$result = db_query("select max(to_number(computer_serial_no, text(9999999999))) as no from housing_online_application 
							where substring(application_no, 1, 2) = :app_no and computer_serial_no is not null", 
							array(':app_no' => 'NA'));
		$data = $result->fetchObject();
		$comp_serial_no = $data->no + 1;
		
		/*add online application*/
		
		$online_app_arr = array();
		$applicant_official_detail_id = add_applicant_official_detail($form, $form_state, $app_type);
		$online_app_arr['applicant_official_detail_id']  =  $applicant_official_detail_id;
		$online_app_arr['status']  =  trim($status);
		
		$online_app_arr['application_no'] = $app_type;
		
		if($app_type == 'NA' && $comp_serial_no != '') {
			$online_app_arr['computer_serial_no'] = $comp_serial_no;
		}		
				
		db_insert('housing_online_application')
		->fields($online_app_arr)
		->execute();

		/*fetching online application id*/
		return max_online_application_id(array('reject','cancel'));
		
   }

   
  
  


