import os
import shutil
from pathlib import Path
import palettes
import params

dst = "../hive-host/data"

params.parseAndWriteParams()
palettes.parseAndWritePalettes()

Path(dst + "/json").mkdir(parents=True, exist_ok=True)

shutil.copytree("../hive-ui/build", dst, dirs_exist_ok=True)
shutil.copyfile("./palettes.json", dst + "/json/palettes.json")
shutil.copyfile("./params.json", dst + "/json/params.json")

print(os.listdir(dst))

print("done!")