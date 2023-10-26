void ps4_data() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial2.available() > 0 && newData == false) {
        rc = Serial2.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0';
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void split_data() {      
    char * strtokIndx;

    strtokIndx = strtok(tempChars,",");      
    strcpy(button_value, strtokIndx); 
 
    strtokIndx = strtok(NULL, ","); 
    l_value = atoi(strtokIndx);     

    strtokIndx = strtok(NULL, ",");
    r_value = atoi(strtokIndx);
         
    strtokIndx = strtok(NULL, ",");
    l_y_value = atoi(strtokIndx);    

    strtokIndx = strtok(NULL, ",");
    r_x_value = atoi(strtokIndx); 
}