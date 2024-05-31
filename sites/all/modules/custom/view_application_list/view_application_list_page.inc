<?php

function view_app_page($status='', $entity = '',$page_status='') {
	//echo $page_status;
	global $user_role;
	$status = decrypt_url($status);
	$entity = decrypt_url($entity);
	//echo $status,$entity;
	$output = '';
	$rows =array();
	$header = array();
	$statusMsg ='';
	
	if($status !== '' && $entity !== '' && preg_match("/^[a-zA-Z0-9\-\_]*$/",$status) && preg_match("/^[a-zA-Z0-9\-\_]*$/",$entity)){
		if($status == 'applied'){
			$statusMsg = 'New ';
		}else if($status == 'ddo_verified_1'){
			$statusMsg = 'DDO Verified ';
		}
		else if($status == 'verified'){
			$statusMsg = 'Verified ';
		}
		else if($status == 'reject'){
			$statusMsg = 'Rejected ';
		}
		
		if($entity == 'new-apply'){
			$entityMsg = 'New Allotment ';
		}
		else if($entity == 'vs'){
			$entityMsg = 'Vertical Shifting ';
		}
		else if($entity == 'cs'){
			$entityMsg = 'Category Shifting ';
		}
		else if($entity == 'new_license'){
			$entityMsg = 'New Licence ';
		}
		
		//new code
		else if($entity == 'vs_licence'){
			$entityMsg = 'VS Licence ';
		}
		else if($entity == 'cs_licence'){
			$entityMsg = 'CS Licence ';
		}
		//
		
		else if($entity == 'renew_license'){
			$entityMsg = 'Renew Licence ';
		}
			
		drupal_set_title($statusMsg.'Application List for '.$entityMsg);
			
		
		// $result = fetch_all_application_detail1($entity,$status);
		$result = application_list_fetch($entity,$status);

		// echo "<pre>";print_r($result);die;


		$header = array(
			'applicant_name' => array(
				'data' => 'Name'
			) ,
			'application_no' => array(
				'data' => 'Application No.',
				'width'=>'20%'
			) 
		);
		
		
		// if($status == 'applied' || $status == 'ddo_verified_1' || $status == 'housing_sup_approved_1' || $status == 'housing_official_approved'){
		// 	$header['date_of_application'] = array('data' => 'Date of Application');
		// }
		//$header[] = array('data' => 'Time of Application');
		
		if($entity == 'new-apply'){//echo $status;
			if($page_status == 'verified-list'|| $page_status=='reject-list'){
				$header['date_of_application'] = array('data' => 'Date of Application');
				$header['flat_type'] = array('data' => 'Flat Type');
				$header['allotment_category'] = array('data' => 'Allotment Reason');
				$header['computer_serial_no'] = array('data' => 'Computer Serial No');
				$header['view'] = array('data' => 'View');
				

			}else{
				$header['date_of_application'] = array('data' => 'Date of Application');
				$header['flat_type'] = array('data' => 'Flat Type');
				$header['allotment_category'] = array('data' => 'Allotment Reason');
				$header['computer_serial_no'] = array('data' => 'Computer Serial No');
				$header['view'] = array('data' => 'View');
				$header['action'] = array('data' => 'Action', 'width'=>'20%');
			}
			/*if($status=='applied'||$status=='ddo_verified_1'||$status=='housing_sup_approved_1'||$status=='alloted'||$status=='applicant_acceptance'||$status=='ddo_verified_2'){
				// echo"i am here";echo $status;
				$header['date_of_application'] = array('data' => 'Date of Application');
				$header['flat_type'] = array('data' => 'Flat Type');
				$header['allotment_category'] = array('data' => 'Allotment Reason');
				$header['computer_serial_no'] = array('data' => 'Computer Serial No');
				$header['view'] = array('data' => 'View');
				$header['action'] = array('data' => 'Action', 'width'=>'20%');
			}else{
				// echo"i am in else";
				$header['date_of_application'] = array('data' => 'Date of Application');
				$header['flat_type'] = array('data' => 'Flat Type');
				$header['allotment_category'] = array('data' => 'Allotment Reason');
				$header['computer_serial_no'] = array('data' => 'Computer Serial No');
				$header['view'] = array('data' => 'View');
			}
			*/
			
		}
		else if($status == 'reject'){
			$header[] = array('data' => 'Reject Date');
		}
		//$header[] = array('data' => 'View');
		
	
		 while($data = $result->fetchObject()) {


			//echo json_encode($data);//die;
			$fields = array();
			if($entity == 'new-apply'){
				//echo $page_status;

				if($page_status == 'verified-list'|| $page_status == 'reject-list'){

					$fields[] = $data->applicant_name;
					$fields[] = $data->application_no;
					$fields[] = implode('/', array_reverse(explode('-', $data->date_of_application)));
					$fields[] = $data->flat_type;
					$fields[] = $data->allotment_category;
					$fields[] = $data->computer_serial_no;
					global $base_path;
			 		$src=$base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
					$fields[] = l(
									'<img src="'.$src.'" alt="View Icon">',
									'application_detail/'.encrypt_url($data->online_application_id), 
									array(
											'html'=>TRUE,
											'attributes'=> array('target' => '_blank'),
									)
								);
					
				}else{

					$fields[] = $data->applicant_name;
					$fields[] = $data->application_no;
					$fields[] = implode('/', array_reverse(explode('-', $data->date_of_application)));
					$fields[] = $data->flat_type;
					$fields[] = $data->allotment_category;
					$fields[] = $data->computer_serial_no;
					global $base_path;
			 		$src=$base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
					$fields[] = l(
									'<img src="'.$src.'" alt="View Icon">',
									'application_detail/'.encrypt_url($data->online_application_id), 
									array(
											'html'=>TRUE,
											'attributes'=> array('target' => '_blank'),
									)
								);

					if($status == 'applied') {
						$update_status = 'ddo_verified_1';
					}else if($status == 'ddo_verified_1'){
						$update_status = 'housing_sup_approved_1';
					}else if($status == 'alloted'){
						//echo 'hg';die;
						$update_status = 'housing_official_approved';
					}

					
					$onclick="return confirm('Are you sure you want to approve?')";
					$onclick1="return confirm('Are you sure you want to reject?')";
					$fields[] = l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'view_application_list').'/images/accept_icon.png" title="Approve" 
					alt="Accept Icon" alt="Accept Icon">Approve' , 'application-approve/'.encrypt_url($data->online_application_id).'/'.encrypt_url($update_status).'/'.encrypt_url($status).'/
					'.encrypt_url($entity), array('html'=>TRUE, 'attributes' => array('onclick' => $onclick, 'style' => 'color: #0090C7;font-weight: 400;text-decoration: underline; 
					font-size:14px'))).' &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <br><br>'.l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'view_application_list'
					).'/images/reject_icon.png" title="Reject" alt="Reject Icon">Reject' ,  'update_status/'.encrypt_url($data->online_application_id).'/'.encrypt_url('reject').'/'.
					encrypt_url($status).'/'.encrypt_url($entity), array('html'=>TRUE, 'attributes' => array('onclick' => $onclick1, 'style' => 'color: #0090C7;font-weight: 
					400;text-decoration: underline; font-size:14px')));		
				}
			}
				
			$rows[] = $fields;
			  // if()
			  // echo "<pre>";print_r($rows[0][6]);die;
		 }
		
		/*$output = theme_table(
			array(
			  'header' => $header,
			  'rows' => $rows,
			  'attributes' => array(),
			  'sticky' => true,
			  'caption' => '',
			  'colgroups' => array(),
			  'empty' => t("No data found!") // The message to be displayed if table is empty
			)
	  	).theme('pager');*/
		
		if(count($rows) > 0) {
			// Render using Drupal's render API.
			$build['datatable'] = array(
			  '#theme' => 'datatable',
			  '#header' => $header,
			  '#rows' => $rows,
			  '#attributes' => array(),
			);
			
			// Or, render using a theme function.
			$variables = array(
			  'attributes' => array(),
			  'header' => $header,
			  'rows' => $rows,
			);
			
			$output = theme('datatable', $variables);
		}
		else {
			$output = '<div>
							<table class="datatable_no_data_found">
								<tr class="tr_no_data_found">
									<th class="th_no_data_found"></th>
								</tr>
								<tr class="tr_no_data_found">
									<td class="td_no_data_found">No data found!</td>
								</tr>
							</table>
						</div>';
		}
	}
	return $output;
}

