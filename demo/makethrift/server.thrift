 struct message  
 {  
    1:i32 seqId,  
    2:string content  
 }  
      
 service serDemo  
 {  
    void put(1:message msg)  
 }  