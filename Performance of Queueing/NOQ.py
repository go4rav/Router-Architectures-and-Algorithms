#Almost completed NOQ, now i need to just solve one problem, in one slot to a destination port only one packet can be sent, i need to just take care of that.

#Also, i made a genius move by creating n threads only once and then just creating placeing the meaty part not in the run() funtion of output port but in another
#function(can be named anything), i named it runn() and so now it was not showing that a thread can be created only once error.


#NOQ as of now i am seeing, it is completed.


#DOUBTS:
#Why 36 threads are created.





import math
import random
from threading import *
from time import sleep
import sys

inputPorts=[]

outputPorts=[]

class InputPort(Thread):
    portNumber=0
    probability=0
    def __init__(self,num):
        Thread.__init__(self)
        self.portNumber = num
    def run(self):
        r=random.randint(0,n-1)
        self.probability = random.random()
        if(self.probability<(1-prob)):
            r=-1
        if(r!=-1):
            z=0
            #print("input port",self.portNumber,"output port",r)

        #print("From input port",self.portNumber,", a packet was switched to output port",r)
        scheduler(self.portNumber,r,slot_num)



class OutputPort(Thread):
    portNumber=0
    def __init__(self,num):
        Thread.__init__(self)
        self.portNumber = num

    def runn(self,num):
        if(num>=0):
            #print("From output port",self.portNumber,"a packet was transmitted from input port",num)
            mean[self.portNumber]+=1
        


def trafficGenerator():
    for i in range(n):
        inputPorts.append(0)
    for i in range(0,n):
        inputPorts[i]= InputPort(i)
    for i in range(n):
        inputPorts[i].start()
        #sleep(0.002)



def scheduler(num1,num2,num3):
    global count
    #print(slot,num3)
    if num3 in slot.keys():
        if(num2!=-1):
            if num2 in schedule.keys():
                schedule[num2].append(num1)
            else:
                schedule[num2]=[]
                schedule[num2].append(num1)   
        count=count+1
        if(count==n):
            for i in range(n):
                if i in schedule.keys():
                    r=random.choice(schedule[i])
                else:
                    r=-1
                outputPorts[i].runn(r)
    else:
        slot[num3]=1


def transmission():
    for i in range(n):
        outputPorts.append(0)
    for i in range(0,n):
        outputPorts[i]= OutputPort(i)
   

n=int(sys.argv[1])


slots=int(sys.argv[8])



f=open(sys.argv[7],"a")




slot_num=1


L= math.floor(float(sys.argv[6])*n)

prob=float(sys.argv[3])  


mean ={}
for i in range(n):
    mean[i]=0
while(slot_num<=slots):
    schedule = {}
    slot = {}
    count=0
    thread1 = Thread(target=trafficGenerator)
    thread3 = Thread(target=transmission) 
    thread3.start()
    scheduler(0,0,slot_num)
    thread1.start()
    sleep(0.01)
    if(slot_num==slots):
        for i in mean.keys():
            mean[i]=mean[i]/slots
        #print(mean)
        avg=0
        for i in mean.keys():
            avg+=mean[i]
        avg=avg/n
        print("AVg. packet delay",1)
        print("Avg. Port Utilisation",avg)
        f.write("AVg. packet delay "+str(1)+"Avg. Port Utilisation "+str(avg))
        f.write('\n')
        f.close()
        #print(slot_num,"slot")
    slot_num+=1



'''
print("Third slot")


thread1 = Thread(target=trafficGenerator,args=(['thread1']))

thread3 = Thread(target=transmission,args=(['thread3']))

thread3.start()

thread1.start()

'''
#thread1.join()

#thread2.join()

#thread3.join()