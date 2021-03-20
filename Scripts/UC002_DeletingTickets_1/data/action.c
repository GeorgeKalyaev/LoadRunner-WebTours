Action()
{

	lr_start_transaction("login");

	web_url("WebTours", 
		"URL=http://192.168.26.1:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_think_time(9);

	web_submit_data("login.pl", 
		"Action=http://192.168.26.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value=130828.180558931zHcQtHtpfDHftADHzpitHccf", ENDITEM, 
		"Name=username", "Value=qwerty5", ENDITEM, 
		"Name=password", "Value=qwerty5", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=login.x", "Value=50", ENDITEM, 
		"Name=login.y", "Value=11", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("iter");

	web_url("Itinerary Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("iter",LR_AUTO);

	lr_start_transaction("del");

	web_submit_data("itinerary.pl", 
		"Action=http://192.168.26.1:1080/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=1", "Value=on", ENDITEM, 
		"Name=flightID", "Value=860820-780-qq", ENDITEM, 
		"Name=.cgifields", "Value=1", ENDITEM, 
		"Name=removeFlights.x", "Value=56", ENDITEM, 
		"Name=removeFlights.y", "Value=9", ENDITEM, 
		LAST);

	lr_end_transaction("del",LR_AUTO);

	lr_think_time(4);

	lr_start_transaction("exit");

	web_url("SignOff Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("exit",LR_AUTO);

	return 0;
}