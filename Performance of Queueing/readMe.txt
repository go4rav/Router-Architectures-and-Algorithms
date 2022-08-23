Execution:

For CIOQ execution:

python CIOQ.py -N switchportcount -B buffersize -p packetgenprob -q NOQ | CIOQ -K knockout -L inpq -o outputfile -T maxslots  

eg: >python CIOQ.py 8 10 0.7 0 0 0.5 output.txt 5


For NOQ execution:

python NOQ.py -N switchportcount -B buffersize -p packetgenprob -q NOQ | CIOQ -K knockout -L inpq -o outputfile -T maxslots