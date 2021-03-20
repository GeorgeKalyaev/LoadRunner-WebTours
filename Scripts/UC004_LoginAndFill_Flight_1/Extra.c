Extra()
{
	return 0;
}


Check(int status, char *tr_name)
{
	if(status == LR_FAIL){
		lr_error_message("Возникла ошибка -> перелогин");
		lr_end_transaction(tr_name, LR_FAIL);
		lr_end_transaction("4_MAIN_LoginAndFill_Flight", LR_FAIL);
		Relogin();
		lr_exit(LR_EXIT_MAIN_ITERATION_AND_CONTINUE, LR_FAIL);
	}
	return 0;
}

Relogin()
{
	
	lr_start_transaction("_UC004_LoginAndFill_Flight_Relogin");
	
	
	lr_save_datetime("%d.%m.%Y %H:%M:%S", DATE_NOW, "currDateTime");
	lr_output_message("Relogin, time=%s, iteration=%s", lr_eval_string("{currDateTime}"), lr_eval_string("{iteration}"));
	
	Logout();
	
	lr_think_time(3); // для закрытии сессии
	
	lr_end_transaction("_UC004_LoginAndFill_Flight_Relogin", LR_FAIL);
	
	Login();
	
	return 0;
}


Logout()
{
	web_reg_find("Text=Web Tours", LAST);
	
	web_url("SignOff Button", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);
	
	return 0;
}
