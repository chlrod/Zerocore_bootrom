import re
import sys, getopt

infile  = None
outfile = None
drambase = 0xc0000000
start_pc = 0x00000

argv = sys.argv[1:]
try:
    opts, args = getopt.getopt(argv, "i:o:")  
except:
    print("Error")
for opt, arg in opts:
    if opt in ['-i']:
        infile = arg
    elif opt in ['-o']:
        outfile = arg
 
# print(infile + " " + outfile)

file_input = open(infile, mode='r')
file_output = open(outfile, mode='w')

lines_input = file_input.readlines()
merge_data = []
merge_buffer = []
lines_output = []
reversed_list = []
addr = drambase

file_output.write("memory_initialization_radix=16;\n")
file_output.write("memory_initialization_vector=\n")

for i in range(len(lines_input)):
    line = lines_input[i].strip()
    
    if line.startswith('@'):
        m = re.match('^@([0-9A-Fa-f]{8})$', line)
        addr_8 = int(str(m.group(1)), 16)

        if addr_8 != addr:
            while (addr < addr_8):
                merge_data.append('00')
                addr += 4

            while len(merge_data) >= 32: #输出buffer中还未输出的结果
                merge_line = "".join(reversed(merge_data[:32]))
                lines_output.append(merge_line + ',' + '\n')
                merge_data = merge_data[32:]
         
    else:
        addr += len(line.split())
        merge_data.extend(line.split())

        if len(merge_data) >= 32:
            while len(merge_data) < 32:
                merge_data.append('00')
            merge_line = "".join(reversed(merge_data[:32]))
            lines_output.append(merge_line + ',' + '\n')            
            merge_data = merge_data[32:]




if merge_data:
    while len(merge_data) < 32:
                merge_data.append('00')
    merge_line = "".join(merge_data[::-1])
    lines_output.append(merge_line + ',' + '\n')
    
file_output.writelines(lines_output)
