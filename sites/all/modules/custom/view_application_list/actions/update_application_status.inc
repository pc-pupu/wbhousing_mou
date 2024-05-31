<?php
function update_application_status($app_id = NULL, $status = NULL, $page = 0)
{
    global $user, $user_role;
    if (!empty($app_id)) {
        $app_id = decrypt_url($app_id);
        $transaction    = db_transaction();
        try {
            $query = db_select("housing_online_application", "t1");
            $query->join('housing_allotment_status_master', 't2', 't1.status = t2.short_code');
            $query->fields('t1', array(
                'online_application_id',
                'application_no'
            ));
            $query->fields('t2');
           
            $query->condition('t1.online_application_id', $app_id);

            if ($status == '1') {
                $approvalChar = 'Approved';
            } else {
                $approvalChar = 'Rejected';
            }
            
            
            $dataArray = array(
                'status' => $approval_status,
                'date_of_verified' => date("Y-m-d")
            );
            $result = $query->execute()->fetchObject();
            
            if (!empty($result)) {
                if ($user_role == 10 && $result->status_id == 2) {
                    if ($status == '1') {
                        $approval_status = 'housing_official_approved';
                        $statusID = 7;
                    } else {
                        $approval_status = 'housing_official_reject';
                        $statusID = 8;
                    }
                    db_update('housing_online_application')
                    ->fields(array(
                        'status' => $approval_status,
                        'date_of_verified' => date("Y-m-d")
                    ))
                    ->condition('online_application_id',$app_id, '=')
                    ->execute();
                    $housingProcessFlowData = housingProcessFlowAdd($statusID, $app_id);
                    drupal_set_message(t('Application No:'.$result->application_no . " successfully ".$approvalChar."."));
                    
                } else if ($user_role == 11 && $result->status_id == 1) {
                    if ($status == '1') {
                        $approval_status = 'ddo_verified_1';
                        $statusID = 2;
                    } else {
                        $approval_status = 'ddo_reject_1';
                        $statusID = 3;
                    }
                    db_update('housing_online_application')
                    ->fields(array(
                        'status' => $approval_status,
                        'date_of_verified' => date("Y-m-d")
                    ))
                    ->condition('online_application_id',$app_id, '=')
                    ->execute();
                    $housingProcessFlowData = housingProcessFlowAdd($statusID, $app_id);
                    drupal_set_message(t('Application No:'.$result->application_no . " successfully ".$approvalChar."."));
                    
                }
                else{
                    drupal_set_message(t("Invaild Request for update."), 'error');
                }
            } else {
                drupal_set_message(t("Invaild Online Application Data."), 'error');
            }
        }
        catch (Exception $e) {
            $transaction->rollback();
            watchdog_exception('view_application_list', $e);
            drupal_set_message(t($e), 'error');
        }
        
    } else {
        drupal_set_message(t("Error: Invaild Online Application Data Not found."), 'error');
    }
    
    $options = array();
    if ($page > 0) {
        $options = array(
            'query' => array(
                'page' => $page
            )
        );
    }
    drupal_goto('application-details-list', $options);
}