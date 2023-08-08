  if (isalpha(string[i + n]) || string[i+n] != '\0') { 
   
     if (string[i+n] == '('){
break;
 }
      
         resultLength++;
            result = realloc(result, resultLength * sizeof(char));
           
            result[resultLength - 1] = string[i + n];
 


 
           
        }