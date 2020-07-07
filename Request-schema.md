1. Client SignUP

Request:
{ "event" : "sign_up", "login" : "somelogin", "password": "somepassword", "nickname" : "somenickname"}

Response:
{"status" : "1" } or { "status" : "2" }
================================================================================


2. Client SignIn

Request:
{ "event" : "sign_in", "login" : "somelogin", "password": "somepassword" }

Response:
If loggesIn { "status" : "0", auth_token: "ASDf4vs424g24gasdfas4fwq2e2e2c" }
If worng log/pass { "status" : "1" }
================================================================================


3. Client renew rooms/messages

Request:
{ "event" : "renew", auth_token: "ASDf4vs424g24gasdfas4fwq2e2e2c"}

Response:
{ "status" : "0", 
    "messages" :
        {
            "room" : "325",
            "message" : "hi!",
            "date_send" : "324516235",
            "atacments" : "0"
        },
        {
            "room" : "325",
            "message" : "hi!",
            "date_send" : "324516235",
            "atacments" : "0"
        },
        ...
}
================================================================================

4. Send message

Request:
{ "event" : "send", "room": "3", "message" : "hi them all!", "auth_token: "ASDf4vs424g24gasdfas4fwq2e2e2c" }
