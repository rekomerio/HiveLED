import json

with open("../hive-host/lib/LEDEffect/LEDEffect.h", 'r') as f:
    isInStruct = False
    index = 0
    jsonObject = ""
    for line in f:
        line = line.strip()
        if isInStruct:
            if line.startswith("//"):
                x = line.split(",")

                _name = x[0].replace("//", "").strip()
                _min = x[1].split("-")[0].strip()
                _max = x[1].split("-")[1].strip()
                _effects = x[2].strip() if len(x) == 3 else [] 

                jsonLine = json.dumps({ str(index): { "name": _name, "min": int(_min), "max": int(_max), "effects": _effects } })
                jsonObject += jsonLine[1:len(jsonLine) - 1] + ",\n"
                index = index + 1
        if line.find("struct LEDParams") != -1:
            isInStruct = True
        if isInStruct and line.find('}') != -1:
            isInStruct = False
    
    with open("params.json", "w") as file:
        file.write('{\n' + jsonObject[0:len(jsonObject) - 2] + '\n}')
        file.close()