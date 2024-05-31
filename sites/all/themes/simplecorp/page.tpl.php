<?php 
global $base_root;
global $base_url;
?>
<!-- #page-wrapper -->
<div id="page-wrapper" style="overflow-x: hidden;">
    <div id="overlay"></div>
    <!-- #page -->
    <div id="page">
        
        <!-- header -->
        <header role="header" class="container clearfix">
        
            <!-- #pre-header -->
            <div id="pre-header" class="clearfix">
            
                <?php if ($page['header']) :?>                
                <?php print render($page['header']); ?>
                <?php endif; ?>

                <?php if (theme_get_setting('social_icons_display','simplecorp')): ?>   
                    <!-- #social-icons -->
                    <div id="social-icons" class="clearfix">
                        <ul id="social-links">
                            <li class="facebook-link"><a href="https://www.facebook.com/morethan.just.themes" class="facebook" id="social-01" title="Join Us on Facebook!">Facebook</a></li>
                            <li class="twitter-link"><a href="https://twitter.com/morethanthemes" class="twitter" id="social-02" title="Follow Us on Twitter">Twitter</a></li>
                            <li class="google-link"><a href="#" id="social-03" title="Google" class="google">Google</a></li>
                            <li class="dribbble-link"><a href="#" id="social-04" title="Dribble" class="dribbble">Dribble</a></li>
                            <li class="vimeo-link"><a href="#" id="social-05" title="Vimeo" class="vimeo">Vimeo</a></li>
                            <li class="skype-link"><a href="#" id="social-06" title="Skype" class="skype">Skype</a></li>
                            <li class="linkedin-link"><a href="#" id="social-07" title="Linkedin" class="linkedin">Linkedin</a></li>
                            <li class="pinterest-link"><a href="#" id="social-09" title="Pinterest" class="pinterest">Pinterest</a></li>
                            <li class="rss-link"><a href="#" id="social-08" title="RSS" class="rss">RSS Feeds</a></li>
                        </ul>
                    </div>
                    <!-- EOF: #social-icons -->
                <?php endif; ?>    
                
            </div>
            <!-- EOF: #pre-header -->
      
            <!-- #header -->
            <div id="header" class="clearfix">
                
                <!-- #header-left -->
                <div id="header-left" class="one-third" style="margin-bottom:0px;"> 
                    
                    <?php if ($logo): ?>
                    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"> <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
                    <?php endif; ?>

                    <?php if (!$logo && ($site_name || $site_slogan)): ?>
                        <!-- #name-and-slogan -->
                        <hgroup id="name-and-slogan">
							<?php if ($site_name):?>
                            <h1 id="site-name"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a></h1>
                            <?php endif; ?>
    
                            <?php if ($site_slogan):?>
                            <h2 id="site-slogan"><?php print $site_slogan; ?></h2>
                            <?php endif; ?>
                        </hgroup> 
                        <!-- EOF:#name-and-slogan -->
                    <?php endif; ?>

                </div>
                <!--EOF: #header-left -->     

                <!-- #header-right -->
                
                <div id="header-right" class="two-third last" style="margin-bottom:0px; position:relative;">   
					
                    <!-- #navigation-wrapper -->
                    
                    <script src="<?php print $base_root.$base_path?>sites/all/themes/simplecorp/js/textresize.js"></script>
                    
                    <a href="<?php print $base_root.$base_path?>screen-reader-access" style="text-decoration:underline; color:#5996D9; position:absolute; top:55px; right:185px; font-size:16px;">Screen Reader</a>
                    <a href="javascript:void()" id="large" style="font-size:16px;"><img src="<?php print $base_root.$base_path?>sites/all/themes/simplecorp/images/icon_large.png" alt="Large Text" style="font-size:16px;"> </a>
                    <a href="javascript:void()" id="medium" style="font-size:16px;"><img src="<?php print $base_root.$base_path?>sites/all/themes/simplecorp/images/icon_medium.png" alt="Medium Text" style="font-size:16px;"></a>
                    <a href="javascript:void()" id="small" style="font-size:16px;"><img src="<?php print $base_root.$base_path?>sites/all/themes/simplecorp/images/icon_small.png" alt="Small Text" style="font-size:16px;"></a>
                    <a href="javascript:void(0)" class="contrast_color" style="font-size:16px;"><img src="<?php print $base_root.$base_path?>sites/all/themes/simplecorp/images/icon_color-change.png" alt="Color Change" style="font-size:16px;"></a>
                    <a href="javascript:void(0)" class="default_color" style="font-size:16px;"><img src="<?php print $base_root.$base_path?>sites/all/themes/simplecorp/images/icon_normal-color.png" alt="Color Default" style="font-size:16px;"></a>
                    
                    <br />
                    
                    <div id="date-time">
                    <?php 
						date_default_timezone_set("Asia/Kolkata"); ?>
					<?php	print date("l\, jS F Y\, h:i:s A"); ?>
                    </div>
                    <br />
                    
                    <?php
						global $user_role;
						
						$file_path = "sites/default/files/misc_files/";
						if(!user_is_logged_in()) {
					?>
							<font class="blink_text" style="font-size:16px">
					<?php	print l('How to Register', $file_path.'HOW_TO_REGISTER_EALLOTMENT_OF_RHE.pdf', array('html' => TRUE, 'attributes' => array('target' => '_blank')));
					?>
							</font>
					<?php
						}
						else {
							if($user_role == 4) {
					?>
                    		<font style="font-size:16px">
                    <?php	
							print l('Download Applicant User Guide', $file_path.'APPLICANT_USER_MANUAL_EALLOTMENT_OF_RHE.pdf', array('html' => TRUE, 'attributes' => array('target' => '_blank')));
					?>
							</font>
                    <?php
							}
						}
					?>
                    
                    <!-- EOF: #navigation-wrapper -->

                </div>
                <!--EOF: #header-right -->

            </div> 
            <!-- EOF: #header -->
            <div id="navigation-wrapper" class="clearfix">
                        <!-- #main-navigation -->                        
                        <nav id="main-navigation" class="main-menu clearfix" role="navigation">
                        <?php if ($page['navigation']) :?>
                        <?php print drupal_render($page['navigation']); ?>
                        <?php else : ?>

                        <?php if (module_exists('i18n_menu')) {
                        $main_menu_tree = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));
                        } else { $main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu')); }
                        print drupal_render($main_menu_tree); ?>

                        <?php endif; ?>
                        </nav>
                        <!-- EOF: #main-navigation -->
                    </div>

        </header>   
        <!-- EOF: header -->

        <div id="content" class="clearfix">

            <?php if ($page['top_content']): ?>
            <!-- #top-content -->
            <div id="top-content" class="container clearfix">
              <!-- intro-page -->
              <div class="intro-page">
              <?php print render($page['top_content']); ?>
              </div>
              <!-- EOF: intro-page -->            
            </div>  
            <!--EOF: #top-content -->
            <?php endif; ?>
            
            <!-- #banner -->
            <div id="banner" class="container">

                <?php if ($page['banner']) : ?>
                <!-- #banner-inside -->
                <div id="banner-inside">
                <?php print render($page['banner']); ?>
                </div>
                <!-- EOF: #banner-inside -->        
                <?php endif; ?>

                <?php if (theme_get_setting('slideshow_display','simplecorp')): ?>

					<?php if ($is_front): ?>
                    <!-- #slider-container -->
                    <div id="slider-container">
                        <div class="flexslider loading">
                            <ul class="slides">
    
                                <!-- first-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">
                                        <a href="<?php print base_path();?>"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/banner-16.jpg" alt="RHE Banner 1" /></a>
                                    </div>
                                    <div class="flex-caption">
                                        <h3>e-Allotment of Rental Housing Estate</h3>
                                    </div>
                                </li>
    
                                <!-- second-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">                        
                                        <a href="<?php print base_path();?>"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/banner-17.jpg" alt="RHE Banner 2" /></a>
                                    </div>                        
                                    <div class="flex-caption">
                                        <h3>e-Allotment of Rental Housing Estate</h3>
                                    </div>
                                </li>
    
                                <!-- third-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">                            
                                        <a href="<?php print base_path();?>"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/banner-18.jpg" alt="RHE Banner 3" /></a>
                                    </div>
                                    <div class="flex-caption">
                                        <h3>e-Allotment of Rental Housing Estate</h3>
                                    </div>
                                </li>
                                 <!-- fourth-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">                            
                                        <a href="<?php print base_path();?>"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/banner-19.jpg" alt="RHE Banner 4" /></a>
                                    </div>
                                    <div class="flex-caption">
                                        <h3>e-Allotment of Rental Housing Estate</h3>
                                    </div>
                                </li>
                                 <!-- fifth-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">                            
                                        <a href="<?php print base_path();?>"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/banner-20.jpg" alt="RHE Banner 5" /></a>
                                    </div>
                                    <div class="flex-caption">
                                        <h3>e-Allotment of Rental Housing Estate</h3>
                                    </div>
                                </li>
    
                            </ul>
                        </div>
                    </div>
                    <!-- EOF: #slider-container -->
                    <?php endif; ?>

                <?php endif; ?>
            
            </div>

            <!-- EOF: #banner -->
            <?php if ($breadcrumb && theme_get_setting('breadcrumb_display','simplecorp')):?>
            <!-- #breadcrumb -->
            <div class="container clearfix">
            <?php print $breadcrumb; ?>
            </div>
            <!-- EOF: #breadcrumb -->
            <?php endif; ?>

            <?php if ($messages):?>
            <!--messages -->
            <div class="container clearfix">
            <?php print $messages; ?>
            </div>
            <!--EOF: messages -->        
            <?php endif; ?>            
            
            <!--#main-content -->
            <div id="main-content" class="container clearfix">
                <?php if ($page['sidebar_first']) :?>
                <!--.sidebar first-->
                <div class="one-fourth">
                <aside class="sidebar">
                <?php print render($page['sidebar_first']); ?>
                </aside>
                </div>
                <!--EOF:.sidebar first-->
                <?php endif; ?>
                <?php if ($page['sidebar_first'] && $page['sidebar_second']) { ?>
                <div class="one-half">
                <?php } elseif ($page['sidebar_first']) { ?>
                <div class="three-fourth last">
                <?php } elseif ($page['sidebar_second']) { ?>
                <div class="three-fourth">  
                <?php } else { ?>
                <div class="clearfix">    
                <?php } ?>
                <!-- </div> -->
                    <!--#main-content-inside-->
                    <div id="main-content-inside" >
                        <?php print render($title_prefix); ?>
                        <?php global $user; global $user_info; global $housing_user_info;  ?>
                        
                        
                        <?php if(substr($_SERVER['REQUEST_URI'],-4,4) == 'user') { 
                                if(user_is_logged_in()){
                        ?> 
                            <?php if (($user_role == 4 || $user_role == 5)): ?><h1><?php  print 'Hello '.$user_info.', Welcome to e-Allotment of RHE'; ?></h1><?php endif; ?>
                            <?php if ($user_role == 6): ?><h1><?php print 'Hello '.$housing_user_info.', Welcome to e-Allotment of RHE'; ?></h1><?php endif; ?>
                            <?php if ($user_role == 9): ?><h1><?php print 'Hello '.$housing_user_info.', Welcome to e-Allotment of RHE'; ?></h1><?php endif; ?>
                            <?php if ($user_role == 10): ?><h1><?php print 'Hello '.$housing_user_info.', Welcome to e-Allotment of RHE'; ?></h1><?php endif; ?>
                            <?php if ($user_role == 7): ?><h1><?php print 'Hello '.$housing_user_info.', Welcome to e-Allotment of RHE'; ?></h1><?php endif; ?>
                            <?php if ($user_role == 8): ?><h1><?php print 'Hello '.$housing_user_info.', Welcome to e-Allotment of RHE'; ?></h1><?php endif; ?>
                            <?php if ($user_role == 3): ?><h1><?php print 'Hello Admin, Welcome to e-Allotment of RHE'; ?></h1><?php endif; ?>
                        <?php }
                            } else {                                    
                                if(arg(0) == 'hrms-login' || (arg(0) == 'user' && (arg(1) == 'password' || arg(1) == 'login'))) {
                                    print '<h1 class="title-center">' . $title . '</h1>';
                                } else {
                                    print '<h1>' . $title . '</h1>';
                                }
                        ?> 
                        <?php /*?><?php if ($title): ?><h1><?php print $title; ?></h1><?php endif; ?><?php */?>
                        <?php } ?>
                        <?php print render($title_suffix); ?>
                        <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
                        <?php print render($page['help']); ?>
                        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
                        
                        <?php print render($page['content']); ?>
                        <?php if ($is_front || ((arg(0) == 'user' && arg(1) == 'login'))): ?>                            
                            <div id="bottom-content" class="container clearfix">
                                <?php if (theme_get_setting('carousel_display','simplecorp')): ?>   
                                    <ul id="projects-carousel" class="loading">        
                                        <!-- PROJECT ITEM STARTS -->
                                        <li>
                                            <div class="item-content">
                                                <div class="link-holder">
                                                    <div class="portfolio-item-holder">
                                                        <div class="portfolio-item-hover-content">
                        
                                                                <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/rhe1-1.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                                                
                                                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/rhe1-1.jpg" alt="RHE Portfolio 1" width="220"  class="portfolio-img" />  
                                                                
                                                                <div class="hover-options"></div>
                                                            </div>
                                                        </div>
                                                        <div class="description">
                                                            <p>
                                                                <a href="#" title="title">e-Allotment of RHE</a>
                                                            </p>
                                                            <!--<span>1</span>-->
                                                        </div>
                                                </div>
                                            </div>
                                        </li>
                                        <!-- PROJECT ITEM ENDS -->
                    
                                        <!-- PROJECT ITEM STARTS -->
                                        <li>
                                            <div class="item-content">
                                                <div class="link-holder">
                                                    <div class="portfolio-item-holder">
                                                        <div class="portfolio-item-hover-content">
                    
                                                            <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/rhe2-1.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                                            
                                                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/rhe2-1.jpg" alt="RHE Portfolio 2" width="220" class="portfolio-img" />
                    
                                                            <div class="hover-options"></div>
                                                        </div>
                                                    </div>
                                                    <div class="description">
                                                        <p>
                                                            <a href="#" title="title">e-Allotment of RHE</a>
                                                        </p>
                                                        <!--<span>2</span>-->
                                                    </div>
                                                </div>
                                            </div>
                                        </li>
                                        <!-- PROJECT ITEM ENDS -->
                    
                                        <!-- PROJECT ITEM STARTS -->
                                        <li>
                                            <div class="item-content">
                                                <div class="link-holder">
                                                    <div class="portfolio-item-holder">
                                                        <div class="portfolio-item-hover-content">
                    
                                                            <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/rhe3-1.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                                            
                                                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/rhe3-1.jpg" alt="RHE Portfolio 3" width="220" class="portfolio-img" />
                    
                                                            <div class="hover-options"></div>
                                                        </div>
                                                    </div>
                                                    <div class="description">
                                                        <p>
                                                            <a href="#" title="title">e-Allotment of RHE</a>
                                                        </p>
                                                        <!--<span>3</span>-->
                                                    </div>
                                                </div>
                                            </div>
                                        </li>
                                        <!-- PROJECT ITEM ENDS -->
                    
                                        <!-- PROJECT ITEM STARTS -->
                                        <li>
                                            <div class="item-content">
                                                <div class="link-holder">
                                                    <div class="portfolio-item-holder">
                                                        <div class="portfolio-item-hover-content">
                    
                                                            <a href="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/rhe4-1.jpg" title="title" data-rel="prettyPhoto" class="zoom">View Image</a>
                                                            
                                                            <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/rhe4-1.jpg" alt="RHE Portfolio 4" width="220" class="portfolio-img" />
                                                            
                                                            <div class="hover-options"></div>
                                                        </div>
                                                    </div>
                                                    <div class="description">
                                                        <p>
                                                            <a href="#" title="title">e-Allotment of RHE</a>
                                                        </p>
                                                        <!--<span>4</span>-->
                                                    </div>
                                                </div>
                                            </div>
                                        </li>
                                        <!-- PROJECT ITEM ENDS -->
                                    </ul>
                                <?php endif; ?> 
                                <?php if ($page['bottom_content']): ?>
                                <?php print render($page['bottom_content']); ?>
                                <?php endif; ?>           
                            </div>                            
                        <?php endif; ?>
                    
                    </div>
                    <!--EOF:#main-content-inside-->
                </div>
                <?php if ($page['sidebar_second']) :?>
                    <!--.sidebar second-->
                    <div class="one-fourth last">
                    <aside class="sidebar">
                    <?php print render($page['sidebar_second']); ?>
                    </aside>
                    </div>
                    <!--EOF:.sidebar second-->
                <?php endif; ?> 
            </div>
            <!--EOF: #main-content -->
        </div> <!-- EOF: #content -->

        <!-- #footer -->
        <footer id="footer">
            
            <?php if ($page['footer_first'] || $page['footer_second'] || $page['footer_third'] || $page['footer_fourth']) :?>
            <div class="container clearfix">

                <div class="first one-fourth footer-area">
                <?php if ($page['footer_first']) :?>
                <?php print render($page['footer_first']); ?>
                <?php endif; ?>
                </div>

                <div class="one-fourth footer-area">
                <?php if ($page['footer_second']) :?>
                <?php print render($page['footer_second']); ?>
                <?php endif; ?>
                </div>

                <div class="one-fourth footer-area">
                <?php if ($page['footer_third']) :?>
                <?php print render($page['footer_third']); ?>
                <?php endif; ?> 
                </div>

                <div class="one-fourth footer-area last">
                <?php if ($page['footer_fourth']) :?>
                <?php print render($page['footer_fourth']); ?>
                <?php endif; ?> 
                </div>

            </div>
            <?php endif; ?>

            <!-- #footer-bottom -->
            <div id="footer-bottom">
                <div class="container clearfix">
                    <!--<span class="right"><a class="backtotop" href="#">↑</a></span>-->
                    <?php //print theme('links__system_secondary_menu', array('links' => $secondary_menu, 'attributes' => array('class' => array('menu', 'secondary-menu', 'links', 'clearfix')))); ?>
                    
                    <?php if ($page['footer']) :?>
                    <?php //print render($page['footer']); ?>
                    <?php endif; ?>
                    
                    <div class="credits">
                    <b>Site Designed, Hosted and Maintained by</b> <a href="http://www.nic.in/" target="_blank" rel="noopener noreferrer">National Informatics Centre</a>. 
                    </div>

                </div>
            </div>
            <!-- EOF: #footer-bottom -->
            
        </footer> 
        <!-- EOF #footer -->

    </div>
    <!-- EOF: #page -->

</div> 
<!-- EOF: #page-wrapper -->
<?php
//global $base_url;
/* if(user_is_logged_in()) {
	drupal_add_js('jQuery(document).ready(function(e) {
		jQuery(\'#main-navigation .menu li:last-child\').removeClass(\'last\');
		jQuery(\'#main-navigation .menu li:last-child\').after(\'<li class="last leaf ulogout"><a href="' . $base_url . '/user/logout' . '">Logout</a></li>\');
	});', 'inline');
} else {
	drupal_add_js('jQuery(document).ready(function(e) {
		jQuery(\'#main-navigation .menu li:last-child\').removeClass(\'last\');
		jQuery(\'#main-navigation .menu li:last-child\').after(\'<li class="last leaf ulogin"><a href="' . $base_url . $base_path . 'user' . '">Login</a></li>\');
	});', 'inline');
} */

if(arg(0) == 'user' && arg(1) == '') {
	drupal_add_js('jQuery(document).ready(function(e) {
		jQuery(\'.ulogin a\').addClass(\'active\');
	});', 'inline');	
}
?>


