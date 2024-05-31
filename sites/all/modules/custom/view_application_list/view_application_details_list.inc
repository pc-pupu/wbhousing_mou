<?php
function view_application_details()
{
    //$build['search_form'] = drupal_get_form('application_search_form');
    $build['details_form'] = drupal_get_form('application_list_form');
    return $build;
}


function application_list_form($form, &$form_state)
{
    global $user_dist_code;
    global $user_block_code;
    global $user_role;
    global $base_path;

    $page = isset($_GET['page']) && !empty($_GET['page']) ? trim($_GET['page']) : 0;

    /*Logo Links*/
    $view = $base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
    $approveLogo = $base_path . drupal_get_path('module', 'view_application_list') . '/images/accept_icon.png';
    $rejectLogo = $base_path . drupal_get_path('module', 'view_application_list') . '/images/reject_icon.png';
    $onclick="return confirm('Are you sure you want to approve?')";
    $onclick1="return confirm('Are you sure you want to reject?')";

    ctools_include('modal');
    ctools_modal_add_js();

    ctools_include('ajax');
    ctools_add_js('ajax-responder');

    $header = array(
        'slno' => array(
            'data' => 'Sl. No.'
        ),
        'applicant_name' => array(
            'data' => 'Name'
        ),
        'application_no' => array(
            'data' => 'Application No.',
            //'width'=>'20%'
        ),
        'date_of_application' => array(
            'data' => 'Date of Application',
            //'width'=>'20%'
        ),
        'status' => array(
            'data' => 'Status'
        ),
        'action' => array(
            'data' => 'Action'
        )
    );

    $result = applicationListData();

    // Looping for filling the table rows
    $rows = array();
    $row_count = 0;
    while ($data = $result->fetchObject())
    {
       
        //echo $user_role;
        //print_r($data);
        //exit();
        $operation_link = NULL;
        $viewStatusFlow = l($data->status_description, 'status-flow-page/nojs/' . encrypt_url($data->online_application_id) , array(
            'html' => true,
            'attributes' => array(
                'class' => 'ctools-use-modal'
            )
        ));
        
        
        $viewApplication = l(
            '<img src="'.$view.'" alt="View Icon">',
            'application_detail/'.encrypt_url($data->online_application_id), 
            array(
                    'html'=>TRUE,
                    'attributes'=> array('target' => '_blank'),
            )
        );
        $operation_link .= $viewApplication;
        
        /*Action For Housing Supervisor & Action For Housing DDO*/
        if (($user_role == 10 && $data->status_id == 2) || ($user_role == 11 && $data->status_id == 1)) {
            $approvalAction = l('<img src="' . $approveLogo . '" width="20" height="20" title="Approve">', "update-application-status/" . encrypt_url($data->online_application_id) . '/1/' . $page, array(
                'html' => true,
                'attributes' => array(
                    'edit' => 'Edit',
                    'onclick' => 'return confirm("Are you sure to approve this Application (' . $data->application_no . ')? You will not be able to revert this change.")'
                )
            ));

            $rejectAction = l('<img src="' . $rejectLogo . '" width="20" height="20" title="Reject">', "update-application-status/" . encrypt_url($data->online_application_id) . '/0/' . $page, array(
                'html' => true,
                'attributes' => array(
                    'edit' => 'Edit',
                    'onclick' => 'return confirm("Are you sure to reject this Application (' . $data->application_no . ')? You will not be able to revert this change.")'
                )
            ));
            $operation_link .= ' | '.$approvalAction . '|'. $rejectAction;
        }
        /*Action For Housing Supervisor END & Action For Housing DDO*/
        
        $row_count++;
        $rows[$data->online_application_id] = array(
            'data' => array(
                'slno' => $row_count,
                'applicant_name' => $data->applicant_name,
                'application_no' => $data->application_no,
                'date_of_application' => $data->date_of_application,
                'status' => $viewStatusFlow,
                'action' => '<div style="white-space:nowrap;">' . $operation_link . '</div>'
            ),
        );       
    }


   
    $html = theme('datatable', array(
        'header' => $header,
        'rows' => $rows,
        'caption' => '',
        'sticky' => true,
        'empty' => 'No data found!',
        'attributes' => array(
            'style' => ''
        )
    ));

    $form['table'] = array(
        '#markup' => $html
    );

    return $form;
}


