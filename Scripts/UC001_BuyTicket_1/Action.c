Action()
{
	int randNumber; 
 	randNumber = rand()%60 + 1;  // генерируем от 1 до 60
 	
 	//lr_output_message("Random Number is %d", randNumber);  
 	
 	lr_save_datetime("%m/%d/%Y", DATE_NOW + ONE_DAY*randNumber, "departD"); 
 	//lr_output_message("depart date is %s", lr_eval_string("{departD}")); 
 	
 	lr_save_datetime("%m/%d/%Y", DATE_NOW + (ONE_DAY*randNumber) + (ONE_DAY*2), "returnD");
 	//lr_output_message("return date is %s", lr_eval_string("{returnD}"));
	
 	lr_start_transaction(tr_main = "1_MAIN_BuyTicket");
 	
	web_reg_save_param_regexp(
	    "ParamName=userSession", 
	    "RegExp=name=\"userSession\" value=\"([^\"]+)\"/>",
	    "Ordinal=1",
		LAST);
 	
 	lr_start_transaction(tr_name = "OpenSite");
 	
	web_reg_find("Text=Welcome to the Web Tours site.", LAST);

	web_url("WebTours", 
		"URL={protocol}://{host}:{port}/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
 	 
 	
 	lr_end_transaction("OpenSite",LR_AUTO);
 	
 	lr_think_time(3);
 
 	lr_start_transaction(tr_name = "Login"); // Логин
 	
	web_set_sockets_option("SSL_VERSION", "AUTO");
	
	
	 //web_reg_find("Text=User password was correct", LAST);
	 web_reg_find("Text=Welcome, <b>{UserName}</b>, to the Web Tours reservation pages.", LAST);

	status = web_submit_data("login.pl", 
		"Action={protocol}://{host}:{port}/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/nav.pl?in=home", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value={userSession}", ENDITEM, 
		"Name=username", "Value={UserName}", ENDITEM, 
		"Name=password", "Value={Password}", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=login.x", "Value=52", ENDITEM, 
		"Name=login.y", "Value=12", ENDITEM, 
		LAST);
	Check(status, tr_name);
  
	lr_end_transaction("Login",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction(tr_name = "Click_Flights"); // Перейти на вкладку «Flights»
	
	web_reg_save_param_ex(
		"ParamName=cities", 
	    "LB/IC=<option value=\"",
	    "RB/IC=\">",
	    "Ordinal=all",
		LAST);
  
	web_reg_find("Text=Web Tours Navigation Bar", LAST);
	
	status = web_url("Search Flights Button", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	 
	Check(status, tr_name);
	
	lr_save_string(lr_paramarr_random("cities"), "depart");
	lr_save_string(lr_paramarr_random("cities"), "arrive");

	while(strcmp(lr_eval_string("{depart}"), lr_eval_string("{arrive}"))== 0){
		lr_save_string(lr_paramarr_random("cities"), "arrive");
	}

	lr_end_transaction("Click_Flights",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction(tr_name = "Fill_Flight"); // Заполнить поля для поиска рейс, нажать кнопку «Continue»

	
	web_reg_save_param_regexp(
	    "ParamName=outboundFlight", 
	    "RegExp=name=\"outboundFlight\" value=\"([^\"]+)\"",
	    "Ordinal=ALL",
		LAST);
	
	web_reg_find("Text=Flight departing from <B>{depart}</B> to <B>{arrive}</B> on <B>{departD}</B>", LAST);
 
	status = web_submit_data("reservations.pl", 
		"Action={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={depart}", ENDITEM, 
		//"Name=departDate", "Value=02/28/2021", ENDITEM,
		"Name=departDate", "Value={departD}", ENDITEM,
		"Name=arrive", "Value={arrive}", ENDITEM, 
		//"Name=returnDate", "Value=03/01/2021", ENDITEM,
		"Name=returnDate", "Value={returnD}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		"Name=findFlights.x", "Value=62", ENDITEM, 
		"Name=findFlights.y", "Value=7", ENDITEM, 
		LAST);
	Check(status, tr_name);

	lr_end_transaction("Fill_Flight",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction(tr_name = "Choose_Flight"); // Выбрать доступный рейс, нажать кнопку «Continue»

	lr_save_string(lr_paramarr_random("outboundFlight"),"outboundFlight");
	
	web_reg_find("Text=Flight Reservation", LAST);
	
	status = web_submit_data("reservations.pl_2", 
		"Action={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=reserveFlights.x", "Value=23", ENDITEM, 
		"Name=reserveFlights.y", "Value=5", ENDITEM, 
		LAST);
	Check(status, tr_name);

	lr_end_transaction("Choose_Flight",LR_AUTO);

	lr_think_time(3);
 
	lr_start_transaction(tr_name = "Fill_Payment_Info"); // Заполнить необходимые данные для платежа, нажать кнопку «Continue»

 	web_reg_find("Text=<b>{UserName}{LastName}'s Flight Invoice</b>", LAST);
 
	status = web_submit_data("reservations.pl_3", 
		"Action={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={UserName}", ENDITEM, 
		"Name=lastName", "Value={LastName}", ENDITEM, 
		"Name=address1", "Value={Street}", ENDITEM, 
		"Name=address2", "Value={depart}", ENDITEM, 
		"Name=pass1", "Value= {UserName} {LastName}", ENDITEM, 
		"Name=creditCard", "Value={CreditCard}", ENDITEM, 
		"Name=expDate", "Value={expDate}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		"Name=buyFlights.x", "Value=48", ENDITEM, 
		"Name=buyFlights.y", "Value=14", ENDITEM, 
		LAST);
	Check(status, tr_name);
 
	lr_end_transaction("Fill_Payment_Info",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction(tr_name = "Logout"); // Выполнить выход из системы, нажать кнопку «Continue»

	Logout(); 

	lr_end_transaction("Logout",LR_AUTO);
	lr_end_transaction("1_MAIN_BuyTicket",LR_AUTO);
	
	return 0;
}