<?php
/**
 * Callback function for Popup page.
 */
function view_status_flow_page($js, $app_id)
{
    
    $output = application_status_flow_details($app_id);
    
    if ($js) {
        // Required includes for ctools to work:
        ctools_include('modal');
        ctools_include('ajax');
        return ctools_modal_render("Application Status Flow Details", $output);
    }
    return $output;
}

function application_status_flow_details($app_id = NULL)
{
    global $base_url;
    $app_id = decrypt_url($app_id);

    $query = db_select("housing_online_application", "hoa");
    $query->innerJoin('housing_process_flow', 't1', 'hoa.online_application_id = t1.online_application_id');
    $query->innerJoin('housing_allotment_status_master', 't2', 't1.status_id = t2.status_id');
    $query->innerJoin('users', 't3', 't1.uid = t3.uid');
    
   
    
    // Adding fields
    $query->fields('t1');
    $query->fields('t2');
    $query->fields('t3', array(
        'name'
    ));
    $query->fields('hoa', array(
        'application_no',
        'online_application_id'
    ));
    $query->fields('t2', array(
        'status_description',
    ));
    
    $query->orderBy('t1.id', 'DESC');
    
    $query->condition('hoa.online_application_id', $app_id);
    
    // Executing query
    $result = $query->execute();
    
    $sl_no      = 0;
    $varLastRow = NULL;
    $header     = array(
        'slno' => array(
            'data' => 'Sl. No.'
        ),
        'status_description' => array(
            'data' => 'Status'
        ),
        'name' => array(
            'data' => 'User'
        ),
        'created_at' => array(
            'data' => 'Date'
        )
    );
    $rows       = array();
    while ($data = $result->fetchObject()) {
        //print_r($data);
        $varLastRow = $data;
        $sl_no++;
        $rows[$data->id] = array(
            'slno' => $sl_no,
            'status_description' => ucfirst($data->status_description),
            'name' => $data->name,
            'created_at' => $data->created_at
        );
    }
    
    $status_flow = theme('table', array(
        'header' => $header,
        'rows' => $rows,
        'caption' => '',
        'sticky' => TRUE,
        'empty' => 'No data found!',
        'attributes' => array(
            /*'width' => "50%",
            'align' => "center"*/
        )
    ));
    
    $data = $varLastRow;

   $htmlOP = '<div id="DivToPrintChallan">
   <h1> Application No: '.$data->application_no.' </h1>
   <div>'.$status_flow.'</div>
   </div>';
    
    return $htmlOP;
}