const String H_start = "<!DOCTYPE html><html><head><meta name=\"author\" content=\"Colden I\"><meta charset=\"utf-8\">";

String Home_page_getHTML(){
  String html = "";
  html += H_start;
  html += "<title>Login</title>";
  html +=
    "<style>input.button {display: inline-block;color: #4a4a97;font-weight: 700;text-decoration: none;user-select: none;padding: .5em 2em;outline: none;border: 2px solid;border-radius: 1px;transition: 0.2s;}"
    "input.button:hover{background: rgb(145 192 221);}input.button:active{background: black;}</style>";
  
  html += "</head>";
  html += "<body>";

  html += 
    "<p style=\"text-align:center\"><span style=\"font-family:Comic Sans MS,cursive\"><strong><span style=\"font-size:28px\"><span style=\"color:#0000ff\">Войти</span></span></strong></span></p>"
    "<p style=\"text-align:center\"><input placeholder=\"Логин\" style=\" padding: 10px; border-radius: 10px;\" id=\"login\" maxlength=\"32\" name=\"login\" type=\"text\" /></p>"
    "<p style=\"text-align:center\"><input placeholder=\"Пароль\" style=\" padding: 10px; border-radius: 10px;\" id=\"password\" maxlength=\"32\" name=\"password\" type=\"password\" /></p>"
    "<p id=\"error_text\" style=\"text-align:center\"></p>"
 // "<p style=\"text-align:center\"><input onclick='if (document.getElementById(\"login\").value == \"" + admin_login + "\" && document.getElementById(\"password\").value == \"" + admin_password + "\") { window.location.assign(\"http://" + local_ip + "/settings?login=\" + document.getElementById(\"login\").value + \"&password=\" + document.getElementById(\"password\").value); } else { document.getElementById(\"error_text\").innerHTML= \"логин или пароль неверен!\"; }' class=\"button\" name=\"sign\" type=\"button\" value=\"Войти\" />&nbsp;&nbsp;<input name=\"main\" onclick='window.location.assign(\"http://" + local_ip + "/main\");' class=\"button\" type=\"button\" value=\"Главная\" /></p>";
    "<p style=\"text-align:center\"><input onclick=' window.location.assign(\"http://" + local_ip + "/settings?login=\" + document.getElementById(\"login\").value + \"&password=\" + document.getElementById(\"password\").value);' class=\"button\" name=\"sign\" type=\"button\" value=\"Войти\" />&nbsp;&nbsp;<input name=\"main\" onclick='window.location.assign(\"http://" + local_ip + "/main\");' class=\"button\" type=\"button\" value=\"Главная\" /></p>";
  html += "</body>";
  html += "</html>";

  return html;
}
String Settings_page_getHTML(){
  String html = "";
  html += H_start;
  html += "<title>Настройки</title>";
  html += 
    "<style>input.button {display: inline-block;color: #4a4a97;font-weight: 700;text-decoration: none;user-select: none;padding: .5em 2em;outline: none;border: 2px solid;border-radius: 1px;transition: 0.2s;}input.button:hover {background: rgb(145 192 221);}input.button:active {background: black;}</style>"
    "<style>div.box{font-family: cursive, sans-serif;background-color: #2ecc71;color: white;padding: 10px;border-radius: 4px;box-shadow: 2px 2px 20px 23px #7fecad;}</style>"
    "<style>input.get {padding: 10px;border-radius: 10px;}</style>";
  html += "</head>";
  html += "<body>";

  html +=

    "<p style=\"text-align:center\"><span style=\"color:#0000ff\"><span style=\"font-family:Comic Sans MS,cursive\"><span style=\"font-size:38px\"><strong>Панель управления</strong></span></span></span></p><p>&nbsp;</p>"
    "<div class=\"box\"><p style=\"text-align:center\"><strong><span style=\"font-size:20px\">Настройки ESP</span></strong></p>"
    //"<p style=\"text-align:center\"><span style=\"font-size:16px\">Скорость Serial соединения:&nbsp;&nbsp;<select id=\"list_serial_speed\" name=\"list_serial_speed\"><option selected=\"selected\" value=\"9600\">9600</option><option value=\"19200\">19200</option><option value=\"38400\">38400</option><option value=\"57600\">57600</option><option value=\"74880\">74880</option><option value=\"115200\">115200</option><option value=\"230400\">230400</option><option value=\"250000\">250000</option></select>&nbsp;&nbsp;<input class=\"button\" name=\"butt_serial_speed_apply\" type=\"button\" value=\"Применить\" onclick=' window.location.assign(\"http://" + local_ip + "/set_serial_speed?login=" + admin_login + "&password=" + admin_password + "&serial_speed=\" + document.getElementById(\"list_serial_speed\").value);' /></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">Глубокая перезагрузка:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;<input class=\"button\" name=\"butt_reset\" type=\"button\" value=\"Перезагрузить ESP контроллер\" onclick='if(confirm(\"Вы уверены?\"))window.location.assign(\"http://" + local_ip + "/reset?login=" + admin_login + "&password=" + admin_password + "\");' /></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">Лёгкая перезагрузка:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;<input class=\"button\" name=\"butt_reset_\" type=\"button\" value=\"Перезагрузить ESP контроллер\" onclick='if(confirm(\"Вы уверены?\"))window.location.assign(\"http://" + local_ip + "/reset_?login=" + admin_login + "&password=" + admin_password + "\");' /></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">Очистить EEPROM память (полный сброс настроек!):&nbsp;<input class=\"button\" name=\"butt_clear_eeprom\" type=\"button\" value=\"Очистить\" onclick='if(confirm(\"Вы уверены?\"))window.location.assign(\"http://" + local_ip + "/clear_eeprom?login=" + admin_login + "&password=" + admin_password + "\");' /></span></p></div>"
    "<p>&nbsp;</p><p>&nbsp;</p>";

  html +=
    "<div class=\"box\">"
    "<p style=\"text-align:center\"><span style=\"font-size:20px\"><strong>Доступ к панели управления</strong></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">Старый логин:&nbsp; &nbsp; &nbsp; &nbsp;<input class=\"get\" placeholder=\"Старый логин\" maxlength=\"32\" name=\"text_admin_login_old\" id=\"text_admin_login_old\" type=\"text\" /></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">Старый пароль:&nbsp; &nbsp;&nbsp;&nbsp;<input class=\"get\" placeholder=\"Старый пароль\" maxlength=\"32\" name=\"text_admin_pass_old\" id=\"text_admin_pass_old\" type=\"password\" /></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">Навый логин:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;<input class=\"get\" maxlength=\"32\" placeholder=\"Навый логин\" name=\"text_admin_login_new\" id=\"text_admin_login_new\" type=\"text\" /></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">Новый пароль:&nbsp; &nbsp; &nbsp; &nbsp;<input class=\"get\" maxlength=\"32\" placeholder=\"Новый пароль\" name=\"text_admin_pass_1_new\" id=\"text_admin_pass_1_new\" type=\"password\" /></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">Повторите пароль:&nbsp;<input class=\"get\" maxlength=\"32\" placeholder=\"Повторите пароль\" name=\"text_admin_pass_2_new\" id=\"text_admin_pass_2_new\" type=\"password\" /></span></p>"
    "<p style=\"text-align:center\"><span id=\"text_error\" style=\"font-size:16px; color:orangered\"></span></p>" 
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">"
    "<input class=\"button\" name=\"butt_admin_login_pass_set\" type=\"button\" value=\"Применить\" onclick='"
    "if(document.getElementById(\"text_admin_login_old\").value == \"" + admin_login + "\" && document.getElementById(\"text_admin_pass_old\").value == \"" + admin_password + "\"){"
    "if(document.getElementById(\"text_admin_pass_1_new\").value == document.getElementById(\"text_admin_pass_2_new\").value) {"
    "{window.location.assign(\"http://" + local_ip + "/set_admin?login=" + admin_login + "&password=" + admin_password + "&new_login=\" + document.getElementById(\"text_admin_login_new\").value + \"&new_password=\" + document.getElementById(\"text_admin_pass_2_new\").value); }} else {"
    "document.getElementById(\"text_error\").innerHTML = \"Пароли не совпадают!\";}} else { document.getElementById(\"text_error\").innerHTML = \"Логин или пароль неверны!\";}'/>"
    "</span></p></div><p>&nbsp;</p><p>&nbsp;</p>";

  html += 
    "<div class=\"box\">"
    "<p style=\"text-align:center\"><span style=\"font-size:20px\"><strong>Настройки Wi-Fi сети</strong></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:18px\"><strong>Для client</strong></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">SSID:&nbsp; &nbsp; &nbsp;<input placeholder=\"SSID\" value=\"" + ssid + "\" class=\"get\" maxlength=\"32\" name=\"wifi_client_ssid\" id=\"wifi_client_ssid\" type=\"text\" /></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">Пароль:&nbsp;<input class=\"get\" placeholder=\"Пароль\" value=\"" + password + "\" maxlength=\"32\" name=\"wifi_client_password\" id=\"wifi_client_password\" type=\"password\" /></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\"><input class=\"button\" name=\"butt_wifi_client_apply\" type=\"button\" value=\"Применить\" onclick='window.location.assign(\"http://" + local_ip + "/set_wifi_client?login=" + admin_login + "&password=" + admin_password + "&ssid=\" + document.getElementById(\"wifi_client_ssid\").value + \"&password_=\" + document.getElementById(\"wifi_client_password\").value);' /></span></p>"
    "<p style=\"text-align:center\">&nbsp;</p>"
    "<p style=\"text-align:center\"><span style=\"font-size:18px\"><strong>Для server</strong></span></p>"
    //"<p style=\"text-align:center\"><span style=\"font-size:16px\">SSID:&nbsp; &nbsp; &nbsp;<input placeholder=\"SSID\" class=\"get\" maxlength=\"32\" value=\"" + ssid_server + "\" name=\"wifi_server_ssid\" id=\"wifi_server_ssid\" type=\"text\" /></span></p>"
    //"<p style=\"text-align:center\"><span style=\"font-size:16px\">Пароль:&nbsp;<input class=\"get\" placeholder=\"Пароль\" maxlength=\"32\" name=\"wifi_server_password\" value=\"" + password_server + "\" id=\"wifi_server_password\" type=\"password\" /></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\"><input class=\"button\" name=\"butt_wifi_server_apply\" type=\"button\" value=\"Применить\" onclick='window.location.assign(\"http://" + local_ip + "/set_wifi_server?login=" + admin_login + "&password=" + admin_password + "&ssid=\" + document.getElementById(\"wifi_server_ssid\").value + \"&password_=\" + document.getElementById(\"wifi_server_password\").value);' /></span></p>"
    "<p style=\"text-align:center\">&nbsp;</p>"
    "<p style=\"text-align:center\"><span style=\"font-size:18px\"><strong>Другое</strong></span></p>"
    "<p style=\"text-align:center\"><span style=\"font-size:16px\">Количество попыток подключения (client)</span></p>"
    "<p style=\"text-align:center\"><input class=\"get\" placeholder=\"Попыток подключения\" maxlength=\"3\" min=\"10\" max=\"500\" name=\"text_connection_attempts\" id=\"text_connection_attempts\" type=\"number\" value=" + String(connection_attempts) + " /></p>"
    "<p style=\"text-align:center\"><input class=\"button\" name=\"butt_connection_attempts\" type=\"button\" value=\"Применить\"  onclick='window.location.assign(\"http://" + local_ip + "/set_connection_attempts?login=" + admin_login + "&password=" + admin_password + "&connection_attempts=\" + document.getElementById(\"text_connection_attempts\").value);'/></p></div>"
    "<p>&nbsp;</p><p>&nbsp;</p>";

  html += 
"<div class=\"box\">"
"<p style=\"text-align:center\"><strong><span style=\"font-size:20px\">Настройка страниц</span></strong></p>"
"<p style=\"text-align:center\"><span style=\"font-size:16px\">Имя главной страницы</span></p>"
//"<p style=\"text-align:center\"><span style=\"font-size:16px\"><input value=\"" + home_page_html_title_page + "\" id=\"text_home_page_html_title_page\" placeholder=\"Имя страницы\" class=\"get\" maxlength=\"32\" name=\"text_home_page_html_title_page\" type=\"text\" value=\"Mega USB\" /></span>&nbsp;</p>"
"<p style=\"text-align:center\"><input class=\"button\" name=\"butt_home_page_html_title_page_apply\" type=\"button\" value=\"Применить\" onclick='window.location.assign(\"http://" + local_ip + "/set_text_home_page_html_title_page?login=" + admin_login + "&password=" + admin_password + "&text=\" + document.getElementById(\"text_home_page_html_title_page\").value)';/></p>"
"</div><p>&nbsp;</p><p>&nbsp;</p>";

  html += "</body>";
  html += "</html>";

  return html;
}

