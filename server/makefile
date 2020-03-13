target = im_server
cc = gcc
llibs = -lpthread -lm
objects = main.o bll/tcpserver/tcpserver.o bll/process/process.o model/msgqueue/msgqueue.o model/userlist/userlist.o public/protocol/protocol.o helper/cjson/cjson.o public/foo/common.o 

$(target):$(objects)
	$(cc) -o $(target) $(objects) $(llibs)
main.o:bll/tcpserver/tcpserver.h public/foo/common.h
bll/tcpserver/tcpserver.o:bll/process/process.h model/userlist/userlist.h model/msgqueue/msgqueue.h
bll/process/process.o:public/protocol/protocol.h model/userlist/userlist.h model/msgqueue/msgqueue.h
public/protocol/protocol.o:helper/cjson/cjson.h

clean:
	rm $(target) $(objects) -f