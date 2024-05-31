<?php

function download_and_upload($form, &$form_state, $online_application_id = ''){
    global $base_path;

    $form['markup_application'] = array(
        '#type' => 'markup',
        '#markup' => '<br><div class="row" style="padding-right:20px;">'.l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'application_of_registration_list').'/images/download_icon.png" title="Download Application Form" alt="PDF Icon"> Download Application Form ', 'form-of-application/'.$online_application_id, array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'</div><br>'
    );


    

    $form['markup_declaration'] = array(
        '#type' => 'markup',
        '#markup' => '<br><div class="row" style="padding-right:20px;">'.l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'application_of_registration_list').'/images/download_icon.png" title="Download Declaration" alt="PDF Icon"> Download Declaration ', 'generate-declaration/'.$online_application_id, array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'</div><br>'

        
    );

    $form['applicant_data_file'] = array(
        '#title' => t('Upload Applicant Signed Data'),
        '#type' => 'managed_file',
        '#description' => t('Allowed extensions: pdf'),
        '#progress_message' => t('Please wait...'),
        '#progress_indicator' => 'bar',
        '#default_value' => variable_get('Upload File', ''),
        '#upload_validators' => array(
                                        'file_validate_extensions' => array("pdf"),
                                        // 'file_validated_size' => array(MAX_FILE_SIZE*1024*1024),
                                        'file_validated_size' => array(2*1024*1024),
                                     ),
        '#upload_location' => 'public://doc/tmp/',
        '#required' => TRUE,
        '#process' => array('download_and_upload_element_process'),
    );
    
    // $form['#attributes'] = array('onsubmit' => 'return validate_applicant_data_upload_form()');
    
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Upload Signed Documents'),
    );
    
    return $form;
    
}

function download_and_upload_element_process($element, &$form_state, $form) {
    $element = file_managed_file_process($element, $form_state, $form);
    $element['upload_button']['#access'] = FALSE;
    return $element;
}


function download_and_upload_submit($form, &$form_state) {
    global $user;
    if (!empty($form_state['values']['applicant_data_file'])) {
        // Load the file object.
        $file = file_load($form_state['values']['applicant_data_file']);
        
        // Define the dynamic directory path.
        $dynamic_folder = 'public://doc/'. $user->uid;
        
        // Ensure the directory exists and is writable.
        file_prepare_directory($dynamic_folder, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
        
        // Move the uploaded file to the dynamic directory.
        $destination = $dynamic_folder . '/' . time().$file->filename;
        $file = file_copy($file, $destination, FILE_EXISTS_REPLACE);
        
        // Set the file status to permanent.
        $file->status = FILE_STATUS_PERMANENT;
        // Save the file.
        file_save($file);
        
        // If you want to keep a reference to the file, save the file ID (fid).
        $fid = $file->fid;
        // Save the fid to your custom table or perform other operations.
        



        drupal_set_message(t('The doc has been uploaded successfully.'));
    }
}


