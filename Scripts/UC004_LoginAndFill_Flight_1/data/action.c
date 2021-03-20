Action()
{

	web_url("WebTours", 
		"URL=http://192.168.26.1:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	lr_think_time(20);

	lr_start_transaction("login");

	web_submit_data("login.pl", 
		"Action=http://192.168.26.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value=130777.656865128zHcziHfpHcftADzVpcftDf", ENDITEM, 
		"Name=username", "Value=kalyaev", ENDITEM, 
		"Name=password", "Value=kalyaev", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=login.x", "Value=52", ENDITEM, 
		"Name=login.y", "Value=12", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_think_time(22);

	lr_start_transaction("Flights");

	web_url("Search Flights Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Flights",LR_AUTO);

	lr_think_time(32);

	lr_start_transaction("Find_flight");

	web_submit_data("reservations.pl", 
		"Action=http://192.168.26.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value=Los Angeles", ENDITEM, 
		"Name=departDate", "Value=02/28/2021", ENDITEM, 
		"Name=arrive", "Value=London", ENDITEM, 
		"Name=returnDate", "Value=03/01/2021", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value=Window", ENDITEM, 
		"Name=seatType", "Value=Business", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		"Name=findFlights.x", "Value=62", ENDITEM, 
		"Name=findFlights.y", "Value=7", ENDITEM, 
		LAST);

	lr_end_transaction("Find_flight",LR_AUTO);

	lr_think_time(26);

	lr_start_transaction("bay_ticket");

	web_submit_data("reservations.pl_2", 
		"Action=http://192.168.26.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/reservations.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value=322;1060;02/28/2021", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value=Business", ENDITEM, 
		"Name=seatPref", "Value=Window", ENDITEM, 
		"Name=reserveFlights.x", "Value=23", ENDITEM, 
		"Name=reserveFlights.y", "Value=5", ENDITEM, 
		LAST);

	lr_end_transaction("bay_ticket",LR_AUTO);

	lr_think_time(86);

	lr_start_transaction("fillform_payment_detalise");

	web_submit_data("reservations.pl_3", 
		"Action=http://192.168.26.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value=kalyaev_First_Name ", ENDITEM, 
		"Name=lastName", "Value=kalyaev_Last_Name", ENDITEM, 
		"Name=address1", "Value=Puskina", ENDITEM, 
		"Name=address2", "Value=Moscow", ENDITEM, 
		"Name=pass1", "Value= PassengerNames_rnd ", ENDITEM, 
		"Name=creditCard", "Value=23141234312234", ENDITEM, 
		"Name=expDate", "Value=02/21", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value=Business", ENDITEM, 
		"Name=seatPref", "Value=Window", ENDITEM, 
		"Name=outboundFlight", "Value=322;1060;02/28/2021", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		"Name=buyFlights.x", "Value=48", ENDITEM, 
		"Name=buyFlights.y", "Value=14", ENDITEM, 
		LAST);

	lr_end_transaction("fillform_payment_detalise",LR_AUTO);

	lr_think_time(13);

	lr_start_transaction("logout");

	web_url("SignOff Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);

	return 0;
}