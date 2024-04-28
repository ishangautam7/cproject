import smtplib
import argparse


def main(args:argparse.ArgumentParser.parse_args) -> None:
    HOST = "smtp-mail.outlook.com"
    PORT = 587

    FROM_EMAIL = "testproject6912@outlook.com"
    PASSWORD = "your_password"

    email:str= args.email
    password:str= args.password
    TO_EMAIL = email

    MESSAGE = f"""Subject: Your Password has been reset

    Hi, You have been locked on your password manager and your new password is "{password}"

    -Password Manager"""

    smtp = smtplib.SMTP(HOST, PORT)

    # print(f"Attempting to send email from {FROM_EMAIL} to {TO_EMAIL} with message: {MESSAGE}")

    status_code = smtp.ehlo()[0]
    status_code = smtp.starttls()[0]
    status_code = smtp.login(FROM_EMAIL, PASSWORD)
    smtp.sendmail(FROM_EMAIL, TO_EMAIL, MESSAGE)
    smtp.quit()


# Create the parser
parser = argparse.ArgumentParser(description="Password Manager")

# Add arguments
parser.add_argument("-email", type=str, default="isangautam@gmail.com", help="Email address to send the password to.")
parser.add_argument("-password", type=str, default="testpwm1", help="Password to send to the use")

# Parse the command line arguments
args = parser.parse_args()

main(args)
