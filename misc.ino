String UID_as_string(byte* uid_byte_array, byte uid_size){

  String out = "";
  
  for (byte i = 0; i < uid_size; i++) {
    out += (uid_byte_array[i] < 0x10 ? "0" : "");
    out += String(uid_byte_array[i], HEX);
  }

  out.toUpperCase();

 return out;
  
}
