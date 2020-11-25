import json

def getParamName(line):
    start = line.find('@') + 1
    end = line.find(':')
    return line[start:end].strip()

def getParamValue(line):
    start = line.find(':') + 1
    end = len(line)
    return line[start:end].strip()

with open("../hive-host/lib/LEDEffect/LEDEffect.h", 'r') as f:
    isInStruct = False
    index = 0
    jsonObject = ""
    _min = ''
    _max = ''
    _effects = ''
    _name = ''
    for line in f:
        line = line.strip()
        if isInStruct:
            if line.startswith("//"):
                paramName = getParamName(line)
                paramValue = getParamValue(line)
                # print(paramName + ": " + paramValue)

                if paramName == 'Name':
                    _name = paramValue
                if paramName == 'Effects': 
                    _effects = paramValue
                if paramName == 'Range':
                    _min = paramValue.split("-")[0].strip()
                    _max = paramValue.split("-")[1].strip()

            elif _name != '':
                if _effects == '':
                    _effects = '[]'

                jsonLine = json.dumps({ str(index): { "name": _name, "min": int(_min), "max": int(_max), "effects": _effects } })
                jsonObject += jsonLine[1:len(jsonLine) - 1] + ",\n"
                index = index + 1
                
                _min = ''
                _max = ''
                _effects = ''
                _name = ''

        if line.find("struct LEDParams") != -1:
            isInStruct = True
        if isInStruct and line.find('}') != -1:
            isInStruct = False
    
    with open("params.json", "w") as file:
        file.write('{\n' + jsonObject[0:len(jsonObject) - 2] + '\n}')
        file.close()

