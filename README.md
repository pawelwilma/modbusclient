# modbusclient
This is very light native implementation of the client for MODBUS-TCP protocol. It connects to Modbus slave to read or write modbus registers.
```
Usage: ./modbusclient host_ip port read|write reg_start reg_count [write_val1,write_val2...]

./modbusclient 192.168.1.111 502 read 100 1
./modbusclient 192.168.1.111 502 write 111 3 1,2,3
```
I used this program on my router with OpenWRT 19.07 as a simple gateway between shell/lua scripts and Fatek PLC.
