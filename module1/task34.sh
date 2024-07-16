#/bin/bash
touch file1.txt
touch file2.txt
touch file3.txt
tar -cf archive.tar file1.txt
tar -t -f archive.tar 
tar --append --file=archive.tar file2.txt
tar -t -f archive.tar 
tar --append --file=archive.tar file3.txt
tar -t -f archive.tar 
tar --delete --file=archive.tar file2.txt
tar -t -f archive.tar 