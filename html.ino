// Head partias
// Style
const String styles = "<style>"
  "body{font-family: Verdana, Geneva, sans-serif; margin: 0px; background: #cccccc;}"
  ".wrapper{margin: 25px auto; width: 95%; max-width: 500px; background: white;  box-shadow: 0 10px 20px rgba(0,0,0,0.19), 0 6px 6px rgba(0,0,0,0.23);}"
  "header{ padding: 15px; color: white; background: DimGrey; box-shadow: 0 10px 20px rgba(0,0,0,0.19), 0 6px 6px rgba(0,0,0,0.23);}"
  "main{padding: 15px;}"
  "nav{padding: 15px;}"
  "form{text-align:center;}"
  "footer{text-align: center; padding: 10px; background: DarkGrey; color: white;}"
  "</style>";


// Body partials
const String header = "<header>"
  "<h1>IoT RFID reader</h1>"
  "</header>";

const String nav = "<nav>"
  "<h2>Menu</h2>"
  "<ul>"
  "<li><a href='/'>Status</a></li>"
  "<li><a href='/reboot_form'>Reboot</a></li>"
  "<li><a href='/update_form'>Firmware update</a></li>"
  "</ul>"
  "</nav>";
  
const String footer= "<footer>"
  "Maxime Moreillon"
  "</footer>";

// Update form
String update_form = "<h2>Firmware update</h2>"
  "<form method='POST' action='/update' enctype='multipart/form-data'>"
  "<input type='file' name='update'>"
  "<input type='submit' value='Update'>"
  "</form>";

String reboot_form = "<h2>Reboot</h2>"
  "<form method='POST' action='/reboot'>"
  "<input type='submit' value='Reboot'>"
  "</form>";
  
// Combinations
String head ="<head>"
  "<title>IoT RFID reader</title>"
  + styles +
  "</head>";

String pre_main = "<html>"
  + head +
  "<body>"
  "<div class='wrapper'>"
  + header +
  "<main>";
  
String post_main = "</main>"
  + nav + footer +
  "</div>"
  "</body>"
  "</html>";

// Root
String transaction_description = TRANSACTION_DESCRIPTION;
String root_main = "<h2>Transaction</h2>"
  "<div>"
  + transaction_description +
  "</div>";
