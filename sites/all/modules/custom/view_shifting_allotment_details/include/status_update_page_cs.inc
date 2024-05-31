<?php

	function status_update_page_cs($online_application_id = '', $status = '') {
		$online_id = decrypt_url($online_application_id);
		$accept_reject_status = decrypt_url($status);
		
		$result = fetch_cs_allotment_details();
		$data = $result->fetchObject();
		
		if($accept_reject_status == 'Accept') {
			
			db_update('housing_flat_occupant')
			->fields(array('accept_reject_status' => 'Accept'))
			->condition('online_application_id', $online_id, '=')
			->execute();
			
			drupal_set_message('You accept the allotment.');
			drupal_goto('view_cs_allotment_details');
		}
		else if($accept_reject_status == 'Reject'){
			
			/*$reject_offer_arr = array();
			$reject_offer_arr['status']  = 'reject_offer';
			$reject_offer_arr['online_application_id']  = $online_id;
		
			db_update('housing_online_application')
			->fields($reject_offer_arr)
			->condition('online_application_id', $reject_offer_arr['online_application_id'])
			->execute();*/
			
			db_update('housing_flat')
			->fields(array('flat_status_id' => 1))
			->condition('flat_id', $data->flat_id, '=')
			->execute();
			
			//actual old flat
			/*db_update('housing_flat')
			->fields(array('flat_status_id' => 2))
			->condition('flat_id', $data->occupation_flat, '=')
			->execute();*/
			
			db_update('housing_flat_occupant')
			->fields(array('accept_reject_status' => 'Reject'))
			->condition('online_application_id', $online_id, '=')
			->execute();
			
			//db_query('update housing_flat set flat_status_id = 1 where flat_id = '.$data->flat_id);	
			drupal_set_message('You reject the allotment.');
			drupal_goto('view_cs_allotment_details');
		}
	}