import hmac
import hashlib
import sys

def compute_file_hmac(file_path, key, chunk_size=4096):
    try:
        hmac_obj = hmac.new(key.encode('utf-8'), digestmod=hashlib.sha256)
        with open(file_path, 'rb') as f:
            while True:
                chunk = f.read(chunk_size)
                if not chunk:
                    break
                hmac_obj.update(chunk)
        return hmac_obj.hexdigest()
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
        sys.exit(1)
    except Exception as e:
        print(f"Error reading file '{file_path}': {e}")
        sys.exit(1)

def main():
    print("=== HMAC File Digest & Validator ===")
    file_path = input("Enter the file path: ").strip()
    secret_key = input("Enter the secret key: ").strip()
    expected_digest = input("Enter the expected digest (leave blank to skip validation): ").strip()

    computed_digest = compute_file_hmac(file_path, secret_key)
    print("\nComputed HMAC digest (SHA-256):")
    print(computed_digest)
    
    if expected_digest:
        if hmac.compare_digest(computed_digest, expected_digest):
            print("\nValidation succeeded: The computed digest matches the expected value.")
        else:
            print("\nValidation failed: The computed digest does not match the expected value.")

if __name__ == "__main__":
    main()