function applicationListData(){
    global $user, $user_role;
        
    $query = db_select('housing_applicant_official_detail', 'haod');
    $query->innerJoin('housing_applicant', 'ha','ha.uid = haod.uid');
    $query->innerJoin('housing_online_application', 'hoa', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
    //$query->innerJoin('housing_process_flow', 't1', 'hoa.online_application_id = t1.online_application_id');
    $query->innerJoin('housing_allotment_status_master', 't2', 'hoa.status = t2.short_code');
    $query->innerJoin('housing_ddo', 'hd', 'hd.ddo_id = haod.ddo_id');
    $query->innerJoin('housing_pay_band', 'hpb', 'hpb.pay_band_id = haod.pay_band_id');
    $query->leftJoin('file_managed', 'fm_app_form', 'fm_app_form.fid = hoa.uploaded_app_form');
        
        /*if($entity == 'new-apply'){ 
            $query->innerJoin('housing_new_allotment_application', 'hna',
            'hna.online_application_id = hoa.online_application_id');
            $query->innerJoin('housing_flat_type', 'hft',
            'hna.flat_type_id = hft.flat_type_id');
            
            $query->leftJoin('file_managed', 'fm',
            'fm.fid = hna.document');
            $query->leftJoin('file_managed', 'fm1',
            'fm1.fid = hna.extra_doc');
            $query->leftJoin('file_managed', 'fm2',
            'fm2.fid = hna.scaned_sign');
        }
        else if($entity == 'vs'){
            $query->innerJoin('housing_vs_application', 'hva',
            'hva.online_application_id = hoa.online_application_id');
            
            $query->leftJoin('file_managed', 'fm_vs',
            'fm_vs.fid = hva.file_licence');
        }
        else if($entity == 'cs'){
            $query->innerJoin('housing_cs_application', 'hca',
            'hca.online_application_id = hoa.online_application_id');
            
            $query->leftJoin('file_managed', 'fm_cs',
            'fm_cs.fid = hca.file_licence');
        }
        else if($entity == 'new_license' || $entity == 'renew_license'){
            $query->innerJoin('housing_license_application', 'hla',
            'hla.online_application_id = hoa.online_application_id');
            
            $query->leftJoin('file_managed', 'fm_licence',
            'fm_licence.fid = hla.document');
        }
        
        //new code
        else if($entity == 'vs_licence' || $entity == 'cs_licence'){
            $query->innerJoin('housing_license_application', 'hla',
            'hla.online_application_id = hoa.online_application_id');
            
            $query->leftJoin('file_managed', 'fm_licence',
            'fm_licence.fid = hla.document');
        }*/
        //
        
        /*if($entity == 'new-apply'){
            $query->addField('hft', 'flat_type_id');
        }*/
        $query->fields('ha', array(
            'applicant_name'
        ));
        $query->fields('t2', array(
            'status_description',
            'status_id',
        ));
        $query->fields('hoa', array(
            'online_application_id',
            'application_no',
            'date_of_application',
        ));
        $query->fields('hd', array(
            'district_code',
            'ddo_designation',
            'ddo_address',
        ));
        $query->fields('haod');
        /*$query->fields('haod', array(
            'applicant_designation',
            'applicant_headquarter',
            'applicant_posting_place',
        ));*/
       
      /*  $query->addField('hpb', 'payband');
        $query->addField('hpb', 'scale_from');
        $query->addField('hpb', 'scale_to');
       
        $query->addField('hoa', 'status');
        $query->addField('hoa', 'date_of_verified');
        $query->addField('hoa', 'computer_serial_no');
        
        $query->addField('hoa', 'is_backlog_applicant');
        $query->addField('hoa', 'computer_serial_no');
        $query->addField('hoa', 'uploaded_app_form');
        $query->addField('fm_app_form', 'uri', 'uri_app_form');*/
        
        /*if($entity == 'new-apply'){
            $query->addField('hna', 'allotment_category');
            $query->addField('hft', 'flat_type');
            $query->addField('fm', 'uri', 'uri_doc');
            $query->addField('fm2', 'uri', 'uri_scaned_sign');
            $query->addField('fm1', 'uri', 'uri_extra_doc');
        }
        else if($entity == 'vs'){
            $query->addField('hva', 'allotment_category');
            $query->addField('fm_vs', 'uri', 'uri_vs');
        }
        else if($entity == 'cs'){
            $query->addField('hca', 'allotment_category');
            $query->addField('fm_cs', 'uri', 'uri_cs');
        }
        else if($entity == 'new_license' || $entity == 'vs_licence' || $entity == 'cs_licence' || $entity == 'renew_license'){
            $query->addField('fm_licence', 'uri', 'uri_licence');
        }

        if($user_role == 11){           // ddo user
            $query->condition('hoa.status', 'applied', '=');
        }else if($user_role == 10){   // Housing Supervisor
            $query->condition('hoa.status', 'ddo_verified_1', '=');  
        }else if($user_role == 6){      // Housing Official
            $query->condition('hoa.status', 'housing_sup_approved_1', '=');
        }*/
        
        
        
       /* if($entity == 'new-apply'){
            $query->orderBy('to_number(hoa.computer_serial_no, text(9999999999))', 'ASC');
            $query->orderBy('hoa.computer_serial_no','ASC');
        }
        
        if($entity == 'vs' || $entity == 'cs' || $entity == 'new_license' || $entity == 'vs_licence' || $entity == 'cs_licence' || $entity == 'renew_license'){
            $query->orderBy('online_application_id','ASC');
        }*/
        
        //echo $query;die;
        //$query = $query->extend('PagerDefault')->limit(10);
        return $query->execute();
}