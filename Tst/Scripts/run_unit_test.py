import os
import stat
import subprocess

def is_executable(file_path):
    """Check if a file is executable."""
    return os.path.isfile(file_path) and os.access(file_path, os.X_OK)

def run_executable(file_path):
    """Run an executable file."""
    try:
        print(f"Running: {file_path}")
        result = subprocess.run([file_path], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print(f"Output: {result.stdout.decode('utf-8')}")
    except subprocess.CalledProcessError as e:
        print(f"Error running {file_path}: {e.stderr.decode('utf-8')}")

def run_executables_in_folder(folder_path):
    """Run all executable files in a folder and its subfolders."""
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            file_path = os.path.join(root, file)
            if is_executable(file_path):
                run_executable(file_path)

if __name__ == "__main__":
    folder_path = "/home/shubham/project/banking-server/build/Tst"
    run_executables_in_folder(folder_path)
