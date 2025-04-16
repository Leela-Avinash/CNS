import secrets
import string

def generate_password(length=16):
    alphabet = string.ascii_letters + string.digits + string.punctuation
    password = ''.join(secrets.choice(alphabet) for _ in range(length))
    return password

def main():
    print("Secure Password Generator using the secrets module")
    try:
        length = int(input("Enter the desired password length (minimum recommended is 12): "))
        if length < 12:
            print("Warning: For a strong password, consider using at least 12 characters.")
    except ValueError:
        print("Invalid input. Using default length of 16 characters.")
        length = 16

    password = generate_password(length)
    print(f"\nYour generated password is:\n{password}")

if __name__ == "__main__":
    main()
