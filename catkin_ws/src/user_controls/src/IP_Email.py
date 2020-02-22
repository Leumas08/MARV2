#!/usr/bin/env python
import smtplib, ssl

import socket

#Used to get host IP and email to swp0001@mix.wvu.edu
if __name__ == '__main__':
    port = 465  # For SSL
    password = "DietCoke"
    smtp_server = "smtp.gmail.com"
    sender_email = "emailformarv2@gmail.com"  # Enter your address
    receiver_email = "swp0001@mix.wvu.edu"  # Enter receiver address
    # Create a secure SSL context
    context = ssl.create_default_context()
    found = 0
    while found == 0:
        try:
            host_name = socket.gethostname()
            host_ip = socket.gethostbyname(host_name)
            with smtplib.SMTP_SSL("smtp.gmail.com", port, context=context) as server:
                server.login("emailformarv2@gmail.com", password)
                server.sendmail(sender_email, receiver_email, host_ip)

            found = 1
        except:
            found = 0
