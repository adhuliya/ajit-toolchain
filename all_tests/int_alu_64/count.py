import re

# Open the file in read mode
text = open("integer_alu_64.s", "r")
  
# Create an empty dictionary
d = dict()
  
# Loop through each line of the file
for line in text:
    # Remove the leading spaces and newline character
    line = line.strip("\n")
    line = re.split(r'[;,\s%]', line)
  
    # Convert the characters in line to 
    # lowercase to avoid case mismatch
    #line = line.lower()
  
    # Split the line into words
    #words = line.split(" ")
  
    # Iterate over each word in line
    for word in line:
        # Check if the word is already in dictionary
        if word in d:
            # Increment count of word by 1
            d[word] = d[word] + 1
        else:
            # Add the word to dictionary with count 1
            d[word] = 1
  
# Print the contents of dictionary
for key in list(d.keys()):
    print(key, ":", d[key])


def compare(first, second):
    sharedKeys = set(first.keys()).intersection(second.keys())
    for key in sharedKeys:
        if first[key] != second[key]:
            print('Key: {}, Value 1: {}, Value 2: {}'.format(key, first[key], second[key]))
