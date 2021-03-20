Action()
{
	
	lr_start_transaction("2_MAIN_DeletingTickets");
	
	web_reg_save_param_regexp(
	    "ParamName=userSession", 
	    "RegExp=name=\"userSession\" value=\"([^\"]+)\"/>",
	    "Ordinal=1",
		LAST);
	 
	web_reg_find("Text=Welcome to the Web Tours site.", LAST);
	
	lr_start_transaction("OpenSite");
	
	web_reg_find("Text=Welcome to the Web Tours site.", LAST);

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
	  
	lr_think_time(3);
	 
	lr_start_transaction("Login"); 
	
	 web_reg_find("Text=Welcome, <b>{UserName}</b>, to the Web Tours reservation pages.", LAST);
	
	web_submit_data("login.pl", 
		"Action=http://192.168.26.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value={userSession}", ENDITEM, 
		"Name=username", "Value={UserName}", ENDITEM, 
		"Name=password", "Value={Password}", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=login.x", "Value=50", ENDITEM, 
		"Name=login.y", "Value=11", ENDITEM, 
		LAST);
  
	lr_end_transaction("Login",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction("Click_Itinerary");
	 
	web_reg_find("Text=Invoice sent to:", "SaveCount=Tickets_Count", LAST);
	
		/*Correlation comment - Do not change!  Original value='860820-780-qq' Name ='flightID' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=flightID",
		"TagName=input",
		"Extract=value",
		"Name=flightID",
		"Type=hidden",
		"NotFound=WARNING",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/itinerary.pl*",
		LAST);
		// <input type="hidden" name="flightID" value="22619029-829-RA"  />
		
//		web_reg_save_param_ex(
//		"ParamName=kol_tik", 
//	    "LB/IC=<input type=\"hidden\" name=\"flightID\" value=\"",
//	    "RB/IC=\" >",
//	    "Ordinal=all",
//		LAST);

//web_reg_save_param_ex(
//		"ParamName=Tikets_count",
//		"LB=type\=\"checkbox\" name=\"",
//		"RB=\"",
//		"Ordinal=all",
//		SEARCH_FILTERS,
//		LAST);
		
		/*Correlation comment - Do not change!  Original value='22603419-794-RA' Name ='flightID' Type ='Manual'*/
//	web_reg_save_param_attrib(
//		"ParamName=flightID_bilet",
//		"TagName=input",
//		"Extract=value",
//		"Name=flightID",
//		"Type=hidden",
//		"Ordinal=all",
//		SEARCH_FILTERS,
//		"IgnoreRedirections=No",
//		"RequestUrl=*/itinerary.pl*",
//		LAST);
			
	web_reg_save_param_regexp(
		"ParamName=biletsIDbefore",
		"RegExp=name=\"flightID\"\\ value=\"(.*?)-",
		"Ordinal=all",
		"NotFound=WARNING",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		"RequestUrl=*/itinerary.pl*",
		LAST);

	web_url("Itinerary Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
//
//		for(int i = 0; i < atoi(lr_eval_string("{biletsIDbefore_count}")); i++){
//			if(lr_eval_integer(biletsIDbefore_1)) ==
//		}	

//	web_stream_get_param_int();
//	lr_save_int(qwerty, "test");

		
	lr_end_transaction("Click_Itinerary",LR_AUTO);


Tickets = atoi(lr_eval_string("{Tickets_Count}"));
if (Tickets != 0){
	
	lr_start_transaction("Tickets_Remove");
	
//	web_submit_data("itinerary.pl",
//		"Action=http://192.168.26.1:1080/cgi-bin/itinerary.pl",
//		"Method=POST",
//		"TargetFrame=",
//		"RecContentType=text/html",
//		"Referer=http://192.168.26.1:1080/cgi-bin/itinerary.pl",
//		"Snapshot=t4.inf",
//		"Mode=HTML",
//		ITEMDATA,
//		"Name=1", "Value=on", ENDITEM,
//		"Name=flightID", "Value={flightID}", ENDITEM,
//		"Name=.cgifields", "Value=1", ENDITEM,
//		"Name=removeFlights.x", "Value=56", ENDITEM,
//		"Name=removeFlights.y", "Value=9", ENDITEM,
//		LAST);
	
	  
	web_reg_save_param_regexp(
		"ParamName=biletsIDafter",
		"RegExp=name=\"flightID\"\\ value=\"(.*?)-",
		"Ordinal=all",
		"NotFound=WARNING",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		"RequestUrl=*/itinerary.pl*",
		LAST);
	
	//Удаление билета
	web_submit_form("itinerary.pl",
		 "Snapshot=t4.inf",
		 ITEMDATA,
		"Name=1", "Value=on", ENDITEM,
		"Name=removeFlights.x", "Value=56", ENDITEM,
		"Name=removeFlights.y", "Value=9", ENDITEM,
	LAST);

biletsIDbefore_1 = atoi(lr_eval_string("{biletsIDbefore_1}"));
biletsIDafter_1 = atoi(lr_eval_string("{biletsIDafter_1}"));

if(biletsIDbefore_1 == biletsIDafter_1){

	lr_error_message("Error: %s", "the ticket was not deleted");	
	
} else if(biletsIDbefore_1 != biletsIDafter_1){

	lr_output_message( "The ticket was deleted #%s", lr_eval_string("{biletsIDbefore_1}"));

}

	lr_end_transaction("Tickets_Remove",LR_AUTO);
	 
	lr_think_time(3);
	
	lr_start_transaction("Logout");
	web_url("SignOff Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("Logout",LR_AUTO);
	lr_end_transaction("2_MAIN_DeletingTickets",LR_AUTO);
}

else
	
{
	lr_think_time(3);
	
	web_reg_find("Text=Web Tours", LAST);
	
    lr_start_transaction("Logout");
	web_url("SignOff Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("Logout",LR_AUTO);
	lr_end_transaction("2_MAIN_DeletingTickets",LR_AUTO);
}



// На заметку для себя
// Можно было так, но если билетов не будет, то будет ошибка о том, что не может найти билеты (пока обойти не получилось) - нашел решение подставить: "NotFound=WARNING", предупреждение но скрипт не зафейлится

	/*web_reg_save_param_ex(
		"ParamName=Tikets_count",
		"LB=type\=\"checkbox\" name=\"",
		"RB=\"",
		"Ordinal=all",
		SEARCH_FILTERS,
		LAST);

	web_url("Itinerary Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);*/
	
/*lr_save_int(i, "prmCounter");
lr_output_message("String value of prmCounter: %s", lr_eval_string("{prmCounter}"));*/
	
/*
if (strcmp(lr_eval_string("{Tikets_count}"),"0") == 0)
 {
    lr_start_transaction("exit");
	web_url("welcome.pl", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("exit",LR_AUTO);
 }
else
{
	
}*/

/*
 //web_reg_find("Text=No flights have been reserved.","Search=Body",  LAST);
//<center><H3>No flights have been reserved.</H3></center>
 */

	 

	return 0;
}