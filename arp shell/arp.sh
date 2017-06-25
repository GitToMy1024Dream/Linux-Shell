#!/bin/bash 
net='192.168.119.'   #当前局域网的网络号
i=1                  #表示主机号
count=0
while [ $i -le 254 ]  #主机号1-254
do
    if [ $count -eq 20 ];then   #每 ping 20个ip，sleep 1秒
	    count=0
            sleep 1
	fi
	ping -c1 $net$i &  #后台运行
	let i++
	let count++
done
wait
echo '###################################################################'
arp | grep -v 'incomplete' #过滤不含有incomplete的内容
echo '###################################################################'
