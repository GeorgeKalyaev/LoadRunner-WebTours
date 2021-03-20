Action()
{

	lr_start_transaction("OpenSite");

	web_url("WebTours", 
		"URL=http://192.168.26.1:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("OpenSite",LR_AUTO);

	lr_start_transaction("sign_up_now");

	web_url("sign up now", 
		"URL=http://192.168.26.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	lr_end_transaction("sign_up_now",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("fillform_and_ok");

	web_submit_data("login.pl", 
		"Action=http://192.168.26.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=qwerty2", ENDITEM, 
		"Name=password", "Value=qwerty2", ENDITEM, 
		"Name=passwordConfirm", "Value=qwerty2", ENDITEM, 
		"Name=firstName", "Value=", ENDITEM, 
		"Name=lastName", "Value=", ENDITEM, 
		"Name=address1", "Value=", ENDITEM, 
		"Name=address2", "Value=", ENDITEM, 
		"Name=register.x", "Value=61", ENDITEM, 
		"Name=register.y", "Value=3", ENDITEM, 
		LAST);

	lr_end_transaction("fillform_and_ok",LR_AUTO);

	return 0;
}