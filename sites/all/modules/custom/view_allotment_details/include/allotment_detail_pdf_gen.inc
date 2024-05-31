<?php 

//date('d/m/Y', time()+(330*60))
function allotment_detail_pdf_gen($app_id='', $file_name = '') {
	
	$online_application_id = decrypt_url($app_id);
	
	$result = fetch_allotment_details();
	$data = $result->fetchObject();
	
	$page_output = '';
	$page_output = '
	<div>
		<table style="font-family: Arial, sans-serif;">
			<tr><td align="center" colspan="2"><font size="6"><b>GOVERNMENT OF WEST BENGAL</b></font></td></tr>
			<tr><td align="center" colspan="2"><font size="4">DEPARTMENT OF HOUSING : Allotment Branch</font></td></tr>
			<tr><td align="center" colspan="2"><font size="5"><u>1, K.S. Roy Road , N.S. Building, A Block, 1st Floor, Kolkata-1</u></font></td></tr>
			<br><br><br>
			<tr>
				<td>No. '.$data->allotment_no.'</td>
				<td align="center">Date : '.implode('/', array_reverse(explode('-', $data->allotment_date))).'</td>
			</tr>
			<br><br><br>
			<tr>
				<td colspan="2">
					From: The Commissioner<br>
						  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Housing Department<br>
						  		   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;and<br>
						  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Competent Authority under the West Bengal<br>
						  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Govt. Premises (Regulation of Occupancy) Act, 1984
				</td>
			</tr>
			<br><br><br><br>
			<tr>
				<td colspan="2">
					To &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>'.$data->applicant_name.'</b><br><br>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;C/O&nbsp;<b>'.$data->guardian_name.'</b><br><br>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Sub. : </b>Allotment of flat at <b>'.$data->estate_name.'</b>,<br><br> 
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>'.$data->estate_address.'</b> housing estate located in <b>'.$data->district_name.'</b>.
				</td>
			</tr>
			<br><br><br><br>
			<tr>
				<td colspan="2">
					Madam/Sir,<br>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I am directed to inform you that this Department has been considering to allot you one R.H.E. Flat by 
					way of fresh allotment at the above mentioned Housing Estate subject to your eligibility for the same. You are, therefore, requested to 
					download this offer letter and to fill up the prescribed Form for application for Licence for fresh allotment within 7(Seven) days from 
					the date of receipt of this letter failing which the offer will be treated as cancelled.<br>
					<br>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Please note that this letter does not entitle you to the grant of a licence.
				</td>
			</tr>
			<br><br><br><br>
			<tr>
				<td>
				</td>
				<td align="center">
					Yours faithfully,<br><br><br><br>
					COMMISSIONER<br>
					&<br>
					COMPETENT AUTHORITY UNDER<br>
					THE WEST BENGAL GOVT. PREMISES<br>
					(REGULATION OF OCCUPANCY) ACT, 1984
					
					
				</td>
			</tr>
		</table>
	</div>';
	
	ob_end_clean();
	return pdf_using_mpdf_api($page_output, $file_name);
	
	

}


