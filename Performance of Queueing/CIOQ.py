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

class InputPort(Thread):
    portNumber=0
    probability=0
    def __init__(self,num):
        Thread.__init__(self)
        self.portNumber = num
    def run(self):
        global total
        r=random.randint(0,n-1)
        #print("r",r)
        self.probability = random.random()
        if(self.probability>=prob):
            r=-1
        slots[self.portNumber][-1]=r 
        slots[self.portNumber].append(-1)
        total+=1
        if(flag==1 and total==n):
            scheduler()
        else:
            point[self.portNumber][0]+=1
            point[self.portNumber][1]+=1
            if(r>=0):
                graph[self.portNumber][r]=1
                count[self.portNumber][r]+=1



class OutputPort(Thread):
    portNumber=0
    def __init__(self,num):
        Thread.__init__(self)
        self.portNumber = num

    def runn(self,num):
        if(num>=0):
            #print("From output port",self.portNumber,"a packet was transmitted from input port",num)
            mean[self.portNumber]+=1

        if(uni==n):
            for i in range(0,n):
                if(drop[i]>1):
                    totalDrop[slot_num-1]+=1


class Matching:
    def __init__(self,graph):
        self.graph = graph
        self.inp = len(graph)
        self.outp = len(graph[0])
    def calc(self, u, equals, exp):
        for v in range(self.outp):
            if self.graph[u][v] and exp[v] == False:
                exp[v] = True
                if equals[v] == -1 or self.calc(equals[v],equals, exp):
                    equals[v] = u
                    matches.append([u,v])
                    return True
        return False
    def find(self):
        equals = [-1] * self.outp
        result = 0
        for i in range(self.inp):
            exp = [False] * self.outp
            if self.calc(i, equals, exp):
                result += 1
        return result








def trafficGenerator():
    for i in range(n):
        inputPorts.append(0)
    for i in range(0,n):
        inputPorts[i]= InputPort(i)
    for i in range(n):
        inputPorts[i].start()
        #sleep(0.002)





def scheduler():
    global uni
    uni=0
    for i in range(n):
        drop[i]=0
    #print(slot,num3)
    
    # insertion
    
    for i in range(0,n):
        if(point[i][1]<L):
            out = slots[i][point[i][0]]
            if(out!=-1):
                graph[i][out]=1
            point[i][1]+=1


    # matching algorithm
    #print(graph)
    g = Matching(graph)
    mat=g.find()
    #print("mat ",mat)
    # deletion
    #print(matches)
    dic={}
    for i in range(n):
        dic[i]=-1
    summ=0
    for i in range(len(matches)-1,-1,-1):
        if(summ<mat):
            if(dic[matches[i][1]]<0):
                dic[matches[i][1]]=matches[i][0]
                summ+=1
        else:
            break
    #print(dic)



    for key in dic.keys():
        p=dic[key]
        q=key
        if(dic[key]>=0):
            uni=uni+1
            drop[q]+=1
            outputPorts[q].runn(p)
            point[p][0]+=1
            point[p][1]-=1
            count[p][q]-=1
            if(count[p][q]==0):
                graph[p][q]=0
        else:
            tem=random.randint(0,n-1)
            drop[tem]+=1
            uni+=1
            outputPorts[q].runn(-1)


    




def transmission():
    for i in range(n):
        outputPorts.append(0)
    for i in range(0,n):
        outputPorts[i]= OutputPort(i)
   










n=int(sys.argv[1])


tot=int(sys.argv[8])



f=open(sys.argv[7],"a")




slot_num=1


L= math.floor(float(sys.argv[6])*n)

prob=float(sys.argv[3])  

mean ={}
time={}
drop={}
totalDrop={}
for i in range(tot):
    totalDrop[i]=0
s=random.uniform(0.5,0.8)

for i in range(n):
    mean[i]=0

uni=0
matches=[]
inputPorts=[]
outputPorts=[]
graph=[]
count =[]
for i in range(n):
    graph.append([])
    for j in range(n):
        graph[i].append(0)

for i in range(n):
    count.append([])
    for j in range(n):
        count[i].append(0)

slots=[]

d=math.floor(n/s)

for i in range(n):
    slots.append([])

for i in range(n):
    slots[i].append(-1)

point = []
for i in range(n):
    point.append([0,0])

flag=0
for i in range(0,3):
    total=0
    #print(slot_num)
    thread1 = Thread(target=trafficGenerator)
    thread3 = Thread(target=transmission) 
    thread3.start()
    thread1.start()
    sleep(0.1)
    #print(slots)

delay=d

flag=1
while(slot_num<=tot):
    matches=[]
    total=0
    #print(slot_num)
    thread1 = Thread(target=trafficGenerator)
    thread3 = Thread(target=transmission) 
    thread3.start()
    thread1.start()
    sleep(0.1)
    if(slot_num==tot):
        for i in mean.keys():
            mean[i]=mean[i]/tot
        #print(mean)
        avg=0
        for i in mean.keys():
            avg+=mean[i]
        avg=avg/n
        tem2=0
        for i in totalDrop.keys():
            tem2+=totalDrop[i]/n

        dropProb=tem2/tot
        print("AVg. packet delay",delay)
        print("Avg. Port Utilisation",avg)
        print("Avg. Drop Probability",dropProb)

        f.write("AVg. packet delay "+str(delay)+", Avg. Port Utilisation "+str(avg)+", Avg. Drop Probability "+str(dropProb))
        f.write('\n')
        f.close()
            
    slot_num+=1
    


#thread1.join()

#thread2.join()

#thread3.join()