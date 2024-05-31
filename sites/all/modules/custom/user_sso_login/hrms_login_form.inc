<?php
function hrms_login_form($form, &$form_state) {
    if(!user_is_logged_in()) {
        $form['name'] = array(
            '#type' => 'item',
            '#prefix' => '<div id="hrms" class="login-panel">',
            '#suffix' => '</div>',
        );
        $form['name']['hrms_id'] = array(
            '#type' => 'textfield',
            '#required' => TRUE,	
            '#title' => t('Enter HRMS Id'),
        );
        $form['name']['submit'] = array(
            '#type' => 'submit',
            '#value' => 'Login with HRMS',
        );
        $form['name']['rhe_user_login'] = array(
            '#type'    => 'link',    
            '#title'   => t('Click here for Housing users login'),    
            '#href'  => '/user/login',
            '#attributes' => array('class' => 'user-login-links'),
        
          );
        return $form;
    } else {
        drupal_goto('/user');
    }
    
}

function hrms_login_form_submit($form, &$form_state) {
    if(isset($form_state['values']['hrms_id']) && !empty($form_state['values']['hrms_id'])) {
        $hrms_id = base64_encode(trim($form_state['values']['hrms_id']));
        
        drupal_goto('/user/sso/' . $hrms_id);

    }
}
?>