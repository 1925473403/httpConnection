# httpConnection
Simple lightweight http Client classes

# To Build the binary
source ./build.sh

# To run the binary
./obj.x86_64/replay <input file>
# Input file format eg:
1
https://www.google.com
rhel71
GET
https://www.google.com

First line indicates how many links are to be captured by application as 'n'
Second line indicates dummy link (It could be actual link as well)
Third line indicates local host name
Fourth line indicates Http Method
Fifth line onwards there are n-1 links follow.