String NotFound_page_getHTML(){
  String html = "";
  html += H_start;
  html += "<title>Error</title>"
   "<style>input.button {display: inline-block;color: #4a4a97;font-weight: 700;text-decoration: none;user-select: none;padding: .5em 2em;outline: none;border: 2px solid;border-radius: 1px;transition: 0.2s;}input.button:hover {background: rgb(145 192 221);}input.button:active {background: black;}</style>";
  html += "</head>";
  html += "<body>";

  html += 
    "<p style=\"text-align:center\">&nbsp;</p>"
    "<p style=\"text-align:center\"><span style=\"font-size:90px\"><span style=\"font-family:Courier New,Courier,monospace\"><span style=\"color:#ff0000\"><strong>404</strong></span> </span></span><span style=\"font-size:48px\"><span style=\"font-family:Courier New,Courier,monospace\">Страница не существует!</span></span></p>"
    "<p style=\"text-align:center\">&nbsp;</p>"
    "<p style=\"text-align:center\"><span style=\"font-size:48px\"><span style=\"font-family:Courier New,Courier,monospace\"><input class=\"button\" name=\"butt\" onclick='window.location.assign(\"http://" + local_ip + "/home\");'  type=\"button\" value=\"Главная\" /></span></span></p>";
  html += "</body>";
  html += "</html>";

  return html;
}

String Error_page_getHTML(){
  String html = "";
  html += H_start;
  html += "<title>404</title>"
   "<style>input.button {display: inline-block;color: #4a4a97;font-weight: 700;text-decoration: none;user-select: none;padding: .5em 2em;outline: none;border: 2px solid;border-radius: 1px;transition: 0.2s;}input.button:hover {background: rgb(145 192 221);}input.button:active {background: black;}</style>";
  html += "</head>";
  html += "<body>";

  html += 
  
    "<p style=\"text-align:center\">&nbsp;</p>"
    "<p style=\"text-align:center\"><span style=\"font-size:48px\"><span style=\"font-family:Courier New,Courier,monospace\">Что то пошло не так!</span></span></p><p>&nbsp;</p>"
    "<p style=\"text-align:center\">&nbsp;</p>"
    "<p style=\"text-align:center\"><span style=\"font-size:48px\"><span style=\"font-family:Courier New,Courier,monospace\"><input class=\"button\" name=\"butt\" onclick='window.location.assign(\"http://" + local_ip + "/home\");'  type=\"button\" value=\"Главная\" /></span></span></p>";
  html += "</body>";
  html += "</html>";

  return html;
}
