import sys
from Bio import SeqIO
from Bio.Seq import Seq
filename = sys.argv[1] #gets the second argument passed into the command line
fastq_file = sys.argv[2] #gets the third argument passed into the command line
featList = list()
revList = list()
#Parses genbank file into its sequence
for gb_record in SeqIO.parse(open(filename,"r"), "genbank") :
    a = gb_record.seq
#Creates lists for features of the genbank file
for i in range(len(gb_record.features)):
    start = gb_record.features[i].location.nofuzzy_start
    end = gb_record.features[i].location.nofuzzy_end
    featList.append(str(gb_record.seq[start:end]))
    revList.append(str(gb_record.seq[start:end].reverse_complement()))
b = a.reverse_complement()
reg = str(a)
rev = str(b)
#Format for printing output, right side oriented
print('{:>10} {:>10} {:>10} {:>10} {:>10} {:>10}'.format("id","state","start","end","strand","gene"))
#Main loop for going through reads in fastq file
for record in SeqIO.parse(fastq_file, "fastq"):
    count = 1
    id = record.id
    state = "no match"
    start = ""
    end = ""
    strand = ""
    gene = ""
    a = reg.find(str(record.seq))
    b = rev.find(str(record.seq))
    #Check to see if read is found in genbank sequence
    if((a>-1) or (b>-1)):
        state = "match"
        if((reg.count(str(record.seq)) > 1)or (rev.count(str(record.seq)) > 1)):
            state = "ambiguous"
            count = 2 #indicates it's ambiguous
        #Checks if its normal strand that matches only once
        if(a>-1 and count < 2):
            start = a
            end = a + len(record)-1
            strand = "+"
            #Loop for getting normal feature sequences
            for i in range(len(featList)):
                if (str(record.seq) in featList[i]):
                    a = gb_record.features[i] #gets matching gene feature
                    b = str(a.qualifiers.get('gene')) #gets gene name
                    gene = b[2:len(b)-2]
        #Checks if its reverse complement strand that matches only once
        elif(b>-1 and count < 2):
            end = len(rev)-b-1
            start = end - len(record) + 1
            strand = "-"
            df = str(gb_record.seq)[start:end+1]
            #Loop for getting reverse complement feature sequences
            for i in range(len(featList)):
                if (df in featList[i]):
                    a = gb_record.features[i] #gets matching gene feature
                    b = str(a.qualifiers.get('gene')) #gets gene name
                    gene = b[2:len(b)-2]
    print('{:>10} {:>10} {:>10} {:>10} {:>10} {:>10}'.format(id,state,start,end,strand,gene))
