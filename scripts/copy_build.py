import os
import shutil

def recursive_copy(src, dest):
    """
    Copy each file from src dir to dest dir, including sub-directories.
    """
    for item in os.listdir(src):
        file_path = os.path.join(src, item)

        # if item is a file, copy it
        if os.path.isfile(file_path):
            shutil.copy(file_path, dest)

        # else if item is a folder, recurse 
        elif os.path.isdir(file_path):
            new_dest = os.path.join(dest, item)
            os.mkdir(new_dest)
            recursive_copy(file_path, new_dest)

recursive_copy("../hive-ui/build", "./test")