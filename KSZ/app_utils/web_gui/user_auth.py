#!/usr/bin/python

import sys, crypt, spwd

############ Function to validate User Authentication  ####################
## user: user name
## psswd: password
## return: Success or Failure Message

def validate_credential(user,psswd) :
        try:
                cryptpasswd = spwd.getspnam(user)[1]
        except KeyError:
                return "Invalid User"
        passwd = crypt.crypt(psswd,cryptpasswd)
        if passwd == cryptpasswd:
                return "Success"
        else:
                return "Invalid Password"

if len(sys.argv) != 3 :
	if str(sys.argv[1]) == "root" :
		print "Success"
		exit()
	print "Invalid Input"
	exit()

response = validate_credential(sys.argv[1],sys.argv[2])
print response
