import wolframalpha
import re


first_line = False;
cout = ''

try:
	with open('power_output.txt', 'r') as reader:
		if(first_line == False):
			first_line = True
			line = reader.readline()	#read  the first line

			temp = re.findall("\d+\s", line)	#get the base
			base = re.sub('\s','',temp[0])		#remove space

			temp = re.findall("\s\d+", line)	#get exponent
			exp = re.sub('\s','',temp[0])		#remove space 

		
		line = reader.readline()				#read the C file text output 
		cout=cout+line
	print("C output:\n"+cout+"\n")

	app_id = 'WJ9WXK-V9XLPLXK89'  #https://products.wolframalpha.com/api/
	client = wolframalpha.Client(app_id)

	res = client.query(base+'^'+exp)	#pass the numbers to Wolfram
	answer = next(res.results).text 
	#print(answer)

	print("Model answer:\n"+answer+"\n") 

	if(cout == answer):	#if C file output matches Wolfram's answer, it's a Pass
		print("PASS")
	else:
		print("FAIL")

except IOError:
	print("ERROR:Input file not found\n")
