#!/bin/bash 
net='192.168.119.'   #��ǰ�������������
i=1                  #��ʾ������
count=0
while [ $i -le 254 ]  #������1-254
do
    if [ $count -eq 20 ];then   #ÿ ping 20��ip��sleep 1��
	    count=0
            sleep 1
	fi
	ping -c1 $net$i &  #��̨����
	let i++
	let count++
done
wait
echo '###################################################################'
arp | grep -v 'incomplete' #���˲�����incomplete������
echo '###################################################################'
