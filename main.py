import smtplib

HOST = "smtp-mail.outlook.com"
PORT = 587

FROM_EMAIL = "testproject6912@outlook.com"
TO_EMAIL = "isangautam@gmail.com"
PASSWORD = "testpwm1"

MESSAGE = """Subject: Your Password has been reset

Hi, You have been locked on your password manager and your new password is newpassword

-Password Manager"""

smtp = smtplib.SMTP(HOST, PORT)

status_code = smtp.ehlo()[0]
status_code = smtp.starttls()[0]
status_code = smtp.login(FROM_EMAIL, PASSWORD)
smtp.sendmail(FROM_EMAIL, TO_EMAIL, MESSAGE)
smtp.quit()
