import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email.utils import COMMASPACE
from email import encoders
import os

# Sender and recipient email addresses
sender = 'ngoc20122012@zohomail.eu'
recipient = 'm4saintsulpice@gmail.com'

# Email subject and body text
subject = 'Email with attachment'
body = 'This email contains an attachment.'

# File path and name of attachment
attachment_file = 'sendemail.py'
attachment_name = 'sendemail.py'

# SMTP server details
#smtp_server = 'smtp.gmail.com'
#smtp_server = 'smtp.zoho.com'
smtp_server = 'smtp.zoho.eu'
smtp_port = 587
#smtp_username = 'm5saintsulpice@gmail.com'
smtp_username = 'ngoc20122012@zohomail.eu'
#smtp_password = 'vF87GXHGh6ixpub'
smtp_password = 'g0BLW28tPdZj'

# Create a multipart message object
msg = MIMEMultipart()
msg['From'] = sender
msg['To'] = recipient
msg['Subject'] = subject

# Add body text to message
msg.attach(MIMEText(body))

# Add attachment to message
with open(attachment_file, 'rb') as f:
    attachment = MIMEBase('application', 'octet-stream')
    attachment.set_payload(f.read())
    encoders.encode_base64(attachment)
    attachment.add_header('Content-Disposition', f'attachment; filename="{attachment_name}"')
    msg.attach(attachment)

# Send the message using SMTP
smtp = smtplib.SMTP(smtp_server, smtp_port)
smtp.ehlo()
smtp.starttls()
smtp.login(smtp_username, smtp_password)
smtp.sendmail(sender, COMMASPACE.join([recipient]), msg.as_string())
smtp.quit()
