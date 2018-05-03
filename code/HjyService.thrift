struct hjy_request{  
 1: i32 api,  
 2: i64 logid,  
 3: string req_string,  
}  
struct hjy_respose{  
 1: i16 ret,  
 2: string res_string,  
}  
service HjyService{  
 hjy_respose call(1: hjy_request req),  
} 