function generate_application_form_pdf($online_application_id = ''){
	$page_output = '';
	$page_output = '
	<div>
		<h3 align="center"><b>Form of Application for grant of licence for occupation of Government premises </b></h3>
		<p align="right">Dated..................</p>
		<p align="left">To</p><br>
		<p align="left">The Competent Authority under the</p>
		<p align="left">West Bengal Government Premises</p>
		<p align="left">(Regulation of Occupancy) Act, 1984 in respect of...........................</p>
		<p align="left">Under the Housing Department</p>
		<p align="left">Sir,</p>
		<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I am in the employment of the Government of West Bengal and I hold a specified post under it. I pray that a licence under Section 4 of the West Bengal Government premises (Regulation of (Occupancy) Act, 1984 may kindly be granted in my favour for the occupation of the Government premises at.........................................................................................(mention details premises).
		I have read and understood the provisions of the aforesaid Act and I know that I shall have to abide by the terms and conditions mentioned in Schedule I to the Act and such other terms and conditions as may be stipulated by the Competent Authority.
		I hereby declare that I do not possess any house/flat/residential accommodation either in my own name or in the name of any dependent members of my family within the local limits of...........................................................................................................Corporation/Municipality/within twenty Kilometres from my office.</p>
		<p align="left">I furnish all relevant particulars below for consideration of my application:</p>
		<ol>
			<li>Name of  the applicant:</li>
			<li>Fathers’/Husband’s name:</li>
			<li>Designation of the post hold:</li>
			<li>Headquarters of the post hold:</li>
			<li>Department/ Directorate/Office to which the post is attached with full address  :</li>
			<li>Date of joining the post:</li>
			<li>Scale of pay:</li>
			<li>Present basic pay and special pay, if any:</li>
			<li> Designation of Drawing and Disbursing Officer with address:</li>
			<li> Date of birth according to Service Book:</li>
			<li> Date of retirement according to Service Book:</li>
		</ol> 
		<p align="right">Yours faithfully,</p>
		<p align="right"><br>Signature&nbsp;&nbsp;&nbsp;&nbsp;</p>
		<p align="left">Counter Signature of Drawing and Disbursing Officer/
		<p>Head of Department/Head of Office with official seal.</p>
	</div>';

	ob_end_clean();
	return pdf_using_mpdf_api($page_output, $file_name);

}

function generate_declaration_form_pdf($online_application_id = ''){
	$page_output = '';
	$page_output = '
	<div>
		<h3 align="center"><b>DECLARATION BEFORE COMPETENT AUTHORITY </b></h3>
		<p align="left">I,Sri/Smt. ......................................son/daughter/wife of Sri/Smt. ................................................., resident at................................................present working as....................................................in the office/ Department of..................................................................hereby declare and affirm.</p>
		<ol>
			<li>That I have no house/flat in my name, in my spouse’s name or in name of and dependent member of my family within Kolkata Municipal Corporation area or Howrah Municipal Corporation area or within 20KM from Rental Housing Estate chosen by me.</li>
			<li>That I shall use the flat for the purpose for which it has been allotted to me and shall not use it for any other purpose.</li>
			<li>That I shall not let any other person to reside in flat issued in favour of me or keep it vacant for more than six months.</li>
			<li>I shall not assign or transfer the premises in any way to any person or put any person in procession of the premises. </li>
			<li>I shall not add to, or alter, any fixtures of the premises or make any structural alteration in the flat without the express permission in writing of the Competent Authority.</li>
			<li>I shall not cause, or suffer to be caused, any damage to the premises beyond the normal wear and tear through the proper use and occupation of the premises.</li>
			<li>I shall allow any offer duly authorized in this behalf by the Competent Authority to inspect the flat as when necessary.</li>
			<li>I shall pay such licence fee for the flat as may be determined from time to time by the Competent Authority.</li>
			<li> I shall inform the Competent Authority in Writing about every change in my post on place of posting and every change in my position by reason of going to leave or being placed under suspension or by any other reason within a week of the change taking place.</li>
			<li> That further I do hereby undertake that I shall not violate any of the terms and conditions as laid down in the license issued in my favour. If I violate any of the terms and conditions of license the Competent Authority shall be free to terminate my license.</li>
			<li> I further I do hereby undertake that upon the expiry of term license of upon termination or license. I shall delivered vacant possession of the flat to the Competent Authority or to any other person authorized by the Competent Authority in this behalf, in the same condition in which I took possession of the premises. </li>
			<li>	I further undertake that I will vacate the flat within 30 days from the date of my transfer (beyond 20 kms. From the concerned RHE)/ retirement/ resignation or dismissal/ removal from service. I shall be liable to pay whatever occupational charge will be fixed for the said period.</li>
		</ol> 
		<p align="left">Mobile No.  ____________________</p>
		<p align="left"><i><b>*Pay Slip</i><b></p>
		<p align="left">Date:</p>
		<p align="left">Place:</p>
		<p align="right">_________________________________________________</p>
		<p align="right"><i>(Signature of the Declarant)</i>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</p>
	</div>';

	ob_end_clean();
	return pdf_using_mpdf_api($page_output, $file_name);

}